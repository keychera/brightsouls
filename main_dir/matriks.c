#include "header_dir/matriks.h"
#include <stdio.h>

/* ********** DEFINISI PROTOTIPE PRIMITIF ********** */
/* *** Konstruktor membentuk MATRIKS *** */
void MakeMATRIKS (int NB, int NK, MATRIKS * M)
/* Membentuk sebuah MATRIKS "kosong" yang siap diisi berukuran NB x NK di "ujung kiri" memori */
/* I.S. NB dan NK adalah valid untuk memori matriks yang dibuat */
/* F.S. Matriks M sesuai dengan definisi di atas terbentuk */
{
    NBrsEff(*M) = NB;
    NKolEff(*M) = NK;
}

/* *** Selektor "DUNIA MATRIKS" *** */
boolean IsIdxValid (int i, int j)
/* Mengirimkan true jika i, j adalah indeks yang valid untuk matriks apa pun */
{
    return ((i >= BrsMin) && (i <= BrsMax) && (j >= KolMin) && (j <= KolMax));
}

/* *** Selektor: Untuk sebuah matriks M yang terdefinisi: *** */
indeks GetFirstIdxBrs (MATRIKS M)
/* Mengirimkan indeks baris terkecil M */
{
    return BrsMin;
}
indeks GetFirstIdxKol (MATRIKS M)
/* Mengirimkan indeks kolom terkecil M */
{
    return KolMin;
}
indeks GetLastIdxBrs (MATRIKS M)
/* Mengirimkan indeks baris terbesar M */
{
    return NBrsEff(M);
}
indeks GetLastIdxKol (MATRIKS M)
/* Mengirimkan indeks kolom terbesar M */
{
    return NKolEff(M);
}
boolean IsIdxEff (MATRIKS M, indeks i, indeks j)
/* Mengirimkan true jika i, j adalah indeks efektif bagi M */
{
    return ((i >= GetFirstIdxBrs(M)) && (i <= GetLastIdxBrs(M)) && (j >= GetFirstIdxKol(M)) && (j <= GetLastIdxKol(M)));
}
ElType GetElmtDiagonal (MATRIKS M, indeks i)
/* Mengirimkan elemen M(i,i) */
{
    return Elmt(M,i,i);
}

/* ********** Assignment  MATRIKS ********** */
void CopyMATRIKS (MATRIKS MIn, MATRIKS * MHsl)
/* Melakukan assignment MHsl  MIn */
{
    *MHsl = MIn;
}

/* ********** KELOMPOK BACA/TULIS ********** */
void BacaMATRIKS (MATRIKS * M, int NB, int NK)
/* I.S. IsIdxValid(NB,NK) */
/* F.S. M terdefinisi nilai elemen efektifnya, berukuran NB x NK */
/* Proses: Melakukan MakeMATRIKS(M,NB,NK) dan mengisi nilai efektifnya */
/* Selanjutnya membaca nilai elemen per baris dan kolom */
/* Contoh: Jika NB = 3 dan NK = 3, maka contoh cara membaca isi matriks :
1 2 3
4 5 6
8 9 10
*/
{
    int i,j;
    MakeMATRIKS(NB,NK,M);
    for (i=1; i<=NB; i++) {
        for (j=1; j<=NK; j++) {
            scanf("%d",&Elmt(*M,i,j));
        }
    }
}
void TulisMATRIKS (MATRIKS M)
/* I.S. M terdefinisi */
/* F.S. Nilai M(i,j) ditulis ke layar per baris per kolom, masing-masing elemen per baris
   dipisahkan sebuah spasi */
/* Proses: Menulis nilai setiap elemen M ke layar dengan traversal per baris dan per kolom */
/* Contoh: menulis matriks 3x3 (ingat di akhir tiap baris, tidak ada spasi)
1 2 3
4 5 6
8 9 10
*/
{
    int i,j;
    for (i=GetFirstIdxBrs(M); i<=GetLastIdxBrs(M); i++) {
        for (j=GetFirstIdxKol(M); j<=GetLastIdxKol(M); j++) {
            printf("%d",Elmt(M,i,j));
            if (j != GetLastIdxKol(M)) {
                printf(" ");
            }
        }
        if (i != GetLastIdxBrs(M)) {
            printf("\n");
        }
    }
}

