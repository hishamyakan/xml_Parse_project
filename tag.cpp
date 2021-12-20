
#include "tag.h"
#include <iostream>
#include <fstream>
#include <vector>
#include "Stack.h"
using namespace std;



/*
 * Description :
 * Returns true if the passed string is an xml tag(Starts with < and ends with >).
 */
bool isTag(string word) {
	char openTag = '<';
	char closeTag = '>';
	bool isTag = false;

	if (!word.size()) {  //if the string is of size zero return false//
		isTag = false;
	}
	if (word[0] == openTag && word[word.length() - 1] == closeTag) {
		isTag = true;
	}
	return isTag;

}

/*
 * Description :
 * Returns true if the passed string is a prolog.
 * Ex: <?xml version="1.0" encoding="UTF-8"?>
 */
bool isProlog(string tag) {
	char QM = '?';
	bool isProlog = false;

	if (isTag(tag) && tag[1] == QM && tag[tag.length() - 2] == QM)
		isProlog = true;

	return isProlog;
}

/*
 * Description :
 * Returns true if the passed string is a Comment.
 * Ex: <!-- This is a comment -->
 */
bool isComment(string tag) {
	char Ex = '!';
	char dashes = '-';
	bool isComment = false;


	if (isTag(tag) && tag[1] == Ex && tag[2] == dashes && tag[3] == dashes && tag[tag.length() - 3] == dashes && tag[tag.length() - 2] == dashes) {
		isComment = true;
	}

	return isComment;

}

/*
 * Description :
 * Returns true if the passed string is a self closing tag.
 * Ex: <user /> , <name /> .
 */
bool isSelfClosingTag(string tag) {
	char slash = '/';
	bool isSelfClosingTag = false;

	if (isTag(tag) && tag[tag.length() - 2] == slash)
		isSelfClosingTag = true;

	return isSelfClosingTag;
}

/*
 * Description :
 * Returns true if the passed string is a closing tag.
 * Ex: </user> , </name> .
 */
bool isClosingTag(string word) {
	char slash = '/';
	bool isClosing = false;

	if (isTag(word) && word[1] == slash) {
		isClosing = true;
	}

	return isClosing;

}

/*
 * Description :
 * Returns true if the passed string is an opening tag.
 * Ex: <user> , <name> .
 */
bool isOpeningTag(string word) {
	bool isOpening = false;

	if (isTag(word) && !isClosingTag(word) && !isComment(word) && !isSelfClosingTag(word) && !isProlog(word)) {
		isOpening = true;
	}

	return isOpening;

}

/*
 * Description :
 * Returns true if the opening tag and closing tag match each other.
 * Ex: <user> , </user>  --> true
 * Ex: <name> , <name>  --> false
 * Ex: </name> , <name> --> false
 * Ex: <user> , </name> --> false
 */
bool areMatching(string opening_tag , string closing_tag){

	if (!(isOpeningTag(opening_tag) && isClosingTag(closing_tag)))
		return false;

	return (opening_tag.substr(1) == closing_tag.substr(2)); //returns "true" if the 2 substrings are the same and "false" otherwise//

}


