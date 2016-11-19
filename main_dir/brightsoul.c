//#include "mesinkata.h"
//#include "point.h"
//#include "matriks.h"
//#include "tree.h"

#include "header_dir/brightsoul.h"
//map header
#include "header_dir/map.h"
//skill header
#include "header_dir/skill.h"
/*battle header, moved to map.c there is no calling this module here
#include "header_dir/battle.h" 
#include "header_dir/monsterdb.h"*/
//general purpose
//#include "mystring.h" - moved to brightsoul.h
#include <stdio.h>

int main() {
    // start coding here
    boolean IsNamaValid = false;
	boolean InputValid = true;
	int input, i;
	int message = 0; //key edit for messages
    // start coding here
	//load data?
	do{
		//clearscreen
		clear();
		printf("BrightSoul 0.0.1\n");
		for (i=0;i<=12;i++)
		{printf("*");}
		printf("\n");
		printf("[1] New Game\n");
		printf("[2] Start Game\n");
		printf("[3] Load Game\n");
		printf("[4] Exit Game\n");
		for (i=0;i<=12;i++)
		{printf("*");}
		printf("\n");
		//key edit - message preserve to make it compatible with clear screen
		switch (message) {
			case 0 : break;
			case 1 : printf("Nama masih kosong\n"); break;
			case 2 : printf("input salah \n"); break;
			case 3 : printf("load feature is not added yet :(\n"); break;
			default:
			printf("this shouldn't be printed");
		}
		message = 0;
		//key edit end
		printf("pilih angka : ");
		InputValid = true;
		scanf("%d",&input);//pilih input		
		if (input == 1) //new game
		{			
			//clearscreen
			printf("Input nama : ");
			scanf("%s",	Player.Nama);//input nama
			if (mystrlen(Player.Nama) != 0);
			{
				IsNamaValid = true;
			}
			printf("\n");
		}
		else if (input == 2) //start game
		{
			if(IsNamaValid)//cek nama tidak kosong
			{
				//setting player initial stat
				Player.LVL = 1;
				Player.HP = 25;
				Player.STR = 8;
				Player.DEF = 7;
				Player.EXP = 0;
				Player.maxHP = 25;
				Player.maxEXP = 100;
				//initiate map
				InitGame(&BigMap);
				ImportSkill();
				Skill = ImportTree("data_dir/tree.txt");
				Player.Spoint = 15;
				Game(&BigMap);
			}
			else
			{
				//printf("Nama masih kosong\n"); //key edit formatting
				message = 1;
				InputValid = false;
			}
			
		}			
		
		else if (input == 3) //load game
		{
			//load
			message = 3;
			InputValid = false; //key edit for looping instead of exiting
		}
		else if (input != 4)
		{
			//printf("input salah \n"); key edit
			message = 2;
			InputValid = false;
		}
		
	} while(input==1 || InputValid==false);
	printf("\n");
	
    
    
    
    
   			
	
	/* battle testing, moved to map.c
				;//because case 2 : is being an asshole
				int battle_outcome;
				EnemyStat enemy;
				LoadEnemy("data_dir/MonsterDB.txt");
				Enemy[1].ID = 1;
				mystrcpy(Player.Nama,"chera");
				Player.LVL = 1;
				Player.HP = 25;
				Player.STR = 8;
				Player.DEF = 7;
				Player.EXP = 0;
				Player.maxHP = 25;
				Player.maxEXP = 100;
				battle_initiate(Enemy[1].ID, 1,&battle_outcome);
				switch (battle_outcome) {
					case 1 :printf("You defeated the monster!\n"); break;
					case 2 :printf("You suck at this.\n"); break;
					case 3 :printf("ooo better luck next time kiddo\n"); break;
					default:
						printf("apparently you found a bug!\n  this isn't supposed to be printed.\n");
				}
	*/
    return 0;
}
