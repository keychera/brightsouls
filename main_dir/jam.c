#include "header_dir/boolean.h"
#include "header_dir/jam.h"

/* ***************************************************************** */
/* DEFINISI PRIMITIF                                                 */
/* ***************************************************************** */
/* KELOMPOK VALIDASI TERHADAP TYPE                                   */
/* ***************************************************************** */
boolean IsJAMValid (int H, int M, int S){
    if((H>0)&&(H<24)&&(M>0)&&(M<60)&&(S>0)&&(S<60)){
        return true;
    }
    else {
        return false;
    }
}
/* Mengirim true  jika H,M,S dapat membentuk J yang valid */
/* dipakai untuk mentest SEBELUM membentuk sebuah Jam */

/* *** Konstruktor: Membentuk sebuah JAM dari komponen-komponennya *** */
JAM MakeJAM (int HH, int MM, int SS){
    JAM J;
    Hour(J)=HH;
    Minute(J)=MM;
    Second(J)=SS;
    return J;
}
/* Membentuk sebuah JAM dari komponen-komponennya yang valid */
/* Prekondisi : HH, MM, SS valid untuk membentuk JAM */

/* ***************************************************************** */
/* KELOMPOK BACA/TULIS                                               */
/* ***************************************************************** */
void BacaJAM (JAM * J){
    int HH,MM,SS;
    scanf("%d",&HH);
    scanf("%d",&MM);
    scanf("%d",&SS);
    Hour(*J)=HH;
    Minute(*J)==MM;
    Second(*J)==SS;
}
/* I.S. : J tidak terdefinisi */
/* F.S. : J terdefinisi dan merupakan jam yang valid */
/* Proses : mengulangi membaca komponen HH, MM, SS sehingga membentuk J */
/* yang valid. Tidak mungkin menghasilkan J yang tidak valid. */
/* Pembacaan dilakukan dengan mengetikkan komponen HH, MM, SS
   dalam satu baris, masing-masing dipisahkan 1 spasi, diakhiri enter. */
/* Jika JAM tidak valid maka diberikan pesan: "Jam tidak valid", dan pembacaan
   diulangi hingga didapatkan jam yang valid. */
/* Contoh:
   60 3 4
   Jam tidak valid
   1 3 4
   --> akan terbentuk JAM <1,3,4> */

void TulisJAM (JAM J){
    printf("&d:%d:%d",Hour(J),Minute(J),Second(J));
}
/* I.S. : J sembarang */
/* F.S. :   Nilai J ditulis dg format HH:MM:SS */
/* Proses : menulis nilai setiap komponen J ke layar dalam format HH:MM:SS
   tanpa karakter apa pun di depan atau belakangnya, termasuk spasi, enter, dll.*/

/* ***************************************************************** */
/* KELOMPOK KONVERSI TERHADAP TYPE                                   */
/* ***************************************************************** */
long JAMToDetik (JAM J){
    long detik;
    detik = Hour(J)*3600 + Minute(J)*60 + Second(J);
    return detik;
}
/* Diberikan sebuah JAM, mengkonversi menjadi jumlah detik dari pukul 0:0:0 */
/* Rumus : detik = 3600*HH + 60*MM + SS */
/* Nilai maksimum = 3600*23+59*60+59 */

JAM DetikToJAM (long N){
    JAM J;
    long N1;
    N1 = N % 86400;
    Second(J) = N1 & 60;
    N1 = N1 / 60;
    Minute(J) = N1 & 60;
    N1 = N1 /60;
    Hour(J) = N1;
    return J;
}
/* Mengirim  konversi detik ke JAM */
/* Catatan: Jika N >= 86400, maka harus dikonversi dulu menjadi jumlah detik yang
   mewakili jumlah detik yang mungkin dalam 1 hari, yaitu dengan rumus:
   N1 = N mod 86400, baru N1 dikonversi menjadi JAM */

/* ***************************************************************** */
/* KELOMPOK OPERASI TERHADAP TYPE                                    */
/* ***************************************************************** */
/* *** Kelompok Operator Relational *** */
boolean JEQ (JAM J1, JAM J2){
    if ((Hour(J1)==Hour(J2))&&(Minute(J1)==Minute(J2))&&(Second(J1)==Second(J2))){
            return true;
    }
    else {
        return false;
    }
}
/* Mengirimkan true jika J1=J2, false jika tidak */
boolean JNEQ (JAM J1, JAM J2){
    if ((Hour(J1)==Hour(J2))&&(Minute(J1)==Minute(J2))&&(Second(J1)==Second(J2))){
            return false;
    }
    else {
        return true;
    }
}
/* Mengirimkan true jika J1 tidak sama dengan J2 */
boolean JLT (JAM J1, JAM J2){
   long D1,D2;
   D1 = JAMToDetik (J1);
   D2 = JAMToDetik (J2);
   if (D1<D2) {
        return true;
   }
   else {
        return false;
   }
}
/* Mengirimkan true jika J1<J2, false jika tidak */
boolean JGT (JAM J1, JAM J2){
   long D1,D2;
   D1 = JAMToDetik (J1);
   D2 = JAMToDetik (J2);
   if (D1>D2) {
        return true;
   }
   else {
        return false;
   }
}
/* Mengirimkan true jika J1>J2, false jika tidak */
/* *** Operator aritmatika JAM *** */
JAM NextDetik (JAM J){
    JAM J1;
    long D;
    D = JAMToDetik(J)+1;
    /*J1=DetikToJam(D);*/
    return J1;
}
/* Mengirim 1 detik setelah J dalam bentuk JAM */
JAM NextNDetik (JAM J, int N){
    JAM J1;
    long D;
    D = JAMToDetik(J)+N;
    /*J1=DetikToJam(D);*/
    return J1;
}
/* Mengirim N detik setelah J dalam bentuk JAM */
JAM PrevDetik (JAM J){
    JAM J1;
    long D;
    D = JAMToDetik(J)-1;
    /*J1=DetikToJam(D);*/
    return J1;
}
/* Mengirim 1 detik sebelum J dalam bentuk JAM */
JAM PrevNDetik (JAM J, int N){
    JAM J1;
    long D;
    D = JAMToDetik(J)-N;
    /*J1=DetikToJam(D);*/
    return J1;
}
/* Mengirim N detik sebelum J dalam bentuk JAM */
/* *** Kelompok Operator Aritmetika *** */
long Durasi (JAM JAw, JAM JAkh){
    long DAw,DAkh,D;
        DAw=JAMToDetik(JAw);
        DAkh=JAMToDetik(JAkh);
    if (DAw>DAkh){
        DAw=DAw+86400;
    }
    D = DAw - DAkh;
    return D;
}
/* Mengirim JAkh-JAw dlm Detik, dengan kalkulasi */
/* Jika JAw > JAkh, maka JAkh adalah 1 hari setelah JAw */
