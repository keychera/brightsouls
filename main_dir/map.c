#include "header_dir//brightsoul.h"
#include "header_dir/map.h"
#include "header_dir/skill.h"
//battle purposes - key edit
#include "header_dir/battle.h" 
#include "header_dir/monsterdb.h"

#define FileMap "data_dir/map.txt"

/*********************/
/*****LIST SUBMAP*****/
/*********************/

void PrintInfoSubMap(ListSubMap L){
	addressSubMap P;
	printf("////////////////\n");
	P=First(L);
	while(P!=Nil){
		printf("Info:%d Tele:",Info(P));
		if(First(Tele(P))==Nil){
			printf("Tidak ada ");
		}
		else{
			printf("Ada ");
		}
		if(Next(P)==Nil){
			printf("Tidak lanjut \n");
		}
		else{
			printf("Lanjut \n");
		}
		P=Next(P);
	}
	printf("////////////////");
}
boolean IsEmptySubMap(ListSubMap L)
{
	return (First(L)==Nil);
}

void CreateEmptySubMap(ListSubMap *L)
{
	First(*L)=Nil;
}

addressSubMap AlokasiSubMap (infotypeSubMap X)
{
	addressSubMap P;
	(P) = (ElmtListSubMap*) malloc (sizeof(ElmtListSubMap));
	Info(P)=X;
	First(Tele(P))=Nil;
	Next(P)=Nil;

	return P;
}

void DealokasiSubMap (addressSubMap P)
{
	free (P);
}

addressSubMap SearchSubMap (ListSubMap L,infotypeSubMap X)
{
	addressSubMap P;
	boolean found;
	found=false;
	P = First(L);
	while((!found) && (P!=Nil)){
		if(Info(P)==X){
			found=true;
		}
		else{
			P=Next(P);
		}
	}
	/*found or P==Nil*/
	if (found){
		return P;
	}
	else{
		return Nil;
	}
}

void InsVFirstSubMap (ListSubMap *L, infotypeSubMap X)
{
	addressSubMap P;
	P = AlokasiSubMap(X);
	if(IsEmptySubMap(*L)){
		First(*L)=P;
	}
	else{
		Next(P)=First(*L);
		First(*L)=P;
	}
}

void DelSubMap (ListSubMap *L, addressSubMap P, infotypeSubMap *X)
{
	addressSubMap PCur,Prev;
	boolean found;
	*X=Info(P);
	if(!IsEmptySubMap(*L)){
		found = false;
		PCur=First(*L);
		Prev=Nil;

		while(!found && PCur!=Nil){
			if(PCur==P){
				found=true;
			}
			else{
				Prev=PCur;
				PCur=Next(PCur);
			}
		}

		/*found or PCur==Nil*/
		if (found){
			if(PCur == First(*L)){
				First(*L)=Next(PCur);
			}
			else{
				Next(Prev)=Next(PCur);
			}
			DealokasiSubMap(PCur);
		}
	}
}
/*********************/
/******LIST TELE******/
/*********************/
boolean IsEmptyTele(ListTele L)
{
	return (First(L)==Nil);
}

void CreateEmptyTele(ListTele L)
{
	First(L)=Nil;
}

addressTele AlokasiTele (POINT From,POINT To, addressSubMap Dest)
{
	addressTele P;
	P=(ElmtListTele*) malloc (sizeof (ElmtListTele));
	Absis(From(P))=Absis(From);
	Ordinat(From(P))=Ordinat(From);
	Absis(To(P))=Absis(To);
	Ordinat(To(P))=Ordinat(To);
	Destination(P)=Dest;
	Next(P)=Nil;
	return P;
}

void InsVFirstTele(ListTele *L, POINT From,POINT To, addressSubMap Dest)
{
	addressTele PTele;
	PTele=AlokasiTele(From,To,Dest);
	Next(PTele)=First(*L);
	First(*L)=PTele;
}

