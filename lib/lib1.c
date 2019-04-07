#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "lib2.c"
#include "lib3.c"
#include "lib4.c"
#include "lib8.c"
#include "lib9.c"

//***********************************************************//
//                      [ Source Code ]
//
// Institution       : Institut Teknologi Bandung
// Name              : Johannes Felix Rimbun
// File Name         : lib1.c
// Dependency        : stdio.h, stdlib.h, stdbool.h, math.h, lib1.c, lib2,c
//lib3.c , lib4.c, lib5.c, lib6.c, lib7.c, lib8.c, lib9.c
//
// Description:
//     MENU UTAMA
//
//
// Status:
// 1. Johannes Felix Rimbun 13217006 : Create the file
//***********************************************************//
//Masih belum sempurna
void main(){
    //KAMUS LOKAL
    pcb_t *pcb;
    char *projectName;
    bool isQuitMain, isQuitMenuUtama = false;
    bool isSuccess;
    int pilihan;

    //ALGORITMA
    //mengalokasikan memori
    pcb=(pcb_t*)malloc(sizeof(pcb_t));
    projectName=(char*)malloc(20*sizeof(char));
    isSuccess=true;
    while (isQuitMain==false){
        printf("Menu: \n");
        printf("\t1. Buat Proyek Baru\n");
        printf("\t2. Muat Proyek dari Berkas\n");
        printf("\t3.");
        do{//mengulangi masukan sampai isSuccess berhasil
            do{
                printf("Masukan : ");
                scanf("%d", &pilihan);
                if (pilihan<1 || pilihan>3){
                    printf("Input Salah. Ulangi\n");
                }
            }
            while (pilihan<1 || pilihan>3);
            if (pilihan ==1){
                NewProject(projectName, pcb);
            }else if (pilihan == 2){
                LoadProject(projectName, pcb, &isSuccess);
                if (isSuccess==false){
                    printf("File tidak dapat dibuka.\n");
                }
            }else
                isQuitMain=true;
            }
        }while (isSuccess==false);
        while (isQuitMenuUtama==false && isQuitMain==false){
            printf("[Menu Utama]n");
            printf("Pilih Mode:\n");
            printf("\t1. Tampilkan layout\n");
            printf("\t2. Layouting Manual\n");
            printf("\t3. Tampilkan Routing\n");
            pritnf("\t4. Routing Manual\n");
            printf("\t5. Layout Otomatis\n");
            printf("\t6. Routing otomatis\n");
            printf("\t7. Design Rule Checker\n");
            printf("\t8. Reset Layout\n");
            printf("\t9. Reset Routing\n");
            printf("\t10. Help\n")
            printf("\t11. Simpan Proyek dan Keluar\n");
            printf("\t12. Keluar\n")
            printf("Pilih Mode : ");
            do{
                scanf("%d", pilihan);
            }while (pilihan>12 || pilihan<1);]
            if (pilihan==1){
                PrintLayout(pcb);
            }else if (pilihan==2){
                LayoutManual(pcb);
            }else if (pilihan == 3){
                PrintRouting(pcb);
            }else if (pilihan == 4){
                RoutingManual(pcb);
            }else if (pilihan ==5){
                LayoutOtomatis(pcb);
            }else if (pilihan == 6){
                RoutingOtomatis(pcb);
            }else if (pilihan == 7){
                DRC(pcb);
            }else if (pilihan == 8){
                ResetLayout(pcb);
            }else if (pilihan == 9){
                ResetRouting(pcb);
            }else if (pilihan == 10){
                printf("HELLLPPPPPPP");
            }else if (pilihan == 11){
                Save(pcb);
                isQuitMenuUtama==false;
            }else if (pilihan == 12){
                isQuitMenuUtama==false;
            }
        }
    }




}

