/******************************************************************************
 *
 * File Name: correction.h
 *
 * Description: Header file for error detection and correction functions
 *
 * Author: Nada Yousef and Nada Amgad
 *
 *******************************************************************************/
#ifndef CORRECTION_H_
#define CORRECTION_H_

#include <iostream>
#include <vector>
#include "Tree.h"

using namespace std;


#define SWAP(X,Y) {int temp = X ; X = Y ; Y = temp;}
/*******************************************************************************
 *                           Type Declarations                                 *
 *******************************************************************************/
typedef struct{

	string name;
	int loc;

}Tag;

struct Tag2 {
	string tag;
	int line;
};

/*
 * Description :
 * Converts a file to a tree after correction and returns a pointer to its root.
 */
Node* correctTree(string file_path);

/*
 *Description :
 *function that takes the file path to detect the errors returning error line and the wrong tag
 */
vector<Tag2> Errors(string file_path);

#endif /* CORRECTION_H_ */
