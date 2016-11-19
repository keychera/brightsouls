#ifndef MAP_H
#define MAP_H

#include <stdlib.h>
#include <stdio.h>
#include "brightsoul.h" //key edit for compatibility
#include "boolean.h"
#include "point.h"
#include <string.h>

#define Nil NULL

#define HSizeMap 10
#define WSizeMap 10

/* moved to brightsoul.h for more global usage key edit
#define RED   "\x1B[31m"    //merah
#define GRN   "\x1B[32m"    //hijau
#define YEL   "\x1B[33m"    //kuning
#define BLU   "\x1B[34m"    //biru
#define MAG   "\x1B[35m"    //merah muda
#define CYN   "\x1B[36m"    //biru muda
#define WHT   "\x1B[37m"    //putih
#define RESET "\x1B[0m"     //reset warna
#define clear() printf("\e[2J\e[H")
*/
//#define FileMap "../data_dir/map.txt" //key edit for compatibility - nope not working this way - moved to map.c

char CurMap[HSizeMap][WSizeMap];

typedef struct tElmtlistTele *addressTele;
typedef struct tElmtlistSubMap *addressSubMap;

typedef struct tElmtlistTele {

	POINT From;
	POINT To;
	addressSubMap Destination;
	addressTele next;
} ElmtListTele;
typedef struct{
	addressTele First;
}	ListTele;

typedef  int infotypeSubMap;
typedef struct tElmtlistSubMap {
	infotypeSubMap info;
	ListTele Tele;
	addressSubMap next;
} ElmtListSubMap;
typedef struct {
	addressSubMap First;
} ListSubMap;

/*Selektor*/
#define From(P) (P)->From
#define To(P) (P)->To
#define Destination(P) (P)->Destination
#define Next(P) (P)->next
#define Info(P) (P)->info
#define Tele(P) (P)->Tele
#define First(L) (L).First
/*********************/
/*****LIST SUBMAP*****/
/*********************/

void PrintInfoSubMap(ListSubMap L);
/*Memprint informasi Elemen pada List SubMap L. Untuk debugging*/

addressSubMap AlokasiSubMap (infotypeSubMap X);
/*Memesan alamat dalam memori untuk sebuah elemen list submap dengan
info(P) X, Tele(P).First Nil, dan Next(P) Nil.*/

void DealokasiSubMap (addressSubMap P);
/*Mengirim Elemen SubMap beralamat P ke Limbo*/

addressSubMap SearchSubMap (ListSubMap L,infotypeSubMap X);
/*Mengembalikan addressSubMap dengan info X pertama dalam list SubMap
LSM*/

void InsVFirstSubMap (ListSubMap *L, infotypeSubMap X);
/*Memasukan elemen dengan info X pada awal List*/

void DelSubMap (ListSubMap *L, addressSubMap P, infotypeSubMap *X);
/*Menghapus elemen beralamatkan P dari List. Info(P) ditampung dalam X.
lalu didealokasi. Jika tidak ada P dalam List, tidak ada perubahan*/

/*********************/
/******LIST TELE******/
/*********************/
boolean IsEmptyTele(ListTele L);
/*Menentukan apakah List Tele L kosong*/

void CreateEmptyTele(ListTele L);
/*Mengosongkan List Tele L*/

addressTele AlokasiTele (POINT From,POINT To, addressSubMap Dest);
/*Memesan memori untuk elemen List Tele. Next bernilai nil*/

void InsVFirstTele(ListTele *L, POINT From,POINT To, addressSubMap Dest);
/*Menginsert Elemen Tele dengan parameter From To dan Destination ke
List Tele L*/

addressTele SearchPOINTTele(ListTele L,POINT P);
/*Mengembalikan alamat Tele yang memiliki From yang sama dengan P.
Mengembalikkan Nil jika tidak ditemukan*/

/*********************/
/*******BERSAMA*******/
/*********************/
void ConnectSubMap(ListSubMap *L, infotypeSubMap X1,POINT C1 ,infotypeSubMap X2,POINT C2);
/*Menyambungkan 2 submap yaitu submap X1 pada koordinat C1 dan submap
X2 padaa koordinat C2*/


/*********************/
/******MAIN_GAME******/
/*********************/
void CreateEmptyCurMap();
/*Mengosongkan CurMap. Mengisinya dengan '#'*/

char IntToChar(int X);
/*Mengembalikan integer kurang dari 10 X dalam bentuk char.*/

void ImportCurMap(infotypeSubMap X);
/*Mengimpor map dengan id X dan memasukannya ke dalam CurMap*/

void PrintCurMap(POINT Player);
/*Memprint isi dari CurMap. Player ada pada korrdinatnya*/

void Move(POINT *P,float X, float Y);
/*Memindahkan koordinat player sejauh X,Y. jika ada dinding atau batas
terluar peta, tidak jadi pindah*/

void InitGame(ListSubMap *L);
/*Menginisialisasi game. Jalankan sebelum prosedur game*/

void Game(ListSubMap *L);
/*I.S. Game sudah di inisialisasi*/
/*Mengimpor map dari file eksternal dan menampilkan game dalam mode peta.
saat ini tidak ada cara untuk keluar dari mode peta karena loop infinite*/


#endif
