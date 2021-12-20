
#include <iostream>
#include <fstream>
#include "parse.h"
#include "tag.h"
using namespace std;

/*
 * Description :
 * Accepts a file path and returns its content as a string.
 *  Time Complexity = O(n)
 * Space Complexity = O(1)
 */
string FileToString(string file_path) {

	ifstream fin;

	fin.open(file_path);
	string line , total_file;

	while(fin) {

		if(fin.eof()== true)
			break;
		getline(fin,line);

		total_file  = total_file + line+ '\n';

	}

	return total_file;

}


/*
 * Description :
 * Returns a string representation of the file in one line.
 * It adds spaces between tags and each other, and between tags and data as well.
 * Time Complexity = O(n)
 * Space Complexity = O(1)
 */
string FileToString2(string file_path){

	ifstream fin;

	/*Open the file*/
	fin.open(file_path);

	string line , total_file = "" , final_str = "";
	while(fin){

		/*For each line in the file: */
		getline(fin,line);

		/*break when reaching the end of the file*/
		if(fin.eof()== true)
		{
			break;
		}

		/*Accumulate the line in the string "total_file" (all in one line).*/
		total_file+= line+" ";
	}

	/*This loop adds spaces between tags and data to simplify splitting them*/

	for(int i = 0 ; i < (int)total_file.size() ; i++){

		if(total_file[i] == '\n')
			total_file[i] = ' ';

		/*If the current character is an opening tag, add a space before it*/
		if(total_file[i] == '<')
			final_str+=" ";

		/*Add the current character to "final_str"*/
		final_str+= total_file[i];

		/*If the current character is an closing tag, add a space after it*/
		if(total_file[i] == '>')
			final_str+=" ";



	}
	return final_str;
}

/*
 * Description :
 * Returns a vector of all tag strings in a line.
 * Time Complexity = O(n^2)
 * Space Complexity = O(n)
 */
vector<string> getTagsFromLine(string line) {

	string temp = "";

	for(int i = 0 ; i < (int)line.size() ; i++){
		if(line[i] == '<')
			temp+= " ";

		temp+= line[i];

		if(line[i] == '>')
			temp+=" ";

	}
	vector<string> s = split(temp);
	vector<string> res  ;

	for(int i = 0 ; i < (int)s.size() ; i++){

		if(isTag(s[i]))
			res.push_back(s[i]);
	}
	return res;

}

/*
 * Description :
 * Returns a vector of all tag strings in a File.
 * Time Complexity = O(n^2)
 * Space Complexity = O(n)
 */
vector <string> getTagsFromFile(string file_path) {
#ifdef aaa
	/*Opening the file and declaring some variables*/

	ifstream fin;

	fin.open(file_path);
	string line;

	string out ;
	vector <string> total ;

	while(fin) {

		if(fin.eof()== true)
			break;
		getline(fin , line);
		/*Get all tags from each line*/
		vector <string> ptr = getTagsFromLine(line);

		/*Accumulate tags in a string*/
		for(int i = 0 ; i < (int)ptr.size() ; i++) {
			out = out+ptr[i];
		}

		ptr.clear();
	}

	fin.close();
#endif
	/*Get tags from the resulting string*/
	vector<string> total = getTagsFromLine(FileToString2(file_path));
	return total;

}


/*
 * Description :
 * Returns the location of the specified tag starting from a certain index.
 * Time Complexity = O(n)
 * Space Complexity = O(1)
 */
int TagLoc(string file , int start , char tag) {

	for(int i = start ; i < (int)file.size() ; i++) {

		if(file[i] == tag)
			return i ;
	}

	return -1;
}


/*
 * Description :
 * Returns a vector of all Data in a File.
 * Time Complexity = O(n^2)
 * Space Complexity = O(n)
 */
