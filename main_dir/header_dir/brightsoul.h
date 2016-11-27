// DEKLARASI TIPE DAN KONSTANTA
#ifndef brightsoul_H
#define brightsoul_H

#define SMax 50
#define EMax 5

//skill header
#include "mystring.h"
#include "listskill.h"
#include "mesinkata.h"
#include "map.h"
#include "tree.h"

//formatting purposes
#define RED   "\x1B[31m"    //merah
#define GRN   "\x1B[32m"    //hijau
#define YEL   "\x1B[33m"    //kuning
#define BLU   "\x1B[34m"    //biru
#define MAG   "\x1B[35m"    //merah muda
#define CYN   "\x1B[36m"    //biru muda
#define WHT   "\x1B[37m"    //putih
#define RESET "\x1B[0m"     //reset warna
#define clear() printf("\033[H\033[J")

typedef struct SkillStat {
    Kata Nama;
    int Stat;                   // 0 : HP, 1 : STR, 2 : DEF
    int Change;                 // dalam persentase (50 berarti 50%)
} SkillStat;

typedef struct ELoc {
    int ID;
    //POINT Pos;
} ELoc;

typedef struct PlayerStat {
    char Nama[99]; //conflict Kata datatype and string/char*
    int HP;
    int maxHP;
    int STR;
    int DEF;
    int EXP;
    int maxEXP;
    int LVL;
    //POINT pos;
    int Spoint;
    ListSkill aqcuired;
} PlayerStat;

/* don't know why this here - key
typedef struct CurMap {
    int ID;
    //MATRIKS Map;
} CurMap;*/

//DEKLARASI VARIABEL GLOBAL
SkillStat DataSkill[SMax];
PlayerStat Player;
ELoc Enemy[EMax];
//CurMap Map;
//ListSubMap BigMap;
Tree Skill;
// PLACEHOLDER : <tipe_untuk_map_besar> BigMap;


#endif
