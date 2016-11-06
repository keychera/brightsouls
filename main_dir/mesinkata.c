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
    while ((CC == BLANK) && (CC != MARK)) {
        ADV();
    }
}

void STARTKATA(char File[])
/* I.S. : CC sembarang
   F.S. : EndKata = true, dan CC = MARK;
          atau EndKata = false, CKata adalah kata yang sudah diakuisisi,
          CC karakter pertama sesudah karakter terakhir kata */
{
    START(File);
    IgnoreBlank();
	if (CC != ENDMARK) {
		if (CC == MARK) {
		    EndKata = true;
		}
		else {
		    EndKata = false;
		    SalinKata();
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
	if (CC != ENDMARK) {
		if (CC == MARK) {
		    EndKata = true;
		}
		else {
			EndKata = false;
		    SalinKata();
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
        if ((CC != MARK) && (CC != BLANK)) {
            i++;
        }
    } while ((CC != MARK) && (CC != BLANK));
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
    char c;
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
