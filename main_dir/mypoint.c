#include <stdio.h>
#include "header_dir/mypoint.h"
#include <math.h>


/* *** DEFINISI PROTOTIPE PRIMITIF *** */
/* *** Konstruktor membentuk POINT *** */
POINT MakePOINT (float X, float Y){
    POINT P;
    Absis (P) = X;
    Ordinat(P) = Y;
    return (P);
}
/* Membentuk sebuah POINT dari komponen-komponennya */

/* *** KELOMPOK Interaksi dengan I/O device, BACA/TULIS  *** */
void BacaPOINT (POINT * P){
    float X,Y;
    scanf ("%f",&X);
    scanf("%f",&Y);
    *P = MakePOINT(X,Y);
}
/* Membaca nilai absis dan ordinat dari keyboard dan membentuk
   POINT P berdasarkan dari nilai absis dan ordinat tersebut */
/* Komponen X dan Y dibaca dalam 1 baris, dipisahkan 1 buah spasi */
/* Contoh: 1 2
   akan membentuk POINT <1,2> */
/* I.S. Sembarang */
/* F.S. P terdefinisi */
void TulisPOINT (POINT P){
    printf("(%f,%f)",Absis(P),Ordinat(P));
}
/* Nilai P ditulis ke layar dengan format "(X,Y)"
   tanpa spasi, enter, atau karakter lain di depan, belakang,
   atau di antaranya */
/* I.S. P terdefinisi */
/* F.S. P tertulis di layar dengan format "(X,Y)" */

/* *** Kelompok operasi relasional terhadap POINT *** */
boolean POINTEQ (POINT P1, POINT P2){
    if ((Absis(P1)==Absis(P2))&&(Ordinat(P1)==Ordinat(P2))) {
        return true;
    }
    else {
        return false;
    }
}
/* Mengirimkan true jika P1 = P2 : absis dan ordinatnya sama */
boolean POINTNEQ (POINT P1, POINT P2){
    if ((Absis(P1)==Absis(P2))&&(Ordinat(P1)==Ordinat(P2))) {
        return false;
    }
    else {
        return true;
    }
}
/* Mengirimkan true jika P1 tidak sama dengan P2 */

/* *** Kelompok menentukan di mana P berada *** */
boolean IsOrigin (POINT P){
    if ((Absis(P)== 0)&&(Ordinat(P)== 0)) {
        return true;
    }
    else {
        return false;
    }
}
/* Menghasilkan true jika P adalah titik origin */
boolean IsOnSbX (POINT P){
if ((Ordinat(P)== 0)) {
        return true;
    }
    else {
        return false;
    }
}
/* Menghasilkan true jika P terletak Pada sumbu X */
boolean IsOnSbY (POINT P){
if ((Absis(P)== 0)) {
        return true;
    }
    else {
        return false;
    }
}
/* Menghasilkan true jika P terletak pada sumbu Y */
int Kuadran (POINT P){
    if ((Absis(P)>0)&&(Ordinat(P)>0)){
        return 1;
    }
    else {
            if ((Absis(P)<0)&&(Ordinat(P)>0)){
                return 2;
            }
            else {
                if ((Absis(P)<0)&&(Ordinat(P)<0)){
                    return 3;
                }
                else {
                    if ((Absis(P)>0)&&(Ordinat(P)<0)){
                        return 4;
                    }
                    else{
						return 0;
					}
                }
            }

        }

}
/* Menghasilkan kuadran dari P: 1, 2, 3, atau 4 */
/* Prekondisi : P bukan titik origin, */
/*              dan P tidak terletak di salah satu sumbu */

