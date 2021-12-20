#ifndef PARSE_H_
#define PARSE_H_
#include <iostream>
#include <vector>
using namespace std;

/*
 * Description :
 * Accepts a file path and returns its content as a string.
 */
string FileToString(string file_path);

/*
 * Description :
 * Returns a string representation of the file in one line.
 * It adds spaces between tags and each other, and between tags and data as well.
 */
string FileToString2(string file_path);

/*
 * Description :
 * Returns a vector of all tag strings in a line.
 */
vector<string> getTagsFromLine(string line);


/*
 * Description :
 * Returns a vector of all tag strings in a File.
 */
vector <string> getTagsFromFile(string file_path );

/*
 * Description :
 * Returns the location of the specified tag starting from a certain index.
 */
int TagLoc(string file , int start , char tag);

/*
 * Description :
 * Returns a vector of all Data in a File.
 */
vector<string> extractData(string file_path);


/*
 * Description :
 * Removes all left and right spaces in a string.
 */
void strip(string *s);

/*
 * Description :
 * Splits a group of strings separated by spaces and returns a vector of them.
 * It handles multiple spaced words.
 */
vector<string> split(string str);

/*
 * Description :
 * Splits the XML File to words and returns them as a vector of strings.
 */
vector<string> FileToVector(string file_path);



#endif /* PARSE_H_ */
