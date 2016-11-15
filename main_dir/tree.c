#include <stdio.h>
#include <stdlib.h>
#include "header_dir/tree.h" //key edit
#include "header_dir/mesinkata.h" //key edit

boolean EndKata;
Kata CKata;

/* PROTOTYPE */
/****************** TEST TREE KOSONG ******************/
boolean IsEmptyT (Tree T)
/* Mengirim true jika tree kosong. Lihat definisi di atas. */
{
    return (T == Nil);
}

/****************** PEMBUATAN LIST KOSONG ******************/
void CreateEmptyT (Tree *T)
/* I.S. L sembarang  */
/* F.S. Terbentuk tree kosong. Lihat definisi di atas. */
{
    *T = Nil;
}

/****************** Manajemen Memori ******************/
addressT AlokasiT (infotree X)
/* Mengirimkan addressT hasil alokasi sebuah elemen */
/* Jika alokasi berhasil, maka addressT tidak nil. */
/* Misalnya: menghasilkan P, maka Info(P)=X, Left(P)=Nil, Right(P)=Nil */
/* Jika alokasi gagal, mengirimkan Nil. */
{
    addressT P = malloc(sizeof(ElmtTree));
    if (P != Nil) {
        Info(P) = X;
        Left(P) = Nil;
        Right(P) = Nil;
    }
    return P;
}
void DealokasiT (addressT P)
/* I.S. P terdefinisi */
/* F.S. P dikembalikan ke sistem */
/* Melakukan dealokasi/pengembalian addressT P */
{
    free(P);
}

addressT SearchT (Tree T, infotree X)
/****************** PENCARIAN SEBUAH ELEMEN LIST ******************/
/* Fungsi rekursif untuk search */
{
    addressT P1;
    if (Info(T) == X) {
        return T;
    }
    else {
        P1 = Nil;
        if (Left(T) != Nil) {
            P1 = SearchT(Left(T),X);
        }
        if ((P1 == Nil) && (Right(T) != Nil)) {
            P1 = SearchT(Right(T),X);
        }
        return P1;
    }
}
addressT SearchPrecT (Tree T, infotree X)
/* Fungsi rekursif untuk search */
{
    addressT P1;
    if (((Left(T) != Nil) && (Info(Left(T)) == X)) || ((Right(T) != Nil) && (Info(Right(T)) == X))) {
        return T;
    }
    else {
        P1 = Nil;
        if (Left(T) != Nil) {
            P1 = SearchPrecT(Left(T),X);
        }
        if ((P1 == Nil) && (Right(T) != Nil)) {
            P1 = SearchPrecT(Right(T),X);
        }
        return P1;
    }
}

/*********************** PRIMITIF PADA TREE ***********************/
/*********** PENAMBAHAN ELEMEN ***********/
void InsertRoot(Tree *T, infotree X)
/* I.S. T sembarang */
/* F.S. Alokasi tempat untuk X dan Root(T) = X jika alokasi berhasil */
{
    *T = AlokasiT(X);
}
void InsertLeft(Tree *T, infotree X)
/* I.S. T tidak kosong */
/* F.S. Alokasi tempat untuk X dan Left(Root(T)) = X jika alokasi berhasil */
{
    Left(*T) = AlokasiT(X);
}
void InsertRight(Tree *T, infotree X)
/* I.S. T tidak kosong */
/* F.S. Alokasi tempat untuk X dan Right(Root(T)) = X jika alokasi berhasil */
{
    Right(*T) = AlokasiT(X);
}

