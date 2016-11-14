#ifndef narrate_H
#define narrate_H

#include <stdio.h>
#include "boolean.h"
#include "reader.h"

#define arraysize 10

typedef struct stringArray {
	char array[arraysize][strlength];
	int size;
} tNarrative;

void narrate_createEmpty(tNarrative *narratives);

void narrate_narrativeAdd(tNarrative *narratives,char* inp);

void narrate_narrativeDel(tNarrative *narratives);

#endif