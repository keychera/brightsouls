/* File : queuelist.h */
/* Representasi queue dengan list berkait dengan first (HEAD) dan last (TAIL) */

#include "queuelist.h"


boolean IsQEmpty (Queue Q)
/* Mengirim true jika Q kosong: HEAD(Q)=Nil and TAIL(Q)=Nil */
{
	return ((Head(Q) == Nil) && (Tail(Q) == Nil));
}
int NbElmt(Queue Q)
/* Mengirimkan banyaknya elemen queue. Mengirimkan 0 jika Q kosong */
{
	int n = 0;
	if (!IsQEmpty(Q)) {
		n = 1;
		address P;
		P = Head(Q);
		while (P != Tail(Q)) {
			P = Next(P);
			n++;
		}
	}
	return n;
}
/*** Kreator ***/
void CreateEmptyQ(Queue * Q)
/* I.S. sembarang */
/* F.S. Sebuah Q kosong terbentuk */
{
	Head(*Q) = Nil;
	Tail(*Q) = Nil;
}
/*** Primitif Add/Delete ***/
void Add (Queue * Q, infotype X)
/* Proses: Mengalokasi X dan menambahkan X pada bagian TAIL dari Q
   jika alokasi berhasil; jika alokasi gagal Q tetap */
/* Pada dasarnya adalah proses insert last */
/* I.S. Q mungkin kosong */
/* F.S. X menjadi TAIL, TAIL "maju" */
{
	address P;
	Alokasi(&P,X);
	if (P != Nil) {
		if (IsQEmpty(*Q)) {
			Head(*Q) = P;
			Tail(*Q) = P;
		} else {
			Next(Tail(*Q)) = P;
			Tail(*Q) = P;
		}
	}
}
void Del(Queue * Q, infotype * X)
/* Proses: Menghapus X pada bagian HEAD dari Q dan mendealokasi
   elemen HEAD */
/* Pada dasarnya operasi delete first */
/* I.S. Q tidak mungkin kosong */
/* F.S. X = nilai elemen HEAD pd I.S., HEAD "mundur" */
{
	*X = InfoHead(*Q);
	if (Head(*Q) == Tail(*Q)) {
		Dealokasi(Head(*Q));
		CreateEmptyQ(&*Q);
	} else {
		address Pdel = Head(*Q);
		Head(*Q) = Next(Head(*Q));
		Dealokasi(Pdel);
	}
}