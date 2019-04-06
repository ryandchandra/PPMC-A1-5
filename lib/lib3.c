//***********************************************************//
//                      [ Source Code ]
//
// Institution       : Institut Teknologi Bandung
// Name              : Ryan Dharma Chandra
// File Name         : lib3.c
// Dependency        : stdio.h, stdlib.h, stdbool.h, math.h
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
#include <math.h>

void LayoutManual(pcb_t *pcb){
	//Melakukan layout manual pada PCB
	
	//KAMUS LOKAL
	bool isQuit=false;
	bool isTrue=false;
	char *s = (char*)malloc(20*sizeof(char));
	
	//ALGORITMA
	printf("Isi 'q' atau 'Q' untuk kembali ke menu\n");
	do {
		printf("Pilih Komponen (R,C,T,J): ");
		gets(s);
		if (strlen(s)==1){ //panjang s hanya satu karakter
			if ((s[0]=='q')||(s[0]=='Q')){ //quit
				isQuit = 1;
			} else if ((s[0]=='R')||(s[0]=='C')||(s[0]=='J')){
				printf("Error. Nama komponen R,C,J harus dua karakter.\n\n");
			} else if (s[0]=='T'){ //input transistor
				if (pcb->countT==TMAX){
					printf("Error. Jumlah transistor sudah max(%d).\n\n",TMAX);
				} else {
					InputTransistorCoordinate(pcb,&isQuit);
				}
			} else {
				printf("Error. Tidak ada komponen. Silakan masukkan komponen R,C,T,J.\n\n");
			}
		} else if (strlen(s)>2){ //panjang s lebih dari dua karakter
			printf("Error. Nama komponen harus dua karakter.\n");
		} else { //panjang s 2 karakter
			if (IsComponentCorrect(s)==false){
				printf("Error. Tidak ada komponen. Silakan masukkan komponen R,C,T,J.\n\n");
			} else {
				if (s[0]=='R'){ //input resistor
					if (pcb->countR==RMAX){ //jumlah resistor sudah 4
						printf("Error. Jumlah resistor sudah max(%d).\n\n",RMAX);
					} else if (IsResistorExist(s,*pcb)==true){
						printf("Error. Nama %s sudah dipakai.\n\n",s);
					} else {
						//cek R
						InputRCJCoordinate(pcb,'R',JARAKMINR,s,&isQuit);
					}
				} else if (s[0]=='C'){ //input kapasitor
					if (pcb->countC==CMAX){ //jumlah kapasitor sudah 3
						printf("Error. Jumlah kapasitor sudah max(%d).\n\n",CMAX);
					} else if (IsCapacitorExist(s,*pcb)==true){
						printf("Error. Nama %s sudah dipakai.\n\n",s);
					} else {
						//cek C
						InputRCJCoordinate(pcb,'C',JARAKMINC,s,&isQuit);
					}
				} else if (s[0]=='J'){ //input junction
					if (pcb->countJ==JMAX){ //jumlah junction sudah 4
						printf("Error. Jumlah junction sudah max(%d).\n\n",JMAX);
					} else if (IsJunctionExist(s,*pcb)==true){
						printf("Error. Nama %s sudah dipakai.\n\n",s);
					} else {
						//cek J
						InputRCJCoordinate(pcb,'J',JARAKMINJ,s,&isQuit);
					}
				} else if (s[0]=='T'){
					printf("Error. Nama transistor hanya satu karakter yaitu 'T'.\n\n");
				}
			}
		}
	} while (isQuit==0);
	
	free(s);
}

short int PosisiKoma(char *s){
	//Mengembalikan posisi dari koma pada string, -1 jika koma tidak ada
	
	//KAMUS LOKAL
	short int i;
	bool found = false;

	//ALGORITMA
	i = 0;
	while ((i<strlen(s))&&(found==0)){
		if (s[i]==','){
			//Jika ditemukan koma, found = true
			found = true;
		} else {
			//Jika bukan koma, lanjut ke indeks selanjutnya
			i++;
		}
	}
	
	if (found==true){
		//Jika found = true (koma ditemukan), return indeks
		return i;
	} else {
		//found = false, iterasi dilakukan sampai akhir dari string
		return -1;
	}
}

bool IsLayoutFree(pcb_t pcb, koor_t koor){
	//Mengecek apakah layout pada posisi koor free (tidak ada komponen) atau tidak
	if ((pcb.layout[koor.y-1][koor.x-1][0]==' ')||(pcb.layout[koor.y-1][koor.x-1][0]=='\0')){
		//Tidak ada komponen (isi array hanya spasi atau null)
		return true;
	} else {
		//Ada komponen pada posisi xpos, ypos
		return false;
	}
}

