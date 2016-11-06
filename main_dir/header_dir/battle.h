#ifndef battle_H
#define battle_H

#include "brightsoul.h"
#include <string.h>
#include "boolean.h"
#include "stacklist.h"
#include "queuelist.h"
#include "reader.h"
#include "narrate.h"

#define nameSize 99
#define actionNumber 4

//global variable
	extern PlayerStat Player;
//player and enemy status
	extern char enemy_name[nameSize];
	extern char player_name[nameSize];
	extern int enemy_hp,enemy_str,enemy_def,enemy_reward;
	extern int player_lvl,player_hp,player_str,player_def;
	extern Stack enemy_action;
//battle simulation variable
	extern int battle_round;
	extern boolean battle_ongoing;
	extern int game_state; // 1 for input, 2 for battle simulation
	extern char player_action[actionNumber + 1]; // + 1 because there was an unknown error when changing the last idx value, it somehow affects other variab.. NOPE I know exactly what happened
	extern char current_action[actionNumber + 1]; // + 1 because we're not using idx 0
	extern int damageDone;
//narrative variable
	extern tNarrative narratives;
//enemy show & close action array
    extern char display_action[actionNumber + 1];

//directives
void battle_initiate(int monsterID,int *battle_outcome);
//initiate the battle system, which consist of loading enemies, displaying battle interface, and simulate the battle process
void battle_playerLoad(char name[nameSize],int lvl, int hp, int str, int def,int exp,int player_maxhp,int player_maxexp);
//load player stat input to machine's global variable
void battle_enemyLoad(int monsterID);
//picking random enemy data from enemy database
void battle_engage();
//readying enemy, setting rounds
void battle_display(int simulatePass);
//printing battle to screen, used by battle_input() and battle_simulate()
void battle_input();
//input sequence each round
void battle_simulate();
//calculate and simulate battle outcome each round
//void battle_calculatepassive();
//space for intermediate passives modifier
void battle_calculateImpact(int *outcome);
//calculate battle impact
void battle_narrate(char narrateType,int outcome);
//for narration
int battle_compareAct(char proponent,char opponent);
//return the value to determine what outcome 
void battle_showAction(char currentAct[]);
//randomized which action is hidden
int isBoss(int id);

#endif