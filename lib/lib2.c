//***********************************************************//
//                      [ Source Code ]
//
// Institution       : Institut Teknologi Bandung
// Name              : Ryan Dharma Chandra
// File Name         : lib2.c
// Dependency        : stdio.h, stdlib.h, stdbool.h
//
// Description:
//     Please only write 64 characters maximum. If you write
// more than 64, please write it on the next line. Thanks!
//
// Status:
// 1. Ryan Dharma Chandra - 13217018 : Create the file
//***********************************************************//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void NewProject(char *projectName, pcb_t *pcb){
	//Membuat Project Baru
	
	//KAMUS LOKAL
	short int i,j;
	int panjang, lebar;
	char *s = (char*)malloc(100*sizeof(char));

	//ALGORITMA
	printf("====== Membuat Proyek Baru ======\n");
	printf("Masukkan nama proyek: ");
	gets(projectName);
	do { //validasi
		printf("Masukkan ukuran PCB NxM (N,M<40): ");
		gets(s);
		panjang=atoi(strtok(s," "));
		lebar=atoi(strtok(NULL,"\n"));
		if ((panjang>PANJANGMAX)||(lebar>LEBARMAX)){
			printf("Error. Ukuran PCB maksimal 40x40.\n\n");
		} else if (panjang==0){
			printf("Error. Masukkan ukuran PCB dengan benar.\n\n");
		} else if ((panjang<0)||(lebar<0)){
			printf("Error. Ukuran PCB harus positif.\n\n");
		}
	} while ((panjang>PANJANGMAX)||(panjang<=0)||(lebar>LEBARMAX)||(lebar<=0));
	
	pcb->panjang=panjang;
	pcb->lebar=lebar;
	
	//inisialisasi count
	pcb->countR=0;
	pcb->countC=0;
	pcb->countJ=0;
	pcb->countT=0;
	
	//inisialisasi isi pcb
	for(i=0;i<pcb->lebar;i++){
		for(j=0;j<pcb->panjang;j++){
			pcb->layout[i][j][0]=' ';
			pcb->layout[i][j][1]='\0';
			pcb->routing[i][j]=' ';
		}
	}
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
	
	free(s);
}

void LoadProject(char *projectName, pcb_t *pcb, bool *isSuccess){
	//Memuat project dari file yang sudah ada
	
	//KAMUS LOKAL
	char *layoutFile = (char*)malloc(100*sizeof(char));
	char *routingFile = (char*)malloc(100*sizeof(char));
	char *s = (char*)malloc(150*sizeof(char));
	char *token;
	short int i,j;
	short int currentR, currentC, currentT, currentJ;
	FILE *fLayout, *fRouting;
	
	//ALGORITMA
	printf("====== Memuat Proyek ======\n");
	printf("Masukkan nama proyek: ");
	gets(projectName);

	//Membuat nama file
	strcpy(layoutFile, projectName);
	strcpy(routingFile, projectName);
	strcat(layoutFile, LAYOUTEXTENSION);
	strcat(routingFile, ROUTINGEXTENSION);
	
	//Membuka file
	fLayout = fopen(layoutFile, "r");
	fRouting = fopen(routingFile, "r");
	
	//Cek apakah file berhasil dibuka
	if ((fLayout==NULL)||(fRouting==NULL)){ //File gagal dibuka, munculkan pesan kesalahan
		printf("Error. Project tidak ditemukan. Silakan ulangi lagi.\n\n");
		*isSuccess = false;
	} else { //File berhasil dibuka
		//inisialisasi untuk perhitungan jumlah R,C,T,J pada file
		pcb->countR=0;
		pcb->countC=0;
		pcb->countJ=0;
		pcb->countT=0;
		currentR=0;
		currentC=0;
		currentT=0;
		currentJ=0;
		//inisialisasi nama komponen dalam array R,C,T,J
		for (i=0;i<4;i++){
			pcb->R[i][0]=' ';
			pcb->R[i][1]='\0';
		}
		for (i=0;i<4;i++){
			pcb->C[i][0]=' ';
			pcb->C[i][1]='\0';
		}
		for (i=0;i<4;i++){
			pcb->J[i][0]=' ';
			pcb->J[i][1]='\0';
		}
		pcb->T='\0';
		
		//Membaca file layout
		bool cekPanjang=false;
		i=0;
		while (!feof(fLayout)){
			fgets(s, 150, fLayout);
			token = strtok(s, ",");
			j=0;
			while (token!=NULL){
				if (token[strlen(token)-1]=='\n'){
					//khusus untuk token di ujung baris, hapuskan enter
					token[strlen(token)-1]='\0';
				}
				pcb->layout[i][j][0]=token[0];
				pcb->layout[i][j][1]=token[1];
				pcb->layout[i][j][2]='\0';
				if (pcb->layout[i][j][0]=='R'){ //Jika komponen resistor (R)
					pcb->countR++;
					if (IsResistorExist(token,*pcb)==false){
						//Cek apakah nama resistor seperti token sudah ada di array atau belum (sudah diinput sebelumnya)
						pcb->R[currentR][0]=token[0];
						pcb->R[currentR][1]=token[1];
						pcb->R[currentR][2]='\0';
						currentR++;
					}
				} else if (pcb->layout[i][j][0]=='C'){ //Jika komponen kapasitor (C)
					pcb->countC++;
					if (IsCapacitorExist(token,*pcb)==false){
						//Cek apakah nama kapasitor seperti token sudah ada di array atau belum (sudah diinput sebelumnya)
						pcb->C[currentC][0]=token[0];
						pcb->C[currentC][1]=token[1];
						pcb->C[currentC][2]='\0';
						currentC++;
					}
				} else if (pcb->layout[i][j][0]=='T'){ //Jika komponen transistor (T)
					pcb->countT++;
					pcb->T='T';
				} else if (pcb->layout[i][j][0]=='J'){ //Jika komponen junction (J)
					pcb->countJ++;
					if (IsJunctionExist(token,*pcb)==false){
						//Cek apakah nama junction seperti token sudah ada di array atau belum (sudah diinput sebelumnya)
						pcb->J[currentJ][0]=token[0];
						pcb->J[currentJ][1]=token[1];
						pcb->J[currentJ][2]='\0';
						currentJ++;
					}
				}
				j++;
				//Lanjutkan membaca sampai koma selanjutnya
				token = strtok(NULL, ",");
			}
			if (cekPanjang==false){
				pcb->panjang=j;
				cekPanjang=true;
			}
			i++;
		}
		pcb->lebar=i-1;
		
		pcb->countR=pcb->countR/2;
		pcb->countC=pcb->countC/2;
		pcb->countT=pcb->countT/3;
		pcb->countJ=pcb->countJ/2;
		
		//Membaca file routing
		i=0;
		while (!feof(fRouting)){
			fgets(s, 150, fRouting);
			token = strtok(s, ",");
			j=0;
			while (token!=NULL){
				pcb->routing[i][j]=token[0];
				j++;
				token = strtok(NULL, ",");
			}
			i++;
		}
		
		*isSuccess = true;
	}
	
	//tutup file
	fclose(fLayout);
	fclose(fRouting);

	free(layoutFile);
	free(routingFile);
	free(s);
}