vector<string> extractData(string file_path) {

	/*Opening the file and declaring some variables*/
	string file = FileToString(file_path);
	vector<string> data ;
	bool isData ;
	int start = -1 , end = -1;
	string out ;


	do{
		out = "";
		isData = true;

		/*get the location of the end tag*/
		start = TagLoc(file , start+1 , '>');

		/*get the location of the start tag*/
		end   = TagLoc(file , start , '<');

		/*If one of them is not found, break the loop*/
		if(start == -1 || end == -1)
			break;

		/*Check that there are no tags between them*/
		for(int i = start+1 ; i < end ; i++) {

			if(file[i] == '<' || file[i] == '>') {
				isData = false;
				break;
			}

			out = out + file[i];

		}

		/*If it is a data, push it in a data vector*/
		if(isData) {
			data.push_back(out);
		}

	}while(start < (int)file.size() && end<(int)file.size());

	/*Strip the data from unnecessary spaces and newlines*/

	for(int i = 0 ; i <(int)data.size() ; i++) {

		strip(&data[i]);

	}

	vector <string> temp ;

	/*Remove any empty data*/

	for(int i = 0 ; i <(int)data.size() ; i++) {

		if(data[i] == "")
			continue ;
		temp.push_back(data[i]);

	}

	return temp;
}



/*
 * Description :
 * Removes all left and right spaces in a string.
 * Time Complexity = O(n)
 * Space Complexity = O(1)
 */
void strip(string *s) {

	int i = 0 , j = s->size()-1 ;
	string out = "";
	/* Get the index of the first non-space and non-newline character from the beginning.*/
	while((*s)[i] == ' ' || (*s)[i] == '\n' )
		i++;
	/* Get the index of the first non-space and non-newline character from the end.*/
	while((*s)[j] == ' ' || (*s)[j] == '\n')
		j--;

	/*Extract that sub-string*/
	for(int k = i ; k<= j ; k++) {

		out = out+(*s)[k];

	}

	*s = out;
}



/*
 * Description :
 * Splits a group of strings separated by spaces and returns a vector of them.
 * It handles multiple spaced words.
 * Time Complexity = O(n^2)
 * Space Complexity = O(n)
 */
vector<string> split(string str){
	int  i = 0;

	int startIndex = 0, endIndex = 0;

	vector<string> total_words;

	/*Looping through the characters of the string: */
	while (i <= (int)str.size())
	{
		/*Upon reaching a space or the end of the string: */
		if (str[i] == ' ' || i == (int)str.size())
		{
			endIndex = i;
			string subStr = "";

			/*Cut the string from startIndex to endIndex*/
			subStr.append(str, startIndex, endIndex - startIndex);

			/*Add it to the vector of words*/
			total_words.push_back(subStr);

			/*Advance startIndex*/
			startIndex = endIndex + 1;

		}
		i++;
	}

	vector<string> final_vector;
	/*The purpose of this loop is to remove spaces at the beginning and end of every word*/

	/*For every word" */
	for(int i = 0 ; i < (int)total_words.size() ; i++){

		/*Strip it from left and right spaces*/
		strip(&total_words[i]);

		/*Ignore empty strings*/
		if(total_words[i] == "")
			continue;
		/*Add the words after removing side spaces*/
		final_vector.push_back(total_words[i]);
	}
	return final_vector;
}



/*
 * Description :
 * Splits the XML File to words and returns them as a vector of strings.
 * Time Complexity = O(n^2)
 * Space Complexity = O(n)
 */
vector<string> FileToVector(string file_path){

	/*Get a single-line version of the file*/
	string file = FileToString2(file_path);

	/*Split the single line into a vector of words*/
	vector<string> words = split(file);

	/*The problem at this point is that data of a field is split among multiple words.
	 * We need to accumulate data in a variable and push it once.
	 */
	vector<string> final_vector ;

	string buff = "";

	/*For every word in "words": */

	for(int i = 0 ; i < (int)words.size() ; i++){

		/*If it is a tag, add it immediately*/
		if( isTag(words[i]) ){

			/*If the previous word was one of the data words,
			  and the current one is a tag, this means that the
			  data is ready to be added to "final_vector"*/
			if(buff != ""){
				strip(&buff);
				final_vector.push_back(buff);
				buff = "";
			}

			final_vector.push_back(words[i]);



		}

		/*If the current word is not a tag,then it must be a data word,
		 So, accumulate it in a variable for now*/

		else{
			buff+=words[i]+" ";
		}

	}
	return final_vector;
}


