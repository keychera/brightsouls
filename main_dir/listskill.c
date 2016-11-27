/*
NIM			: 13515052
Nama		: Kevin Jonathan Koswara
Tanggal		: 20 Oktober 2016
Topik		: ListSkill linear
Deskripsi	:
*/

#include "header_dir/listskill.h"
#include <stdio.h>
#include <stdlib.h>

/* PROTOTYPE */
/****************** TEST ListSkill KOSONG ******************/
boolean IsEmptyS (ListSkill L)
/* Mengirim true jika ListSkill kosong */
{
    return (First(L) == Nil);
}

/****************** PEMBUATAN ListSkill KOSONG ******************/
void CreateEmptyS (ListSkill *L)
/* I.S. sembarang             */
/* F.S. Terbentuk ListSkill kosong */
{
    First(*L) = Nil;
}

/****************** Manajemen Memori ******************/
addressS AlokasiS (infoskill X)
/* Mengirimkan addressS hasil alokasi sebuah elemen */
/* Jika alokasi berhasil, maka addressS tidak nil, dan misalnya */
/* menghasilkan P, maka Info(P)=X, Next(P)=Nil */
/* Jika alokasi gagal, mengirimkan Nil */
{
    addressS P = malloc(sizeof(ElmtSkill));
    if (P != Nil) {
        Info(P) = X;
        Next(P) = Nil;
    }
    return P;
}
void DealokasiS (addressS *P)
/* I.S. P terdefinisi */
/* F.S. P dikembalikan ke sistem */
/* Melakukan dealokasi/pengembalian addressS P */
{
    free(*P);
}

/****************** PENCARIAN SEBUAH ELEMEN ListSkill ******************/
addressS SearchS (ListSkill L, int id)
/* Mencari apakah ada elemen ListSkill dengan Info(P)= X */
/* Jika ada, mengirimkan addressS elemen tersebut. */
/* Jika tidak ada, mengirimkan Nil */
{
    addressS P = First(L);
    while ((P != Nil) && (ID(P) != id)) {
        P = Next(P);
    }
    return P;
}

/****************** PRIMITIF BERDASARKAN NILAI ******************/
/*** PENAMBAHAN ELEMEN ***/
void InsVFirstS (ListSkill *L, infoskill X)
/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen pertama dengan nilai X jika alokasi berhasil */
{
    addressS P = AlokasiS(X);
    Next(P) = First(*L);
    First(*L) = P;
}
void InsVLastS (ListSkill *L, infoskill X)
/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen ListSkill di akhir: elemen terakhir yang baru */
/* bernilai X jika alokasi berhasil. Jika alokasi gagal: I.S.= F.S. */
{
    addressS P = First(*L);
    if (IsEmptyS(*L)) {
        First(*L) = AlokasiS(X);
    }
    else {
        while (Next(P) != Nil) {
            P = Next(P);
        }
        Next(P) = AlokasiS(X);
    }
}

/*** PENGHAPUSAN ELEMEN ***/
void DelVFirstS (ListSkill *L, infoskill *X)
/* I.S. ListSkill L tidak kosong  */
/* F.S. Elemen pertama ListSkill dihapus: nilai info disimpan pada X */
/*      dan alamat elemen pertama di-dealokasi */
{
    addressS P = First(*L);
    *X = Info(P);
    First(*L) = Next(P);
    DealokasiS(&P);
}
void DelVLastS (ListSkill *L, infoskill *X)
/* I.S. ListSkill tidak kosong */
/* F.S. Elemen terakhir ListSkill dihapus: nilai info disimpan pada X */
/*      dan alamat elemen terakhir di-dealokasi */
{
    addressS P = First(*L);
    addressS P1;
    if (Next(P) == Nil) {               // kasus hanya 1 elemen
        *X = Info(P);
        First(*L) = Nil;
        DealokasiS(&P);
    }
    else {
        while (Next(Next(P)) != Nil) {
            P = Next(P);
        }
        P1 = Next(P);
        *X = Info(P1);
        Next(P) = Nil;
        DealokasiS(&P1);
    }
}

/****************** PRIMITIF BERDASARKAN ALAMAT ******************/
/*** PENGHAPUSAN SEBUAH ELEMEN ***/
void DelFirstS (ListSkill *L, addressS *P)                 //22 23
/* I.S. ListSkill tidak kosong */
/* F.S. P adalah alamat elemen pertama ListSkill sebelum penghapusan */
/*      Elemen ListSkill berkurang satu (mungkin menjadi kosong) */
/* First element yg baru adalah suksesor elemen pertama yang lama */
{
    *P = First(*L);
    First(*L) = Next(First(*L));
}
void DelPS (ListSkill *L, int id)                 //18 19 20
/* I.S. Sembarang */
/* F.S. Jika ada elemen ListSkill beraddressS P, dengan Info(P)=X  */
/* Maka P dihapus dari ListSkill dan di-dealokasi */
/* Jika tidak ada elemen ListSkill dengan Info(P)=X, maka ListSkill tetap */
/* ListSkill mungkin menjadi kosong karena penghapusan */
{
    addressS P = First(*L);
    addressS Prec = Nil;
    if (!IsEmptyS(*L)) {
        while ((P != Nil) && (ID(P) != id)) {
            Prec = P;
            P = Next(P);
        }
        if (P != Nil) {                 // ketemu
            if (P == First(*L)) {          // ketemu di elemen pertama
                First(*L) = Next(P);
                DealokasiS(&P);
            }
            else {
                Next(Prec) = Next(P);
                DealokasiS(&P);
            }
        }
    }
}
void DelLastS (ListSkill *L, addressS *P)
/* I.S. ListSkill tidak kosong */
/* F.S. P adalah alamat elemen terakhir ListSkill sebelum penghapusan  */
/*      Elemen ListSkill berkurang satu (mungkin menjadi kosong) */
/* Last element baru adalah predesesor elemen pertama yg lama, */
/* jika ada */
{
    addressS P1 = First(*L);
    if (Next(P1) == Nil) {
        *P = P1;
        First(*L) = Nil;
    }
    else {
        while (Next(Next(P1)) != Nil) {
            P1 = Next(P1);
        }
        *P = Next(P1);
        Next(P1) = Nil;
    }
}
void DelAfterS (ListSkill *L, addressS *Pdel, addressS Prec)                    //17
/* I.S. ListSkill tidak kosong. Prec adalah anggota ListSkill  */
/* F.S. Menghapus Next(Prec): */
/*      Pdel adalah alamat elemen ListSkill yang dihapus  */
{
    *Pdel = Next(Prec);
    if (Next(Prec) != Nil) {
        Next(Prec) = Next(Next(Prec));
    }
}

int NbElmtS (ListSkill L)
/* Mengirimkan banyaknya elemen ListSkill; mengirimkan 0 jika ListSkill kosong */
{
    int n = 0;
    addressS P = First(L);
    while (P != Nil) {
        P = Next(P);
        n++;
    }
    return n;
}

/****************** PROSES TERHADAP ListSkill ******************/
void DelAllS (ListSkill *L)
/* Delete semua elemen ListSkill dan alamat elemen di-dealokasi */
{
    addressS P = First(*L);
    addressS P1;
    while (P != Nil) {
        P1 = P;
        P = Next(P);
        DealokasiS(&P1);
    }
    CreateEmptyS(L);
}