bool IsKeluar(char *s){
	//Mengecek apakah inputan user 'q' atau 'Q' (keluar)
	//Return true jika input 'q' atau 'Q', false jika tidak
	if (strlen(s)==1){
		if ((s[0]=='q')||(s[0]=='Q')){
			return true;
		} else {
			return false;
		}
	} else {
		return false;
	}
}

bool IsStringNumber(char *s){
	//Mengecek apakah string s seluruhnya terdiri dari angka atau tidak
	//Return true jika string seluruhnya angka, false jika ada karakter yang bukan angka
	
	//KAMUS LOKAL
	short int i;
	bool found = false;
	
	//ALGORITMA
	i = 0;
	while ((i<strlen(s))&&(found==false)){
		if ((s[i]<'0')||(s[i]>'9')){
			//Jika ada karakter dalam string yang bukan angka
			found = true;
		} else {
			//Jika tidak, lanjut iterasi
			i++;
		}
	}
	
	return !(found);
}

bool IsComponentCorrect(char *s){
	//Mengecek apakah inputan string berupa nama komponen yang benar
	//Return true jika inputan berupa nama komponen yang benar, false jika tidak
	
	if ((s[0]!='R')&&(s[0]!='C')&&(s[0]!='T')&&(s[0]!='J')){
		return false;
	} else {
		return true;
	}
}

bool IsInsidePCB(pcb_t pcb, koor_t koor){
	//Mengecek apakah posisi koor berada di dalam range PCB atau tidak
	//Return true jika koor berada di dalam range pcb, false jika tidak

	if ((koor.x>pcb.panjang)||(koor.y>pcb.lebar)){
		//Kasus xpos dan ypos lebih besar dari panjang dan lebar PCB
		return false;
	} else if ((koor.x<=0)||(koor.y<=0)){
		//Kasus xpos dan ypos negatif atau 0
		return false;
	} else {
		return true;
	}
}

bool IsDiagonal(koor_t titik1, koor_t titik2){
	//Mengecek apakah posisi (x1,y1) dan (x2,y2) diagonal atau tidak
	//Return true jika titik1 dan titik2 berhubungan secara diagonal, false jika tidak
	
	if ((titik1.x==titik2.x)||(titik1.y==titik2.y)){
		return false;
	} else {
		return true;
	}
}

void ParseKoordinat(char *s, koor_t *koor, bool *isSuccess){
	//Parse koordinat dari string s menjadi koordinat koor
	//Output isSuccess true jika berhasil, false jika gagal
	//Output koor sebagai hasil parse koordinat dari s jika berhasil
	
	//KAMUS LOKAL
	char *x = (char*)malloc(10*sizeof(char));
	char *y = (char*)malloc(10*sizeof(char));
	short int i,j;
	
	//ALGORITMA
	if (PosisiKoma(s)==-1){
		//Kasus tidak ada koma pada string s
		printf("Error. Masukkan koordinat dengan benar.\n\n");
		*isSuccess = false;
	} else {
		//Parsing
		//Parse string di kiri koma sebagai y
		i = 0;
		j = 0;
		while (i<PosisiKoma(s)){
			y[j]=s[i];
			i++;
			j++;
		}
		y[j]='\0'; //terminate string y
		
		//Parse string di kanan koma sebagai x
		i++;
		j = 0;
		while (i<strlen(s)){
			x[j]=s[i];
			i++;
			j++;
		}
		x[j]='\0'; //terminate string x
		
		if ((IsStringNumber(x)==false)||(IsStringNumber(y)==false)){
			//Kasus string x dan y mengandung satu karakter bukan angka
			printf("Error. Masukkan koordinat dengan benar.\n\n");
			*isSuccess = false;
		} else {
			//Parsing berhasil dilakukan
			koor->x = atoi(x);
			koor->y = atoi(y);
			*isSuccess = true;
		}
	}
	
	free(x);
	free(y);
}

bool CheckTwoString(char *s1, char *s2){
	//Mengecek string s1 dan s2
	//Return true jika kedua string sama, false jika kedua string berbeda

	//KAMUS LOKAL
	short int i = 0;
	bool found = false;
	
	//ALGORITMA
	if ((strlen(s1)!=(strlen(s2)))){
		return false;
	} else {
		i = 0;
		while ((i<strlen(s1))&&(found==false)){
			if (s1[i]==s2[i]){
				i++;
			} else {
				found = true;
			}
		}
		if (found==true){
			return false;
		} else {
			return true;
		}
	}
}