addressTele SearchPOINTTele(ListTele L,POINT P){
	addressTele PTemp;
	boolean found;
	PTemp=First(L);
	found=false;
	while(!found && PTemp != Nil){
		if(Absis(From(PTemp))==Absis(P) && Ordinat(From(PTemp))==Ordinat(P)){
			found=true;
		}
		else{
			PTemp=Next(PTemp);
		}
	}

	if(found){
		return PTemp;
	}
	else{
		return Nil;
	}

}


/*********************/
/*******BERSAMA*******/
/*********************/
void ConnectSubMap(ListSubMap *L, infotypeSubMap X1,POINT C1 ,infotypeSubMap X2,POINT C2)
{
	addressSubMap P1,P2;
	P1=SearchSubMap(*L,X1);
	P2=SearchSubMap(*L,X2);
	InsVFirstTele(&Tele(P1),C1,C2,P2);
	InsVFirstTele(&Tele(P2),C2,C1,P1);
}



/*********************/
/*********MAP*********/
/*********************/
void CreateEmptyCurMap()
{
	int i,j;
	for(i=0;i<=HSizeMap-1;i++){
		for(j=0;j<=WSizeMap-1;j++){
			CurMap[i][j]='#';
		}
	}
}

char IntToChar(int X){
	if(X==1){
		return '1';
	}
	else if(X==2){
		return '2';
	}
	else if(X==3){
		return '3';
	}
	else if(X==4){
		return '4';
	}
	else if(X==5){
		return '5';
	}
	else if(X==6){
		return '6';
	}
	else if(X==7){
		return '7';
	}
	else if(X==8){
		return '8';
	}
	else if(X==9){
		return '9';
	}
	else {
		return '0';
	}
}

void ImportCurMap(infotypeSubMap X)
{
	int i,j,retval;
	char C;
	FILE *filex;
	filex = fopen (FileMap,"r");
	retval = fscanf(filex,"%c",&C);
	while(C!=IntToChar(X)){
		retval = fscanf(filex,"%c\n",&C);
	}
	for(i=0;i<=HSizeMap-1;i++){
		for(j=0;j<=WSizeMap-1;j++){
		retval = fscanf(filex,"%c\n",&C);
		CurMap[i][j]=C;
		}
	}

}

void PrintCurMap(POINT Player){
    clear();
	int i,j;
	for(i=0;i<=HSizeMap-1;i++){
		for(j=0;j<=WSizeMap-1;j++){
			if(i==(int)Ordinat(Player) && j==(int)Absis(Player)){
				printf(BLU"P"RESET);
			}
			else{
                if (CurMap[i][j] == '#') {
                    printf(YEL);
                }
                else if (CurMap[i][j] == '-') {
                    printf(WHT);
                }
                else if (CurMap[i][j] == 'E') {
                    printf(RED);
                }
                else if (CurMap[i][j] == 'M') {
                    printf(GRN);
                }
				printf("%c"RESET,CurMap[i][j]);
			}
		}
		printf("\n");
	}
}

void Move(POINT *P,float X, float Y){
	POINT PTemp;
	Absis(PTemp)=Absis(*P)+X;
	Ordinat(PTemp)=Ordinat(*P)+Y;
	if(Absis(PTemp)>=0 || Absis(PTemp)<10 || Ordinat(PTemp)>=0 || Ordinat(PTemp)<10){
		if((CurMap[(int)Ordinat(PTemp)][(int)Absis(PTemp)]) != '#'){
            if ((CurMap[(int)Ordinat(PTemp)][(int)Absis(PTemp)]) == 'E') {
                //enemy - key edit
				int battle_outcome;
				//ENEMY ID NEED HANDLING, connected to Afif's spawnenemy, which I guess isn't here already
				// EnemyStat enemy; key edit - not used
				LoadEnemy("data_dir/MonsterDB.txt");
				Enemy[1].ID = 1; //handle this
				battle_initiate(Enemy[1].ID, 1,&battle_outcome); //handle enemy id please
				//do something with battle_outcome here, a message to Lazu
				switch (battle_outcome) {
					case 1 :printf("You defeated the monster!\n"); break;
					case 2 :printf("You suck at this.\n"); break;
					case 3 :printf("ooo better luck next time kiddo\n"); break;
					default:
						printf("apparently you found a bug!\n  this isn't supposed to be printed.\n");
				}
            }
			else if ((CurMap[(int)Ordinat(PTemp)][(int)Absis(PTemp)]) != 'M') {
			    //medicine
			    CurMap[(int)Ordinat(PTemp)][(int)Absis(PTemp)] = '-';
                Absis(*P)=Absis(PTemp);
                Ordinat(*P)=Ordinat(PTemp);
			}
			else {
                Absis(*P)=Absis(PTemp);
                Ordinat(*P)=Ordinat(PTemp);
			}
		}
	}
}

