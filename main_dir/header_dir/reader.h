#ifndef reader_H
#define reader_H

#include "boolean.h"

#define strlength 99
#define idlength 5
//file var for reader.c
//static FILE * source;

boolean reader_openFile(char fileName[strlength]);

void reader_checkID(char* sentence,char *outp);

void reader_searchID(char* id,char *outp);

void reader_build(char* id,char** battleStatus,char* outp);

void reader_specialChar(char* special,char** battleStatus,char* outp,int *newLength);

void reader_close();


#endif