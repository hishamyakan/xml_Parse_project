/******************************************************************************
 *
 * File Name: tag.cpp
 *
 * Description: Source file for tag-related functions
 *
 * Author: Hussam Eldin Wael
 *
 *******************************************************************************/
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

    return (word[0] == '<' && word[word.length()-1] == '>');

}


/*
 * Description :
 * Returns true if the passed string is a prolog.
 * Ex: <?xml version="1.0" encoding="UTF-8"?>
 */
bool isProlog(string tag) {

    return isTag(tag) && tag[1] == '?' && tag[tag.size()-2] == '?';

}


/*
 * Description :
 * Returns true if the passed string is a Comment.
 * Ex: <!-- This is a comment -->
 */
bool isComment(string tag) {
    return isTag(tag) && tag[1] == '!';
}
/*
 * Description :
 * Returns true if the passed string is a Comment.
 * Ex: <!-- This is a comment -->
 */
bool isSelfClosingTag(string tag) {
    return isTag(tag) && tag[tag.size()-2] == '//';
}

/*
 * Description :
 * Returns true if the passed string is a closing tag.
 * Ex: </user> , </name> .
 */
bool isClosingTag(string word) {
    return isTag(word) && word[1]== '/';
}

/*
 * Description :
 * Returns true if the passed string is an opening tag.
 * Ex: </user> , </name> .
 */
bool isOpeningTag(string word) {

    return isTag(word)  && !isClosingTag(word);

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

    return isOpeningTag(opening_tag)&& isClosingTag(closing_tag)&&closing_tag.substr(2) == opening_tag.substr(1);
}






#ifdef NEEDED
int endTagLoc(int start , string line) {
    for(int i = start ; i < (int)line.length() ; i++) {

        if(line[i] == '>')
            return i ;

    }
    return -1;
}
#endif


