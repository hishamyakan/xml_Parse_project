/******************************************************************************
 *
 * File Name: correction.h
 *
 * Description: Source file for error detection and correction functions
 *
 * Author: Nada Yousef and Nada Amgad
 *
 *******************************************************************************/
#include "correction.h"
#include <fstream>
#include <iostream>
using namespace std;
#include <vector>
#include "Tag.h"
#include "Tree.h"
#include "parse.h"
#include "Stack.h"
#include <stack>

#define CLOSING_TAG(OP_TAG) "</"+OP_TAG.substr(1)

static void sort(vector<int> &arr){

    int size = arr.size();
    bool sorted;
    for(int i = 0 ; i <size ; i++){
        sorted = true;
        for(int j = 0 ; j < size-i-1 ; j++){

            if(arr[j] > arr[j+1]){
                sorted = false;
                SWAP(arr[j] , arr[j+1]);
            }

        }
        if(sorted)
            return;
    }
}





/*
 * Description :
 * Removes any closing tags at the beginning, opening tags at the end, or data outside the vector bounds.
 */
static vector<string> removeBounds(vector<string> v){

    int start = 0 , end = v.size()-1 ;

    //Search for the location of the first Opening Tag.
    while(!isOpeningTag(v[start]))
        start++;

    //Search for the location of the last Closing Tag.
    while(!isClosingTag(v[end]))
        end--;

    vector<string> res ;

    //Extract this portion from the original vector.
    for(int i = start ; i <= end ; i++){
        res.push_back(v[i]);
        cout<<"Remove bound "<<v[i]<<endl;
    }
    return res;
}


/*
 * Description :
 * Checks if an element is present in a vector.
 * Returns true if it is present, otherwise it returns false.
 */
static bool in(vector<int> arr , int element){

    for(int i = 0 ; i < arr.size() ; i++){
        if(arr[i] == element)
            return true;
    }
    return false;
}


/*
 * Description :
 * Removes incorrect opening and closing tags in the middle of the file.
 * First, It detects the incorrect tags and their locations.
 * Then it returns a vector of the tags that are correct.
 */
static vector<string> removeExtraTags(vector<string> v){

    Stack<Tag> s;
    vector<int> indices;
    vector<Tag> TAGS;
    Tag temp ;

    /* For every tag in the vector: Create an object of TAG,
     * assign its name and location(index) in the vector*/
    for(int i = 0  ; i <(int)v.size() ; i++){
        temp.name = v[i];
        temp.loc = i ;
        TAGS.push_back(temp);
    }

    /*Starting from here, error detection is performed on each tag as follows:
     * If its is a comment, prolog or self closing tag, it is ignored.
     *  If the tag is an opening tag, it is pushed on the stack.
     *  If it is a closing tag,then we check if it matches the top of the stack.
     *  If they do match, the opening tag is popped from the stack.
     *  If they don't, One of the two tags is misplaced.
     *  Detecting which one is the incorrect tag starts at line ...
     *  When an incorrect tag is detected, its index is pushed in a vector of indices.
     *
     */

    for(int i = 0 ; i <(int)v.size() ; i++){

        string tag = v[i];

        if(isComment(tag) || isProlog(tag) || isSelfClosingTag(tag))
            continue;

        else if(isOpeningTag(tag)){

            s.push(TAGS[i]);

        }

        else if(isClosingTag(tag)){
            //cout<<"The top of the stack now is "<<s.top().name<<endl;
            //cout<<"The closing tag now is "<<tag<<endl;
            if(!areMatching(s.top().name , tag )){

                cout<<"Error detected"<<endl;
                cout<<"Opening Tag: "<<s.top().name<<endl;
                cout<<"Closing Tag: "<<tag<<endl;

                /*When a mismatch occurs, we create a copy of the stack
                 * and check whether there exists an opening tag that
                 * matches the current closing tag.*/

                Stack<Tag> temp = s;

                int count = 0 ;


                while(!temp.isEmpty()){

                    if(areMatching(temp.top().name , tag )){
                        break;
                    }
                    temp.pop();
                    count++;

                }

                //If there's no matching opening tag, that means that the closing tag is wrong.
                if(temp.isEmpty()){
                    //Mafish opening tag lay2a 3aleha
                    //Di makanha ghalat ka closing tag
                    indices.push_back(i);
                }

                //Otherwise, the previously popped opening tags are wrong.
                else{
                    while(count){
                        Tag t = s.pop();

                        //cout<<"Error in "<<t.name<<" and the count is "<<count<<endl;
                        indices.push_back(t.loc);
                        count-- ;
                        cout<<"The top of the stack after error is "<<s.top().name<<endl;
                        s.pop();
                    }
                    //Kol el opening tags ely etshaalet di kanet ghalat
                }


            }
            else
                s.pop();
        }

    }


    cout<<"Error List: "<<endl;
    for(int i = 0 ; i < indices.size() ; i++){
        cout<<v[indices[i]]<<endl;
    }
    cout<<"End of error list"<<endl;


    vector<string> finalists;

    sort(indices);
    int i = 0 ;

    /*The last step is to select the correct tags only from the original vector.*/
    for(int i = 0 ; i < (int)v.size() ; i++){

        /*If the current index is in the list of error indices, ignore this tag*/
       if(in(indices , i) && isClosingTag(v[i]))
            continue;
        finalists.push_back(v[i]);

    }

    return finalists;

}


