/******************************************************************************
 *
 * Class: Tree
 *
 * File Name: Tree.h
 *
 * Description: Header file for the Tree Class
 *
 * Author: Hussam Eldin Wael
 *
 *******************************************************************************/

#ifndef TREE_H_
#define TREE_H_

#include <iostream>
#include <vector>
#include "Tag.h"
using namespace std;


/******************************************************************************
 *                           Types Declarations                               *
 ******************************************************************************/

class Node{

    /******************************************************************************
     *                           Attributes                                       *
     ******************************************************************************/

private:
    string tag_name;
    string op_tag;
    string close_tag;
    string data;



    /******************************************************************************
     *                             Methods                                        *
     ******************************************************************************/
public:
vector<Node*> children;
    /*
     * Description :
     * Node Constructor with string parameter.
     */
    Node(string data = "NONE") {
        this->data = data;
    }


    /*
     * Description :
     * Adds a child node to the children vector of the current node.
     * Time Complexity = O(1)
     * Space Complexity = O(1)
     */
    void addChild(Node *child) {
        children.push_back(child);
    }


    /*
     * Description :
     * Setter for the data attribute.
     * Time Complexity = O(1)
     * Space Complexity = O(1)
     */
    void setData(string data) {
        this->data = data;
    }


    /*
     * Description :
     * Getter for the data attribute.
     */
    string getData() {
        return data;
    }

    /*
     * Description :
     * Returns a child from the children vector at the given index.
     */
    Node* getChild(int index) {

        if(index < (int)children.size())

            return children[index];

        return NULL;
    }


    /*
     * Description :
     * Sets the tag name of the node.
     * Time Complexity = O(n)
     * Space Complexity = O(1)
     */
    void setTagName(string name) {
        this->tag_name = name;

        this->op_tag = name;

        this->close_tag = "</"+tag_name.substr(1);

    }


    /*
     * Description :
     * Returns the tag name of the node.
     */
    string getTagName() {
        return tag_name;
    }


    /*
     * Description :
     * Returns the opening tag of the node.
     */
    string getOpTag() {
        return op_tag;
    }

    /*
     * Description :
     * Returns the closing tag of the node.
     */
    string getCloseTag() {
        return close_tag;
    }

    /*
     * Description :
     * Prints the content of the node and all of its children recursively.
     * Base Condition : When a node has no children.
     * Time Complexity = O(n)
     * Space Complexity = O(1)
     */
    void print(){

        cout<<"Tag : "<<tag_name<<endl ;
        if(data!= "NONE")
            cout<<"Data : "<<data<<endl ;
        if(children.empty())
            return;

        for(int i = 0 ; i < (int)children.size() ; i++) {

            children[i]->print();
        }


    }


    /*
     * Description :
     * returns true if the node has children nodes.
     */
    bool hasChildren() {

        return children.size() > 0 ;

    }

    int ChildrenNo(){
        return this->children.size();
    }
    friend class Tree;
    friend class XML_File;
};



class Tree{
    /******************************************************************************
     *                           Attributes                                       *
     ******************************************************************************/
private:
    Node* root;

    /******************************************************************************
     *                             Methods                                        *
     ******************************************************************************/

    /*
     * Description :
     * Deletes all the nodes within a tree.
     * Time Complexity = O(n)
     * Space Complexity = O(1)
     */
    void clear(Node *n) {

        if(n->hasChildren()) {

            for(int i = 0 ; i < (int)n->children.size() ; i++) {

                clear(n->getChild(i));

            }

        }
        delete n;

    }

public:

    /*
     * Description :
     * Tree empty Constructor.
     */
    Tree(){
        root = new Node();
    }


    /*
     * Description :
     * Tree Constructor with node parameter.
     */
    Tree(Node *d) {
        root = d ;
    }


    /*
     * Description :
     * Adds a child node in the tree according to the given path.
     * If the path doesn't exist, It does nothing.
     * The path is a sequence of numbers indicating the nodes order.
     * Example: {0,1} means the second child of the first child of the root node.
     */
    void addChild(Node *child  , vector<int> path) {

        Node* current = root;

        for(int i = 0 ; i < (int)path.size() ; i++) {

            if( path[i] >= (int)current->children.size() )
                return;

            current = current->children[path[i]];

        }
        current->children.push_back(child);

    }


    /*
     * Description :
     * Prints the tree content starting from its root.
     * Base Condition : When a node has no children.
     */
    void print() {
        root->print();
    }


    /*
     * Description :
     * Deletes all the nodes within the tree.
     */
    void clear(){
        clear(root);
    }


    friend class XML_File;
};


#endif /* TREE_H_ */
