#include "header_dir/spawnenemy.h"
#include "header_dir/map.h"
#include <stdio.h>
#include <stdlib.h>
#include "matriks.h"
#include "boolean.h"
#include <time.h>
void spawn(MATRIKS *m, int e)
{
	srand(time(NULL));
	int i,j,k,r;
	k = 0;
	boolean spawned;
	while (k < e) { //key edit, for making sure the number of enemy reach e - not working somehow
		for (i=GetFirstIdxBrs(*m)+1;i<=GetLastIdxBrs(*m)-1;i++)
		{
			spawned = false;
			for (j=GetFirstIdxKol(*m)+1;j<=GetLastIdxKol(*m)-1;j++)
			{
				r = rand()%100;
				if (r<2 && k < e && Elmt(*m,i,j)=='-' && i!=Absis(PlayerPos) && j!= Ordinat(PlayerPos) && !spawned) //k jumlah musuh yang di spawn
				{
					Elmt(*m,i,j) = 'E'; // key edit e to E
					//masukin monster ke list(placeholder)
					k++;
					spawned = true;
				}
			}
		}
	}
	
}
