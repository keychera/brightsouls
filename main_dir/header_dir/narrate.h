#ifndef narrate_H
#define narrate_H

#include "boolean.h"

#define strlength 99
#define idlength 5
//file var for narrate.c
//static FILE * source;

boolean narrate_openFile(char fileName[strlength]);

void narrate_checkID(char* sentence,char *outp);

void narrate_searchID(char* id,char *outp);

void narrate_build(char* id,char** battleStatus,char* outp);

void narrate_specialChar(char* special,char** battleStatus,char* outp,int *newLength);

void narrate_close();


#endif