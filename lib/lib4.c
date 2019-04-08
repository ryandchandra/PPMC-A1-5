//***********************************************************//
//                      [ Source Code ]
//
// Institution       : Institut Teknologi Bandung
// Name              : Johannes Felix Rimbun
// File Name         : lib4.c
// Dependency        : stdio.h, stdlib.h, stdbool.h, math.h, lib3.c
//
// Description:
//     lib3.c merupakan implementasi dari fungsi RoutingManual
// 
//
// Status:
// 1. Johannes Felix Rimbun 13217006 : Create the file
//***********************************************************//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

void RoutingManual(pcb_t *pcb){
    //KAMUS LOKAL
    bool isQuit=false;
    bool isNext;
    char *s = (char*)malloc(20*sizeof(char)); //Untuk menempatkan simbol !@#$%%^&*()
    koor_t *arr_koor = (koor_t*)malloc(40*sizeof(koor_t));//Menempatkan
    //arr_koor[40].x =20;
    int i;
    //ALGORITMA
    printf("[Mode Routing]");
    printf("Isi 'q' atau 'Q' untuk kembali ke menu\n");
    printf("Isi `n` atau `N` untuk memulai pada simpul (node) baru\n");
    while (isQuit==false){
        //MELAKUKAN INPUT SIMBOL dan verifikasi simbol yang digunakan
        isNext=false;//reset nilai isNext agar nanti bisa masuk ke InputRoutingCoordinate
        do {
            printf("Pilih Simbol (!,@,#,$,%,^,&,*,(,)) : ");
            gets(s);
            if (((s[0]!='!')&&(s[0]!='@')&&(s[0]!='#')&&(s[0]!='$')&&(s[0]!='%')&&(s[0]!='^')&&(s[0]!='&')&&(s[0]!='*')&&(s[0]!='(')&&(s[0]!=')'))||(strlen(s)!=1)){ //HARUS DIPASTIKAN APAKAH MEMBUTUHKAN '*' ATAU TIDAK
                printf("Error. Karakter tidak terdefinisi\n");
            }
        } while ((s[0]!='!'&&s[0]!='@'&&s[0]!='#'&&s[0]!='$'&&s[0]!='%'&&s[0]!='^'&&s[0]!='&'&&s[0]!='*'&&s[0]!='('&&s[0]!=')')||strlen(s)!=1);
        InputRoutingCoordinate(pcb, s, arr_koor, &isQuit, &isNext);
    }
    free(s);
    free(arr_koor);
}

bool isNn(char *s_temp){
    //sudah di cek
    //Mengecek apakah inputan user 'N' atau 'n'
    if ((strlen(s_temp)==1)&&(s_temp[0]=='N'||s_temp[0]=='n')){
        return true;
    }else{
        return false;
    }
}
bool isQq(char *s_temp){
    //sudah di cek
    //Mengecek apakah s_temp merupakan 'Q' atau 'q'
    if ((strlen(s_temp)==1)&&(s_temp[0]=='Q'||s_temp[0]=='q')){
        return true;
    }else{
        return false;
    }
}

int banyakKoma(char *s_koor){
    //sudah diperiksa
    //Mengecek jumlah koma pada string s_koor
    int i = 0;
    int count = 0;//menghitung jumlah koma
    for (i=0; i<strlen(s_koor) ; i++){
        if (s_koor[i]==','){
            count=count+1;
        }
    }
    return count;
}

int posisiKoma(char *s_koor){
    //Mengecek posisi Koma memunculkan nilai koma pertama
    //Sudah di cek dan berhasil
    int ans=0;//posisi koma
    bool isTrue = false;
    int i=0; // increment
    while(isTrue==false && i<strlen(s_koor)){
        if(s_koor[i]==','){
            isTrue=true;
            ans=i;
        }
        i++;
    }
    if (isTrue==false){
        return -1;
    }else{
        return ans;
    }
    //mengeluarkan -1 ketika tidak ada koma
}

