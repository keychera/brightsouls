#include <stdio.h>
#include <time.h> //needed because srand uses time as seed
#include <conio.h>
#include <stdlib.h>
#include "battle.h"  //30/10/2016 last edited - inserted commands
#include "lilfx.h"

//global variable
//player and enemy status
	char enemy_name[nameSize];
	char player_name[nameSize];
	int enemy_hp,enemy_str,enemy_def,enemy_reward;
	int player_lvl,player_hp,player_str,player_def;
	Stack enemy_actions;
//battle simulation variable
	int battle_round;
	boolean battle_ongoing;
	int game_state; // 1 for input, 2 for battle simulation
	char player_action[actionNumber + 1]; // + 1 because there was an unknown error when changing the last idx value, it somehow affects other variab.. NOPE I know exactly what happened
	char current_action[actionNumber + 1]; // + 1 because we're not using idx 0
//enemy show & close action array
    char display_action[actionNumber + 1];


//directives
void battle_initiate(char name[nameSize],int *lvl,int *hp,int str,int def,int *exp)
//initiate the battle system, which consist of loading enemies, displaying battle interface, and simulate the battle process
{
	battle_ongoing = true;
	battle_round = 0;
	battle_playerLoad(name,*lvl,*hp,str,def);
	battle_enemyLoad();
	while (battle_ongoing) {
		battle_engage();
		battle_input();
		//battle_simulate();
		printf("works!\n");
		battle_ongoing = false;
	}
}

void battle_playerLoad(char name[nameSize],int lvl, int hp, int str, int def)
//load player stat input to machine's global variable
{
	strcpy(player_name,name);
	player_lvl = lvl;
	player_hp = hp;
	player_str = str;
	player_def = def;
}

void battle_enemyLoad()
//picking random enemy data from enemy database
//ALT pick enemy based on monster id
//NOT IMPLEMENTED
{
	strcpy(enemy_name,"dummy01");
	enemy_hp = 42;
	enemy_str = 12;
	enemy_def = 7;
	enemy_reward = 25;
	CreateEmpty(&enemy_actions);
	Push(&enemy_actions," AABA"); //with a leading space each stack element
	Push(&enemy_actions," AFBA");
	Push(&enemy_actions," ABBA");
	Push(&enemy_actions," FFBA");
	Push(&enemy_actions," AFFF");
	Push(&enemy_actions," ABAF");
}

void battle_engage()
//readying enemy and player current action, setting rounds, <additional : setting narratives>
{
	infotype currentAct;
	Pop(&enemy_actions,&currentAct);
	int i;
	for(i = 1;i <= actionNumber;i++){
		current_action[i] = currentAct[i];
	}
	for(i = 1;i <= actionNumber;i++){
		player_action[i] = '_';
	}
    battle_showAction(current_action); // edited
	battle_round++;
}

