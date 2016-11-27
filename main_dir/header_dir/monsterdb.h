#ifndef monsterdb_H
#define monsterdb_H

#define EnemyMax 50 //Jumlah enemy

typedef struct EnemyStat{
	char Nama[99];
    int HP;
    int STR;
    int DEF;
    int EXP;
    char ACTION[20][5]; // 10 set aksi untuk masing" musuh, 20 utk boss
} EnemyStat;

//DEKLARASI VARIABLE GLOBAL
int enemyCount;
EnemyStat enemy[EnemyMax];

void LoadEnemy(char namaFile[]); //Membaca database enemy dari file eksternal, dijalankan diawal program

EnemyStat GetEnemy(int id, int monsterLVL);

#endif
