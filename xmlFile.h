/******************************************************************************
 *
 * Class: XML_File
 *
 * File Name: xmlFile.h
 *
 * Description: Header file for the XML_File Class
 *
 * Author: Hussam Eldin Wael
 *
 *******************************************************************************/

#ifndef XMLFILE_H_
#define XMLFILE_H_
#include <iostream>
#include <vector>
using namespace std;
#include <fstream>
#include "tag.h"
#include "Stack.h"
#include "Tree.h"
#include "json.h"
#include "parse.h"
#include "correction.h"
#include <string>
/*******************************************************************************
 *                            Global Variables                                 *
 *******************************************************************************/
string aligned_str = "";
string minified_str = "";
string json_str = "";
bool prevArrayNotation = false;


/*******************************************************************************
 *                               Definitions                                   *
 *******************************************************************************/

#define TAG_TO_TAG_SPACE   "   "
#define TAG_TO_DATA_SPACE  "   "



/*******************************************************************************
 *                            Class Definition                                 *
 *******************************************************************************/
class XML_File{

	/*******************************************************************************
	 *                                Attributes                                   *
	 *******************************************************************************/
private:
	string file_path;
	Tree file_struct ;

	/*******************************************************************************
	 *                                Methods                                      *
	 *******************************************************************************/

private:

	/*
	 * Description :
	 * Prints the XML File in an aligned way.
	 * It starts with a node and recursively prints its children.
	 * Each Child is spaced by TAG_TO_TAG_SPACE from his parent.
	 * Each Data is spaced by TAG_TO_DATA_SPACE from its node.
	 * Accumulates the resulting string in aligned_str.
	 * Assumes that the XML File is valid.
	 * T(n) = c*T(n-1)+O(n)
	 * Time Complexity = O(n^2)
	 * Space Complexity = O(n)
	 */
	string print_aligned(Node * start , string spaces = "") {


		Node* current = start ;
		string tag , op_tag , close_tag;

		/*Get the tag*/
		//tag = current->getTagName();

		/*Set the opening tag*/
		//op_tag = tag;
		op_tag = current->getOpTag();

		/*Set the closing tag*/
		//close_tag ="</"+op_tag.substr(1);
		close_tag = current->getCloseTag();

		/*Add the opening tag with its spaces*/
		aligned_str+= spaces+op_tag+ '\n' ;
		//cout<<spaces<<op_tag<<endl ;

		/*If the node has data: */
		if(!current->hasChildren()) {

			/*Add the data-tag space then the data then the closing tag*/
			aligned_str+= spaces+TAG_TO_DATA_SPACE+ current->data +'\n' + spaces+close_tag+'\n' ;

			//cout<<spaces<<"    "<<current->data<<endl ;
			//cout<<spaces<<close_tag<<endl ;

			return aligned_str ;
		}

		else {

			/*The node has a child, so add the tag-tag space*/
			string new_spaces = spaces + TAG_TO_TAG_SPACE;

			/*Recursively, print each child*/
			for(int i = 0 ; i < (int)current->children.size() ; i++ ) {

				//				cout<<no<<endl;
				print_aligned(current->getChild(i), new_spaces);
			}

			/*After printing all children, print the closing tag*/
			aligned_str+= spaces+close_tag+'\n' ;
			//cout<<spaces<<close_tag<<endl;
		}



		return aligned_str;

	}



	/*
	 * Description :
	 * Stores the XML File in one line.
	 * It starts with a node and recursively calls its children.
	 * Accumulates the resulting string in minified_str.
	 * Assumes that the XML File is valid.
	 * Time Complexity = O(n^2)
	 * Space Complexity = O(n)
	 */
	void minify_file(Node* start) {

		Node* current = start ;
		string tag , op_tag , close_tag;

		/*Get the tag*/
		//tag = current->getTagName();

		/*Set the opening tag*/
		//op_tag = tag;
		op_tag = current->getOpTag();

		/*Set the closing tag*/
		//close_tag ="</"+op_tag.substr(1);
		close_tag = current->getCloseTag();

		/*Add the opening Tag*/
		minified_str += op_tag;

		/*If the tag has data:*/
		if(!current->hasChildren()) {

			/*Add the data and the closing tag*/
			minified_str+= current->getData()+close_tag;
			return ;

		}

		/*If it doesn't , recursively minify each child node*/

		for(int i = 0 ; i < (int)current->children.size() ; i++) {

			minify_file(current->getChild(i));

		}

		/*Finally, add the close tag*/
		minified_str+= close_tag;

	}



