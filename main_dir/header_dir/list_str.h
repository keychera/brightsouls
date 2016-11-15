#ifndef _LIST_H
#define _LIST_H

#include <stdlib.h>

/* Konstanta */
#define Nil NULL

/* Deklarasi infotype */
typedef char* infotypestr;

/* Queue dengan representasi berkait dengan pointer */
typedef struct tElmt * address;
typedef struct tElmt {
	infotypestr Info;
	address Next;
} Elmt; 

#define NextLstr(P) (P)->Next
#define InfoLstr(P) (P)->Info

/* Prototype manajemen memori */
void Alokasi (address *P, infotypestr X);
/* I.S. Sembarang */
/* F.S. Alamat P dialokasi, jika berhasil maka Info(P)=X dan 
        Next(P)=Nil */
/*      P=Nil jika alokasi gagal */
void Dealokasi (address P);
/* I.S. P adalah hasil alokasi, P != Nil */
/* F.S. Alamat P didealokasi, dikembalikan ke sistem */

#endif
