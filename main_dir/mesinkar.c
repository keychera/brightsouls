/* File: mesinkar.c */
/* Implementasi Mesin Karakter */

#include "header_dir/mesinkar.h"
#include <stdio.h>

char CC;
boolean EOP;
boolean EndBaris;

static FILE * pita;
static int retval;

void START(char File[]) {
/* Mesin siap dioperasikan. Pita disiapkan untuk dibaca.
   Karakter pertama yang ada pada pita posisinya adalah pada jendela.
   I.S. : sembarang
   F.S. : CC adalah karakter pertama pada pita. Jika CC != MARK maka EOP akan padam (false).
          Jika CC = MARK maka EOP akan menyala (true) */

	/* Algoritma */
	pita = fopen(File,"r");
	ADV();
}

void ADV() {
/* Pita dimajukan satu karakter.
   I.S. : Karakter pada jendela =
          CC, CC != MARK
   F.S. : CC adalah karakter berikutnya dari CC yang lama,
          CC mungkin = MARK.
		  Jika  CC = MARK maka EOP akan menyala (true) */

	/* Algoritma */
	retval = fscanf(pita,"%c",&CC);
	EndBaris = (CC == MARK);
	EOP = (CC == ENDMARK);
	if (EndBaris) {
		fscanf(pita, "%*[^\n]\n"); //Skip to next line
	}
	if (EOP) {
       fclose(pita);
 	}
}
