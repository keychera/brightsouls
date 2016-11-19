
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "header_dir/battle.h"  //30/10/2016 last edited - inserted commands
#include "header_dir/lilfx.h"
#include "header_dir/monsterdb.h"
#include "header_dir/brightsoul.h"

//global variable
	//PlayerStat Player; declared globally
//player and enemy status
	char enemy_name[nameSize];
	char player_name[nameSize];
	int enemy_hp,enemy_str,enemy_def,enemy_reward;
	int player_lvl,player_hp,player_str,player_def,player_exp,player_maxhp,player_maxexp;
	Stack enemy_actions;
//battle simulation variable
	int battle_round;
	boolean battle_ongoing;
	int game_state; // 1 for input, 3 for battle simulation
	Queue player_action; // change to Queue, size declaration in battle_engage // + 1 because there was an unknown error when changing the last idx value, it somehow affects other variab.. NOPE I know exactly what happened
	Queue current_action; // + 1 because we're not using idx 0 //key edit queue
	int damageDone;
//narrative variable
	tNarrative narratives;
//enemy show & close action array
    Queue display_action; //key edit Queue rep for spec

//directives
void battle_initiate(int monsterID,int monsterLVL,int *battle_outcome) {
/*
battle_outcome value table
	Win					= 1
	Lose 				= 2
	Draw | Round Clear	= 3
*/
//initiate the battle system, which consist of loading enemies, 
//displaying battle interface, and simulate the battle
	int roundMax = isBoss(monsterID)? 20 : 10;
	battle_ongoing = true;
	battle_round = 0;
	battle_playerLoad(Player.Nama,Player.LVL,Player.HP,Player.STR,Player.DEF,Player.EXP,Player.maxHP,Player.maxEXP);
	battle_enemyLoad(monsterID,monsterLVL);
	while (battle_ongoing) {
		battle_engage();
		battle_input();
		battle_simulate();
		battle_ongoing = (battle_round <= roundMax);
		*battle_outcome = battle_conclude();
	}
}

int battle_conclude(){
//battle_conlude return battle_outcome value
	if (player_hp > 0 && enemy_hp > 0) {
		Player.HP = player_hp;
		return 3;
	}
	else if (player_hp > 0 && enemy_hp <= 0)
	{
		Player.HP = player_hp;
		Player.EXP += enemy_reward;
		if (Player.EXP >= Player.maxEXP)
		{
			Player.EXP = Player.maxEXP - Player.EXP;
			battle_lvlup();
		}
		battle_ongoing = false;
		return 1;
	}
	else if (player_hp <= 0 && enemy_hp > 0)
	{
		Player.HP = 0;
		battle_ongoing = false;
		return 2;
	}
}

void battle_lvlup(){
/* Player Level Up Calculation	
	
	HP 	= HP + (PlayerLVL%2 + 2) + (PlayerLVL%5/5)
	STR = STR + (PlayerLVL%2 + 1) + (PlayerLVL%5/5)
	DEF = DEF + (PlayerLVL%2 + 1)
	EXP = EXP + (PlayerLVL*EXP/2)
*/
	Player.LVL++;
	Player.maxHP += (Player.LVL%2 + 2) + (Player.LVL%2/5);
	Player.STR += (Player.LVL%2 + 1) + (Player.LVL%2/5);
	Player.DEF += (Player.LVL%2 + 1);
	Player.maxEXP += (Player.LVL*Player.maxEXP/2);
}

void battle_playerLoad(char name[nameSize],int lvl, int hp, int str, int def,int exp,int maxhp,int maxexp){
//load player stat input to machine's global variable
	mystrcpy(player_name,name);
	player_lvl = lvl;
	player_hp = hp;
	player_str = str;
	player_def = def;
	player_exp = exp;
	player_maxhp = maxhp;
	player_maxexp = maxexp;
}

void battle_enemyLoad(int monsterID,int monsterLVL){
//picking random enemy data from enemy database
//ALT pick enemy based on monster id
	int i,j,k,r[10];
	EnemyStat curEnemy;
	curEnemy = GetEnemy(monsterID, monsterLVL); //Second argument is LVL
	mystrcpy(enemy_name,curEnemy.Nama); 
	enemy_hp = curEnemy.HP;
	enemy_str = curEnemy.STR;
	enemy_def = curEnemy.DEF;
	enemy_reward = curEnemy.EXP;
	CreateEmptyStack(&enemy_actions);
	for (i = 0; i < 10; i++)
	{
		char *s = (char *) malloc(actionNumber + 1); //key fix for issue #4
		j = 0;
		srand(time(NULL));
		r[i] = rand() % 10;
		while (i > j){
			if(r[i] != r[j])
			{
				j++;
			} else 
			{
				j = 0;
				r[i] = rand() % 10;
			}			
		}
		s[0] = ' ';
		for (k = 1;k <= actionNumber;k++)
		{
			s[k] = curEnemy.ACTION[r[i]][k-1];
		}
		Push(&enemy_actions, s);
	}
}

