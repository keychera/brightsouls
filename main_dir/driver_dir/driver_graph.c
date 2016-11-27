#include "header_dir/map.h"

int main(){
	ListSubMap L;
	infotypeSubMap X,X1,X2;
	addressSubMap P1;
	addressTele P2;
	
	
	CreateEmptySubMap(&L);
	if(IsEmptySubMap(L)){
		printf("ListKosong. Lancar\n\n");
	}
	else{
		printf("Error. CreateEmpty atau IsEmpty gagal\n\n");
	}
	PrintInfoSubMap(L);
	
	P1=AlokasiSubMap(1);
	if(P1!=Nil){
		if(Info(P1)==1){
			printf("Alokasi node berhasil\n\n");
		}
		else{
			printf("Alokasi node gagal\n\n");
		}
	}
	
	P2=AlokasiTele(MakePOINT(1,2),MakePOINT(3,4),Nil);
	if(Absis(From(P2))==1 && Ordinat(From(P2))==2 && Absis(To(P2))==3 && Ordinat(To(P2))==4 ){
		printf("Alokasi Koneksi berhasil\n\n");
	}
	else{
		printf("Alokasi Koneksi Gagal\n\n");
	}
	
	First(Tele(P1))=P2;
	P2=SearchPOINTTele(Tele(P1),MakePOINT(1,2));
	if(Absis(From(P2))==1 && Ordinat(From(P2))==2 ){
		printf("Search Tele berhasil\n\n");
	}
	else{
		printf("Search Tele gagal\n\n");
	}
	DealokasiSubMap(P1);
	
	
	printf("Mulai Isi dengan Node (-999 untuk berhenti)\n");
	scanf("%d",&X);
	while(X!=-999){
		InsVFirstSubMap(&L,X);
		printf("\n");
		PrintInfoSubMap(L);
		printf("\n");
		printf("Isi dengan Node(-999 untuk berhenti)\n");
		scanf("%d",&X);
	}
	PrintInfoSubMap(L);
	
	P1=SearchSubMap(L,2);
	if(P1!=Nil){
		printf("\nAda Node berId 2 di dalam graf\n\n");
	}
	else{
		printf("\nTidak Ada Node berId 2 di dalam graf\n\n");	
	}
	
	printf("Mulai menyambungkan node)(-999 untuk berhenti)\n");
	printf("Sambungkan node berid :");
	scanf("%d",&X1);
	while(X1!=-999){
		printf("dengan node berid :");
		scanf("%d",&X2);
		ConnectSubMap(&L,X1,MakePOINT(0,0),X2,MakePOINT(0,0));
		printf("\n");
		PrintInfoSubMap(L);
		printf("\n");
		printf("Sambungkan node berid (-999 untuk berhenti):");
		scanf("%d",&X1);
	}
	
	
}
