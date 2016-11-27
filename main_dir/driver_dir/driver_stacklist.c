#include "header_dir/stacklist.h"
#include <stdio.h>
 
int main () {
	addressSt P;
	infotypeSt dummy;
	infotypeSt X = (char *) malloc(31);
	X = "Primarina is a thing of beauty";
	Alokasi(&P,X);
	printf("the info at the address : %s\n",InfoLstr(P));
	Dealokasi(P);
	
	Stack S;
	CreateEmptyStack(&S);
	char *confirm = (IsSEmpty(S))? "yes" : "no";
	printf("is the stack empty : %s\n",confirm);
	Push(&S,"Solgaleo");
	printf("the top of stack is now %s\n",InfoTop(S));
	Push(&S,"Lunala");
	printf("the top of stack is now %s\n",InfoTop(S));
	Pop(&S,&dummy);
	char *confirm2 = (IsSEmpty(S))? "yes" : "no";
	printf("is the stack empty after one Pop : %s\n",confirm2);
	Pop(&S,&dummy);
	char *confirm3 = (IsSEmpty(S))? "yes" : "no";
	printf("is the stack empty after two Pop : %s\n",confirm3);
	return 0;
}
