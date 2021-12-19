//This class is responsable of compressing XML File

#include "xmlcompress.h"
#include"XML_Aux.h"
#include <string>
#include "Tag.h"
#include "parse.h"

using namespace std;

xmlCompress::xmlCompress()
{

}
xmlCompress::xmlCompress(string myFullFileName)
{
    this->FullFileWithExt = myFullFileName;
    Huff myHuff(FileToString(myFullFileName));
    myHuff.char_Setup();
    myHuff.Frq_setup();
    unsigned char *arr;
    arr = myHuff.getChar();
    int *freq;
    freq = myHuff.getFreq();

    this->myRoot = HuffmanCodes(arr, freq, 256,charEnc);

}


void xmlCompress::setFileName(string myFullFileName)
{
    this->FullFileWithExt = myFullFileName;
    Huff myHuff(FileToString(myFullFileName));
    myHuff.char_Setup();
    myHuff.Frq_setup();
    unsigned char *arr;
    arr = myHuff.getChar();
    int *freq;
    freq = myHuff.getFreq();

    this->myRoot = HuffmanCodes(arr, freq, 256,charEnc);
}

long long xmlCompress::getOrigSize()
{
    return this->originalFileSize;
}
long long xmlCompress::getCompSize()
{
    return this->compressedFileSize;
}

void xmlCompress::CompressFile()
{

    string m(this->FullFileWithExt);

    char* charArrayFileName = &m[0];

    this->originalFileSize =  xmlCompress::GetFileSize(charArrayFileName);

    this->leftOver = xmlCompress::Compress(charArrayFileName,this->originalFileSize);

    string n(this->FullFileWithExt+".huff");

    char* charArrayFileNameComp = &n[0];


    this->compressedFileSize = xmlCompress::GetFileSize(charArrayFileNameComp);


}

void xmlCompress::deCompressFile()
{


    string s =xmlCompress::newFileWithXmlExt(this->FullFileWithExt);
    string temp(s);
    char* newDes = &temp[0];

    string m(this->FullFileWithExt);

    char* charArrayFileName = &m[0];

    if(this->FullFileWithExt.substr(this->FullFileWithExt.find_last_of(".") + 1) == "huff")
    {
        cout<<"here";
         string s = this->FullFileWithExt.replace(this->FullFileWithExt.find(".huff"),5,"");
         string l(s);
         char* charArrayFileName2 = &l[0];
          Decompress(charArrayFileName2,newDes,this->compressedFileSize, this->leftOver, myRoot);
    }



    Decompress(charArrayFileName,newDes,this->compressedFileSize, this->leftOver, myRoot);

}

