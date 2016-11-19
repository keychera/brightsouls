/* File : queue.c */
/* Definisi ADT Queue dengan representasi array secara eksplisit dan alokasi dinamik */
/* Model Implementasi Versi III dengan circular buffer */

#include <stdio.h>
#include <stdlib.h>
#include "header_dir/queue.h"

/* ********* Prototype ********* */
boolean IsEmptyQueue (Queue Q)
/* Mengirim true jika Q kosong: lihat definisi di header */
{
	return ((Head(Q) == NilQ) && (Tail(Q) == NilQ));
}
boolean IsFullQueue (Queue Q)
/* Mengirim true jika tabel penampung elemen Q sudah penuh */
/* yaitu mengandung elemen sebanyak MaxEl */
{
	return (NBElmtQueue(Q) == MaxEl(Q));
}
int NBElmtQueue (Queue Q)
/* Mengirimkan banyaknya elemen queue. Mengirimkan 0 jika Q kosong */
{
	int n;
	if (IsEmptyQueue(Q)) {
		n = 0;
	} else {
		n = Tail(Q) - Head(Q) + 1;
		if (Head(Q) > Tail(Q)) {
			n += MaxEl(Q);
		}
	}
	return n;
}

/* *** Kreator *** */
void CreateEmptyQueue (Queue * Q, int Max)
/* I.S. sembarang */
/* F.S. Sebuah Q kosong terbentuk dan salah satu kondisi sbb: */
/* Jika alokasi berhasil, Tabel memori dialokasi berukuran Max */
/* atau : jika alokasi gagal, Q kosong dg MaxEl=0 */
/* Proses : Melakukan alokasi,Membuat sebuah Q kosong */
{
	(*Q).T = (infotypeQ*) malloc ((Max+1) * sizeof(infotypeQ));
	if ((*Q).T != NULL) {
		Head(*Q) = NilQ;
		Tail(*Q) = NilQ;
		MaxEl(*Q) = Max;
	} else {
		MaxEl(*Q) =NilQ;
	}
	
}

/* *** Destruktor *** */
void DeAlokasiQueue(Queue * Q)
/* Proses: Mengembalikan memori Q */
/* I.S. Q pernah dialokasi */
/* F.S. Q menjadi tidak terdefinisi lagi, MaxEl(Q) diset 0 */
{
	MaxEl(*Q) = NilQ;
	free((*Q).T);
}

void Add (Queue * Q, infotypeQ X)
/* Proses: Menambahkan X pada Q dengan aturan FIFO */
/* I.S. Q mungkin kosong, tabel penampung elemen Q TIDAK penuh */
/* F.S. X menjadi TAIL yang baru, TAIL "maju" dengan mekanisme circular buffer */
{
	if (IsEmptyQueue(*Q)) {
		Head(*Q) = 1;
		Tail(*Q) = 1;
		InfoHead(*Q) = X;
	} else {
		Tail(*Q) = (Tail(*Q) + 1) % MaxEl(*Q);
		if (Tail(*Q) == 0) Tail(*Q) = MaxEl(*Q);
		InfoTail(*Q) = X;
	}
}
void Del(Queue * Q, infotypeQ * X)
/* Proses: Menghapus X pada Q dengan aturan FIFO */
/* I.S. Q tidak mungkin kosong */
/* F.S. X = nilai elemen HEAD pd I.S., HEAD "maju" dengan mekanisme circular buffer; 
        Q mungkin kosong */
{
	*X = InfoHead(*Q);
	if (Head(*Q) == Tail(*Q)) {
		Head(*Q) = NilQ;
		Tail(*Q) = NilQ;
	} else {
		Head(*Q) = (Head(*Q) + 1) % MaxEl(*Q);
		if (Head(*Q) == 0) Head(*Q) = MaxEl(*Q);
	}
}

//debugging purposes
void printQ(Queue *Q)
{
	int i,n;
	infotypeQ x;
	printf("\nnb elmt %d\n",NBElmtQueue(*Q));
	printf("head idx %d\n",Head(*Q));
	printf("tail idx %d\n",Tail(*Q));
	n = NBElmtQueue(*Q);
	for(i = 1;i <= n;i++) {
		Del(&*Q,&x);
		printf("%d. %c | ",i,x);
		printf("head idx %c |",Head(*Q));
		printf(" tail idx %c\n",Tail(*Q));
	}
}
