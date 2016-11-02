/* File : stacklist.h */
#include "header_dir/stacklist.h"



/* ********* PROTOTYPE REPRESENTASI LOJIK STACK ***************/
boolean IsSEmpty (Stack S)
/* Mengirim true jika Stack kosong: TOP(S) = Nil */
{
	return (Top(S) == Nil);
}
void CreateEmptyS (Stack * S)
/* I.S. sembarang */ 
/* F.S. Membuat sebuah stack S yang kosong */
{
	Top(*S) = Nil;
}
void Push (Stack * S, infotype X)
/* Menambahkan X sebagai elemen Stack S */
/* I.S. S mungkin kosong, X terdefinisi */
/* F.S. X menjadi TOP yang baru jika alokasi X berhasil, */
/*      jika tidak, S tetap */
/* Pada dasarnya adalah operasi Insert First pada list linier */
{
	address P;
	Alokasi(&P,X);
	if (P != Nil) {
		if (IsSEmpty(*S)) {
			Top(*S) = P;
		} else {
			Next(P) = Top(*S);
			Top(*S) = P;
		}
	}
}
void Pop (Stack * S, infotype * X)
/* Menghapus X dari Stack S. */
/* I.S. S tidak mungkin kosong */
/* F.S. X adalah nilai elemen TOP yang lama, */
/*      elemen TOP yang lama didealokasi */
/* Pada dasarnya adalah operasi Delete First pada list linier */
{
	*X = InfoTop(*S);
	if (Next(Top(*S)) == Nil) {
		Dealokasi(Top(*S));
		CreateEmptyS(&*S);
	} else {
		address Pdel = Top(*S);
		Top(*S) = Next(Top(*S));
		Dealokasi(Pdel);
	}
}