/* ********** KELOMPOK OPERASI ARITMATIKA TERHADAP TYPE ********** */
MATRIKS TambahMATRIKS (MATRIKS M1, MATRIKS M2)
/* Prekondisi : M1  berukuran sama dengan M2 */
/* Mengirim hasil penjumlahan matriks: M1 + M2 */
{
    MATRIKS M3;
    int i,j;
    MakeMATRIKS(NBrsEff(M1),NKolEff(M1),&M3);
    for (i=GetFirstIdxBrs(M1); i<=GetLastIdxBrs(M1); i++) {
        for (j=GetFirstIdxKol(M1); j<=GetLastIdxKol(M1); j++) {
            Elmt(M3,i,j) = Elmt(M1,i,j) + Elmt(M2,i,j);
        }
    }
    return M3;
}
MATRIKS KurangMATRIKS (MATRIKS M1, MATRIKS M2)
/* Prekondisi : M berukuran sama dengan M */
/* Mengirim hasil pengurangan matriks: salinan M1 – M2 */
{
    MATRIKS M3;
    int i,j;
    MakeMATRIKS(NBrsEff(M1),NKolEff(M1),&M3);
    for (i=GetFirstIdxBrs(M1); i<=GetLastIdxBrs(M1); i++) {
        for (j=GetFirstIdxKol(M1); j<=GetLastIdxKol(M1); j++) {
            Elmt(M3,i,j) = Elmt(M1,i,j) - Elmt(M2,i,j);
        }
    }
    return M3;
}
MATRIKS KaliMATRIKS (MATRIKS M1, MATRIKS M2)
/* Prekondisi : Ukuran kolom efektif M1 = ukuran baris efektif M2 */
/* Mengirim hasil perkalian matriks: salinan M1 * M2 */
{
    MATRIKS M3;
    int i,j,k;
    MakeMATRIKS(NBrsEff(M1),NKolEff(M2),&M3);
    for (i=GetFirstIdxBrs(M1); i<=GetLastIdxBrs(M1); i++) {
        for (j=GetFirstIdxKol(M2); j<=GetLastIdxKol(M2); j++) {
            Elmt(M3,i,j) = 0;
            for (k=GetFirstIdxBrs(M2); k<=GetLastIdxBrs(M2); k++) {
                Elmt(M3,i,j) += Elmt(M1,i,k) * Elmt(M2,k,j);
            }
        }
    }
    return M3;
}
MATRIKS KaliKons (MATRIKS M, ElType X)
/* Mengirim hasil perkalian setiap elemen M dengan X */
{
    MATRIKS M3;
    int i,j;
    MakeMATRIKS(NBrsEff(M),NKolEff(M),&M3);
    for (i=GetFirstIdxBrs(M); i<=GetLastIdxBrs(M); i++) {
        for (j=GetFirstIdxKol(M); j<=GetLastIdxKol(M); j++) {
            Elmt(M3,i,j) = Elmt(M,i,j) * X;
        }
    }
    return M3;
}
void PKaliKons (MATRIKS * M, ElType K)
/* I.S. M terdefinisi, K terdefinisi */
/* F.S. Mengalikan setiap elemen M dengan K */
{
    *M = KaliKons(*M,K);
}

/* ********** KELOMPOK OPERASI RELASIONAL TERHADAP MATRIKS ********** */
boolean EQM (MATRIKS M1, MATRIKS M2)
/* Mengirimkan true jika M1 = M2, yaitu NBElmt(M1) = NBElmt(M2) dan */
/* untuk setiap i,j yang merupakan indeks baris dan kolom M1(i,j) = M2(i,j) */
/* Juga merupakan strong EQ karena GetFirstIdxBrs(M1) = GetFirstIdxBrs(M2)
   dan GetLastIdxKol(M1) = GetLastIdxKol(M2) */
{
    int i,j;
    boolean valid = false;
    if ((NBrsEff(M1) == NBrsEff(M2)) && (NKolEff(M1) == NKolEff(M2))) {
        valid = true;
        for (i=GetFirstIdxBrs(M1); i<=GetLastIdxBrs(M1); i++) {
            for (j=GetFirstIdxKol(M1); j<=GetLastIdxKol(M1); j++) {
                if (Elmt(M1,i,j) != Elmt(M2,i,j)) {
                    valid = false;
                }
            }
        }
    }
    return valid;
}
boolean NEQM (MATRIKS M1, MATRIKS M2)
/* Mengirimkan true jika M1 tidak sama dengan M2 */
{
    return (!EQM(M1,M2));
}
boolean EQSize (MATRIKS M1, MATRIKS M2)
/* Mengirimkan true jika ukuran efektif matriks M1 sama dengan ukuran efektif M2 */
/* yaitu GetBrsEff(M1) = GetNBrsEff (M2) dan GetNKolEff (M1) = GetNKolEff (M2) */
{
    return ((NBrsEff(M1) == NBrsEff(M2)) && (NKolEff(M1) == NKolEff(M2)));
}

/* ********** Operasi lain ********** */
int NBElmt (MATRIKS M)
/* Mengirimkan banyaknya elemen M */
{
    return (NBrsEff(M) * NKolEff(M));
}