void battle_display()
//displaying battle situation when input and when simulation
{
	int sub_size = 10;
	int name_size = 2*sub_size;
	int display_size = ((name_size + 5*(sub_size)) + 12) ;
	int i,j; //for intense looping right here
	int spaces;
	system("cls"); //somehow clrscr() doesn't work here
	//upperline
		printf(" ");
		for(i = 1;i <= display_size-2;i++) printf("_");
		printf(" \n");

	//player stat
		//name
			printf("|");
			printf("%s",player_name); //assumption : name under 20 char
			for(i = 1;i <= name_size - strlen(player_name);i++) printf(" ");
			printf("|");
		//the rest of the stat
			for(j = 1;j <= 5;j++) {
				printf("|");
				spaces = 6;
				switch (j) {
					case 1 :
						printf("LVL : %d",player_lvl);
						spaces += digit(player_lvl);
						break;
					case 2 :
						printf("HP  : %d",player_hp);
						spaces += digit(player_hp);
						break;
					case 3 :
						printf("STR : %d",player_str);
						spaces += digit(player_str);
						break;
					case 4 :
						printf("DEF : %d",player_def);
						spaces += digit(player_def);
						break;
					case 5 :
						printf("Round %d",battle_round);
						spaces += digit(battle_round);
						break;
					default :
						spaces = 0;
				}
				for(i = 1;i <= sub_size - spaces;i++) printf(" ");
				printf("|");
			}
		//newline 'line'
			printf("\n|");
			for(i = 1;i <= name_size;i++) printf("_");
			printf("|");
			for(j = 1;j <= 5;j++) {
				printf("|");
				for(i = 1;i <= sub_size;i++) printf("_");
				printf("|");
			}
			printf("\n");

	//enemy stat
		//name
			printf("|");
			printf("%s",enemy_name); //assumption : name under 20 char
			for(i = 1;i <= name_size - strlen(enemy_name);i++) printf(" ");
			printf("|");
		//hp
			printf("|");
			printf("HP  : %d",enemy_hp);
			spaces = 6 + digit(player_hp);
			for(i = 1;i <= sub_size - spaces;i++) printf(" ");
			printf("|");
		//action
			printf("|");
			for(i = 1;i <= actionNumber;i++) {
                printf("%c ",display_action[i]);
			}
			for(i = 1;i <= (sub_size * 4) - 2;i++) printf(" ");
			printf("|");
		//newline 'line'
			printf("\n|");
			for(i = 1;i <= name_size;i++) printf("_");
			printf("|");
			printf("|");
			for(i = 1;i <= sub_size;i++) printf("_");
			printf("|");
			printf("|");
			for(i = 1;i <= (sub_size * 4) + 6;i++) printf("_");
			printf("|");
			printf("\n");

	//narratives element
		//upper margin
			printf("|");
			for(i = 1;i <= display_size-2;i++) printf(" ");
			printf("|\n");
		//text
			//writeNarrative();
		//lower margin
			printf("|");
			for(i = 1;i <= display_size-2;i++) printf(" ");
			printf("|\n");
		//newline 'line'
			printf("|");
			for(i = 1;i <= display_size-2;i++) printf("_");
			printf("|\n");

	//player's current action
		//interface
			printf("|");
			printf("Inserted Commands"); //assumption : name under 20 char
			for(i = 1;i <= name_size - 17;i++) printf(" ");
			printf("|");
		//action
			printf("|");
			for(i = 1;i <= actionNumber;i++) {
				printf("%c ",player_action[i]);
			}
			for(i = 1;i <= (sub_size * 5);i++) printf(" ");
			printf("|");
		//newline 'line'
			printf("\n|");
			for(i = 1;i <= name_size;i++) printf("_");
			printf("|");
			printf("|");
			for(i = 1;i <= (sub_size * 5) + 8;i++) printf("_");
			printf("|");
			printf("\n");

	//user interface
		switch (game_state) {
			case 1	:
				printf("    input here >> ");
				break;
			default :
				printf("something wrong with the game state\n");
		}

}

void battle_input()
{
	char inp;
	game_state = 1;
	battle_display();
	int i = 1;
	while (i != 5) {
		scanf(" %c",&inp);
		if (inp == 'E') {
			if (i != 1) {
				player_action[i-1] = '_';
			}
			i--;
		} else {
			//assumption : the input is always correct
			player_action[i] = inp;
			i++;
		}
		battle_display();
	}

}

void battle_showAction(char currentAct[])
//randomized which action is hidden
//NOT IMPLEMENTED
{
    int i,j,k;
    srand (time(NULL));
    j = (rand()%4)+1; // Plus 1 because starting index at 1
    do{
        k = (rand()%4)+1;
    }while(j == k); // we want to avoid j overlap with k

    for(i = 1; i <= actionNumber; i++)
    {
        display_action[i] = currentAct[i];
    }

    display_action[j] = '#';
    display_action[k] = '#';
}
