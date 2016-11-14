#include "header_dir/narrate.h"
#include "header_dir/mystring.h"

void narrate_createEmpty(tNarrative *narratives){
	(*narratives).size = 0;
}

void narrate_narrativeAdd(tNarrative *narratives,char* inp){
	if ((*narratives).size != (arraysize - 1)) {
		mystrcpy((*narratives).array[(*narratives).size],inp);
		(*narratives).size++;
	} else {
		printf("the array is full\n");
	}
}

void narrate_narrativeDel(tNarrative *narratives)
{
	if ((*narratives).size != 0) (*narratives).size--;
}
