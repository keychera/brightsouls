//#include "mesinkata.h"
//#include "point.h"
//#include "matriks.h"
//#include "tree.h"

#include "header_dir/brightsoul.h"
//skill header
#include "header_dir/skill.h"
//battle header 
#include "header_dir/battle.h"
#include "header_dir/monsterdb.h"
//general purpose
#include "header_dir/mystring.h"
#include <stdio.h>

int main() {
    // start coding here
    int inp;
    printf("testing feature\n");
    printf("1 : Skill \n2 : Battle \n99 : stop testing\n   >>");
    scanf("%d",&inp);
    while (inp != 99) {
		switch (inp) {
			case 1 :
				ImportSkill();
				ImportTree("data_dir/tree.txt",&Skill);
				Player.Spoint = 15;
				SkillMenu();
					break;
			case 2 :
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
				break;
			default:
			printf("wrong input\n");
		}
		scanf(" %d",&inp);
	}
    return 0;
}
