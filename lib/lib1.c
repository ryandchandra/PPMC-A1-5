#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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
void MenuUtama(char *projectName, pcb_t *pcb){
    //KAMUS LOKAL
    bool isQuitMenuUtama = false;
    int pilihan;

    //ALGORITMA
    //mengalokasikan memori
    while (isQuitMenuUtama==false){
        printf("[Menu Utama]\n");
        printf("Pilih Mode:\n");
        printf("\t1. Tampilkan Layout\n");
        printf("\t2. Layouting Manual\n");
        printf("\t3. Tampilkan Routing\n");
        printf("\t4. Routing Manual\n");
        printf("\t5. Layout Otomatis\n");
        printf("\t6. Routing otomatis\n");
        printf("\t7. Design Rule Checker\n");
        printf("\t8. Reset Layout\n");
        printf("\t9. Reset Routing\n");
        printf("\t10. Help\n");
        printf("\t11. Simpan Proyek dan Keluar\n");
        printf("\t12. Keluar\n");
        printf("Pilih Mode : ");
        do{
            scanf("%d", &pilihan);
			if (pilihan>12 || pilihan<1){
				printf("Input salah. Ulangi\n");
			}
        }while (pilihan>12 || pilihan<1);
        if (pilihan==1){
            PrintLayout(*pcb);
        }else if (pilihan==2){
            LayoutManual(pcb);
        }else if (pilihan == 3){
            PrintRouting(*pcb);
        }else if (pilihan == 4){
            RoutingManual(pcb);
        }else if (pilihan ==5){
            LayoutOtomatis(pcb);
        }else if (pilihan == 6){
            RoutingOtomatis(pcb);
        }else if (pilihan == 7){
            DRC(*pcb);
        }else if (pilihan == 8){
            ResetLayout(pcb);
        }else if (pilihan == 9){
            ResetRouting(pcb);
        }else if (pilihan == 10){
            printf("[Bantuan]\n");
            printf("1. Tampilkan layout\n");
            printf("Menampilkan layout yang berisi lokasi kaki-kaki komponen\n");
            printf("2. Layouting Manual\n");
            printf("Menempatkan kaki-kaki komponen\n");
            printf("3. Tampilkan Routing\n");
            printf("Menampilkan jalur-jalur pada PCB\n");
            printf("4. Routing Manual\n");
            printf("Menambahkan jalur pada PCB\n");
            printf("5. Layout Otomatis\n");
            printf("Menambahkan kaki-kaki komponen secara otomatis membentuk rangkaian Common Emitter\n");
            printf("6. Routing otomatis\n");
            printf("Membentuk jalur PCB secara otomatis membentuk rangkaian Common Emitter\n");
            printf("7. Design Rule Checker\n");
            printf("Memeriksa apakah jalur dan komponen PCB sesuai dengan file DRC\n");
            printf("8. Reset Layout\n");
            printf("Menghapus layout\n");
            printf("9. Reset Routing\n");
            printf("Menghapus routing\n");
            printf("10. Help\n");
            printf("Bantuan\n");
            printf("11. Simpan Proyek dan Keluar\n");
            printf("Menyimpan file pada .csv\n");
            printf("12. Keluar\n");
        }else if (pilihan == 11){
            SaveLayout(projectName,*pcb);
			SaveRouting(projectName,*pcb);
            isQuitMenuUtama=true;
        }else if (pilihan == 12){
            isQuitMenuUtama=true;
        }
    }
}

