/******************************************************************************
 *
 * File Name: json.h
 *
 * Description: Header file for JSON function definitions.
 *
 * Author: Hussam Eldin Wael
 *
 *******************************************************************************/

#include <iostream>
#include "json.h"
using namespace std;


/*
 * Description :
 * Checks if a data is numeric.
 * Time Complexity = O(n)
 * Space Complexity = O(1)
 */
bool isNumeric(string data)  {

	for(int i = 0 ; i < data.size() ; i++) {
		if(data[i] >= '0' && data[i] <= '9')
			continue;
		return false;
	}
	return true;
}


/*
 * Description :
 * Checks if a data is boolean (true or false).
 * * Time Complexity = O(1)
 * Space Complexity = O(1)
 */
bool isBoolean(string data)	{

	return data == "true" || data == "false";

}


/*
 * Description :
 * Checks if a data is equal to "null".
 * * Time Complexity = O(1)
 * Space Complexity = O(1)
 */
bool isNull(string data){

	return data == "null";

}

