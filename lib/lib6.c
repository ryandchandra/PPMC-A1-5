//***********************************************************//
//                      [ Source Code ]
//
// Institution       : Institut Teknologi Bandung
// Name              : Naila Amani
// File Name         : lib6.c
// Dependency        : stdio.h
//
// Description:
//     lib6.c berisi tentang perintah mereset layout
// dan routing pada pcb
// Status:
// 1. Naila Amani - 13217012 : Create the file
//***********************************************************//

#include <stdio.h>

void ResetRouting(pcb_t *pcb)
{	//melakukan proses mereset Routing pada PCB

	int i,j;

	printf("   ");
	
	//menuliskan nomer 1,2,3.. memanjang
    	for(i=0; i<pcb->panjang; i++)
    		{
    		printf("%3d", i+1);
		}
	
	printf("\n");
	
	for(j=0; j<pcb->lebar; j++)
    		{
    		printf("%3d", j+1); //menuliskan 1,2,3... melebar
    		for(i=0; i<pcb->panjang; i++)
        		{
        		pcb->routing[j][i]=' ';
			//mengosongkan routing
			printf("%3c", pcb->routing[j][i]); 
			//mencetak hasil pengosongan
			}
		printf("\n");
	}
}


void ResetLayout(pcb_t *pcb)
{
	int i,j;
    
 	printf("   ");
	
	//penomeran 1,2,3 memanjang pada tabel tampilan
	for(i=0; i<pcb->panjang; i++)
    	{
    	printf("%3d", i+1);
	}
	
	printf("\n");

	for(j=0; j<pcb->lebar; j++)
    	{
    	printf(" %3d ", j+1); //penomeran 1,2,3 melebar
	    	for(i=0; i<pcb->panjang; i++)
        	{
			//mereset layout pada layout
        		strcpy (pcb->layout[j][i]," "); 
			//mencetak layout hasil reset
			printf("%3s", pcb->layout[j][i]);
		}
	printf("\n");
	}

	pcb->countR=0;
	pcb->countC=0;
	pcb->countJ=0;
	pcb->countT=0;
	
	//inisialisasi isi pcb
	for (i=0;i<4;i++){
		pcb->R[i][0]=' ';
		pcb->R[i][1]='\0';
	}
	for (i=0;i<3;i++){
		pcb->C[i][0]=' ';
		pcb->C[i][1]='\0';
	}
	for (i=0;i<4;i++){
		pcb->J[i][0]=' ';
		pcb->J[i][1]='\0';
	}
	pcb->T='\0';

}
