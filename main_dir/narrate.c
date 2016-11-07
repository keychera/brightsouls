#include "header_dir/narrate.h"
#include <string.h>

void narrate_createEmpty(tNarrative *narratives){
	(*narratives).size = 0;
}

void narrate_narrativeAdd(tNarrative *narratives,char* inp){
	if ((*narratives).size != (arraysize - 1)) {
		strcpy((*narratives).array[(*narratives).size],inp);
		(*narratives).size++;
	} else {
		printf("the array is full\n");
	}
}

void narrate_narrativeDel(tNarrative *narratives)
{
	if ((*narratives).size != 0) (*narratives).size--;
}