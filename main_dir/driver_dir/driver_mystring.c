#include <stdio.h>
#include "header_dir/mystring.h"

int main () {
	char inp[10];
	printf("please input string less than 10 char to compare to string \"abc\" : ");
	scanf("%s",inp);
	int i;
	for(i = 0; i < 10;i++){
		printf("%d\n",mystrcmp("abc",inp));
		printf("please input %d more : ",(10-i));
		scanf("%s",inp);
	}
	char copied[10];
	mystrcpy(copied,inp);
	printf("this is copied from last input : %s\n",copied);
	printf("length of what's copied : %d\n",mystrlen(copied));
	printf("testing printing procedure\n");
	myprintstr(copied);
	printf("\n");
	return 0;
}
	
