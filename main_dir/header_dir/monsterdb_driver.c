#include <stdio.h>
#include <string.h>
#include "monsterdb.h"
#include "stacklist.h"

//compile command : gcc monsterdb_driver.c ../monsterdb.c ../stacklist.c ../mesinkata.c ../mesinkar.c

int main()
{
    char *act = (char *) malloc(5);
    int i,j;
    EnemyStat en;
    Stack action;
    LoadEnemy("../data_dir/MonsterDB.txt");
    printf("Masukan enemy id: ");
    scanf("%d",&i);
    if (i >= 0 && i <= 7)
    {
        CreateEmptyStack(&action);
        en = GetEnemy(i,1);
        printf("%s\n", en.Nama);
        if (i != 7)
        {
            for(j = 0; j < 10; j++)
                Push(&action, en.ACTION[j]);
            while(!IsSEmpty(action))
            {
                Pop(&action,&act);
                printf("%s\n", act);
            }
        } else {
            for(j = 0; j < 20; j++)
                Push(&action, en.ACTION[j]);
            while(!IsSEmpty(action))
            {
                Pop(&action,&act);
                printf("%s\n", act);
            }
        }
    }
    else
    {
        printf("Monster ID salah!\n");
    }
    return 0;
}