int StringtoInt (int posisiawal, int posisiakhir, char *s_koor){
    //UDAH FIX BENAR YEEEEAYY
    //Mengeluarkan integer yang merupakan bagian dari string s
    int panjang = posisiakhir-posisiawal+1;//panjang dari string yang akan diubah ke int
    char *s_temp=(char*)calloc(panjang, sizeof(char));
    int z;
    for (z=0; z<panjang; z++){
        s_temp[z]=s_koor[posisiawal+z];
    }
    return (atoi(s_temp));
}
bool validasiKoordinat (char *s_koor, pcb_t *pcb){
    //Memastikan apakah koordinat s_koor sesuai dengan format, true jika benar, false jika salah
    //sudah diperiksa secara khusus
    int i, x, y;
    x=StringtoInt(0, posisiKoma(s_koor), s_koor);
    y=StringtoInt(posisiKoma(s_koor)+1, strlen(s_koor)-1, s_koor);
    bool isCorrect=true;//menandakan apakah input false
    //Melakukan validasi terhadap koordinat, True jika koordinat benar, False jika koordinat salah
    //printf("validasi koordinat :: \n");
    if (banyakKoma(s_koor)!=1){
        isCorrect=false;
    }else if (s_koor[0]==',' || s_koor[strlen(s_koor)-1]==','){
        isCorrect=false;
        //panjang ke kanan (x), lebar ke bawah (y)
        //(y,x)
    }else if (x>pcb->panjang ||  y> pcb->lebar || x<=0 || y<=0){
        isCorrect=false;
    }else{
        i=0;//mengecek apakah string s_koor menganding angka
        while (isCorrect==true && i<strlen(s_koor)){
            if ((s_koor[i]<'0' || s_koor[i]>'9') && s_koor[i]!=','){
                isCorrect=false;
            }
            i++;
        }
    }
    if (isCorrect==false){
        return false;
    }else{
        return true;
    }
}

bool ApakahRangeMatriksTerisi(pcb_t* pcb, koor_t *posisiAwal, koor_t *posisiAkhir){
//Memastikan apakah dari titik posisiAwal sampai posisiAkhir, range matriks telah terisi (true jika telah terisi
//telah diperiksa
//harus di cek apabila posisiAkhir < posisiAwal
    int x,y;//increment
    bool isTerisi=false;
    if (posisiAwal==posisiAkhir){//digunakan untuk input koordinat pertama kali
        x=posisiAwal->x;
        y=posisiAwal->y;
        if (pcb->routing[y-1][x-1]!=' '){
            isTerisi= true;
        }
    }else{
        if (posisiAwal->x == posisiAkhir->x){//apabila komponen y mengalami perubahan
            x=posisiAwal->x;
            if(posisiAwal->y < posisiAkhir->y){
                for (y=posisiAwal->y+1; y<=posisiAkhir->y; y++){
                    if (pcb->routing[y-1][x-1]!=' '){
                        isTerisi= true;
                    }
                }
            }else{
                for (y=posisiAwal->y-1; y>=posisiAkhir->y; y=y-1){
                    if (pcb->routing[y-1][x-1]!=' '){
                        isTerisi= true;
                    }
                }
            }
        }else{ //(posisiAwal->y == posisiAkhir->y)
            y=posisiAwal->y;
            if (posisiAwal->x<posisiAkhir->x){
                for (x=posisiAwal->x+1; x<=posisiAkhir->x; x++){
                    if (pcb->routing[y-1][x-1]!=' '){
                        isTerisi=true;
                    }
                }
            }else{
                for (x=posisiAwal->x-1; x>=posisiAkhir->x; x=x-1){
                    if (pcb->routing[y-1][x-1]!=' '){
                        isTerisi=true;
                    }
                }
            }
        }
    }
    if (isTerisi==true){
        return true;
    }else{
        return false;
    }
}