/* *** KELOMPOK OPERASI LAIN TERHADAP TYPE *** */
POINT NextX (POINT P){
    POINT A;
    Absis(A)=Absis(P)+1;
    Ordinat(A)=Ordinat(P);
    return A;
}
/* Mengirim salinan P dengan absis ditambah satu */
POINT NextY (POINT P){
    POINT A;
    Absis(A)=Absis(P);
    Ordinat(A)=Ordinat(P)+1;
    return A;
}
/* Mengirim salinan P dengan ordinat ditambah satu */
POINT PlusDelta (POINT P, float deltaX, float deltaY){
    POINT A;
    Absis(A)=Absis(P)+deltaX;
    Ordinat(A)=Ordinat(P)+deltaY;
    return A;
}
/* Mengirim salinan P yang absisnya adalah Absis(P) + deltaX dan ordinatnya adalah Ordinat(P) + deltaY */
POINT MirrorOf (POINT P, boolean SbX){
    POINT A;
    if (SbX==true){
        Absis(A)=Absis(P);
        Ordinat(A)=Ordinat(P)*(-1);
    }
    else {
        Absis(A)=Absis(P)*(-1);
        Ordinat(A)=Ordinat(P);
    }
    return A;
}
/* Menghasilkan salinan P yang dicerminkan terhadap salah satu sumbu */
/* Jika SbX bernilai true, maka dicerminkan terhadap sumbu X */
/* Jika SbX bernilai false, maka dicerminkan terhadap sumbu Y */
float Jarak0 (POINT P){
    float j;
    j=(Absis(P)*Absis(P))+(Ordinat(P)*Ordinat(P));
    return j;
}
/* Menghitung jarak P ke (0,0) */
float Panjang (POINT P1, POINT P2){
    float j;
    j=((Absis(P1)-Absis(P2))*(Absis(P1)-Absis(P2)))+((Ordinat(P1)-Ordinat(P2))*(Ordinat(P1)-Ordinat(P2)));
    return j;
}
/* Menghitung panjang garis yang dibentuk P1 dan P2 */
/* Perhatikanlah bahwa di sini spec fungsi kurang baik sebab menyangkut ADT Garis. */
/* Tuliskan spec fungsi yang lebih tepat. */
void Geser (POINT *P, float deltaX, float deltaY){
    Absis(*P)=Absis(*P)+deltaX;
    Ordinat(*P)=Ordinat(*P)+deltaY;
}
/* I.S. P terdefinisi */
/* F.S. P digeser, absisnya sebesar deltaX dan ordinatnya sebesar deltaY */
void GeserKeSbX (POINT *P){
    Ordinat(*P)=0;
}
/* I.S. P terdefinisi */
/* F.S. P berada pada sumbu X dengan absis sama dengan absis semula. */
/* Proses : P digeser ke sumbu X. */
/* Contoh : Jika koordinat semula (9,9), maka menjadi (9,0) */
void GeserKeSbY (POINT *P){
    Absis(*P)=0;
}
/* I.S. P terdefinisi*/
/* F.S. P berada pada sumbu Y dengan ordinat yang sama dengan semula. */
/* Proses : P digeser ke sumbu Y. */
/* Contoh : Jika koordinat semula (9,9), maka menjadi (0,9) */
void Mirror (POINT *P, boolean SbX){
    if (SbX==true){
        Ordinat(*P)=Ordinat(*P)*(-1);
    }
    else {
        Absis(*P)=Absis(*P)*(-1);
    }
}
/* I.S. P terdefinisi */
/* F.S. P dicerminkan tergantung nilai SbX atau SbY */
/* Jika SbX true maka dicerminkan terhadap sumbu X */
/* Jika SbX false maka dicerminkan terhadap sumbu Y */
void Putar (POINT *P, float Sudut){
    float Sudut2,SAbsis,SOrdinat;
    Sudut2=Sudut*3.14/180;
    SAbsis=Absis(*P);
    SOrdinat=Ordinat(*P);
    Absis(*P)=(SAbsis*cos(Sudut2)) - (SOrdinat*sin(Sudut2));
    Ordinat(*P)=(SAbsis*sin(Sudut2)) + (SOrdinat*cos(Sudut2));
}
/* I.S. P terdefinisi */
/* F.S. P digeser sebesar Sudut derajat dengan sumbu titik (0,0) */
