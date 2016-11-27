//#include "mesinkata.h"
//#include "point.h"
//#include "matriks.h"
//#include "tree.h"

#include "header_dir/brightsoul.h"
//map header
#include "header_dir/map.h"
//skill header
#include "header_dir/skill.h"
//monster database header
#include "header_dir/monsterdb.h"
/*battle header, moved to map.c there is no calling this module here
#include "header_dir/battle.h" */
//general purpose
//#include "mystring.h" - moved to brightsoul.h
#include "header_dir/jam.h"
#include <stdio.h>

int main() {
    // start coding here
    boolean IsNamaValid = false;
	boolean InputValid = true;
	int input, i;
	int message = 0; //key edit for messages
    // start coding here
    LoadEnemy("data_dir/MonsterDB.txt");
	//load data?
	do{
		//clearscreen
		clear();
        printf(" __________________________________________________________________________________\n");
        printf("|   / \\                                                                            |\n");
        printf("|   | |   ____________ _____ _____  _   _ _____ _____  _____ _   _ _      _____    |\n");
        printf("|   |.|   | ___ \\ ___ \\_   _|  __ \\| | | |_   _/  ___||  _  | | | | |    /  ___|   |\n");
        printf("|   |.|   | |_/ / |_/ / | | | |  \\/| |_| | | | \\ `--. | | | | | | | |    \\ `--.    |\n");
        printf("|   |:|   | ___ \\    /  | | | | __ |  _  | | |  `--. \\| | | | | | | |     `--. \\   |\n");
        printf("|   |:|   | |_/ / |\\ \\ _| |_| |_\\ \\| | | | | | /\\__/ /\\ \\_/ / |_| | |____/\\__/ /   |\n");
        printf("| `--8--` \\____/\\_| \\_|\\___/ \\____/\\_| |_/ \\_/ \\____/  \\___/ \\___/\\_____/\\____/    |\n");
        printf("|    0                                                                             |\n");
        printf("|    0                                                                             |\n");
        printf("|                                                                                  |\n");
        printf("|                                [1] New Game                                      |\n");
        printf("|                                [2] Start Game                                    |\n");
        printf("|                                [3] Load Game                                     |\n");
        printf("|                                [4] Exit Game                                     |\n");
        printf("|__________________________________________________________________________________|\n");
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
				Player.HP = 15;
				Player.STR = 5;
				Player.DEF = 3;
				Player.EXP = 0;
				Player.maxHP = 15;
				Player.maxEXP = 100;
				//initiate map
				ImportSkill();
				Skill = ImportTree("data_dir/tree.txt");
				Player.Spoint = 0;
				Game(true);
                clear();
                printf("                            "RED"Credit :\n");
                printf("                 "YEL"Kevin Erdiza Yogatama - 13515016\n");
                printf("                "GRN"Kevin Jonathan Koswara - 13515052\n");
                printf("                 "BLU"Afif Bambang Prasetya - 13515058\n");
                printf("                       "CYN"Winarto - 13515061\n");
                printf("                  "MAG"Lazuardi Firdaus - 13515136\n");
                printf(RESET"\n\nPress ENTER to continue\n");
                while (getchar() != '\n');
				InputValid = false;
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
			Game(false);
			clear();
            printf("                            "RED"Credit :\n");
            printf("                 "YEL"Kevin Erdiza Yogatama - 13515016\n");
            printf("                "GRN"Kevin Jonathan Koswara - 13515052\n");
            printf("                 "BLU"Afif Bambang Prasetya - 13515058\n");
            printf("                       "CYN"Winarto - 13515061\n");
            printf("                  "MAG"Lazuardi Firdaus - 13515136\n");
            printf(RESET"\n\nPress ENTER to continue\n");
            while (getchar() != '\n');
			message = 0;
			InputValid = false; //key edit for looping instead of exiting
		}
        else if (input == 99)
        {
            //cheat initialization
            mystrcpy(Player.Nama,"ChuckNorris");
            Player.LVL = 99;
            Player.HP = 999;
            Player.STR = 999;
            Player.DEF = 99;
            Player.EXP = 0;
            Player.maxHP = 999;
            Player.maxEXP = 999;
            Load(false); //not sure with the parameter - key
            ImportSkill();
            Skill = ImportTree("data_dir/tree.txt");
            Player.Spoint = 999;
            Game(true);
            clear();
            printf("                            "RED"Credit :\n");
            printf("                 "YEL"Kevin Erdiza Yogatama - 13515016\n");
            printf("                "GRN"Kevin Jonathan Koswara - 13515052\n");
            printf("                 "BLU"Afif Bambang Prasetya - 13515058\n");
            printf("                       "CYN"Winarto - 13515061\n");
            printf("                  "MAG"Lazuardi Firdaus - 13515136\n");
            printf(RESET"\n\nPress ENTER to continue\n");
            while (getchar() != '\n');
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
