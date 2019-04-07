#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include "lib7.c"

void LayoutOtomatis(pcb_t* pcb){
    printf("Layout Otomatis/Routing Otomatis bekerja Pada Rangkaian Common Emitter\n");
    if (pcb->panjang <20 || pcb->lebar <20){
        printf("Ukuran pcb diubah menjadi 20*20\n");
        pcb->panjang = 20;
        pcb->lebar = 20;
    }
    int i, j;
    for (i=0; i<20; i++){
        for (j=0; j<20; j++){
            strcpy(pcb->layout[i][j],"  ");
        }
    }
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
    strcpy(pcb->layout[10][17],"C2");
    strcpy(pcb->layout[8][19],"J4");
    strcpy(pcb->layout[8][9],"Tc");
    strcpy(pcb->layout[9][9],"Tb");
    strcpy(pcb->layout[10][9],"Tc");
    strcpy(pcb->layout[19][8],"J3");

     strcpy(pcb->routing[0],"     !!!!!!!        ");
     strcpy(pcb->routing[1],"     !     !        ");
     strcpy(pcb->routing[2],"     !     !        ");
     strcpy(pcb->routing[3],"                    ");
     strcpy(pcb->routing[4],"                    ");
     strcpy(pcb->routing[5],"                    ");
     strcpy(pcb->routing[6],"     @     ^        ");
     strcpy(pcb->routing[7],"     @     ^        ");
     strcpy(pcb->routing[8],"     @   ^^^^    (((");
     strcpy(pcb->routing[9],"##  @@@@@@          ");
    strcpy(pcb->routing[10],"     @   $$$        ");
    strcpy(pcb->routing[11],"           $        ");
    strcpy(pcb->routing[12],"     @     $        ");
    strcpy(pcb->routing[13],"     @     $        ");
    strcpy(pcb->routing[14],"                    ");
    strcpy(pcb->routing[15],"                    ");
    strcpy(pcb->routing[16],"                    ");
    strcpy(pcb->routing[17],"     #     #        ");
    strcpy(pcb->routing[18],"     #######        ");
    strcpy(pcb->routing[19],"                    ");



}
void RoutingOtomatis(pcb_t* pcb){
    LayoutOtomatis(pcb);
}

