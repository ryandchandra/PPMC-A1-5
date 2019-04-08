//***********************************************************//
//                      [ Source Code ]
//
// Institution       : Institut Teknologi Bandung
// Name              : Johannes Felix Rimbun, Naila Amani, Ryan Dharma Chandra
// File Name         : main.c
// Dependency        : stdio.h, stdlib.h, stdbool.h, lib.h
//
// Description:
//     MENU UTAMA
//
//
// Status:
// 1. Johannes Felix Rimbun 13217006 : Create the code di lib1.c
// 2. Naila Amani 13217012 : Edit code, perbaikin tampilan
// 3. Ryan Dharma Chandra 13217018 : Import dari lib1.c
//***********************************************************//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "lib.h"

int main(){
    //KAMUS LOKAL
    pcb_t pcb;
    char *projectName;
    bool isQuitMain = false;
    bool isSuccess;
    char pilihan_s[10];
    int pilihan;

    //ALGORITMA
    //mengalokasikan memori
    projectName=(char*)malloc(20*sizeof(char));
    isSuccess=false;
    while (isQuitMain==false){
        printf("Menu: \n");
        printf("\t1. Buat Proyek Baru\n");
        printf("\t2. Muat Proyek dari Berkas\n");
        printf("\t3. Keluar\n");
        do{
            printf("Masukan : ");
            gets(pilihan_s);
            pilihan=atoi(pilihan_s);
            if (pilihan<1 || pilihan>3){
                printf("Input Salah. Ulangi\n");
            }
        }
        while (pilihan<1 || pilihan>3);
        if (pilihan ==1){
            NewProject(projectName, &pcb);
			MenuUtama(projectName, &pcb);
        } else if (pilihan == 2){
            LoadProject(projectName, &pcb, &isSuccess);
            if (isSuccess==false){
                printf("File tidak dapat dibuka.\n");
            } else {
				MenuUtama(projectName, &pcb);
			}
		} else if (pilihan == 3){
            isQuitMain=true;
        }
	}

	free(projectName);

	return 0;
}
