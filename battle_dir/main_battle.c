#include "battle.h"

int main () {
	char player_name[nameSize] = "chera";
	int player_lvl, player_hp, player_str, player_def,player_exp;
	player_lvl = 7;
	player_hp = 28;
	player_str = 21;
	player_def = 2;
	player_exp = 13;
	battle_initiate(player_name, &player_lvl, &player_hp, player_str, player_def, &player_exp);
	return 0;
}


//this main driver is obsolete