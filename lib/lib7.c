//***********************************************************//
//                      [ Source Code ]
//
// Institution       : Institut Teknologi Bandung
// Name              : Naila Amani
// File Name         : lib7.c
// Dependency        : stdio.h, stdlib.h, string.h
//
// Description:
//     lib7.c berisi tentang perintah saving pada CSV.
// Akan terdapat 2 perintah yaitu, save untuk csv layout dan
// csv routing.
//
// Status:
// 1. Naila Amani - 13217012 : Create the file
//***********************************************************//

#include<stdio.h>
#include<stdlib.h>
#include<string.h>


void SaveLayout(char *filename, pcb_t pcb)
{
	
	//membuka file eksternal
	FILE *fp;
	char *fileLayout=(char*)calloc(20,sizeof(char));
	
	//membuat nama file eksternal dengan menggabungkan
	//inputan namafile dengan _layout.csv
	strcat(fileLayout,filename);
	strcat(fileLayout,"_layout.csv");
	
	fp=fopen(fileLayout,"w+");
 
	int i,j;
	
	//menuliskan kedalam file
	for(j=0;j<pcb.lebar;j++)
		{
    		for(i=0;i<pcb.panjang;i++)
			{
			fprintf(fp,"%s,",pcb.layout[i][j]);
    			}
    		fprintf(fp,"\n");
		}
	
	fclose(fp); //menutup file

	//keterangan
	printf("\n Layout disimpan dalam berkas %s", fileLayout);
	printf("\n");
	printf("\n %s file berhasil disimpan",fileLayout);

	free(fileLayout);

}


void SaveRouting(char *filename, pcb_t pcb)
{	
	//membuka file eksternal
	FILE *fp;
	char *fileRouting=(char*)calloc(20,sizeof(char));
	
	//membuat nama file eksternal dengan menggabungkan
	//inputan namafile dengan _layout.csv
	strcat(fileRouting,filename);
	strcat(fileRouting,"_routing.csv");
	
	fp=fopen(fileRouting,"w+");
 
 	//kamus lokal
	int i,j;

	//menuliskan pada file
	for(j=0;j<pcb.lebar;j++)
		{
	    	for(i=0;i<pcb.panjang;i++)
			{
			fprintf(fp,"%c,",pcb.routing[i][j]);
    			}
    		fprintf(fp,"\n");
		}
	
	//menutup file
	fclose(fp);

	//keterangan
	printf("\n Routing disimpan dalam berkas %s", fileRouting);
	printf("\n");
	printf("\n %s file berhasil disimpan",fileRouting);

	free(fileRouting);

}
