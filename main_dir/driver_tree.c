#include <stdio.h>
#include "tree.h"
#include "mesinkata.h"

boolean EndKata;
Kata CKata;

int main() {
    char file1[50] = "input.txt";
    Tree T;
    CreateEmptyT(&T);
    T = ImportTree(file1);
    PrintTreeT(T);
    printf("\n");
    DelTree(&T);

    return 0;
}
