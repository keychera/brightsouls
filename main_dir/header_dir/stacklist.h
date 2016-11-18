
/* File : stacklist.h */
#ifndef _STACKLIST_H
#define _STACKLIST_H
#include "boolean.h"
#include "list_str.h"


/* Type stack dengan ciri TOP : */
typedef struct {
	address TOP;  /* alamat TOP: elemen puncak */
} Stack;

/* Selektor */
#define Top(S) (S).TOP
#define InfoTop(S) (S).TOP->Info 


/* ********* PROTOTYPE REPRESENTASI LOJIK STACK ***************/
boolean IsSEmpty (Stack S);
/* Mengirim true jika Stack kosong: TOP(S) = Nil */
void CreateEmptyStack (Stack * S);
/* I.S. sembarang */ 
/* F.S. Membuat sebuah stack S yang kosong */
void Push (Stack * S, infotypestr X);
/* Menambahkan X sebagai elemen Stack S */
/* I.S. S mungkin kosong, X terdefinisi */
/* F.S. X menjadi TOP yang baru jika alokasi X berhasil, */
/*      jika tidak, S tetap */
/* Pada dasarnya adalah operasi Insert First pada list linier */
void Pop (Stack * S, infotypestr *X); //key fix for issue #4
/* Menghapus X dari Stack S. */
/* I.S. S tidak mungkin kosong */
/* F.S. X adalah nilai elemen TOP yang lama, */
/*      elemen TOP yang lama didealokasi */
/* Pada dasarnya adalah operasi Delete First pada list linier */

#endif
