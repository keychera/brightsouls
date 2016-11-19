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
#include <stdio.h>

int main() {
    // start coding here
    InitGame(&BigMap);
    ImportSkill();
    Skill = ImportTree("data_dir/tree.txt");
    Player.Spoint = 15;
    Game(&BigMap);
    
   			
	
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
