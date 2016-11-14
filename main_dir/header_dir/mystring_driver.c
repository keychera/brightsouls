#include <stdio.h>
#include "mystring.h"

int main () {
	char inp[10];
	scanf("%s",inp);
	int i;
	for(i = 0; i < 10;i++){
		printf("%d\n",strcmp("abc",inp));
		scanf("%s",inp);
	}
	return 0;
}
	
