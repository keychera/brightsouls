#include "header_dir/spawnenemy.h"
#include <stdio.h>
#include <stdlib.h>
#include "header_dir/matriks.h"
#include "header_dir/boolean.h"
#include <time.h>
void spawn(MATRIKS *m, int e)
{
	srand(time(NULL));
	int i,j,k,r;
	k = 0;
	while (k < e) { //key edit, for making sure the number of enemy reach e - not working somehow
		for (i=GetFirstIdxBrs(*m);i<=GetLastIdxBrs(*m);i++)
		{
			for (j=GetFirstIdxKol(*m);j<GetLastIdxKol(*m);j++)
			{
				r = rand()%25;
				if (r<5 && k < e && Elmt(*m,i,j)=='-') //r jumlah musuh yang di spawn
				{
					Elmt(*m,i,j) = 'E'; // key edit e to E
					//masukin monster ke list(placeholder)
					k++;
				}
			}
		}
	}
	
}
