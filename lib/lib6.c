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

void ResetRouting(pcb_t pcb)
{	//melakukan proses mereset Routing pada PCB

	int i,j;

	printf("   ");
	
	//menuliskan nomer 1,2,3.. memanjang
    	for(i=0; i<pcb.panjang; i++)
    		{
    		printf(" %3d ", i);
		}
	
	printf("\n");

	
	for(j=0; j<pcb.lebar; j++)
    		{
    		printf(" %3d ", j+1); //menuliskan 1,2,3... melebar
    		for(i=0; i<pcb.panjang; i++)
        		{
        		pcb.routing[i][j]=' ';
			//mengosongkan routing
			printf(" %3c ", pcb.routing[i][j]); 
			//mencetak hasil pengosongan
			}
		printf("\n");
	}
}


void ResetLayout(pcb_t pcb)
{
	int i,j;
    
 	printf("   ");
	
	//penomeran 1,2,3 memanjang pada tabel tampilan
	for(i=0; i<pcb.panjang; i++)
    	{
    	printf(" %3d ", i+1);
	}
	
	printf("\n");

	for(j=0; j<pcb.lebar; j++)
    	{
    	printf(" %3d ", j+1); //penomeran 1,2,3 melebar
	    	for(i=0; i<pcb.panjang; i++)
        	{
			//mereset layout pada layout
        		strcpy (pcb.layout[i][j]," "); 
			//mencetak layout hasil reset
			printf(" %3s ", pcb.layout[i][j]);
		}
	printf("\n");
	}

}
