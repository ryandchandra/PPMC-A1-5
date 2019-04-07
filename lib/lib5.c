//***********************************************************//
//                      [ Source Code ]
//
// Institution       : Institut Teknologi Bandung
// Name              : Naila Amani
// File Name         : lib5.c
// Dependency        : stdio.h
//
// Description:
//     lib5.c berisi tentang perintah PrintLayout dan PrintRouting.
//
// Status:
// 1. Naila Amani - 13217012 : Create the file
//***********************************************************//

#include <stdio.h>


void PrintLayout(pcb_t pcb){
//melakukan proses mencetak/print hasil layout pada pcb

	//KAMUS LOKAL
	int i,j;
    
	
	//ALGORITMA
	printf("   ");
	
	for(i=0; i<pcb.panjang; i++)		 
    	{
    		printf(" %3d ", i+1); //Sebagai nomer 1,2,3.. memanjang
	}
	
	
	printf("\n");
	
	
	for(j=0; j<pcb.lebar; j++)
 	{
    		printf(" %3d ", j+1); //Sebagai nomer 1,2,3.. melebar
    		for(i=0; i<pcb.panjang; i++)
        	{
		//mencetak hasil layout
		printf(" %3s ", pcb.layout[i][j]); 
		}
	printf("\n");
	}

}


void PrintRouting(pcb_t pcb){	
//melakukan proses mencetak/print hasil routing pada pcb

	//KAMUS LOKAL
	int i,j; 
 	 	
	//ALGORITMA
	printf("   ");
	
    for(i=0; i<pcb.panjang; i++)
	{
    	printf(" %3d ", i+1); //Sebagai nomer 1,2,3.. memanjang
	}
	printf("\n");

	for(j=0; j<pcb.lebar; j++)
		{
    		printf(" %3d ", j+1);	//Sebagai nomer 1,2,3.. melebar
	    	for(i=0; i<pcb.panjang; i++)
      	  		{
			//mencetak hasil routing
			printf(" %3c ", pcb.routing[i][j]); 
			}
		printf("\n");
	}
}
