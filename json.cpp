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
 */
bool isNumeric(string data)  {

    for(int i = 0 ; i < (int)data.size() ; i++) {
        if(data[i] >= '0' && data[i] <= '9')
            continue;
        return false;
    }
    return true;
}


/*
 * Description :
 * Checks if a data is boolean (true or false).
 */
bool isBoolean(string data)	{

    return data == "true" || data == "false";

}


/*
 * Description :
 * Checks if a data is equal to "null".
 */
bool isNull(string data){

    return data == "null";

}

