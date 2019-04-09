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
	char *fileLayout=(char*)malloc(50*sizeof(char));
	
	//membuat nama file eksternal dengan menggabungkan
	//inputan namafile dengan _layout.csv
	strcpy(fileLayout,filename);
	strcat(fileLayout,"_layout.csv");
	
	fp=fopen(fileLayout,"w+");
 
	int i,j;
	
	//menuliskan kedalam file
	for(j=0;j<pcb.lebar-1;j++)
		{
    		for(i=0;i<pcb.panjang-1;i++)
			{
			fprintf(fp,"%s,",pcb.layout[j][i]);
    			}
			fprintf(fp,"%s\n",pcb.layout[j][pcb.panjang-1]);
		}
		
	for(i=0;i<pcb.panjang-1;i++)
	{
		fprintf(fp,"%s,",pcb.layout[pcb.lebar-1][i]);
	}
	fprintf(fp,"%s\n",pcb.layout[pcb.lebar-1][pcb.panjang-1]);
	
	fclose(fp); //menutup file

	//keterangan
	printf("\n Layout disimpan dalam berkas %s", fileLayout);
	printf("\n");
	printf("\n %s file berhasil disimpan\n",fileLayout);

	free(fileLayout);

}

void SaveRouting(char *filename, pcb_t pcb)
{	
	//membuka file eksternal
	FILE *fp;
	char *fileRouting=(char*)malloc(50*sizeof(char));
	
	//membuat nama file eksternal dengan menggabungkan
	//inputan namafile dengan _routing.csv
	strcpy(fileRouting,filename);
	strcat(fileRouting,"_routing.csv");
	
	fp=fopen(fileRouting,"w+");
 
 	//kamus lokal
	int i,j;

	//menuliskan pada file
	for(j=0;j<pcb.lebar-1;j++)
		{
	    	for(i=0;i<pcb.panjang-1;i++)
			{
			fprintf(fp,"%c,",pcb.routing[j][i]);
    			}
			fprintf(fp,"%c\n",pcb.routing[j][pcb.panjang-1]);
		}
	
	for(i=0;i<pcb.panjang-1;i++)
	{
		fprintf(fp,"%c,",pcb.routing[pcb.lebar-1][i]);
	}
	fprintf(fp,"%c\n",pcb.routing[pcb.lebar-1][pcb.panjang-1]);
	
	//menutup file
	fclose(fp);

	//keterangan
	printf("\n Routing disimpan dalam berkas %s", fileRouting);
	printf("\n");
	printf("\n %s file berhasil disimpan\n",fileRouting);

	free(fileRouting);

}