/*********** PENGGABUNGAN TREE ***********/
Tree CreateTree (infotree rootItem, infotree leftItem, infotree rightItem)
/* Fungsi mengembalikan sebuah tree T dengan Info(Root(T)) = rootItem, */
/* Info(Left(T)) = leftItem, Info(Right(T)) = rightItem */
{
    Tree T;
    InsertRoot(&T,rootItem);
    if (T != Nil) {
        if (leftItem != -1) {
            InsertLeft(&T,leftItem);
        }
        if (rightItem != -1) {
            InsertRight(&T,rightItem);
        }
    }
    return T;
}
Tree CombineTree (infotree rootItem, Tree leftTree, Tree rightTree)
/* Fungsi mengembalikan sebuah tree T dengan Info(Root(T)) = rootItem, */
/* Left(T) = Root(leftTree), Right(T) = Root(rightTree) */
{
    Tree T;
    InsertRoot(&T,rootItem);
    if (T != Nil) {
        if (leftTree != Nil) {
            Left(T) = leftTree;
        }
        if (rightTree != Nil) {
            Right(T) = rightTree;
        }
    }
    return T;
}
void ImportTree (char File[], Tree *T)
/* Fungsi membentuk tree dari data yang ada di file eksternal */
{
    addressT P;
    int temp;
    STARTKATA(File);
    temp = KataToInteger(CKata);
    *T = AlokasiT(temp);
    ADVKATA();
    temp = KataToInteger(CKata);
    if (temp != -1) {
        Left(*T) = AlokasiT(temp);
    }
    ADVKATA();
    temp = KataToInteger(CKata);
    if (temp != -1) {
        Right(*T) = AlokasiT(temp);
    }
    ADVKATA();
    while (!EndFile) {
        if (EndKata) {
            ADVKATA();
        }
        else {
            temp = KataToInteger(CKata);
            P = SearchT(*T,temp);
            if (P != Nil) {
                ADVKATA();
                temp = KataToInteger(CKata);
                if (temp != -1) {
                    Left(P) = AlokasiT(temp);
                }
                ADVKATA();
                temp = KataToInteger(CKata);
                if (temp != -1) {
                    Right(P) = AlokasiT(temp);
                }
            }
            else {
                ADVKATA();
                ADVKATA();
            }
            ADVKATA();
        }
    }
}

/************ PEMECAHAN TREE ************/
void DetachLeft (Tree *T, Tree *leftTree)
/* I.S. T sembarang */
/* F.S. leftTree adalah subtree Left(T) dan Left(T) = Nil */
{
    Tree T1;
    T1 = Left(*T);
    if (Left(*T) != Nil) {
        Left(*T) = Nil;
    }
    *leftTree = T1;
}
void DetachRight (Tree *T, Tree *rightTree)
/* I.S. T sembarang */
/* F.S. rightTree adalah subtree Right(T) dan Right(T) = Nil */
{
    Tree T1;
    T1 = Right(*T);
    if (Right(*T) != Nil) {
        Right(*T) = Nil;
    }
    *rightTree = T1;
}

/*********** PENGHAPUSAN TREE ***********/
void DelTree (Tree *T)
/* I.S. T sembarang */
/* F.S. Seluruh elemn T di dealokasi dan T menjadi kosong */
{
    Tree T1;
    if (*T != Nil) {
        if (Left(*T) != Nil) {
            DetachLeft(T,&T1);
            DelTree(&T1);
        }
        if (Right(*T) != Nil) {
            DetachRight(T,&T1);
            DelTree(&T1);
        }
        DealokasiT(*T);
        *T = Nil;
    }
}

/*********** PROSEDUR LAINNYA ***********/
void SaveTree (Tree T)
/* I.S. P anggota tree T */
/* F.S. menuliskan ke layar isi tree dengan format */
/* [Info(P)] [Info(Left(P))] [Info(Right(P))] */
{
    if (!IsEmptyT(T)) {
        printf("%d",Info(T));
        if (Left(T) != Nil) {
            printf(" %d",Info(Left(T)));
        }
        else {
            printf(" -");
        }
        if (Right(T) != Nil) {
            printf(" %d",Info(Right(T)));
        }
        else {
            printf(" -");
        }
        printf("\n");
        if (Left(T) != Nil) {
            SaveTree(Left(T));
        }
        if (Right(T) != Nil) {
            SaveTree(Right(T));
        }
    }
}

void PrintSubTreeT(addressT P, int n, int a[])
{
    int i;
    for (i=1; i<n; i++) {
        if (i == n-1) {
            printf("  |-");
        }
        else if (a[i] == 1) {
            printf("  | ");
        }
        else {
            printf("    ");
        }
    }
    printf("(%2d)\n",Info(P));
    //REKURSIF
    if ((Left(P) != Nil) && (Right(P) != Nil)) {
        a[n] = 1;
        PrintSubTreeT(Left(P), (n+1), a);
        a[n] = 0;
        PrintSubTreeT(Right(P), (n+1), a);
    }
    else if (Left(P) != Nil) {
        a[n] = 0;
        PrintSubTreeT(Left(P), (n+1), a);
    }
    else if (Right(P) != Nil) {
        a[n] = 0;
        PrintSubTreeT(Right(P), (n+1), a);
    }
}

void PrintTreeT(Tree T)
{
    int gambar[10];
    PrintSubTreeT(T,1,gambar);
}

