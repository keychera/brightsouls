//#include "mesinkata.h"
//#include "point.h"
//#include "matriks.h"
//#include "tree.h"
#include "header_dir/battle.h"
#include "header_dir/brightsoul.h"
#include "header_dir/monsterdb.h"
#include "header_dir/mystring.h"
#include <stdio.h>

int main() {
    // start coding here
	int battle_outcome;
	EnemyStat enemy;
	LoadEnemy("MonsterDB.txt");
	Enemy[1].ID = 1;
	strcpy(Player.Nama,"chera");
	Player.LVL = 1;
	Player.HP = 25;
	Player.STR = 8;
	Player.DEF = 7;
	Player.EXP = 0;
	Player.maxHP = 25;
	Player.maxEXP = 100;
	battle_initiate(Enemy[1].ID, 1,&battle_outcome);
    return 0;
}