void PrintKeMatriks(pcb_t *pcb, char *s, koor_t *arr_koor, int i){
//Melakukan print simbol s ke matriks pcb->routing dari arr_koor[i-1] sampai arr_koor[i]
//Sudah diperiksa
    int x,y;

    if (i==0){
        pcb->routing[arr_koor[i].y-1][arr_koor[i].x-1]=s[0];
    }else {  //i>=1
        if (arr_koor[i-1].x == arr_koor[i].x){
            x=arr_koor[i-1].x;
            if (arr_koor[i-1].y<arr_koor[i].y){
                y=arr_koor[i-1].y;
                for(y=arr_koor[i-1].y; y<= arr_koor[i].y; y++){
                    pcb->routing[y-1][x-1]=s[0];
                }
            }else
                for(y=arr_koor[i-1].y; y>= arr_koor[i].y; y=y-1){
                    pcb->routing[y-1][x-1]=s[0];
                }
        }else if (arr_koor[i-1].y == arr_koor[i].y){
            y=arr_koor[i-1].y;
            if (arr_koor[i-1].x<arr_koor[i].x){
                for(x=arr_koor[i-1].x; x<= arr_koor[i].x; x++){
                    pcb->routing[y-1][x-1]=s[0];
                }
            }else{
                for(x=arr_koor[i-1].x; x>= arr_koor[i].x; x=x-1){
                    pcb->routing[y-1][x-1]=s[0];
                }
            }
        }else{
            printf("PrintKeMatriks GAGAL\n");
        }
    }

}

void InputRoutingCoordinate (pcb_t *pcb, char *s, koor_t *arr_koor, bool *isQuit, bool *isNext){
//Memasukkan input ke sebuah array koor_t dan memvalidasi
//input koordinat beruurtan sama tidak ada validasi
    int i=0;
    int x, y;
    char *s_koor=(char*)malloc(20*sizeof(char));//menemparkan koordinat dalam bentuk string

    do {
        printf("Koordinat %d :", i+1);
        gets(s_koor);//(y,x)
        //printf("%s", s_koor);
        *isQuit=isQq(s_koor);
        *isNext=isNn(s_koor);
        //validasi inputan
        arr_koor[i].y=StringtoInt(0, posisiKoma(s_koor), s_koor);
        arr_koor[i].x=StringtoInt(posisiKoma(s_koor)+1, strlen(s_koor), s_koor);

        if((*isQuit)==false && (*isNext)==false){
            if (validasiKoordinat(s_koor, pcb)==false){
                printf("Format Koordinat Salah\n");
            }else if (ApakahRangeMatriksTerisi (pcb, arr_koor+i, arr_koor+i)){
                printf("Koordinat telah terisi\n");
            }
        }
    }while ( (validasiKoordinat(s_koor, pcb)==false || ApakahRangeMatriksTerisi(pcb,arr_koor+i, arr_koor+i))&& *isQuit==false && *isNext==false);
    PrintKeMatriks(pcb, s, arr_koor, i);
    while ((*isNext)==false && (*isQuit) == false){
        i=i+1;
        do {
            printf("Koordinat %d :", i+1);
            gets(s_koor);
            *isQuit=isQq(s_koor);
            *isNext=isNn(s_koor);
            //validasi inputan
            arr_koor[i].y=StringtoInt(0, posisiKoma(s_koor), s_koor);
            arr_koor[i].x=StringtoInt(posisiKoma(s_koor)+1, strlen(s_koor), s_koor);

            if((*isQuit)==false && (*isNext)==false){
                if (validasiKoordinat(s_koor, pcb)==false){
                    printf("Format Koordinat Salah\n");
                }else if (IsDiagonal(arr_koor[i-1], arr_koor[i]) ){
                    printf("Koordinat tidak segaris\n");
                }else if (ApakahRangeMatriksTerisi(pcb, arr_koor+i-1, arr_koor+i)){
                    printf("Koordinat telah terisi\n");
                }else if ((arr_koor[i-1].x==arr_koor[i].x)&&(arr_koor[i-1].y==arr_koor[i].y)){
                    printf("Koordinat ke-%d dan ke-%d sama\n", i, i-1);
                }
            }
        }while ( (validasiKoordinat(s_koor, pcb)==false || ApakahRangeMatriksTerisi(pcb,arr_koor+i-1, arr_koor+i) || IsDiagonal(arr_koor[i-1], arr_koor[i]))&& *isQuit==false && *isNext==false);
        //Melakukan Print Ke Matriks
        if (*isNext==false && *isQuit==false){
            PrintKeMatriks(pcb, s, arr_koor, i);
        }
    }
    printf("\n");
    free(s_koor);
}