	/*
	 * Description :
	 * Converts the XML File to JSON.
	 * It starts with a node and recursively calls its children.
	 * Accumulates the resulting string in json_str.
	 * Assumes that the XML File is valid.
	 * Time Complexity = O(n^2)
	 * Space Complexity = O(n)
	 */
	void toJSON(Node *start , bool prev_Array_notation = false) {

		Node *current = start ;

		/*Get the tag*/
		string tag = start->getTagName();
		string tag_name = "";

		//string tag_name = current->getTagName();

		/*Extract its name only*/
		for(int i = 1 ; i < (int)tag.size()-1 ; i++) {
			tag_name += tag[i];
		}


		/*If this node is not a part of an array with similar tag names, print its tag name*/
		if(!prev_Array_notation) {
			//cout<<"\""<<tag_name<<"\":";
			json_str+="\""+tag_name+"\":";
		}


		/*If this node has data*/
		if(!current->hasChildren()) {
			/*Get the data*/
			string data = current->getData();

			/*Add double quotations if and only if it is a string*/
			if( !(isNumeric(data) || isBoolean(data) || isNull(data) ) ) {

				data = "\""+data+"\"";
			}

			//cout<<data ;

			/*Add the data to the string*/
			json_str+=data;

			return;

		}


		/*Check for the presence of array of children*/
		bool arrayNotation =(current->children).size()>1;

		string common_tag = current->getChild(0)->getTagName();

		/*if all of the children have the same tag name, an array is detected*/
		for(int i = 1 ; i < (int)(current->children).size() ; i++) {

			if(common_tag !=  current->getChild(i)->getTagName() ) {

				arrayNotation = false ;
				break ;
			}
		}
		int size = current->children.size();

		/*If the children form an array:
		 * 1) Add the open braces {
		 * 2) Add the common tag name and :
		 * 3)Add the open square bracket [ ;
		 */
		if(arrayNotation) {

			//cout<<"{"<<endl;
			json_str+="{\n";

			//cout<<"\""<<common_tag.substr(1,common_tag.size()-2)<<"\":"<<endl;
			json_str+="\""+common_tag.substr(1,common_tag.size()-2)+"\":"+"\n";

			//cout<<"[\n" ;
			json_str+="[\n";

			/*set this variable to true so the children won't print their tag names*/
			prev_Array_notation = true;
		}

		/*If the children do not form an array:
		 * Just add the open braces {.
		 */
		else{
			//cout<<"{" ;
			json_str+="{";
			prev_Array_notation = false;
		}


		/*For every child of the current node: */
		for(int i = 0 ; i < size ; i++) {

			/*Add a comma except for the first one*/
			if(i > 0){
				//	cout<<",";
				json_str+=",";
			}

			/*Recursively convert all children to JSON taking into consideration if they form an array*/
			toJSON(current->getChild(i) , prev_Array_notation);
			//cout<<endl ;

		}

		/*Close the brackets according to the notation*/
		if(arrayNotation) {

			//				cout<<"]\n}\n" ;
			json_str+="]\n}\n";
		}
		else{
			//			cout<<"}\n" ;
			json_str+="}\n";
		}


	}







public:

	/*
	 * Description :
	 * XML File Constructor with a string parameter (path of the file).
	 */
	XML_File(string path) {

		this->file_path = path;
		//file_struct = toTree();

	}


	/*
	 * Description :
	 * Prints the XML file on the Console.
	 */
	void print() {

		ifstream fin;

		fin.open(file_path);
		string line;

		while(fin){
			//fin>>line;

			if(fin.eof()== true)
			{
				fin.close();
				return;
			}

			getline(fin,line);


			cout<<line<<endl;

		}


	}


	/*
	 * Description :
	 * Checks if the XML file is correct (concerning the correctness of tags order).
	 * returns true if the XML file is consistent.
	 * Time Complexity = O(n^2)
	 * Space Complexity = O(n)
	 */

	bool isCorrect() {

		Stack<string> tag_stack ;

		//ifstream fin;

		int line_loc = 0 ;

		/*Open the file*/

		//fin.open(file_path);

		string line , word;
		//int tag_count;
		vector<string> words = getTagsFromFile(file_path);

		//while(fin) {
		for(int i = 0 ; i < (int)words.size() ; i++) {
			line_loc++ ;

			/*Break when reaching the end of the file*/

			//if(fin.eof()== true)
			//	break;

			//getline(fin, line);



			/*Get all tags from each line*/
			//words = getTagsFromLine(line);

			/*For every tag in the line*/

			word = words[i];


			/*If it's a comment, prolog or a self closing one, ignore it*/
			if(isComment(word) || isProlog(word) || isSelfClosingTag(word))
				continue ;

			/*If it's an opening one, push it on the stack*/

			if(isOpeningTag(word)) {
				//cout<<word<<"is an opening tag\n";
				tag_stack.push(word);
			}

			/*If it's an closing one: */
			else if( isClosingTag(word) ) {
				//cout<<word<<"is a closing tag\n";

				/*Check if the stack is not empty or if it doesn't match the top of the stack*/
				if(tag_stack.isEmpty() || !areMatching( tag_stack.top(), word) ){
					cout<<"Error location is on line "<<line_loc<<endl ;
					return false;
				}

				/*If it does, pop a tag from the stack*/
				tag_stack.pop();

			}


		}



		//cout<<"Iam out from isCorrect"<<endl;
		/*Check if the stack is empty*/
		return tag_stack.isEmpty();

	}



