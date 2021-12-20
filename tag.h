#ifndef TAG_H_
#define TAG_H_

#include <iostream>
#include <vector>
using namespace std ;

/*
 * Description :
 * Returns true if the passed string is an xml tag(Starts with < and ends with >).
 */
bool isTag(string word);

/*
 * Description :
 * Returns true if the passed string is a prolog.
 * Ex: <?xml version="1.0" encoding="UTF-8"?>
 */
bool isProlog(string tag);

/*
 * Description :
 * Returns true if the passed string is a Comment.
 * Ex: <!-- This is a comment -->
 */
bool isComment(string tag);

/*
 * Description :
 * Returns true if the passed string is a self closing tag.
 * Ex: <user /> , <name /> .
 */
bool isSelfClosingTag(string tag);

/*
 * Description :
 * Returns true if the passed string is a closing tag.
 * Ex: </user> , </name> .
 */
bool isClosingTag(string word);

/*
 * Description :
 * Returns true if the passed string is an opening tag.
 * Ex: </user> , </name> .
 */
bool isOpeningTag(string word);

/*
 * Description :
 * Returns true if the opening tag and closing tag match each other.
 * Ex: <user> , </user>  --> true
 * Ex: <name> , <name>  --> false
 * Ex: </name> , <name> --> false
 * Ex: <user> , </name> --> false
 */
bool areMatching(string opening_tag , string closing_tag);



#endif /* TAG_H_ */