void InitGame(ListSubMap *L){
	POINT P1,P2;
	CreateEmptySubMap(L);
	InsVFirstSubMap(L,3);
	InsVFirstSubMap(L,2);
	InsVFirstSubMap(L,1);
	P1=MakePOINT(9,2);
	P2=MakePOINT(0,4);
	ConnectSubMap(L,1,P1,2,P2);
	P1=MakePOINT(9,7);
	P2=MakePOINT(0,7);
	ConnectSubMap(L,1,P1,3,P2);
	P1=MakePOINT(9,6);
	P2=MakePOINT(0,1);
	ConnectSubMap(L,2,P1,3,P2);
}

void Game(ListSubMap *L){
	POINT Player;
	addressSubMap PMap;
	addressTele PTele;
	char *a;
	boolean Pindah;

	Pindah=false;
	a=(char*) malloc (2* sizeof(char));
	PMap=First(*L);
	Absis(Player)=5;
	Ordinat(Player)=5;
	ImportCurMap(Info(PMap));

    PrintCurMap(Player);
    scanf("%s",a);
	while(strcmp(a,"EXIT")) {
		if(!strcmp(a,"GU")||!strcmp(a,"gu")){
			Move(&Player,0,-1);
			PTele=SearchPOINTTele(Tele(PMap),Player);
			if(PTele!=Nil){
				PMap=Destination(PTele);
				Player=To(PTele);
				Pindah=true;
			}
		}
		else if(!strcmp(a,"GD")||!strcmp(a,"gd")){
			Move(&Player,0,1);
			PTele=SearchPOINTTele(Tele(PMap),Player);
			if(PTele!=Nil){
				PMap=Destination(PTele);
				Player=To(PTele);
				Pindah=true;
			}
		}
		else if(!strcmp(a,"GL")||!strcmp(a,"gl")){
			Move(&Player,-1,0);
			PTele=SearchPOINTTele(Tele(PMap),Player);
			if(PTele!=Nil){
				PMap=Destination(PTele);
				Player=To(PTele);
				Pindah=true;
			}
		}
		else if(!strcmp(a,"GR")||!strcmp(a,"gr")){
			Move(&Player,1,0);
			PTele=SearchPOINTTele(Tele(PMap),Player);
			if(PTele!=Nil){
				PMap=Destination(PTele);
				Player=To(PTele);
				Pindah=true;
			}
		}
		else if (!strcmp(a,"SKILL")) {
            SkillMenu();
		}
        else {
			printf("NOT GOING ANYWHERE\n");
		}
		if(Pindah){
			ImportCurMap(Info(PMap));
			Pindah=false;
		}
		PrintCurMap(Player);
		if(!strcmp(a,"GU")||!strcmp(a,"gu")){
			printf("Going UP\n");
		}
		else if(!strcmp(a,"GD")||!strcmp(a,"gd")){
			printf("Going DOWN\n");
		}
		else if(!strcmp(a,"GL")||!strcmp(a,"gl")){
			printf("Going LEFT\n");
		}
		else if(!strcmp(a,"GR")||!strcmp(a,"gr")){
			printf("Going RIGHT\n");
		}
		else if (!strcmp(a,"SKILL")) {
		}
        else {
			printf("NOT GOING ANYWHERE\n");
		}
		scanf("%s",a);
	}
}


