//#include "mesinkata.h"
//#include "point.h"
//#include "matriks.h"
//#include "tree.h"
#include "header_dir/battle.h"
#include "header_dir/brightsoul.h"
#include <string.h>

int main() {
    // start coding here
	int battle_outcome;
	Enemy[1].ID = 1;
	strcpy(Player.Nama,"chera");
	Player.LVL = 1;
	Player.HP = 10;
	Player.STR = 5;
	Player.DEF = 2;
	Player.EXP = 0;
	Player.maxHP = 10;
	Player.maxEXP = 9999;
	battle_initiate(Enemy[1].ID,&battle_outcome);
    return 0;
}
