/* File : tree.h */
/* ADT Tree */
/* Representasi berkait dengan addressT adalah pointer */
/* infotree adalah integer */

#ifndef tree_H
#define tree_H

#include "boolean.h"

#define Nil NULL

/* Definisi Type Data */
typedef int infotree;
typedef struct tElmtTree *addressT;
typedef struct tElmtTree {
	infotree info;
	addressT left;
	addressT right;
} ElmtTree;
typedef addressT Tree;

/* Definisi Tree : */
/* List kosong : Root(L) = Nil*/
/* Setiap elemen dengan addressT P dapat diacu Info(P), Left(P), Right(P) */

/* Notasi Akses */
#define Info(P) (P)->info
#define Left(P) (P)->left
#define Right(P) (P)->right

/* PROTOTYPE */
/****************** TEST TREE KOSONG ******************/
boolean IsEmptyT (Tree T);
/* Mengirim true jika tree kosong. Lihat definisi di atas. */

/****************** PEMBUATAN LIST KOSONG ******************/
void CreateEmptyT (Tree *T);
/* I.S. L sembarang  */
/* F.S. Terbentuk tree kosong. Lihat definisi di atas. */

/****************** Manajemen Memori ******************/
addressT AlokasiT (infotree X);
/* Mengirimkan addressT hasil alokasi sebuah elemen */
/* Jika alokasi berhasil, maka addressT tidak nil. */
/* Misalnya: menghasilkan P, maka Info(P)=X, Left(P)=Nil, Right(P)=Nil */
/* Jika alokasi gagal, mengirimkan Nil. */
void DealokasiT (addressT P);
/* I.S. P terdefinisi */
/* F.S. P dikembalikan ke sistem */
/* Melakukan dealokasi/pengembalian addressT P */

/****************** PENCARIAN SEBUAH ELEMEN LIST ******************/
addressT SearchT (Tree T, infotree X);
/* Mencari apakah ada elemen tree dengan Info(P)=X menggunakan algoritma DFS */
/* Jika ada, mengirimkan addressT elemen tersebut. */
/* Jika tidak ada, mengirimkan Nil */
addressT SearchPrecT (Tree T, infotree X);
/* Mencari apakah ada elemen tree sebelum elemen dengan Info(P)=X menggunakan algoritma DFS */
/* Jika ada, mengirimkan addressT elemen tersebut. */
/* Jika tidak ada, mengirimkan Nil */

/*********************** PRIMITIF PADA TREE ***********************/
/*********** PENAMBAHAN ELEMEN ***********/
void InsertRoot(Tree *T, infotree X);
/* I.S. T sembarang */
/* F.S. Alokasi tempat untuk X dan Root(T) = X jika alokasi berhasil */
void InsertLeft(Tree *T, infotree X);
/* I.S. T tidak kosong */
/* F.S. Alokasi tempat untuk X dan Left(Root(T)) = X jika alokasi berhasil */
void InsertRight(Tree *T, infotree X);
/* I.S. T tidak kosong */
/* F.S. Alokasi tempat untuk X dan Right(Root(T)) = X jika alokasi berhasil */

/*********** PENGGABUNGAN TREE ***********/
Tree CreateTree (infotree rootItem, infotree leftItem, infotree rightItem);
/* Fungsi mengembalikan sebuah tree T dengan Info(Root(T)) = rootItem, */
/* Info(Left(T)) = leftItem, Info(Right(T)) = rightItem */
Tree CombineTree (infotree rootItem, Tree leftTree, Tree rightTree);
/* Fungsi mengembalikan sebuah tree T dengan Info(Root(T)) = rootItem, */
/* Left(T) = Root(leftTree), Right(T) = Root(rightTree) */
void ImportTree (char File[], Tree *T);
/* Fungsi membentuk tree dari data yang ada di file eksternal */

/************ PEMECAHAN TREE ************/
void DetachLeft (Tree *T, Tree *leftTree);
/* I.S. T sembarang */
/* F.S. leftTree adalah subtree Left(T) dan Left(T) = Nil */
void DetachRight (Tree *T, Tree *rightTree);
/* I.S. T sembarang */
/* F.S. rightTree adalah subtree Right(T) dan Right(T) = Nil */

/*********** PENGHAPUSAN TREE ***********/
void DelTree (Tree *T);
/* I.S. T sembarang */
/* F.S. Seluruh elemn T di dealokasi dan T menjadi kosong */

/*********** PROSEDUR LAINNYA ***********/
void SaveTree (Tree T);
/* I.S. T sembarang */
/* F.S. menuliskan ke layar isi tree dengan format */
/* [Info(P)] [Info(Left(P))] [Info(Right(P))] */
/* dengan P adalah alamat dari setiap elemen T */
void PrintSubTreeT (addressT P, int n, int a[]);
/* I.S. P anggota tree T */
/* F.S. Menampilkan tree T dengan gambar pohon ke samping */
void PrintTreeT (Tree T);
/* I.S. T sembarang */
/* F.S. Menampilkan tree T dengan gambar pohon ke samping */

#endif
