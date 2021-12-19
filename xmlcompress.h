#ifndef XMLCOMPRESS_H
#define XMLCOMPRESS_H

#include"XML_Aux.h"
#include <iostream>
#include <string>
#include <cstring>
#include <stdio.h>


using namespace std;


class xmlCompress
{
private:
    string FullFileWithExt;
    string CompressedFileName;
    string charEnc[256];
    long long leftOver = 0;
    unsigned long long originalFileSize = 0;
    unsigned long long compressedFileSize = 0;
    MinHeapNode* myRoot;


    static string newFileWithXmlExt(string myString)
    {
        string s = myString.replace(myString.find(".xml"),4,"_new.xml");
        return s;
    }

    long long GetFileSize(char *filename) {
        FILE *p_file = fopen(filename, "rb");
        fseek(p_file, 0, SEEK_END);
        long long size = ftello64(p_file);
        fclose(p_file);
        return size;
    }

    unsigned long long Compress(char *filename, ll filesize) {

        FILE *iptr = fopen(filename, "rb");
        FILE *optr = fopen((string( filename)+".huff").c_str(), "wb");

        if (iptr == NULL) {
            perror("Error: File not found: ");
            exit(-1);
        }

        char ch, fch, counter = 7;
        ll size = 0;
        short i = 0;

        while(size != filesize) {
            ch = fgetc(iptr);
            //get the code of the character
            string huffcode = /*HuffmanValue*/charEnc[(unsigned char)ch];
            i = 0;
            while(huffcode[i] != '\0') {

                //Ac
                fch = fch | ((huffcode[i] - '0')<<counter);
                --counter;
                if(counter == -1) {
                    fputc(fch, optr);
                    counter = 7;
                    fch = 0;
                }
                ++i;
            }
            ++size;
        }
        if(fch)
            fputc(fch, optr);

        fclose(iptr);
        fclose(optr);
        printf("Completed\n");
        return counter+1;
    }


void Decompress(const char*filename, const char*destination , ll filesize, ll leftover, struct MinHeapNode* root) {
    FILE *iptr = fopen((string(filename)+".huff").c_str(), "rb");

    FILE *optr = fopen((string(destination)).c_str(), "wb");

    if (iptr == NULL) {
        perror("Error: File not found: ");
        exit(-1);
    }

    char ch, counter = 7, x;
    ll size = 0;
    struct MinHeapNode *traverse = root;
    unsigned char temp = 0;
    ch = fgetc(iptr);
    //printf("Total filesize: %d\n", filesize);
    while(size != filesize) {
        while(counter > -1) {
            traverse = ( ch & (1<<counter) ) ? traverse->right : traverse->left;
                ch ^= (1<<counter);
                --counter;
                if(traverse->left == NULL && traverse->right == NULL) {
                    fputc(traverse->data, optr);
                    if(size == filesize-1 && leftover == counter+1)
                        break;
                    traverse = root;
                }
            }
            ++size;
            counter = 7;
            if(((size*100/filesize)) > ((size-1)*100/filesize))
                printf("\r%d%% completed, size: %d bytes   ", (size*100/filesize), size);
            ch = fgetc(iptr);
        }
        fclose(iptr);
        fclose(optr);
    }




public:

    xmlCompress();
    xmlCompress(string myFullFileName);
    void setFileName(string myFullFileName);
    long long getOrigSize();
    long long getCompSize();
    void CompressFile();
    void deCompressFile();
};

#endif // XMLCOMPRESS_H