bool IsResistorExist(char *R, pcb_t pcb){
	//Mengecek apakah nama resistor R sudah ada pada layout pcb
	//Return true jika nama resistor R sudah ada, false jika tidak
	
	//KAMUS LOKAL
	short int i;
	bool found = false;
	
	//ALGORITMA
	i = 0;
	while ((i<pcb.countR)&&(found==false)){
		if (CheckTwoString(R,pcb.R[i])){
			found = true;
		} else {
			i++;
		}
	}
	
	return found;
}
	
bool IsCapacitorExist(char *C, pcb_t pcb){
	//Mengecek apakah nama kapasitor C sudah ada pada layout pcb
	//Return true jika nama kapasitor C sudah ada, false jika tidak

	//KAMUS LOKAL
	short int i;
	bool found = false;

	//ALGORITMA
	i = 0;
	while ((i<pcb.countC)&&(found==false)){
		if (CheckTwoString(C,pcb.C[i])){
			found = true;
		} else {
			i++;
		}
	}
	
	return found;
}

bool IsJunctionExist(char *J, pcb_t pcb){
	//Mengecek apakah nama junction J sudah ada pada layout pcb
	//Return true jika nama junction J sudah ada, false jika tidak
	
	//KAMUS LOKAL
	short int i;
	bool found = false;
	
	//ALGORITMA
	i = 0;
	while ((i<pcb.countJ)&&(found==false)){
		if (CheckTwoString(J,pcb.J[i])){
			found = true;
		} else {
			i++;
		}
	}
	
	return found;
}

void InputTransistorCoordinate(pcb_t *pcb, bool *isQuit){
	//Melakukan input koordinat dari transistor ke pcb
	//Output isQuit jika user quit dari mode ini (input 'q' atau 'Q')
	
	//KAMUS LOKAL
	char *s = (char*)malloc(20*sizeof(char));
	bool isTrue; //digunakan untuk cek apakah koordinat yang diinput sudah benar atau tidak
	bool isSuccess; //digunakan untuk cek apakah parse koordinat yang dilakukan berhasil atau tidak
	koor_t koorE,koorB,koorC; //koordinat emitter, base, dan collector

	//ALGORITMA
	//Input Emitter
	isTrue = false;
	isSuccess = false;
	do {
		printf("Koordinat Emitter: ");
		gets(s);
		if (IsKeluar(s)==true){
			*isQuit = true;
		} else {
			ParseKoordinat(s,&koorE,&isSuccess);
			if (isSuccess==true){
				if (IsInsidePCB(*pcb,koorE)==false){
					printf("Error. koordinat berada di luar range PCB.\n\n");
				} else if (IsLayoutFree(*pcb,koorE)==true){
					isTrue = true;
				} else {
					printf("Error. Sudah ada komponen di posisi tersebut.\n\n");
				}
			}
		}
	} while ((isTrue==false)&&(*isQuit==false));		
	
	if (*isQuit==false){
		//Input Base
		isTrue = false;
		isSuccess = false;
		do {
			printf("Koordinat Base: ");
			gets(s);
			if (IsKeluar(s)==true){
				*isQuit = true;
			} else {
				ParseKoordinat(s,&koorB,&isSuccess);
				if (isSuccess==true){
					if (IsInsidePCB(*pcb,koorB)==false){
						printf("Error. koordinat berada di luar range PCB.\n\n");
					} else if ((IsLayoutFree(*pcb,koorB)==true)&&(!((koorB.x==koorE.x)&&(koorB.y==koorE.y)))){
						isTrue = true;
					} else {
						printf("Error. Sudah ada komponen di posisi tersebut.\n\n");
					}
				}
			}
		} while ((isTrue==false)&&(*isQuit==false));
	}		

	if (*isQuit==false){
		//Input Collector
		isTrue = false;
		isSuccess = false;
		do {
			printf("Koordinat Collector: ");
			gets(s);
			if (IsKeluar(s)==true){
				*isQuit = true;
			} else {
				ParseKoordinat(s,&koorC,&isSuccess);
				if (isSuccess==true){
					if (IsInsidePCB(*pcb,koorC)==false){
						printf("Error. koordinat berada di luar range PCB.\n\n");
					} else if ((IsLayoutFree(*pcb,koorC)==true)&&(!((koorC.x==koorB.x)&&(koorC.y==koorB.y)))&&(!((koorC.x==koorE.x)&&(koorC.y==koorE.y)))){
						isTrue = true;
					} else {
						printf("Error. Sudah ada komponen di posisi tersebut.\n\n");
					}
				}
			}
		} while ((isTrue==false)&&(*isQuit==false));		
	}
	
	if (*isQuit==false){
		strcpy(pcb->layout[koorE.y-1][koorE.x-1],"Te");
		strcpy(pcb->layout[koorB.y-1][koorB.x-1],"Tb");
		strcpy(pcb->layout[koorC.y-1][koorC.x-1],"Tc");
		pcb->T='T';
		pcb->countT++;
	}
	
	free(s);
}

