/* File : ListSkill.h */
/* contoh ADT ListSkill berkait dengan representasi fisik pointer  */
/* Representasi addressS dengan pointer */
/* infoskill adalah integer */

#ifndef ListSkill_H
#define ListSkill_H

#include "boolean.h"

#define Nil NULL

typedef struct {
    int ID;
    int level;
}infoskill;
typedef struct tElmtskill *addressS;
typedef struct tElmtskill {
	infoskill info;
	addressS next;
} ElmtSkill;
typedef struct {
	addressS First;
} ListSkill;

/* Definisi ListSkill : */
/* ListSkill kosong : First(L) = Nil */
/* Setiap elemen dengan addressS P dapat diacu Info(P), Next(P) */
/* Elemen terakhir ListSkill : jika addressSnya Last, maka Next(Last)=Nil */

#define ID(P) (P)->info.ID
#define Level(P) (P)->info.level
#define Info(P) (P)->info
#define Next(P) (P)->next
#define First(L) (L).First

/* PROTOTYPE */
/****************** TEST ListSkill KOSONG ******************/
boolean IsEmptyS (ListSkill L);
/* Mengirim true jika ListSkill kosong */

/****************** PEMBUATAN ListSkill KOSONG ******************/
void CreateEmptyS (ListSkill *L);
/* I.S. sembarang             */
/* F.S. Terbentuk ListSkill kosong */

/****************** Manajemen Memori ******************/
addressS AlokasiS (infoskill X);
/* Mengirimkan addressS hasil alokasi sebuah elemen */
/* Jika alokasi berhasil, maka addressS tidak nil, dan misalnya */
/* menghasilkan P, maka Info(P)=X, Next(P)=Nil */
/* Jika alokasi gagal, mengirimkan Nil */
void DealokasiS (addressS *P);
/* I.S. P terdefinisi */
/* F.S. P dikembalikan ke sistem */
/* Melakukan dealokasi/pengembalian addressS P */

/****************** PENCARIAN SEBUAH ELEMEN ListSkill ******************/
addressS SearchS (ListSkill L, int id);
/* Mencari apakah ada elemen ListSkill dengan Info(P)= X */
/* Jika ada, mengirimkan addressS elemen tersebut. */
/* Jika tidak ada, mengirimkan Nil */

/****************** PRIMITIF BERDASARKAN NILAI ******************/
/*** PENAMBAHAN ELEMEN ***/
void InsVFirstS (ListSkill *L, infoskill X);
/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen pertama dengan nilai X jika alokasi berhasil */
void InsVLastS (ListSkill *L, infoskill X);
/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen ListSkill di akhir: elemen terakhir yang baru */
/* bernilai X jika alokasi berhasil. Jika alokasi gagal: I.S.= F.S. */

/*** PENGHAPUSAN ELEMEN ***/
void DelVFirstS (ListSkill *L, infoskill *X);
/* I.S. ListSkill L tidak kosong  */
/* F.S. Elemen pertama ListSkill dihapus: nilai info disimpan pada X */
/*      dan alamat elemen pertama di-dealokasi */
void DelVLastS (ListSkill *L, infoskill *X);
/* I.S. ListSkill tidak kosong */
/* F.S. Elemen terakhir ListSkill dihapus: nilai info disimpan pada X */
/*      dan alamat elemen terakhir di-dealokasi */

/****************** PRIMITIF BERDASARKAN ALAMAT ******************/
/*** PENGHAPUSAN SEBUAH ELEMEN ***/
void DelFirstS (ListSkill *L, addressS *P);
/* I.S. ListSkill tidak kosong */
/* F.S. P adalah alamat elemen pertama ListSkill sebelum penghapusan */
/*      Elemen ListSkill berkurang satu (mungkin menjadi kosong) */
/* First element yg baru adalah suksesor elemen pertama yang lama */
void DelPS (ListSkill *L, int id);
/* I.S. Sembarang */
/* F.S. Jika ada elemen ListSkill beraddressS P, dengan Info(P)=X  */
/* Maka P dihapus dari ListSkill dan di-dealokasi */
/* Jika tidak ada elemen ListSkill dengan Info(P)=X, maka ListSkill tetap */
/* ListSkill mungkin menjadi kosong karena penghapusan */
void DelLastS (ListSkill *L, addressS *P);
/* I.S. ListSkill tidak kosong */
/* F.S. P adalah alamat elemen terakhir ListSkill sebelum penghapusan  */
/*      Elemen ListSkill berkurang satu (mungkin menjadi kosong) */
/* Last element baru adalah predesesor elemen pertama yg lama, */
/* jika ada */
void DelAfterS (ListSkill *L, addressS *Pdel, addressS Prec);
/* I.S. ListSkill tidak kosong. Prec adalah anggota ListSkill  */
/* F.S. Menghapus Next(Prec): */
/*      Pdel adalah alamat elemen ListSkill yang dihapus  */

/****************** PROSES SEMUA ELEMEN ListSkill ******************/
int NbElmtS (ListSkill L);
/* Mengirimkan banyaknya elemen ListSkill; mengirimkan 0 jika ListSkill kosong */

/****************** PROSES TERHADAP ListSkill ******************/
void DelAllS (ListSkill *L);
/* Delete semua elemen ListSkill dan alamat elemen di-dealokasi */

#endif