/* ********** KELOMPOK TEST TERHADAP MATRIKS ********** */
boolean IsBujurSangkar (MATRIKS M)
/* Mengirimkan true jika M adalah matriks dg ukuran baris dan kolom sama */
{
    return (NBrsEff(M) == NKolEff(M));
}
boolean IsSimetri (MATRIKS M)
/* Mengirimkan true jika M adalah matriks simetri : IsBujurSangkar(M)
   dan untuk setiap elemen M, M(i,j)=M(j,i) */
{
    int i,j;
    boolean valid = false;
    if (IsBujurSangkar(M)) {
        valid = true;
        for (i=GetFirstIdxBrs(M); i<=GetLastIdxBrs(M); i++) {
            for (j=GetFirstIdxKol(M); j<=i; j++) {
                if (Elmt(M,i,j) != Elmt(M,j,i)) {
                    valid = false;
                }
            }
        }
    }
    return valid;
}
boolean IsSatuan (MATRIKS M)
/* Mengirimkan true jika M adalah matriks satuan: IsBujurSangkar(M) dan
   setiap elemen diagonal M bernilai 1 dan elemen yang bukan diagonal bernilai 0 */
{
    int i,j;
    boolean valid = false;
    if (IsBujurSangkar(M)) {
        valid = true;
        for (i=GetFirstIdxBrs(M); i<=GetLastIdxBrs(M); i++) {
            for (j=GetFirstIdxKol(M); j<=i; j++) {
                if (i == j) {
                    if (Elmt(M,i,j) != 1) {
                        valid = false;
                    }
                }
                else {
                    if (Elmt(M,i,j) != 0) {
                        valid = false;
                    }
                }
            }
        }
    }
    return valid;
}
boolean IsSparse (MATRIKS M)
/* Mengirimkan true jika M adalah matriks sparse: mariks “jarang” dengan definisi:
   hanya maksimal 5% dari memori matriks yang efektif bukan bernilai 0 */
{
    float persen;
    int i,j,count0 = 0;
    for (i=GetFirstIdxBrs(M); i<=GetLastIdxBrs(M); i++) {
        for (j=GetFirstIdxKol(M); j<=GetLastIdxKol(M); j++) {
            if (Elmt(M,i,j) == 0) {
                count0++;
            }
        }
    }
    persen = ((float)(NBElmt(M) - count0) / (float)NBElmt(M));
    return (persen <= 0.05);
}
MATRIKS Inverse1 (MATRIKS M)
/* Menghasilkan salinan M dengan setiap elemen "di-invers", yaitu dinegasikan (dikalikan -1) */
{
    MATRIKS M3;
    int i,j;
    MakeMATRIKS(NBrsEff(M),NKolEff(M),&M3);
    for (i=GetFirstIdxBrs(M); i<=GetLastIdxBrs(M); i++) {
        for (j=GetFirstIdxKol(M); j<=GetLastIdxKol(M); j++) {
            Elmt(M3,i,j) = Elmt(M,i,j) * (-1);
        }
    }
    return M3;
}
float Determinan (MATRIKS M)
/* Prekondisi: IsBujurSangkar(M) */
/* Menghitung nilai determinan M */
{
    int i,j,k;
    float sum;
    MATRIKS C;
    if (NBrsEff(M) == 1) {
        sum = Elmt(M,1,1);
    }
    else {
        sum = 0;
        for (i=GetFirstIdxKol(M); i<=GetLastIdxKol(M); i++) {
            // Copy C1i
            MakeMATRIKS(NBrsEff(M)-1,NKolEff(M)-1,&C);
            for ((j=GetFirstIdxBrs(M)+1); j<=GetLastIdxBrs(M); j++) {
                for (k=GetFirstIdxKol(M); k<=GetLastIdxKol(M); k++) {
                    if (k<i) {
                        Elmt(C,j-1,k) = Elmt(M,j,k);
                    }
                    else if (k>i) {
                        Elmt(C,j-1,k-1) = Elmt(M,j,k);
                    }
                }
            }

            // hitung determinan
            if ((i+1)%2 == 0){
                sum += (Elmt(M,GetFirstIdxBrs(M),i) * Determinan(C));
            }
            else {
                sum -= (Elmt(M,GetFirstIdxBrs(M),i) * Determinan(C));
            }
        }
    }
    return sum;
}
void PInverse1 (MATRIKS * M)
/* I.S. M terdefinisi */
/* F.S. M di-invers, yaitu setiap elemennya dinegasikan (dikalikan -1) */
{
    *M = Inverse1(*M);
}
void Transpose (MATRIKS * M)
/* I.S. M terdefinisi dan IsBujursangkar(M) */
/* F.S. M "di-transpose", yaitu setiap elemen M(i,j) ditukar nilainya dengan elemen M(j,i) */
{
    int i,j,temp;
    temp = NBrsEff(*M);
    NBrsEff(*M) = NKolEff(*M);
    NKolEff(*M) = temp;
    for (i=GetFirstIdxBrs(*M); i<=GetLastIdxBrs(*M); i++) {
        for (j=GetFirstIdxKol(*M); j<=i; j++) {
            temp = Elmt(*M,i,j);
            Elmt(*M,i,j) = Elmt(*M,j,i);
            Elmt(*M,j,i) = temp;
        }
    }
}
