#include <string.h>
#include <stdio.h>
#include "header_dir/skill.h"
#include "header_dir/brightsoul.h"

void ImportSkill()
/* Prosedur untuk mengambil data skill dari file eksternal */
{
    char F[40] = "data_dir/dataskill.txt"; //key edit for compatibility
    int n = 1;
    int i;
    Kata hp;
    Kata str;
    Kata def;
    hp.Length = 2;
    hp.TabKata[1] = 'H';
    hp.TabKata[2] = 'P';
    str.Length = 3;
    str.TabKata[1] = 'S';
    str.TabKata[2] = 'T';
    str.TabKata[3] = 'R';
    def.Length = 3;
    def.TabKata[1] = 'D';
    def.TabKata[2] = 'E';
    def.TabKata[3] = 'F';
    STARTKATA(F);
    while (!EndFile) {
        if (EndKata) {
            n++;
            ADVKATA();
        }
        else {
            DataSkill[n].Nama.Length = 0;
            for (i=1; i<=CKata.Length; i++) {
                DataSkill[n].Nama.Length++;
                DataSkill[n].Nama.TabKata[DataSkill[n].Nama.Length] = CKata.TabKata[i];
            }
            ADVKATA();
            while (CKata.TabKata[1] != '|') {
                DataSkill[n].Nama.Length++;
                DataSkill[n].Nama.TabKata[DataSkill[n].Nama.Length] = ' ';
                for (i=1; i<=CKata.Length; i++) {
                    DataSkill[n].Nama.Length++;
                    DataSkill[n].Nama.TabKata[DataSkill[n].Nama.Length] = CKata.TabKata[i];
                }
                ADVKATA();
            }
            ADVKATA();
            i = 0;
            while (!EndKata) {
                if (IsKataSama(CKata,hp)) {
                    DataSkill[n].Stat = 0;
                }
                else if (IsKataSama(CKata,str)) {
                    DataSkill[n].Stat = 1;
                }
                else if (IsKataSama(CKata,def)) {
                    DataSkill[n].Stat = 2;
                }
                ADVKATA();
                DataSkill[n].Change = KataToInteger(CKata);
                ADVKATA();
                i++;
                if (i > 20) {
                    break;
                }
            }
        }
    }
}

void PrintSubTree(addressT P, int n, int a[])
/* Prosedur rekursi untuk menampilkan tree */
{
    addressS Cari;
    int i;
    for (i=1; i<n; i++) {
        if (i == n-1) {
            printf(CYN"  |-"RESET);
        }
        else if (a[i] == 1) {
            printf(CYN"  | "RESET);
        }
        else {
            printf(CYN"    "RESET);
        }
    }
    Cari = SearchS(Player.aqcuired,Info(P));
    if (Cari != Nil) {
        printf(GRN "%2d. ",Info(P));
        PrintKata(DataSkill[Info(P)].Nama);
        printf(" LEVEL : %d; ",Level(Cari));
        switch (DataSkill[Info(P)].Stat) {
            case 0 : {
                printf("HP");
                break;
            }
            case 1 : {
                printf("STR");
                break;
            }
            case 2 : {
                printf("DEF");
                break;
            }
        }
        printf(" : +%d\n" RESET,DataSkill[Info(P)].Change*Level(Cari));
    }
    else {
        printf(RED "%2d. ",Info(P));
        PrintKata(DataSkill[Info(P)].Nama);
        printf(" (");
        switch (DataSkill[Info(P)].Stat) {
            case 0 : {
                printf("HP");
                break;
            }
            case 1 : {
                printf("STR");
                break;
            }
            case 2 : {
                printf("DEF");
                break;
            }
        }
        printf(" : +%d)\n" RESET,DataSkill[Info(P)].Change);
    }
    //REKURSIF
    if ((Left(P) != Nil) && (Right(P) != Nil)) {
        a[n] = 1;
        PrintSubTree(Left(P), (n+1), a);
        a[n] = 0;
        PrintSubTree(Right(P), (n+1), a);
    }
    else if (Left(P) != Nil) {
        a[n] = 0;
        PrintSubTree(Left(P), (n+1), a);
    }
    else if (Right(P) != Nil) {
        a[n] = 0;
        PrintSubTree(Right(P), (n+1), a);
    }
}

void PrintSkill()
/* Prosedur untuk menampilkan tampilan menu skill */
{
    clear();
    printf(YEL "__________________________________________________________________\n");
    printf("| SKILL TREE                                                     |\n");
    printf("| "GRN"ACQUIRED       "RED"NOT ACQUIRED"YEL"                                    |\n");
    printf("|________________________________________________________________|\n" RESET);
    int gambar[10];
    PrintSubTree(Skill,1,gambar);
    printf("SKILL POINTS : %d\n\n",Player.Spoint);
}

