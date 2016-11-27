#include "header_dir/narrate.h"
#include "header_dir/mystring.h"
#include <stdio.h>
 
int main () {
	tNarrative test;
	narrate_createEmpty(&test);
	narrate_narrativeAdd(&test,"Tapu Koko did nothing wrong");
	printf("%s\n",test.array[0]);
	narrate_narrativeDel(&test);
	return 0;
}
