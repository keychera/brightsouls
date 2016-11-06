/*
NIM			: 13515052
Nama		: Kevin Jonathan Koswara
Tanggal		: 22 September 2016
Topik		: Mesin kata
Deskripsi	:
*/

#include "header_dir/mesintoken.h"
#include <stdio.h>

boolean EndToken;
Token CToken;

void IgnoreBlank()
/* Mengabaikan satu atau beberapa BLANK
   I.S. : CC sembarang
   F.S. : CC ≠ BLANK atau CC = MARK */
{
	while ((CC == BLANK) && (CC != MARK)) {
        ADV();
    }
}

void STARTTOKEN(char File[])
/* I.S. : CC sembarang
   F.S. : EndToken = true, dan CC = MARK;
          atau EndToken = false, CToken adalah Token yang sudah diakuisisi,
          CC karakter pertama sesudah karakter terakhir Token */
{
	START(File);
    IgnoreBlank();
    if (CC == MARK) {
        EndToken = true;
    }
    else {
        EndToken = false;
        SalinToken();
    }
}

void ADVTOKEN()
/* I.S. : CC adalah karakter pertama kata yang akan diakuisisi
   F.S. : CToken adalah Token terakhir yang sudah diakuisisi,
          CC adalah karakter pertama dari kata berikutnya, mungkin MARK
          Jika CC = MARK, maka EndToken = true
   Proses : Akuisisi kata menggunakan procedure SalinKata */
{
	IgnoreBlank();
    if (CC == MARK) {
        EndToken = true;
    }
    else {
        SalinToken();
    }
}

void SalinToken()
/* Mengakuisisi Token dan menyimpan hasilnya dalam CToken
   I.S. : CC adalah karakter pertama dari Token
   F.S. : CToken berisi Token yang sudah diakuisisi;
          CC = BLANK atau CC = MARK;
          CC adalah karakter sesudah karakter terakhir yang diakuisisi.
          Jika panjang kata melebihi NMax, maka sisa kata "dipotong" */
{
	int nilai;
	if (CC != BLANK) {
		if (CC == '+' || CC == '-' || CC == '*' || CC == '/' || CC == '^') {
			CToken.tkn = CC;
			CToken.val = -1;
			ADV();
		}
		else if (CC == '1' || CC == '2' || CC == '3' || CC == '4' || CC == '5' || CC == '6' || CC == '7' || CC == '8' || CC == '9' || CC == '0') {
			CToken.tkn = 'b';
			CToken.val = 0;
			do {
				switch (CC) {
					case '0' : { nilai = 0; break; }
					case '1' : { nilai = 1; break; }
					case '2' : { nilai = 2; break; }
					case '3' : { nilai = 3; break; }
					case '4' : { nilai = 4; break; }
					case '5' : { nilai = 5; break; }
					case '6' : { nilai = 6; break; }
					case '7' : { nilai = 7; break; }
					case '8' : { nilai = 8; break; }
					case '9' : { nilai = 9; break; }
				}
				CToken.val = CToken.val*10 + nilai;
				ADV();
			} while ((CC != MARK) && (CC != BLANK));
		}
	}
}