	/*
	 * Description :
	 * Converts the XML File into a tree Structure.
	 * Time Complexity = O(n^2)
	 * Space Complexity = O(n)
	 */
	Tree toTree() {

		/*If the file is not correct, return an empty tree*/
		if(!isCorrect()) {
			cout<<"Invalid XML File!!!"<<endl;
			return Tree();
		}


		Stack <Node*> node_stack ;
		vector<Node*> leaves ;

		/*Extract tags and data from the file*/
		vector <string> tags =getTagsFromFile(file_path);
		vector <string> data = extractData(file_path);


		Node *ptr;
		Node *temp;
		Node *root = NULL;
		string tag;

		/*For each tag in the file: */
		for(int i = 0 ; i < (int)tags.size() ; i++) {

			tag = tags[i];

			/*If it is a comment, prolog or a self closing tag, ignore it.*/
			if(isComment(tag) || isProlog(tag) || isSelfClosingTag(tag))
				continue ;

			/*If it's an opening one: */
			else if(isOpeningTag(tag)) {

				/*Create a new node*/
				ptr = new Node();

				/*Set it with the tag name*/
				ptr->setTagName(tag);

				/*push its address on the stack*/
				node_stack.push(ptr);

			}


			/*If it's a closing one: */
			else if(isClosingTag(tag)) {

				/*pop the last node address*/
				temp = node_stack.pop();

				/*if this node has data, add it to the leaves*/
				if( !temp->hasChildren() ) {

					leaves.push_back(temp);

				}

				/*if it was the last node, then it must be the tree root*/
				if(node_stack.isEmpty()) {

					root = temp ;

				}

				/*Otherwise, its the child node of the stack top*/
				else {

					(node_stack.top())->addChild(temp);

				}


			}


		}

		//cout<<"Here I am"<<endl;

		if(leaves.size() != data.size()){
			cout<<"SOME DATA IS MISSING"<<endl ;
			return Tree();
		}

		/*Now assign each leaf with its data*/
		for(int i = 0 ; i < (int)leaves.size() ; i++) {

			leaves[i]->setData(data[i]);


		}


		/*Finally, create a tree and return it*/
		Tree myTree =Tree(root);
		return myTree;
	}


	/*
	 * Description :
	 * public version.
	 * returns a string consisting of the XML File in an aligned way.
	 * Calls the recursive print_aligned method.
	 */
	string printAligned() {

		/*Form a tree of the XML File*/
		//file_struct = toTree();
		file_struct.clear();

		if(isCorrect())
			file_struct = toTree();
		else
			file_struct = correctTree(file_path);
		/*Get the result*/
		string result =  print_aligned(file_struct.root);

		/*Reset the global variable*/
		aligned_str = "";

		return result;

	}


	/*
	 * Description :
	 * public version.
	 * returns a string consisting of the XML File in an one line.
	 * Calls the recursive minify_file method.
	 * Time Complexity = O(n^2)
	 * Space Complexity = O(n)
	 */
	string mini_file() {

		/*Form a tree of the XML File*/
		//file_struct = toTree();

		file_struct.clear();

		if(isCorrect())
			file_struct = toTree();
		else
			file_struct = correctTree(file_path);

		if(file_struct.root == NULL) {
			cout<<"Invalid Operation"<<endl;
			return "ERROR 404";
		}

		/*Minify the file.*/
		minify_file(file_struct.root);

		/*Get the result*/
		string result = minified_str;

		/*Reset the global variable*/
		minified_str = "";

		return result;

	}


	/*
	 * Description :
	 * public version.
	 * returns a string consisting of the JSON format of the XML File.
	 * Calls the recursive toJSON method.
	 * Time Complexity = O(n^2)
	 * Space Complexity = O(n)
	 */
	string toJSON() {

		//cout<<"{";
		/*Add the opening braces for the main object*/
		json_str+="{";

		file_struct.clear();

		if(isCorrect())
			file_struct = toTree();
		else
			file_struct = correctTree(file_path);

		if(file_struct.root == NULL) {
			cout<<"Invalid Operation"<<endl;
			return "ERROR 404";
		}

		/*Convert the file to JSON*/
		toJSON(file_struct.root);
		//cout<<"}"<<endl;

		/*Add the closing braces for the main object*/
		json_str+="}\n";


		/*Get the result*/
		string temp = json_str;

		/*Reset the global variable*/
		json_str = "";
		return temp;
	}