void battle_engage(){
//readying enemy and player current action, setting rounds, <additional : setting narratives>
	char *currentAct = (char *) malloc(actionNumber + 1); //key fix for issue #4
	CreateEmptyQueue(&player_action,actionNumber + 1); //Queue rep for player_action
	CreateEmptyQueue(&current_action,actionNumber + 1); //Queue rep for player_action
	CreateEmptyQueue(&display_action,actionNumber + 1); //Queue rep for player_action
	Pop(&enemy_actions,&currentAct); //key fix for issue #4
	int i;
	for(i = 0;i <= actionNumber + 1;i++){ //key edit
		Add(&current_action,currentAct[i]); //key edit
	}
	for(i = 1;i <= actionNumber+1;i++){ //Queue rep for player_action, 5 times as we accessed like the way array accessed, from the second element
		Add(&player_action,'_'); //Queue rep for player_action
	}
	battle_showAction(current_action);
	battle_round++;
}

void battle_display(int simulatePass){
//displaying battle situation when input and when simulation
//the input exclusive for void battle_simulate()
	int sub_size = 12;
	int name_size = 2*sub_size;
	int display_size = ((name_size + 5*(sub_size)) + 12) ;
	int i,j; //for intense looping right here
	int spaces;
	clear();
	//upperline
		printf(" ");
		for(i = 1;i <= display_size-2;i++) printf("_");
		printf(" \n");
	
	//player stat
		//name
			printf("|");
			printf("%s",player_name); //assumption : name under 20 char
			for(i = 1;i <= name_size - mystrlen(player_name);i++) printf(" ");
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
						spaces += (player_hp < 0)? 1:0;
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
			for(i = 1;i <= name_size - mystrlen(enemy_name);i++) printf(" ");
			printf("|");
		//hp
			printf("|");
			printf("HP  : %d",enemy_hp);
			spaces = 6 + digit(enemy_hp);
			spaces += (enemy_hp < 0)? 1:0;
			for(i = 1;i <= sub_size - spaces;i++) printf(" ");
			printf("|");
		//action
			printf("|");
			for(i = 1;i <= actionNumber;i++) {
				switch (game_state) {
					case 1 :for(i = 1;i <= actionNumber;i++) {
								printf("%c ",display_action.T[display_action.HEAD + i]);
							}
							for(i = 1;i <= (sub_size * 4) - 2;i++) printf(" ");
							break;
					case 3 :for(i = 1;i <= actionNumber;i++) {
								if (i == simulatePass) printf(">");
								if (i > simulatePass)
									printf("%c ",display_action.T[display_action.HEAD + i]);
								else
									printf("%c ",current_action.T[current_action.HEAD + i]);
							}
							for(i = 1;i <= (sub_size * 4) - 3;i++) printf(" ");
							break;
					//default:
				}
			}
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
			printf("|");
			printf("%s attacked!",enemy_name);
			for(i = 1;i <= display_size-2-mystrlen(enemy_name)-10;i++) printf(" ");
			printf("|\n");
		//writeNarrative
			for(j = 1;j <= narratives.size;j++) {
				printf("|");
				printf("%s",narratives.array[j-1]);
				for(i = 1;i <= display_size-2-mystrlen(narratives.array[j-1]);i++) printf(" ");
				printf("|\n");
			}
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
				printf("%c ",player_action.T[player_action.HEAD + i]); //Queue rep for player_action
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
			case 3	:
				printf("    input here >> ");
				break;
			default :
				printf("something wrong with the game state\n");
		}
			
}

void battle_input(){
//input sequence each round
	narrate_createEmpty(&narratives);
	narrate_narrativeAdd(&narratives,"Please input your action");
	char inp;
	game_state = 1;
	//battle_narrate('i',0);
	battle_display(0);
	int i = 1;
	while (i != 6) {
		if (i < 5) {
			scanf(" %c",&inp);
			if (inp == 'E') {
				if (i != 1) {
					player_action.T[player_action.HEAD + i - 1] = '_'; //Queue rep for player_action
					i--;
				}
			} else {
				//assumption : the input is always correct
				player_action.T[player_action.HEAD + i] = inp; //Queue rep for player_action
				i++;
				if (i == 5) {
					narrate_narrativeDel(&narratives);
					narrate_narrativeAdd(&narratives,"Any input but E to confirm actions, E to delete last action");
				}
			}
			battle_display(0);
		} else {
			scanf(" %c",&inp);
			if (inp == 'E') {
				player_action.T[player_action.HEAD + i - 1] = '_'; //Queue rep for player_action
				i--; 
				narrate_narrativeDel(&narratives);
				narrate_narrativeAdd(&narratives,"Please input your action");
			} else {
				i++;
			}
			battle_display(0);
		}
		
	}
	
}