void LearnSkill()
/* Menu Learn skill */
{
    int s;
    addressS P;
    addressT T;
    infoskill X;
    if (Player.Spoint > 0) {
        printf("Enter skill number you want to learn : ");
        scanf("%d",&s);
        P = SearchS(Player.aqcuired,s);
        if (P == Nil) {
            T = SearchPrecT(Skill,s);
            if (T != Nil) {
                P = SearchS(Player.aqcuired,Info(T));
            }
            if (((T != Nil) && (P != Nil)) || (T == Nil)) {
                X.ID = s;
                X.level = 1;
                InsVLastS(&(Player.aqcuired),X);
                switch (DataSkill[s].Stat) {
                    case 0 : {
                        Player.HP += DataSkill[s].Change;
                        Player.maxHP += DataSkill[s].Change;
                        break;
                    }
                    case 1 : {
                        Player.STR += DataSkill[s].Change;
                        break;
                    }
                    case 2 : {
                        Player.DEF += DataSkill[s].Change;
                        break;
                    }
                }
                Player.Spoint--;
                printf("Skill ");
                PrintKata(DataSkill[s].Nama);
                printf(" learned\n");
            }
            else if (T != Nil) {
                printf("You must learn skill ");
                PrintKata(DataSkill[Info(T)].Nama);
                printf(" first\n");
            }
        }
        else {
            printf("You have learned this skill, why bother?\n");
        }
        getchar();
    }
    else {
        printf("Skill point not sufficient\n");
    }
}

void UpgradeSkill()
/* Menu Upgade Skill */
{
    int s;
    addressS P;
    if (Player.Spoint > 0) {
        printf("Enter skill number you want to upgrade : ");
        scanf("%d",&s);
        P = SearchS(Player.aqcuired,s);
        if (P != Nil) {
            if (Level(P) == 10) {
                printf("Skill ");
                PrintKata(DataSkill[ID(P)].Nama);
                printf(" has reached max level\n");
            }
            else {
                Player.Spoint--;
                Level(P) = Level(P) + 1;
                switch (DataSkill[ID(P)].Stat) {
                    case 0 : {
                        Player.HP += DataSkill[ID(P)].Change;
                        Player.maxHP += DataSkill[ID(P)].Change;
                        break;
                    }
                    case 1 : {
                        Player.STR += DataSkill[ID(P)].Change;
                        break;
                    }
                    case 2 : {
                        Player.DEF += DataSkill[ID(P)].Change;
                        break;
                    }
                }
                printf("Skill ");
                PrintKata(DataSkill[ID(P)].Nama);
                printf(" upgraded\n");
            }
        }
        else {
            printf("You have to learn this skill first\n");
        }
        getchar();
    }
    else {
        printf("Skill point not sufficient\n");
    }
}

void HelpSkill(){
	printf("Command List\n\n");
	printf(YEL"HELP"WHT);
	printf(": Open command list menu\n");
	printf(GRN"LEARN"WHT);
	printf(": Learn new skill\n");
	printf(CYN"UPGRADE"WHT);
	printf(": Upgrade already learned skill\n");
	printf(RED"BACK"WHT);
	printf(": Back to map\n");
}

void SkillMenu()
/* menu yang memproses interface skill */
{
    int HelpCount = 0;
    char dummy;
    Kata command;
    Kata upgrade;
    Kata learn;
    Kata back;
    Kata help;
    upgrade.Length = 7;
    upgrade.TabKata[1] = 'U';
    upgrade.TabKata[2] = 'P';
    upgrade.TabKata[3] = 'G';
    upgrade.TabKata[4] = 'R';
    upgrade.TabKata[5] = 'A';
    upgrade.TabKata[6] = 'D';
    upgrade.TabKata[7] = 'E';
    learn.Length = 5;
    learn.TabKata[1] = 'L';
    learn.TabKata[2] = 'E';
    learn.TabKata[3] = 'A';
    learn.TabKata[4] = 'R';
    learn.TabKata[5] = 'N';
    back.Length = 4;
    back.TabKata[1] = 'B';
    back.TabKata[2] = 'A';
    back.TabKata[3] = 'C';
    back.TabKata[4] = 'K';
    help.Length = 4;
    help.TabKata[1] = 'H';
    help.TabKata[2] = 'E';
    help.TabKata[3] = 'L';
    help.TabKata[4] = 'P';
    PrintSkill();
    printf("Input command : ");
    dummy = getchar();
    command = InputKata();
    do {
        PrintSkill();
        if (IsKataSama(command,upgrade)) {
            UpgradeSkill();
            HelpCount = 0;
        }
        else if (IsKataSama(command,learn)) {
            LearnSkill();
            HelpCount = 0;
        }
        else if (IsKataSama(command,help)) {
            HelpSkill();
            HelpCount = 0;
        }
        else if (!IsKataSama(command,back)) {
            printf("Command not recognized\n");
            HelpCount++;
        }
        if(HelpCount>=3){
			printf("type "YEL"HELP"RESET" for the list of commands\n");
		}
        printf("\nInput command : ");
        command = InputKata();
    } while (!IsKataSama(command,back));
}
