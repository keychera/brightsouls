#include "reader.h"
#include <stdio.h>

int main () {
	char inp[strlength],outp[strlength];
	char* dummy[5];
	dummy[0] = "chera";
	dummy[1] = "dummy01";
	dummy[2] = "125";
	dummy[3] = NULL;
	reader_checkID("xyz hollow",inp);
	printf("%s\n",inp);
	
	printf("open the file : ");
	scanf("%s",&inp);
	boolean fileopened = reader_openFile(inp);
	if (fileopened) {
		printf("file opened!\n");
		printf("search ID : ");
		scanf("%s",&inp);
		reader_build(inp,dummy,outp);
		if (outp != NULL) 
			printf("%s\n",outp);
		else
			printf("id not found!\n");
		reader_close();
	} else {
		printf("file failed to be opened!\n");
	}
	return 0;
}