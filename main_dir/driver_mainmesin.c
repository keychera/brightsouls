#include <stdio.h>
#include "mesinkata.h"

//Contoh cara menggunakan mesin kata yang baru

int main() {
    char F[50] = "driver_mainmesininput.txt";
    STARTKATA(F);
    while (!EndFile) {
        if (EndKata) {
            printf("\n");
        }
        else {
            PrintKata(CKata);
            printf(" ");
        }
        ADVKATA();
    }
    printf("\n");

    return 0;
}
