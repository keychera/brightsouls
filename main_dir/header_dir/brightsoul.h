// DEKLARASI TIPE DAN KONSTANTA
#ifndef brightsoul_H
#define brightsoul_H

#define SMax 50
#define EMax 5

typedef struct SkillStat {
    //Kata Nama;
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
} PlayerStat;
typedef struct CurMap {
    int ID;
    //MATRIKS Map;
} CurMap;

//DEKLARASI VARIABEL GLOBAL
SkillStat DataSkill[SMax];
PlayerStat Player;
ELoc Enemy[EMax];
CurMap Map;
// PLACEHOLDER : <tipe_untuk_map_besar> BigMap;
//Tree Skill;

#endif