/*
 * Description :
 * Converts a vector of correct tags and data to a tree and returns a pointer to its root.
 */
static Node* correctTree(vector<string> v){
    /*A stack for pushing nodes*/
    Stack<Node*> myStack;

    Node *root = nullptr;

    /*For every element in the vector: */
    for(int i = 0 ; i <(int)v.size() ; i++){

        if(isProlog(v[i]) || isComment(v[i])||isSelfClosingTag(v[i]))
            continue;
        /*If it is an opening tag: */
        if(isOpeningTag(v[i])){

            cout<<v[i]<<"Is opening tag"<<endl;
            /*Create a new node, assign its tag name with the current tag,
              and push it on the stack.*/
            Node *ptr = new Node();

            ptr->setTagName(v[i]);

            myStack.push(ptr);
        }

        /*If it is a closing tag: */

        else if(isClosingTag(v[i])){

             cout<<v[i]<<"Is closing tag"<<endl;
            /*Pop the last node from the stack*/
            Node *temp = myStack.pop();

            /*If it is the last node, then it is the root of the tree.*/
            if(myStack.isEmpty()){
                cout<<"root = temp";
                root = temp;
            }

            /*Otherwise, then it is the child of node below it.*/
            else{
                myStack.top()->addChild(temp);
            }

        }

        /*If it is not a tag, then assign this data to the node at the top of the stack*/
        else{
            myStack.top()->setData(v[i]);


        }


    }

    cout<<"I am out of tree"<<endl;
    return root;
}


static vector<string> AdjustOpeningTags(vector <string> v){

    Stack<string> myStack;
    Stack<int> locs;
    vector<int> indices;
    vector<string> extra;
    int i ;
    for( i = 0 ; i < (int)v.size() ; i++){

        if(isOpeningTag(v[i])){
            myStack.push(v[i]);
            locs.push(i);
        }

        else if(isClosingTag(v[i])){

                if(!areMatching(myStack.top(), v[i])){


                    int loc = locs.top();
                    if( !isTag(v[loc+1]) ){
                        indices.push_back(loc+2);
                    }
                    else
                        indices.push_back(i);

                    extra.push_back(CLOSING_TAG(myStack.pop()));
                    locs.pop();


                }

                myStack.pop();
                locs.pop();

        }
    }

    while(!myStack.isEmpty()){

        //indices.push_back(i++);

        extra.push_back(CLOSING_TAG(myStack.pop()));

    }

    vector<string> correct;
    int j = 0 ;
    for(int i = 0 ; i < (int)v.size() ; i++){

        if(in(indices, i)){
            correct.push_back(extra[j++]);
        }

        correct.push_back(v[i]);

    }

    while(j<(int)extra.size()){

        correct.push_back(extra[j++]);

    }
    return correct;
}


/*
 * Description :
 * Converts a file to a tree after correction and returns a pointer to its root.
 */
Node* correctTree(string file_path){

   return correctTree(AdjustOpeningTags(removeExtraTags(removeBounds(FileToVector(file_path)))));

}


/*
 *Description :
 *function that takes the file path to detect the errors returning error line and the wrong tag
 */
vector<Tag2> Errors(string file_path) {
    vector<Tag2> errors; //to be returned
    vector<string> tag_str;
    stack<Tag2> st;
    stack<Tag2> copyst;
    bool matchingWithCopy = false;
    int sizeCopy = 0;
    int line_loc = 0;
    string line;
    ifstream t;
    Tag2 temp;
    vector<Tag2> vect;
    vector<Tag2> Copy;
    t.open(file_path, ios::in);

    if (t.is_open()) {

        while (getline(t, line)) {
            line_loc++;
            tag_str = getTagsFromLine(line);
            for (int i = 0; i < tag_str.size(); i++) {   //copy the tags and the line location
                temp.tag = tag_str[i];
                temp.line = line_loc;
                vect.push_back(temp);
            }
        }
        t.close();

    }
    for (int i = 0; i < vect.size(); i++) {
        if (isProlog(vect[i].tag) || isComment(vect[i].tag))
            continue;
        if (isOpeningTag(vect[i].tag)) {
            st.push(vect[i]);
        }
        if (isClosingTag(vect[i].tag)) {
            if (!st.empty()) {
                bool matching = areMatching(st.top().tag, vect[i].tag);
                if (matching) {
                    st.pop();

                }
                else {                                   //mismatching
                    int k;
                    copyst = st; //making a copy of the stack
                    sizeCopy = copyst.size();
                    for (k = 0; k < sizeCopy; k++) { //iteration on the new stack
                        matchingWithCopy = areMatching(copyst.top().tag, vect[i].tag);
                        if (matchingWithCopy)
                        {
                            copyst.pop();
                            break;
                        }

                        copyst.pop();
                    }
                    if (!matchingWithCopy)
                    {


                        temp = vect[i];
                        errors.push_back(temp);
                    }
                    if (matchingWithCopy)
                    {
                        for (int i = 0; i < k; i++) {
                            Copy.push_back(st.top());
                            st.pop();
                        }
                        st.pop();
                        for (int k = 0; k < Copy.size(); k++) {

                            temp = Copy[k];

                            errors.push_back(temp);

                        }

                    }
                }


            }
            Copy.clear();
        }

    }

    if (!st.empty()) {
        int d = st.size();
        for (int n = 1; n <= d; n++) {

            temp = st.top();
            errors.push_back(temp);
            st.pop();
        }
    }
    return errors;
}