void battle_simulate(){
//simulate and calculate battle outcomes each round
	narrate_createEmpty(&narratives);
	getchar();
	game_state = 3;
	int i,round_outcome;
	for(i = 1;i <= 4;i++) {
		round_outcome = battle_compareAct(player_action.T[player_action.HEAD + i],current_action.T[current_action.HEAD + i]); //Queue rep for player_action
		//battle_calculatePassive();
		battle_calculateImpact(&round_outcome);
		battle_narrate('b',round_outcome);
		battle_display(i);
		while(getchar() != '\n');
	}
}

void battle_calculateImpact(int* outcome){
//calculate battle impact
	damageDone = 0;
	switch (*outcome) {
		//case 2,4,5 doesn't affect both sides, no damage done
		case 1	:
		case 9	:
				if (player_str > enemy_str) {
					damageDone = player_str - enemy_def;
					enemy_hp -= damageDone;
				} else {
					if (player_str < enemy_str) {
						damageDone = enemy_str - player_def;
						player_hp -= damageDone;
					} else {
						*outcome = 10;
					}
				}
			break;
		case 3	:
				damageDone = player_str;
				enemy_hp -= damageDone;
			break;
		case 6	:
				damageDone = enemy_str;
				player_hp -= damageDone;
			break;
		case 7	:
				damageDone = enemy_str;
				player_hp -= damageDone;
			break;
		case 8	:
				damageDone = player_str;
				enemy_hp -= damageDone;
			break;
		default:
		printf("this shouldn't be printed\n");
	}
}

void battle_narrate(char narrateType,int outcome){
//for narration
	if (narrateType == 'b') {
		reader_openFile("data_dir/battle_narration.txt");
		char* battleStatus[5]; 	//passing reference for reader_build 
								//where 0 : player name 1 : enemy name 2 : damageDone
		battleStatus[0] = player_name;
		battleStatus[1] = enemy_name;
		char intToStr[strlength];
		sprintf(intToStr,"%d",damageDone);
		battleStatus[2] = intToStr;
		char code[strlength],sentence[strlength];
		switch(outcome) {
			case 1 : mystrcpy(code,"ava");break;
			case 2 : mystrcpy(code,"avb");break;
			case 3 : mystrcpy(code,"avf");break;
			case 4 : mystrcpy(code,"bva");break;
			case 5 : mystrcpy(code,"bvb");break;
			case 6 : mystrcpy(code,"bvf");break;
			case 7 : mystrcpy(code,"fva");break;
			case 8 : mystrcpy(code,"fvb");break;
			case 9 : mystrcpy(code,"fvf");break;
			case 10: mystrcpy(code,"stl");break;
			default :
			mystrcpy(code,"999");
		}
		reader_build(code,battleStatus,sentence);
		reader_close();
		if (sentence != NULL){
			narrate_narrativeDel(&narratives);
			narrate_narrativeAdd(&narratives,sentence);
			narrate_narrativeAdd(&narratives,"Press enter to continue");
		}
	}
}

int battle_compareAct(char proponent,char opponent){
//return the value to determine what outcome, return 0 if the outcome is undefined 
/* return val mapping
	p	o	outcome						value	affects
	A	A	will dmg if higher str		1		depends
		B	o blocked p					2		noone
		F	p attacked o				3		enemy
	B	A	p blocked o					4		noone
		B	do nothing					5		noone
		F	o flanked p					6		player
	F	A	o attacked p				7		player
		B	p flanked o					8		enemy
		F	will dmg if higher str		9		depends
	
*/
	int out = 0;
	switch (proponent) {
		case 'A' :
			switch (opponent) {
				case 'A' :out = 1; break;
				case 'B' :out = 2; break;
				case 'F' :out = 3; break;
				//default:
			} break;
		case 'B' :
			switch (opponent) {
				case 'A' :out = 4; break;
				case 'B' :out = 5; break;
				case 'F' :out = 6; break;
				//default:
			} break;
		case 'F' :
			switch (opponent) {
				case 'A' :out = 7; break;
				case 'B' :out = 8; break;
				case 'F' :out = 9; break;
				//default:
			} break;
		//default:
	}
	return out;
}

void battle_showAction(Queue currentAct){
//randomized which action is hidden
//NOT IMPLEMENTED
	int i,j,k;
    srand (time(NULL));
    j = (rand()%4)+1; // Plus 1 because starting index at 1
    do{
        k = (rand()%4)+1;
    }while(j == k); // we want to avoid j overlap with k

    for(i = 1; i <= actionNumber; i++)
    {
        display_action.T[display_action.HEAD + i] = currentAct.T[currentAct.HEAD + i];
    }

    display_action.T[display_action.HEAD + j] = '#';
    display_action.T[display_action.HEAD + k] = '#';
}



int isBoss(int id){
//NOT IMPLEMENTED
	return false;
}
