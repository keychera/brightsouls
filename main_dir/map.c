#include "header_dir//brightsoul.h"
#include "header_dir/map.h"
#include "header_dir/skill.h"
//battle purposes - key edit
#include "header_dir/battle.h" 
#include "header_dir/monsterdb.h"

#define FileMap "data_dir/map.txt"
#define FileMapSave "data_dir/mapsave.txt"
#define FileMapSaveDefault "data_dir/DefaultMap.txt"
#define FilePlayerSave "data_dir/playersave.dat"
#define FileEnemySave "data_dir/enemysave.txt"

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

void CreateEmptyTele(ListTele *L)
{
	First(*L)=Nil;
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




/**********************/
/******LIST ENEMY******/
/**********************/
boolean IsEmptyEnemy(ListEnemy L){
	return First(L)==Nil;
}

void CreateEmptyEnemy(ListEnemy *L)
{
	First(*L)=Nil;
}

addressEnemy AlokasiEnemy(POINT Pos, int Id,int Level,int Map)
{
	POINT To;
	addressEnemy PEnemy;
	addressSubMap PMap;
	Absis(To)=Id;
	Ordinat(To)=Level;
	PMap=SearchSubMap(LMap,Map);
	
	
	PEnemy=AlokasiTele(Pos,To,PMap);
	return PEnemy;
	
}

void DealokasiEnemy(addressEnemy E){
	free(E);
}

void InsVFirstEnemy(ListEnemy *L, POINT Pos, int Id,int Level, int Map)
{
	addressEnemy PEnemy;
	
	PEnemy=AlokasiEnemy(Pos,Id,Level,Map);
	if(PEnemy!=Nil){
		Next(PEnemy)=First(*L);
		First(*L)=PEnemy;
	}
}

void DeleteEnemy(ListEnemy *L, addressEnemy P){
	addressEnemy PTemp,Prec;
	PTemp=First(*L);
	while(PTemp!=P){
		Prec=PTemp;
		PTemp=Next(PTemp);
	}
	if(PTemp==First(*L)){
		First(*L)=Next(PTemp);
	}
	else{
		Next(Prec)=Next(PTemp);
	}
	
	DealokasiEnemy(PTemp);
}

boolean SearchMapEnemy(ListEnemy L, int Map)
{
	addressEnemy P;
	boolean found;
	
	found=false;
	P=First(L);
	while(!found && P != Nil){
		if(Info(Map(P))==Map){
			found=true;
		}
		else{
			P=Next(P);
		}
	}
	
	return P!=Nil;
}

addressEnemy SearchPosEnemy(ListEnemy L, POINT Pos, int Map)
{
	addressEnemy P;
	boolean found;
	
	found=false;
	P=First(L);
	while(!found && P != Nil){
		if(Ordinat(Pos(P))==Ordinat(Pos) && Absis(Pos(P))==Absis(Pos) && Info(Map(P))==Map){
			found=true;
		}
		else{
			P=Next(P);
		}
	}
	
	return P;
}

void PrintListEnemy(ListEnemy L){
	addressEnemy P;
	
	P=First(L);
	while(P != Nil){
		printf("Id:%.0f ",Id(P));
		printf("Level:%.0f ",Lvl(P));
		printf("Pos:%.0f,%.0f ",Absis(Pos(P)),Ordinat(Pos(P)));
		printf("Map:%d\n",Info(Map(P)));
		P=Next(P);
	}
}

void MelistEnemyBaru(){
	int i,j;
	srand(time(NULL));
	for(i=1;i<=NBrsEff(CurMap);i++){
		for(j=1;j<=NKolEff(CurMap);j++){
			if(Elmt(CurMap,i,j)=='E'){
				InsVFirstEnemy(&LEnemy,MakePOINT(i,j),(rand()%2)+1,Info(CurSubMap),Info(CurSubMap));
			}
		}
	}
}

void ImportEnemy(){
	addressEnemy P;
	
	P=First(LEnemy);
	while(P!=Nil){
		if(Map(P)==CurSubMap){
			Elmt(CurMap,(int) Absis(Pos(P)),(int) Ordinat(Pos(P)))='E';
		}
		P=Next(P);
	}
}



/*********************/
/*********MAP*********/
/*********************/
void CreateEmptyCurMap()
{
	int i,j;
	for(i=1;i<=NBrsEff(CurMap);i++){
		for(j=1;j<=NKolEff(CurMap);j++){
			Elmt(CurMap,i,j)='#';
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
	int i,j;
	char C;
	FILE *filex;
	filex = fopen (FileMap,"r");
	fscanf(filex,"%c",&C);
	while(C!=IntToChar(X)){
		fscanf(filex,"%c\n",&C);
	}
	for(i=1;i<=NBrsEff(CurMap);i++){
		for(j=1;j<=NKolEff(CurMap);j++){
		fscanf(filex,"%c\n",&C);
		Elmt(CurMap,i,j)=C;
		}
	}
	
	if(SearchMapEnemy(LEnemy,Info(CurSubMap))){
		ImportEnemy();
	}
	else{
		spawn(&CurMap,5);
		MelistEnemyBaru();
	}
}

void PrintCurMap(){
    clear();
	int i,j;
	for(i=1;i<=NBrsEff(CurMap);i++){
		for(j=1;j<=NKolEff(CurMap);j++){
			printf(" ");
			if(i==(int)Ordinat(PlayerPos) && j==(int)Absis(PlayerPos)){
				printf(BLU"P"RESET);
			}
			else{
                if (Elmt(CurMap,i,j) == '#') {
                    printf(YEL);
                }
                else if (Elmt(CurMap,i,j) == '-') {
                    printf(WHT);
                }
                else if (Elmt(CurMap,i,j) == 'E') {
                    printf(RED);
                }
                else if (Elmt(CurMap,i,j) == 'M') {
                    printf(GRN);
                }
				printf("%c"RESET,Elmt(CurMap,i,j));
			}
		}
		printf("\n");
	}
}

void Move(float X, float Y){
	POINT PTemp,PWas;
	addressTele PTele;
	addressEnemy PEnemy;
	
	Absis(PWas)=Absis(PlayerPos);
	Ordinat(PWas)=Ordinat(PlayerPos);
	Absis(PTemp)=Absis(PlayerPos)+X;
	Ordinat(PTemp)=Ordinat(PlayerPos)+Y;
	if(Absis(PTemp)>=1 && Absis(PTemp)<=20 && Ordinat(PTemp)>=1 && Ordinat(PTemp)<=20){
		if(Elmt(CurMap,(int)Ordinat(PTemp),(int)Absis(PTemp)) != '#'){
            if (Elmt(CurMap,(int)Ordinat(PTemp),(int)Absis(PTemp)) == 'E') {
				PEnemy=SearchPosEnemy(LEnemy,MakePOINT(Ordinat(PTemp),Absis(PTemp)),Info(CurSubMap));
                //enemy - key edit
				int battle_outcome;
				//ENEMY ID NEED HANDLING, connected to Afif's spawnenemy, which I guess isn't here already
				// EnemyStat enemy; key edit - not used
				LoadEnemy("data_dir/MonsterDB.txt");
				Enemy[1].ID = Id(PEnemy); //handle this
				battle_initiate(Id(PEnemy), Lvl(PEnemy),&battle_outcome); //handle enemy id please
				switch (battle_outcome) {
					case 1 :printf("You defeated the monster!\n"); break;
					case 2 :printf("You suck at this.\n"); break;
					case 3 :printf("ooo better luck next time kiddo\n"); break;
					default:
						printf("apparently you found a bug!\n  this isn't supposed to be printed.\n");
				}
				if(battle_outcome==1){
					Elmt(CurMap,(int)Ordinat(PTemp),(int)Absis(PTemp))='-';
					DeleteEnemy(&LEnemy,PEnemy);
				}
            }
			else if (Elmt(CurMap,(int)Ordinat(PTemp),(int)Absis(PTemp)) != 'M') {
			    //medicine
			    Elmt(CurMap,(int)Ordinat(PTemp),(int)Absis(PTemp)) = '-';
                Absis(PlayerPos)=Absis(PTemp);
                Ordinat(PlayerPos)=Ordinat(PTemp);
			}
			else {
                Absis(PlayerPos)=Absis(PTemp);
                Ordinat(PlayerPos)=Ordinat(PTemp);
			}
		}
	}
	if(Absis(PWas)!=Absis(PlayerPos) || Ordinat(PWas)!=Ordinat(PlayerPos)){
		PTele=SearchPOINTTele(Tele(CurSubMap),PlayerPos);
		if(PTele!=Nil){
			CurSubMap=Destination(PTele);
			PlayerPos=To(PTele);
		}
	}
}



/*********************/
/******SAVE/LOAD******/
/*********************/
void SavePlayerState(){
	FILE *save;
	
	save = fopen(FilePlayerSave,"w");
	
	fwrite(&Player,sizeof(PlayerStat),1,save);
	fclose(save);
}

void LoadPlayerState(){
	FILE *load;
	PlayerStat PTemp;
	
	load = fopen(FilePlayerSave,"r");
	fread(&PTemp,sizeof(PlayerStat),1,load);
	
	Player=PTemp;
	
}

void SaveEnemyList(){
	FILE *save;
	addressEnemy PEnemy;
	int Id,X,Y,Level,Map;
	
	save = fopen(FileEnemySave,"w");
	PEnemy=First(LEnemy);
	while(PEnemy!=Nil){
		Id=(int)Id(PEnemy);
		fprintf(save,"%c%c ",(Id/10)+'0',(Id%10)+'0');
		X=(int)Absis(Pos(PEnemy));
		Y=(int)Ordinat(Pos(PEnemy));
		fprintf(save,"%c%c,%c%c ",(X/10)+'0',(X%10)+'0',(Y/10)+'0',(Y%10)+'0');
		Level=(int)Lvl(PEnemy);
		fprintf(save,"%c%c ",(Level/10)+'0',(Level%10)+'0');
		Map=(int)Info(Map(PEnemy));
		fprintf(save,"%c%c\n",(Map/10)+'0',(Map%10)+'0');
		
		PEnemy=Next(PEnemy);
	}
	fprintf(save,"!");
	
	fclose(save);
	
}

void LoadEnemyList(){
	POINT Pos;
	int Id, Level, Map;
	
	CreateEmptyEnemy(&LEnemy);
	
	START(FileEnemySave);
	while(CC!='!'){
		Id=CC-'0';
		ADV();
		Id=10*Id+(CC-'0');
		
		ADV();
		ADV();
		
		Absis(Pos)=CC-'0';
		ADV();
		Absis(Pos)=10*Absis(Pos)+(CC-'0');
		
		ADV();
		ADV();
		
		Ordinat(Pos)=CC-'0';
		ADV();
		Ordinat(Pos)=10*Ordinat(Pos)+(CC-'0');
		
		ADV();
		ADV();
		
		Level=CC-'0';
		ADV();
		Level=10*Level+(CC-'0');
		
		ADV();
		ADV();
		
		Map=CC-'0';
		ADV();
		Map=10*Map+(CC-'0');
		
		InsVFirstEnemy(&LEnemy,Pos,Id,Level,Map);
		
		ADV();
		ADV();
		
	}
}

void SaveMap(){
	FILE *save;
	addressSubMap PMap;
	addressTele PTele;
	int i;
	
	save = fopen(FileMapSave,"w");
	
	fprintf(save,"PlayerPosition:.\n");
	i=Info(CurSubMap);
	fprintf(save,"%c%c ",(i / 10)+'0',(i % 10)+'0');
	i=(int) Absis(PlayerPos);
	fprintf(save,"%c%c ",(i / 10)+'0',(i % 10)+'0');
	i=(int) Ordinat(PlayerPos);
	fprintf(save,"%c%c.\n",(i / 10)+'0',(i % 10)+'0');
	
	fprintf(save,"List Map:.\n");
	PMap=First(LMap);
	while(PMap!=Nil){
		i=Info(PMap);
		fprintf(save,"%c%c ",(i / 10)+'0',(i % 10)+'0');
		PMap=Next(PMap);
	}
	fprintf(save,".\n");
	
	fprintf(save,"Koneksi Map:.\n");
	PMap=First(LMap);
	while(PMap!=Nil){
		i=Info(PMap);
		fprintf(save,"MAP %c%c :.\n",(i / 10)+'0',(i % 10)+'0');
		PTele=First(Tele(PMap));
		while(PTele!=Nil){
			i=(int) Absis(From(PTele));
			fprintf(save,"FROM %c%c , ",(i / 10)+'0',(i % 10)+'0');
			i=(int) Ordinat(From(PTele));
			fprintf(save,"%c%c ",(i / 10)+'0',(i % 10)+'0');
			i=(int) Absis(To(PTele));
			fprintf(save,"TO %c%c , ",(i / 10)+'0',(i % 10)+'0');
			i=(int) Ordinat(To(PTele));
			fprintf(save,"%c%c ",(i / 10)+'0',(i % 10)+'0');
			i=Info(Destination(PTele));
			fprintf(save,"DestMap %c%c.\n",(i / 10)+'0',(i % 10)+'0');
			PTele=Next(PTele);
		}
		
		PMap=Next(PMap);
	}
	
	fprintf(save,"END!");
	
	fclose(save);
}

void LoadPre(){
	Kata C;
	int i;
	
	i=1;
	STARTKATA(FileMapSave);
	while(!EndFile){
		C=CKata;
		printf("\n%d:",i);
		PrintKata(C);
		ADVKATA();
		i++;
		}
	
	
}

void Load(boolean Default){
	int CurInfo;
	char *Val;
	int i;
	addressSubMap PMap,DestTemp;
	POINT FromTemp,ToTemp;
	
	
	Val=(char*) malloc(2 * sizeof(char));
	
	if(Default){
		STARTKATA(FileMapSaveDefault);
	}else{
		STARTKATA(FileMapSave);
	}
	
	ADVKATA();
	
	ADVKATA();	
	KataToString(CKata,Val);
	i=10*(Val[0]-'0')+(Val[1]-'0');
	CurInfo=i;
	
	ADVKATA();	
	KataToString(CKata,Val);
	i=10*(Val[0]-'0')+(Val[1]-'0');
	Absis(PlayerPos)=i;
	
	ADVKATA();	
	KataToString(CKata,Val);
	i=10*(Val[0]-'0')+(Val[1]-'0');
	Ordinat(PlayerPos)=i;
	ADVKATA();
	
	
	
	
	ADVKATA();
	ADVKATA();
	ADVKATA();
	
	ADVKATA();
	while(CC!='.'){
	KataToString(CKata,Val);
		i=10*(Val[0]-'0')+(Val[1]-'0');
		InsVFirstSubMap(&LMap,i);
		ADVKATA();
	}
	KataToString(CKata,Val);
	i=10*(Val[0]-'0')+(Val[1]-'0');
	InsVFirstSubMap(&LMap,i);
	
	
	CurSubMap=SearchSubMap(LMap,CurInfo);
	
	
	ADVKATA();
	while(CC!='.'){
		ADVKATA();
	}
	ADVKATA();
	ADVKATA();
	ADVKATA();
	ADVKATA();
	
	while(CKata.TabKata[1]!='E'){
		ADVKATA();
		KataToString(CKata,Val);
		i=10*(Val[0]-'0')+(Val[1]-'0');
		PMap=SearchSubMap(LMap,i);
		ADVKATA();
		ADVKATA();
		ADVKATA();
		
		while(CKata.TabKata[1]!='M' && CKata.TabKata[1]!='E'){
		ADVKATA();
		KataToString(CKata,Val);
		i=10*(Val[0]-'0')+(Val[1]-'0');
		Absis(FromTemp)=i;
		ADVKATA();
		ADVKATA();
		KataToString(CKata,Val);
		i=10*(Val[0]-'0')+(Val[1]-'0');
		Ordinat(FromTemp)=i;
		
		ADVKATA();
		ADVKATA();
		KataToString(CKata,Val);
		i=10*(Val[0]-'0')+(Val[1]-'0');
		Absis(ToTemp)=i;
		ADVKATA();
		ADVKATA();
		KataToString(CKata,Val);
		i=10*(Val[0]-'0')+(Val[1]-'0');
		Ordinat(ToTemp)=i;
		
		ADVKATA();
		ADVKATA();
		KataToString(CKata,Val);
		i=10*(Val[0]-'0')+(Val[1]-'0');
		DestTemp=SearchSubMap(LMap,i);
		
		
		ADVKATA();
		ADVKATA();
		
		InsVFirstTele(&Tele(PMap),FromTemp,ToTemp,DestTemp);
		}
		
	}
	
	
	
	/*Versilama
	FILE *load;
	int i,CurInfo;
	char C;
	addressSubMap PMap,DestTemp;
	POINT FromTemp,ToTemp;
	
	CreateEmptySubMap(&LMap);
	
	if(Default){
		load=fopen(FileMapSaveDefault,"r");
	}
	else{
		load=fopen(FileMapSave,"r");
	}
	
	for(i=1;i<=16;i++){
		fscanf(load,"%c",&C);
	}
	
	fscanf(load,"%c",&C);
	i=C-'0';
	fscanf(load,"%c",&C);
	CurInfo=(i*10)+(C-'0');
	
	fscanf(load,"%c",&C);
	fscanf(load,"%c",&C);
	i=C-'0';
	fscanf(load,"%c",&C);
	Absis(PlayerPos)=(i*10)+(C-'0');
	
	fscanf(load,"%c",&C);
	fscanf(load,"%c",&C);
	i=C-'0';
	fscanf(load,"%c",&C);
	Ordinat(PlayerPos)=(i*10)+(C-'0');
	
	
	for(i=1;i<=11;i++){
		fscanf(load,"%c",&C);
	}
	
	
	fscanf(load,"%c",&C);
	while(C=='0'){
		i=C-'0';
		fscanf(load,"%c",&C);
		i=(i*10)+(C-'0');
		InsVFirstSubMap(&LMap,i);
		fscanf(load,"%c",&C);
		fscanf(load,"%c",&C);
	}
	
	CurSubMap=SearchSubMap(LMap,CurInfo);
	
	for(i=1;i<=13;i++){
		fscanf(load,"%c",&C);
	}
	
	
	fscanf(load,"%c",&C);
	while(C=='M'){
		fscanf(load,"%c",&C);
		fscanf(load,"%c",&C);
		fscanf(load,"%c",&C);
		i=C-'0';
		fscanf(load,"%c",&C);
		i=(i*10)+(C-'0');
		PMap=SearchSubMap(LMap,i);
		fscanf(load,"%c",&C);
		fscanf(load,"%c",&C);
		fscanf(load,"%c",&C);
		while(C=='F'){
			fscanf(load,"%c",&C);
			fscanf(load,"%c",&C);
			fscanf(load,"%c",&C);
			fscanf(load,"%c",&C);
			fscanf(load,"%c",&C);
			i=C-'0';
			fscanf(load,"%c",&C);
			Absis(FromTemp)=(i*10)+(C-'0');
			fscanf(load,"%c",&C);
			fscanf(load,"%c",&C);
			i=C-'0';
			fscanf(load,"%c",&C);
			Ordinat(FromTemp)=(i*10)+(C-'0');
			fscanf(load,"%c",&C);
			fscanf(load,"%c",&C);
			fscanf(load,"%c",&C);
			fscanf(load,"%c",&C);
			fscanf(load,"%c",&C);
			i=C-'0';
			fscanf(load,"%c",&C);
			Absis(ToTemp)=(i*10)+(C-'0');
			fscanf(load,"%c",&C);
			fscanf(load,"%c",&C);
			i=C-'0';
			fscanf(load,"%c",&C);
			Ordinat(ToTemp)=(i*10)+(C-'0');
			fscanf(load,"%c",&C);
			fscanf(load,"%c",&C);
			fscanf(load,"%c",&C);
			fscanf(load,"%c",&C);
			fscanf(load,"%c",&C);
			fscanf(load,"%c",&C);
			fscanf(load,"%c",&C);
			fscanf(load,"%c",&C);
			fscanf(load,"%c",&C);
			fscanf(load,"%c",&C);
			i=C-'0';
			fscanf(load,"%c",&C);
			i=(i*10)+(C-'0');
			DestTemp=SearchSubMap(LMap,i);
			InsVFirstTele(&Tele(PMap),FromTemp,ToTemp,DestTemp);
			fscanf(load,"%c",&C);
			fscanf(load,"%c",&C);
		}
	}
	*/
}



/**********************/
/****FINISH_PRODUCT****/
/**********************/
void Game(boolean New){
	char *a;
	addressSubMap CurSubMapTemp;
	
	
	CreateEmptyEnemy(&LEnemy);

	NBrsEff(CurMap)=20;
	NKolEff(CurMap)=20;
	
	a=(char*) malloc (10* sizeof(char));
	if(New){
		Load(true);
	}
	else{
		Load(false);
		LoadPlayerState();
		LoadEnemyList();
	}
	CurSubMapTemp=CurSubMap;
	ImportCurMap(Info(CurSubMap));

    PrintCurMap(Player);
    scanf("%s",a);
	while(mystrcmp(a,"EXIT")) {
		if(!mystrcmp(a,"GU")||!mystrcmp(a,"gu")){
			Move(0,-1);
		}
		else if(!mystrcmp(a,"GD")||!mystrcmp(a,"gd")){
			Move(0,1);
		}
		else if(!mystrcmp(a,"GL")||!mystrcmp(a,"gl")){
			Move(-1,0);
		}
		else if(!mystrcmp(a,"GR")||!mystrcmp(a,"gr")){
			Move(1,0);
		}
        else if(!mystrcmp(a,"SAVE")){
			SaveMap();
			SavePlayerState();
			SaveEnemyList();
		}
		else if(!mystrcmp(a,"LOAD")){
			Load(false);
			LoadPlayerState();
			LoadEnemyList();
			PrintListEnemy(LEnemy);
		}
		else if (!mystrcmp(a,"SKILL")) {
            SkillMenu();
		}
        else {
			printf("NOT GOING ANYWHERE\n");
		}
		if(CurSubMapTemp!=CurSubMap){
			ImportCurMap(Info(CurSubMap));
			CurSubMapTemp=CurSubMap;
		}
		PrintCurMap(Player);
		if(!mystrcmp(a,"GU")||!mystrcmp(a,"gu")){
			printf("Going UP\n");
		}
		else if(!mystrcmp(a,"GD")||!mystrcmp(a,"gd")){
			printf("Going DOWN\n");
		}
		else if(!mystrcmp(a,"GL")||!mystrcmp(a,"gl")){
			printf("Going LEFT\n");
		}
		else if(!mystrcmp(a,"GR")||!mystrcmp(a,"gr")){
			printf("Going RIGHT\n");
		}
		else if (!mystrcmp(a,"SKILL")) {
		}
        else if(!mystrcmp(a,"SAVE")){
			printf("Saved\n");
		}
		else if(!mystrcmp(a,"LOAD")){
			printf("Loaded\n");
		}
		else {
			printf("NOT GOING ANYWHERE\n");
		}
		scanf("%s",a);
	}
}


