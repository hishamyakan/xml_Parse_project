/******************************************************************************
 *
 * File Name: json.h
 *
 * Description: Header file for JSON function prototypes.
 *
 * Author: Hussam Eldin Wael
 *
 *******************************************************************************/

#ifndef JSON_H_
#define JSON_H_
#include <iostream>
using namespace std;

/*
 * Description :
 * Checks if a data is numeric.
 */
bool isNumeric(string data) ;

/*
 * Description :
 * Checks if a data is boolean (true or false).
 */
bool isBoolean(string data)	;


/*
 * Description :
 * Checks if a data is equal to "null".
 */
bool isNull(string data);






#endif /* JSON_H_ */
