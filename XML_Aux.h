#ifndef XML_AUX_H
#define XML_AUX_H

// C++ program for Huffman Coding
#include <iostream>
#include <cstdlib>
#include <string>
#include <stdio.h>


using namespace std;


// This constant can be avoided by explicitly
// calculating height of Huffman Tree
#define MAX_TREE_HT 300


#define ll unsigned long long


typedef struct MinHeapNode{

    // The input character
    unsigned char data;

    // Frequency of the character
    unsigned freq;

    // Left and right child of this node
    MinHeapNode *left, *right;
}MinHeapNode;



// A Min Heap: Collection of
// min-heap (or Huffman tree) nodes
struct MinHeap {

    // Current size of min heap
    unsigned size;

    // capacity of min heap
    unsigned capacity;

    // Array of minheap node pointers
    struct MinHeapNode** array;
};



// A utility function allocate a new
// min heap node with given character
// and frequency of the character
struct MinHeapNode* newNode(char data, unsigned freq);


// A utility function to create
// a min heap of given capacity
struct MinHeap* createMinHeap(unsigned capacity);


// A utility function to
// swap two min heap nodes
void swapMinHeapNode(struct MinHeapNode** a, MinHeapNode** b);


// The standard minHeapify function.
void minHeapify(MinHeap* minHeap, int idx);


// A utility function to check
// if size of heap is 1 or not
int isSizeOne(struct MinHeap* minHeap);


// A standard function to extract
// minimum value node from heap
struct MinHeapNode* extractMin(struct MinHeap* minHeap);


// A utility function to insert
// a new node to Min Heap
void insertMinHeap(struct MinHeap* minHeap,struct MinHeapNode* minHeapNode);


// A standard function to build min heap
void buildMinHeap(struct MinHeap* minHeap);


// A utility function to print an array of size n
//void printArr(int arr[], int n)
//{
//	int i;
//	for (i = 0; i < n; ++i)
//		cout<< arr[i];
//
//	cout<<"\n";
//}

// Utility function to check if this node is leaf
int isLeaf(struct MinHeapNode* root);


// Creates a min heap of capacity
// equal to size and inserts all character of
// data[] in min heap. Initially size of
// min heap is equal to capacity
MinHeap* createAndBuildMinHeap(unsigned char data[], int freq[], int size);

// The main function that builds Huffman tree
MinHeapNode* buildHuffmanTree(unsigned char data[], int freq[], int size);


// Prints huffman codes from the root of Huffman Tree.
// It uses arr[] to store codes
void printCodes(MinHeapNode* root, int arr[], int top,string myArray[]);




// The main function that builds a
// Huffman Tree and print codes by traversing
// the built Huffman Tree
MinHeapNode* HuffmanCodes(unsigned char data[], int freq[], int size,string myArr[]);



class Huff
{
    int Frq_Arr[256]={0};
    unsigned char Char_Arr[256];
    string myFileText;


public :
    Huff(string file){
        myFileText = file;
    }
    void char_Setup(){
        for(int i=0; i<256;i++){
            Char_Arr[i]=(char)i;

        }
    }
    void Frq_setup(){
        for(char s : myFileText){
            Frq_Arr[(int)s]++;
        }

    }
    void PrintArray()
    {
        for(int i = 0; i<256; i++)
        {
            cout<<"freq of "<<Char_Arr[i]<<" is :"<<Frq_Arr[i]<<endl;
        }
    }
    unsigned char * getChar(){
        return this->Char_Arr;
    }
    int * getFreq(){
        return this->Frq_Arr;
    }
    void FillStream(){
        this->char_Setup();
        this->Frq_setup();
        //HuffmanCodes(this->Char_Arr, this->Frq_Arr, 256);
    }

};




#endif // XML_AUX_H
