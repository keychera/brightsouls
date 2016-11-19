/* File: mesinkata.c */
/* Definisi Mesin Kata: Model Akuisisi Versi I */

#include "header_dir/mesinkata.h"
#include "header_dir/mesinkar.h"
#include <stdio.h>

/* State Mesin Kata */
boolean EndFile;
boolean EndKata;
Kata CKata;

void IgnoreBlank()
/* Mengabaikan satu atau beberapa BLANK
   I.S. : CC sembarang
   F.S. : CC ≠ BLANK atau CC = MARK */
{
    while (((CC == BLANK) || (CC == ENTER) || (CC == ENTER2)) && (CC != MARK)) {
        ADV();
    }
}

void STARTKATA(char File[])
/* I.S. : CC sembarang
   F.S. : EndKata = true, dan CC = MARK;
          atau EndKata = false, CKata adalah kata yang sudah diakuisisi,
          CC karakter pertama sesudah karakter terakhir kata */
{
    EndKata = false;
    EndFile = false;
    START(File);
    IgnoreBlank();
	if (CC != ENDMARK) {
		if (EndKata) {
            ADV();
            EndKata = false;
        }
		if (CC == MARK) {
		    EndKata = true;
		}
		else {
			EndKata = false;
		    SalinKata();
			IgnoreBlank();
		}
	} else {
		EndFile = true;
	}
}

void ADVKATA()
/* I.S. : CC adalah karakter pertama kata yang akan diakuisisi
   F.S. : CKata adalah kata terakhir yang sudah diakuisisi,
          CC adalah karakter pertama dari kata berikutnya, mungkin MARK
          Jika CC = MARK, EndKata = true.
   Proses : Akuisisi kata menggunakan procedure SalinKata */
{
	IgnoreBlank();
	if (CC != ENDMARK) { //moved here
    if (EndKata) {
        ADV();
        IgnoreBlank();
        EndKata = false;
    }
	//if (CC != ENDMARK) { fix - moved upwards - it is perceived wrong because it differs from original
		if (CC == MARK) {
		    EndKata = true;
		}
		else {
			EndKata = false;
		    SalinKata();
			IgnoreBlank();
		}
	} else {
		EndFile = true;
	}
}

void SalinKata()
/* Mengakuisisi kata, menyimpan dalam CKata
   I.S. : CC adalah karakter pertama dari kata
   F.S. : CKata berisi kata yang sudah diakuisisi;
          CC = BLANK atau CC = MARK;
          CC adalah karakter sesudah karakter terakhir yang diakuisisi.
          Jika panjang kata melebihi NMax, maka sisa kata "dipotong" */
{
    int i = 1;
    do {
        if (i <= NMax) {
            CKata.TabKata[i] = CC;
        }
        ADV();
        if ((CC != MARK) && (CC != BLANK) && (CC != ENTER) && (CC != ENTER2) && (CC != ENDMARK)) {
            i++;
        }
    } while ((CC != MARK) && (CC != BLANK) && (CC != ENTER) && (CC != ENTER2) && (CC != ENDMARK));
    if (i > NMax) {
        i = NMax;
    }
    CKata.Length = i;
}

int KataToInteger(Kata K)
/* Menghasilkan nilai integer dari kata, jika tidak bisa menghasilkan -1 */
{
    int i = 1;
    int sum = 0;
    boolean valid = true;
    boolean minus = false;
    char c;
    if ((K.Length > 0) && (K.TabKata[1] == '-')) {
        minus = true;
        i++;
    }
    while ((i <= K.Length) && (valid)) {
        c = K.TabKata[i];
        if ((c == '0') || (c == '1') || (c == '2') || (c == '3') || (c == '4') || (c == '5') || (c == '6') || (c == '7') || (c == '8') || (c == '9')) {
            sum = sum*10 + ((int) c - (int) '0');
            i++;
        }
        else {
            valid = false;
        }
    }
    if (valid) {
        if (minus) {
            sum *= -1;
        }
        return sum;
    }
    else {
        return -1;
    }
}

void KataToString(Kata K, char * c){
//WARNING!! STRING STARTING INDEX AT 0
	int i = 1;
	while (i <= K.Length){
		c[i-1] = K.TabKata[i];
		i++;
	}
}

void PrintKata(Kata K)
// Prosedur untuk print kata
{
    int i;
    for (i=1; i<=K.Length; i++) {
        printf("%c",K.TabKata[i]);
    }
}

Kata InputKata()
// Fugsi untuk menerima input dari pengguna
{
    Kata input;
    char c;
    int i = 0;
    do {
        scanf("%c",&c);
        if (c != '\n') {
            i++;
            input.TabKata[i] = c;
        }
    } while (c != '\n');
    input.Length = i;
    return input;
}

boolean IsKataSama (Kata K1, Kata K2)
// Mengecek apakah K1 dan K2 sama
{
    boolean sama;
    int i;
    if (K1.Length != K2.Length) {
        return false;
    }
    else {
        sama = true;
        for (i=1; i<=K1.Length; i++) {
            if (K1.TabKata[i] != K2.TabKata[i]) {
                sama = false;
                break;
            }
        }
        return sama;
    }
}
