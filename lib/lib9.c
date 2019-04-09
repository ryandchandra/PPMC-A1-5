//***********************************************************//
//                      [ Source Code ]
//
// Institution       : Institut Teknologi Bandung
// Name              : Johannes Felix Rimbun
// File Name         : lib9.c
// Dependency        : stdio.h, stdlib.h, stdbool.h, math.h, lib3.c
//
// Description:
//     lib9.c merupakan implementasi dari fungsi RoutingOtomatis dan LayoutOtomatis
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

void LayoutOtomatis(pcb_t* pcb){
	int prevpanjang, prevlebar;
	prevpanjang = pcb->panjang;
	prevlebar = pcb->lebar;
	
    printf("Layout Otomatis/Routing Otomatis bekerja Pada Rangkaian Common Emitter\n");
    //verifikasi, memastikan panjang dan lebar pcb minimal 20
    if (pcb->panjang <20 || pcb->lebar <20){
        printf("Ukuran pcb diubah menjadi 20*20\n");
        pcb->panjang = 20;
        pcb->lebar = 20;
    }
	int i, j;
	if ((prevpanjang<pcb->panjang)||(prevlebar<pcb->lebar)){
		for (i=prevpanjang;i<pcb->panjang;i++){
			for (j=0;j<pcb->lebar;j++){
				pcb->routing[j][i]=' ';
			}
		}
		for (i=0;i<pcb->panjang;i++){
			for (j=prevlebar;j<pcb->lebar;j++){
				pcb->routing[j][i]=' ';
			}
		}
	}
    //inisialisai : mengubah semua bagian layout[i][j] menjadi "  "
    for (i=0; i<pcb->lebar; i++){
        for (j=0; j<pcb->panjang; j++){
            strcpy(pcb->layout[i][j]," ");
        }
    }
    //mengubah data counter dan nama komponen pada pcb
    pcb->countR=4;
    strcpy(pcb->R[0],"R1");
    strcpy(pcb->R[1],"R2");
    strcpy(pcb->R[2],"R3");
    strcpy(pcb->R[3],"R4");
    pcb->countC=2;
    strcpy(pcb->C[0],"C1");
    strcpy(pcb->C[1],"C2");
    pcb->countT=1;
    pcb->T='T';
    pcb->countJ=3;
    strcpy(pcb->J[0],"J1");
    strcpy(pcb->J[1],"J2");
    strcpy(pcb->J[2],"J3");
    
    //mengubah matriks layout menjadi berisi kaki-kaki komponen yang digunakan
    strcpy(pcb->layout[0][8],"J1");
    strcpy(pcb->layout[2][5],"R1");
    strcpy(pcb->layout[6][5],"R1");
    strcpy(pcb->layout[9][1],"C1");
    strcpy(pcb->layout[9][4],"C1");
    strcpy(pcb->layout[9][0],"J2");
    strcpy(pcb->layout[13][5],"R2");
    strcpy(pcb->layout[18][5],"R2");
    strcpy(pcb->layout[2][11],"R3");
    strcpy(pcb->layout[6][11],"R3");
    strcpy(pcb->layout[13][11],"R4");
    strcpy(pcb->layout[18][11],"R4");
    strcpy(pcb->layout[8][13],"C2");
    strcpy(pcb->layout[8][17],"C2");
    strcpy(pcb->layout[8][19],"J3");
    strcpy(pcb->layout[8][9],"Tc");
    strcpy(pcb->layout[9][9],"Tb");
    strcpy(pcb->layout[10][9],"Te");
    strcpy(pcb->layout[19][8],"J1");
	strcpy(pcb->layout[19][9],"J2");
	strcpy(pcb->layout[19][10],"J3");
    

}
void RoutingOtomatis(pcb_t* pcb){
    LayoutOtomatis(pcb);
    //membuat jalur pada pcb->routing
    strcpy(pcb->routing[0],"     !!!!!!!        ");
    strcpy(pcb->routing[1],"     !     !        ");
    strcpy(pcb->routing[2],"     !     !        ");
    strcpy(pcb->routing[3],"                    ");
    strcpy(pcb->routing[4],"                    ");
    strcpy(pcb->routing[5],"                    ");
    strcpy(pcb->routing[6],"     @     ^        ");
    strcpy(pcb->routing[7],"     @     ^        ");
    strcpy(pcb->routing[8],"     @   ^^^^^^  (((");
    strcpy(pcb->routing[9],"##  @@@@@@          ");
    strcpy(pcb->routing[10],"     @   $$$        ");
    strcpy(pcb->routing[11],"     @     $        ");
    strcpy(pcb->routing[12],"     @     $        ");
    strcpy(pcb->routing[13],"     @     $        ");
    strcpy(pcb->routing[14],"                    ");
    strcpy(pcb->routing[15],"                    ");
    strcpy(pcb->routing[16],"                    ");
    strcpy(pcb->routing[17],"     #     #        ");
    strcpy(pcb->routing[18],"     #     #        ");
    strcpy(pcb->routing[19],"     #######        ");
}

