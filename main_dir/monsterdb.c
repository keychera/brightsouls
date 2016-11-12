#include "header_dir/mesinkata.h"
#include "header_dir/monsterdb.h"
#include <stdio.h>

void LoadEnemy(char namaFile[]){ //Membaca database enemy dari file eksternal, dijalankan diawal program
	int statNumber = 0; // Nama = 0, HP = 1, STR = 2, DEF = 3, EXP = 4, ACTION = 5-15	
	int actNumber = 0; // Action Index
	enemyCount = 0;	
	STARTKATA(namaFile);
	while (!EndFile) {
		ADVKATA(); //Skip Monster ID	
		while(!EndKata) {
			if (CKata.TabKata[1] != '|'){
				switch(statNumber) {
					case 0:
						KataToString(CKata, enemy[enemyCount].Nama);
						break;
					case 1:
						enemy[enemyCount].HP = 	KataToInteger(CKata);
						break;
					case 2:
						enemy[enemyCount].STR = KataToInteger(CKata);
						break;
					case 3:
						enemy[enemyCount].DEF = KataToInteger(CKata);
						break;
					case 4:
						enemy[enemyCount].EXP = KataToInteger(CKata);
						break;
					default:
						KataToString(CKata, enemy[enemyCount].ACTION[actNumber]);
						actNumber++;
						break;
				}
				statNumber++;
			}
			ADVKATA();
		}
		ADVROW();
		actNumber = 0;
		statNumber = 0;
		enemyCount++;
		ADVKATA();
	}
}

EnemyStat GetEnemy(int id, int monsterLVL){
	/*		Status Calculation (TEMPORARY)
		HP = HP + monsterLVL*2
		STR = STR + monsterLVL
		DEF = DEF + monsterLVL
		EXP = EXP + monsterLVL*EXP
	*/
	if (monsterLVL > 1) {
		enemy[id].HP 	+= monsterLVL*2;
		enemy[id].STR 	+= monsterLVL;
		enemy[id].DEF 	+= monsterLVL;
		enemy[id].EXP 	+= monsterLVL*enemy[id].EXP;
	}
	return enemy[id];
}

