#include "header_dir/queue.h"
#include <stdio.h>
 
int main () {
	Queue Q;
	CreateEmptyQueue(&Q,7);
	printf("number of element of Q right after emptying it : %d\n",NBElmtQueue(Q));
	char *confirm = (IsEmptyQueue(Q))? "yes" : "no";
	printf("is the queue empty : %s\n",confirm);
	char *confirm2 = (IsFullQueue(Q))? "yes" : "no";
	printf("is the queue full : %s\n",confirm2);
	Add(&Q,'M');
	Add(&Q,'I');
	Add(&Q,'M');
	Add(&Q,'I');
	Add(&Q,'K');
	Add(&Q,'Y');
	Add(&Q,'U');
	char *confirm3 = (IsEmptyQueue(Q))? "yes" : "no";
	printf("is the queue empty : %s\n",confirm3);
	char *confirm4 = (IsFullQueue(Q))? "yes" : "no";
	printf("is the queue full : %s\n",confirm4);
	printf("the content of Queue now : \n");
	printQ(&Q);
	
	DeAlokasiQueue(&Q);
	
	return 0;
}