	/*
	 * Description :
	 * returns a string representation of the xml file aligned after correction of errors.
	 * Time Complexity = O(n^2)
	 * Space Complexity = O(n)
	 */
	string correctedFile(){

		file_struct = correctTree(file_path);
		return printAligned();

	}


	/*
	 * Description :
	 * returns a vector of (tag, line) pairs of the misplaced tags.
	 */
	vector<Tag2> TagErrors(){
		return Errors(file_path);
	}

	string Error_String(){

		vector<Tag2> Error_List = Errors(file_path);
		string result = "";
		for(int i = 0 ; i < (int)Error_List.size() ; i++){

			result+= to_string(i+1)+"- Line "+to_string(Error_List[i].line)+" in tag "+Error_List[i].tag + '\n';

		}

		return result;
	}

	/*
	 * Description :
	 * returns an array of the lines that suffer from an error.
	 * Adjusts the passed parameter to hold the size of the result array.
	 *
	 */
	int * ErrorLines(int *noOfLines = nullptr){

		vector<Tag2> error_tags = TagErrors();
		int *lines = new int[error_tags.size()];
		*(noOfLines) = error_tags.size();

		for(int i = 0 ; i < (int)error_tags.size() ; i++){

			lines[i] = error_tags[i].line ;

		}
		return lines;
	}


};







#ifdef WHEN_NEEDED
void toJSON(Node *start) {
	Node *current = start ;

	string tag = start->getTagName();
	string tag_name = "";
	for(int i = 1 ; i < (int)tag.size()-1 ; i++) {
		tag_name += tag[i];
	}


	cout<<"\""<<tag_name<<"\":";


	if(!current->hasChildren()) {
		string data = current->getData();
		if( !(isNumeric(data) || isBoolean(data) || isNull(data) ) ) {

			data = "\""+data+"\"";
		}

		cout<<data ;

		return;

	}


	bool arrayNotation =(current->children).size()>1;

	string common_tag = current->getChild(0)->getTagName();
	for(int i = 1 ; i < (current->children).size() ; i++) {

		if(common_tag !=  current->getChild(i)->getTagName() ) {

			arrayNotation = false ;
			break ;
		}
	}
	int size = current->children.size();
	if(arrayNotation) {

		cout<<"[\n" ;
	}
	else{
		cout<<"{" ;
	}

	for(int i = 0 ; i < size ; i++) {

		if(i > 0)
			cout<<",";
		toJSON(current->getChild(i));
		//cout<<endl ;

	}

	if(arrayNotation) {

		cout<<"]\n" ;
	}
	else{
		cout<<"}\n" ;
	}


}

void toJSON(Node *start , bool prev_Array_notation = false) {
	Node *current = start ;

	string tag = start->getTagName();
	string tag_name = "";
	for(int i = 1 ; i < (int)tag.size()-1 ; i++) {
		tag_name += tag[i];
	}

	if(!prev_Array_notation)
		cout<<"\""<<tag_name<<"\":";


	if(!current->hasChildren()) {
		string data = current->getData();
		if( !(isNumeric(data) || isBoolean(data) || isNull(data) ) ) {

			data = "\""+data+"\"";
		}

		cout<<data ;

		return;

	}


	bool arrayNotation =(current->children).size()>1;

	string common_tag = current->getChild(0)->getTagName();
	for(int i = 1 ; i < (current->children).size() ; i++) {

		if(common_tag !=  current->getChild(i)->getTagName() ) {

			arrayNotation = false ;
			break ;
		}
	}
	int size = current->children.size();
	if(arrayNotation) {

		cout<<"{"<<endl;

		cout<<"\""<<common_tag.substr(1,common_tag.size()-2)<<"\":"<<endl;
		cout<<"[\n" ;
		prev_Array_notation = true;
	}
	else{
		cout<<"{" ;
		prev_Array_notation = false;
	}

	for(int i = 0 ; i < size ; i++) {

		if(i > 0)
			cout<<",";
		toJSON(current->getChild(i) , prev_Array_notation);
		//cout<<endl ;

	}

	if(arrayNotation) {

		cout<<"]\n}\n" ;
	}
	else{
		cout<<"}\n" ;
	}


}




#endif

#endif /* XMLFILE_H_ */
