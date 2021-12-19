/******************************************************************************
 *
 * Class: Stack
 *
 * File Name: Stack.h
 *
 * Description: Header file for the Stack Class
 *
 * Author: Hussam Eldin Wael
 *
 *******************************************************************************/


#ifndef STACK_H_
#define STACK_H_
#include <iostream>
using namespace std;

/*******************************************************************************
 *                               Definitions                                   *
 *******************************************************************************/

#define MAX_SIZE 1000
#define ERROR_MESSAGE "STACK IS EMPTY"



/******************************************************************************
 *                           Types Declarations                               *
 ******************************************************************************/
template <typename T>
class Stack{


	/******************************************************************************
	 *                                Attributes                                   *
	 *******************************************************************************/

private:
	T data[MAX_SIZE];
	int pos ;

public:

	/******************************************************************************
	 *                                Methods                                      *
	 *******************************************************************************/


	/*
	 * Description :
	 * Stack empty Constructor.
	 */

	Stack() {

		pos = -1 ;

	}


	/*
	 * Description :
	 * Returns true if the stack is empty.
	 */
	bool isEmpty() {

		return pos == -1;
	}

	/*
	 * Description :
	 * Returns true if the stack is full.
	 */
	bool isFull() {
		return pos == MAX_SIZE-1;

	}


	/*
	 * Description :
	 * Pushes an element on the Stack.
	 * If the Stack is full, It does nothing.
	 */
	void push(T word) {
		if( !isFull() )
			data[++pos] = word;
	}


	/*
	 * Description :
	 * Pops an element from the Stack.
	 * If the Stack is empty, It does nothing.
	 */
	T pop() {
		if(!isEmpty())
			return data[pos--] ;

		return T();

	}


	/*
	 * Description :
	 * Returns the element at the top of the Stack.
	 * If the Stack is empty, It displays an error message.
	 */
	T top(){
		if(pos == -1) {
			cout<<"The Stack is Empty";
			return T() ;
		}

		return data[pos];
	}


	/*
	 * Description :
	 * Prints the elements inside the Stack from top to bottom.
	 */
	void print() {
		for(int i = pos ; i >= 0 ; i--) {

			cout<<data[i]<<endl;
		}
	}

};



#endif /* STACK_H_ */