void InputRCJCoordinate(pcb_t *pcb, char component, int jarakmin, char *componentName, bool *isQuit){
	//Melakukan input koordinat untuk komponen resistor, kapasitor, dan junction
	//Input berupa jenis komponen dan jarak minimum
	//Output berupa pengisian pada matriks layout pcb dan array nama pada pcb
	
	//KAMUS LOKAL
	koor_t titik1, titik2;
	bool isTrue, isSuccess;
	char *s = (char*)malloc(20*sizeof(char));
	
	//ALGORITMA
	//Input Koordinat Pertama
	isTrue = false;
	isSuccess = false;
	do {
		printf("Koordinat Kaki 1 : ");
		gets(s);
		if (IsKeluar(s)==true){
			*isQuit = true;
		} else {
			ParseKoordinat(s,&titik1,&isSuccess);
			if (isSuccess==true){
				if (IsInsidePCB(*pcb,titik1)==false){
					printf("Error. Koordinat berada di luar range PCB.\n\n");
				} else if (IsLayoutFree(*pcb,titik1)==true){
					isTrue = true;
				} else {
					printf("Error. Sudah ada komponen di posisi tersebut.\n\n");
				}
			}
		}
	} while ((isTrue==false)&&(*isQuit==false));	
		
	if (*isQuit==false){
		//Input Koordinat Kedua
		isTrue = false;
		isSuccess = false;
		do {
			printf("Koordinat Kaki 2 : ");
			gets(s);
			if (IsKeluar(s)==true){
				*isQuit = true;
			} else {
				ParseKoordinat(s,&titik2,&isSuccess);
				if (isSuccess==true){
					if (IsInsidePCB(*pcb,titik2)==false){
						printf("Error. Koordinat berada di luar range PCB.\n\n");
					} else if (IsDiagonal(titik1,titik2)==true){
						printf("Error. Koordinat tidak boleh diagonal dengan koordinat pertama.\n\n");
					} else if ((titik1.x==titik2.x)){
						if ((abs(titik1.y-titik2.y))<jarakmin){
							printf("Error. Jarak antar kaki %c minimal %d.\n\n",component,jarakmin);
						} else {
							if (IsLayoutFree(*pcb,titik2)==true){
								isTrue = true;
							} else {
								printf("Error. Sudah ada komponen di posisi tersebut.\n\n");
							}
						}
					} else if ((titik1.y==titik2.y)){
						if ((abs(titik1.x-titik2.x))<jarakmin){
							printf("Error. Jarak antar kaki %c minimal %d.\n\n",component, jarakmin);
						} else {
							if (IsLayoutFree(*pcb,titik2)==true){
								isTrue = true;
							} else {
								printf("Error. Sudah ada komponen di posisi tersebut.\n\n");
							}
						}
					}
				}
			}
		} while ((isTrue==false)&&(*isQuit==false));
	}
	
	if (*isQuit==false){
		strcpy(pcb->layout[titik1.y-1][titik1.x-1],componentName);
		strcpy(pcb->layout[titik2.y-1][titik2.x-1],componentName);
		if (componentName[0]=='R'){
			//Jika komponen R, masukkan ke array R
			strcpy(pcb->R[pcb->countR],componentName);
			pcb->countR++;
		} else if (componentName[0]=='C'){
			//Jika komponen C, masukkan ke array C
			strcpy(pcb->C[pcb->countC],componentName);
			pcb->countC++;
		} else if (componentName[0]=='J'){
			//Jika komponen J, masukkan ke array J
			strcpy(pcb->J[pcb->countJ],componentName);
			pcb->countJ++;
		}
	}
	
	free(s);
}