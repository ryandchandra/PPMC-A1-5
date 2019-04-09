//***********************************************************//
//                      [ Source Code ]
//
// Institution       : Institut Teknologi Bandung
// Name              : Ryan Dharma Chandra
// File Name         : lib8.c
// Dependency        : stdio.h, stdlib.h, stdbool.h, string.h
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
#include <string.h>

void DRC(pcb_t pcb){
	//Melakukan design rule check kepada routing jalur pada pcb berdasarkan input berupa file drc
	
	//KAMUS LOKAL
	drc_t drc; //array drc dari file drc
	nodelist_t drclist; //list berisi keterhubungan dari node berdasarkan file drc
	nodelist_t routinglist; //list berisi keterhubungan dari node berdasarkan routing pcb
	FILE *fileDRC;
	char *s = (char*)malloc(50*sizeof(char));
	short int i,j;
	short int index;
	short int drcindex1,drcindex2;
	short int routingindex1, routingindex2;
	short int count,count2,error;
	bool check[20];
	short int mode;
	bool isSuccess = false;
	
	//ALGORITMA
	//Input file DRC
	printf("Masukkan file DRC : ");
	gets(s);
	fileDRC = fopen(s,"r");
	if (fileDRC==NULL){
		printf("Error. File tidak ditemukan. Silakan ulangi lagi.\n\n");
	} else {
		isSuccess = true;
	}
		
	if (isSuccess){
		//Inisalisasi list drclist dan routinglist
		InitNodeList(&drclist);
		InitNodeList(&routinglist);		
		
		//Mengisi array drc
		i = 0;
		drc.size = 0;
		while (!feof(fileDRC)){
			fgets(s,50,fileDRC);
			ParseDRC(s,&(drc.element[i]));			
			
			//Masukkan nama komponen ke node1 pada list drclist 
			index = SearchNodeListIndex(drc.element[i].node1,drclist);
			if (index!=-1){
				//Jika node sudah ada pada list drclist, masukkan nama komponen ke node tersebut
				strcpy(drclist.node[index].connect[drclist.node[index].connected],drc.element[i].komponen);
				drclist.node[index].connected++;
			} else {
				//Jika node belum ada, buat node tersebut sebagai elemen baru pada list drclist
				//Kemudian masukkan nama komponen ke node tersebut (sebagai elemen pertama)
				strcpy(drclist.node[drclist.size].name,drc.element[i].node1);
				strcpy(drclist.node[drclist.size].connect[0],drc.element[i].komponen);
				drclist.node[drclist.size].connected = 1;
				drclist.size++;
			}

			//Masukkan nama komponen ke node2 pada list drclist
			index = SearchNodeListIndex(drc.element[i].node2,drclist);
			if (index!=-1){
				//Jika node sudah ada pada list drclist, masukkan nama komponen ke node tersebut
				strcpy(drclist.node[index].connect[drclist.node[index].connected],drc.element[i].komponen);
				drclist.node[index].connected++;
			} else {
				//Jika node belum ada, buat node tersebut sebagai elemen baru pada list drclist
				//Kemudian masukkan nama komponen ke node tersebut (sebagai elemen pertama)
				strcpy(drclist.node[drclist.size].name,drc.element[i].node2);
				strcpy(drclist.node[drclist.size].connect[0],drc.element[i].komponen);
				drclist.node[drclist.size].connected = 1;
				drclist.size++;
			}
			// Catatan : diasumsikan file DRC sudah benar dan tidak ada nama komponen yang sama muncul dua kali
			i++;
		}
		drc.size = i;
		
		//Cek konektivitas pada pcb
		CheckRoutingConnection(pcb,&routinglist);

		//Bandingkan kedua list drclist dan routinglist
		error = 0;
		for (i=0;i<drc.size;i++){
			//Cek komponen dari list drc dari file
			//Sedang mengecek drc.element[i].komponen
			//Cek node pertama dari drc.element[i].komponen
			//Cari node dari drc.element[i].komponen di drclist
			drcindex1 = SearchNodeListIndex(drc.element[i].node1,drclist);
			drcindex2 = SearchNodeListIndex(drc.element[i].node2,drclist);
			//Cari node dari drc.element[i].komponen di routinglist
			routingindex1 = SearchComponentInListFirst(drc.element[i].komponen,routinglist);
			routingindex2 = SearchComponentInListSecond(drc.element[i].komponen,routinglist);
			
			if (routingindex1==routingindex2){
				//Jika kedua kaki berada pada node yang sama (short)
				printf("Error. Kaki komponen %s terhubung singkat.\n",drc.element[i].komponen);
				check[i] = false;
				error++;
			} else if ((routinglist.node[routingindex1].connected==1)&&(routinglist.node[routingindex2].connected==1)){
				//Komponen belum terhubung ke apapun
				printf("Error. Kaki komponen %s belum terhubung\n",drc.element[i].komponen);
				check[i] = false;
				error++;
			} else {
				//Bandingkan kedua node dari drclist dan routinglist
				//Assign node pada drclist dengan routinglist
				//dengan mengecek lebih banyak mana komponen yang sama pada drcindex dan routingindex dari kedua list	
				mode = AssignNode(drcindex1,drcindex2,routingindex1,routingindex2,drclist,routinglist);
				if (mode==1){
					//Assign : drcindex1 = routingindex2, drcindex2 = routingindex1
					//Cek node drcindex1 vs routingindex1
					count = 0;
					j = 0;
					while (j<drclist.node[drcindex1].connected){
						if (SearchComponentInNode(routinglist.node[routingindex1].connect[j],drclist.node[drcindex1])!=-1){
							//Jika komponen yang terhubung seharusnya ada pada node tersebut (berdasarkan drclist)
							count++;
						}
						j++;
					}
					//Cek node drcindex2 vs routingindex2
					count2 = 0;
					j = 0;
					while (j<drclist.node[drcindex2].connected){
						if (SearchComponentInNode(routinglist.node[routingindex2].connect[j],drclist.node[drcindex2])!=-1){
							//Jika komponen yang terhubung seharusnya ada pada node tersebut (berdasarkan drclist)
							count2++;
						}
						j++;
					}
					//Menggunakan threshold, karena jika ada komponen yang tidak terhubung pada suatu node,
					//Hal tersebut adalah salah dari komponen tersebut
					//Bukan komponen yang sedang diperiksa
					//Kecuali jika sebagian besar dari komponen yang seharusnya terhubung dengan komponen tersebut
					//Tidak terhubung dengan komponen tersebut, maka itu adalah salah dari komponen yang sedang diperiksa
					if ((count<=(drclist.node[drcindex1].connected/2.0))||(count2<=(drclist.node[drcindex2].connected/2.0))){
						check[i]=false;
						error++;
					} else {
						check[i]=true;
					}
				} else if (mode==0){
					//Assign : drcindex1 = routingindex2, drcindex2 = routingindex1
					//Cek node drcindex1 vs routingindex2
					count = 0;
					j = 0;
					while (j<drclist.node[drcindex1].connected){
						if (SearchComponentInNode(routinglist.node[routingindex2].connect[j],drclist.node[drcindex1])!=-1){
							//Jika komponen yang terhubung seharusnya ada pada node tersebut (berdasarkan drclist)
							count++;
						}
						j++;
					}
					//Cek node drcindex2 vs routingindex1
					count2 = 0;
					j = 0;
					while (j<drclist.node[drcindex2].connected){
						if (SearchComponentInNode(routinglist.node[routingindex1].connect[j],drclist.node[drcindex2])!=-1){
							//Jika komponen yang terhubung seharusnya ada pada node tersebut (berdasarkan drclist)
							count2++;
						}
						j++;
					}
					//Menggunakan threshold karena idem
					if ((count<=(drclist.node[drcindex2].connected/2.0))||(count2<=(drclist.node[drcindex1].connected/2.0))){
						check[i]=false;
						error++;
					} else {
						check[i]=true;
					}
				}
			}
		}
		
		//Output
		if (error==0){ 
			//Jika tidak ada error
			printf("%d/%d Rule is checked\n",drc.size,drc.size);
		} else {
			//Ada error
			printf("%d/%d, Kondisi error sebagai berikut:\n",drc.size-error,drc.size);
			for (i=0;i<drc.size;i++){
				if (check[i]==false){
					printf("[x] %s\n",drc.element[i].komponen);
				} else if (check[i]==true){
					printf("[v] %s\n",drc.element[i].komponen);
				}
			}
			printf("Keterangan : [x] belum benar, [v] sudah benar\n");
		}
		//berhasil yey
	}
	
	fclose(fileDRC);
	free(s);
}

int SearchNodeListIndex(char *s, nodelist_t list){
	//Mencari index dari node dengan nama s pada list list
	//Mengembalikan nilai index dari node dengan nama ketika node ada pada list
	//Return -1 jika node dengan nama s tidak ada pada list
	
	//KAMUS LOKAL
	short int i = 0;
	bool found = false;

	//ALGORITMA
	while ((i<list.size)&&(found==false)){
		if (CheckTwoString(s,list.node[i].name)){
			found = true;
		} else {
			i++;
		}
	}
	
	if (found==true){
		return i;
	} else {
		return -1;
	}
}

int SearchComponentInNode(char *s, node_t node){
	//Mencari komponen dengan nama s yang terhubung dengan node node
	//Mengembalikan nilai index dari komponen dengan nama s ketika komponen terhubung dengan node
	//Return -1 jika komponen dengan nama s tidak terhubung pada node
	
	//KAMUS LOKAL
	short int i = 0;
	bool found = false;

	//ALGORITMA
	while ((i<node.connected)&&(found==false)){
		if (CheckTwoString(s,node.connect[i])){
			found = true;
		} else {
			i++;
		}
	}
	
	if (found==true){
		return i;
	} else {
		return -1;
	}
}

int SearchComponentInListFirst(char *s, nodelist_t list){
	//Mencari komponen dengan nama s pada list list dari depan (dari indeks 0)
	//Mengembalikan posisi index dari node yang memiliki komponen s dari list
	//Return -1 jika tidak ditemukan node yang memiliki komponen s pada list
	
	//KAMUS LOKAL
	short int i;
	bool found = false;

	//ALGORITMA
	i = 0;
	while ((i<list.size)&&(found==false)){
		if (SearchComponentInNode(s,list.node[i])!=-1){
			found = true;
		} else {
			i++;
		}
	}
	
	if (found==true){
		return i;
	} else {
		return -1;
	}
}

int SearchComponentInListSecond(char *s, nodelist_t list){
	//Mencari komponen dengan nama s pada list list dari belakang (dari indeks terakhir)
	//Mengembalikan posisi index dari node yang memiliki komponen s dari list
	//Return -1 jika tidak ditemukan node yang memiliki komponen s pada list
	
	short int i;
	bool found = false;
	
	i = list.size;
	while ((i>=0)&&(found==false)){
		if (SearchComponentInNode(s,list.node[i])!=-1){
			found = true;
		} else {
			i--;
		}
	}
	
	if (found==true){
		return i;
	} else {
		return -1;
	}
}

void ParseDRC(char *s, element_drc_t *drc){
	//Melakukan parsing dari string s hasil input dari fileDRC menjadi isi dari array drc
	//Membagi string s menjadi tiga bagian pada array drc: komponen, node1, node2
	//Diasumsikan fileDRC selalu benar sehingga tidak ada validasi
	
	//KAMUS LOKAL
	short int i,j;

	//ALGORITMA
	//bagian pertama dari string s : komponen
	i = 0;
	j = 0;
	while ((i<strlen(s))&&(s[i]!=' ')){
		drc->komponen[j]=s[i];
		j++;
		i++;
	}
	drc->komponen[j]='\0';
	
	//bagian kedua dari string s : node1
	i++;
	j=0;
	while ((i<strlen(s))&&(s[i]!=' ')){
		drc->node1[j]=s[i];
		j++;
		i++;
	}
	drc->node1[j]='\0';

	//bagian ketiga dari string s : node2
	i++;
	j=0;
	while ((i<strlen(s))&&(s[i]!='\n')){
		drc->node2[j]=s[i];
		j++;
		i++;
	}
	drc->node2[j]='\0';
}

void InitNodeList(nodelist_t *list){
	//Melakukan inisialisasi dari list list
	list->size = 0;
	for(int i=0;i<50;i++){
		list->node[i].connected = 0;
	}
}

int CountSameComponentTwoNode(node_t node1, node_t node2){
	//Menghitung banyaknya komponen yang sama yang terhubung pada suatu node
	//Optimalnya diperuntukkan membandingkan antara node pada drclist dan routinglist
	
	//KAMUS LOKAL
	short int i,j,count;
	
	//ALGORITMA
	count = 0;
	i = 0;
	while (i<node1.connected){
		j = 0;
		while (j<node2.connected){
			if (CheckTwoString(node1.connect[i],node2.connect[j])){
				//Jika ditemukan komponen yang sama pada kedua node, tambahkan counter
				count++;
			}
			j++;
		}
		i++;
	}
	
	return count;
}

void CheckRoutingConnection(pcb_t pcb, nodelist_t *routinglist){
	//Melakukan pengecekan pada koneksi komponen berdasarkan routing pcb
	//Output routinglist berupa list node dengan keterhubungan komponennya
	
	//KAMUS LOKAL
	bool visited[40][40]; //digunakan untuk mengecek apakah node yang bersangkutan sudah dicek atau tidak
	short int i,j;
	int iterate;
	char *nodeName = (char*)malloc(5*sizeof(char));
	koor_t current;
	
	//ALGORITMA
	for (i=0;i<pcb.lebar;i++){
		for (j=0;j<pcb.panjang;j++){
			visited[i][j] = false;
		}
	}
	iterate = 1;
	current.x = 1;
	current.y = 1;
	current = FindNextSymbol(current, pcb, visited);
	while ((current.x<=pcb.panjang)&&(current.y<=pcb.lebar)){
		itoa(iterate,nodeName,10); //digunakan nama node berupa angka
		//Cek keterhubungan routing dengan layout
		CheckRoute(current,pcb,visited,routinglist,nodeName);
		current = FindNextSymbol(current, pcb, visited);
		iterate++;
	}
	
	free(nodeName);
}

koor_t FindNextSymbol(koor_t current, pcb_t pcb, bool visited[40][40]){
	//Mencari keberadaan simbol selanjutnya dari posisi koordinat current yang belum dicek
	//Pencarian dilakukan dari kiri ke kanan, atas ke bawah
	//Return koordinat selanjutnya yang memiliki simbol yang belum dicek
	//Return (100,100) jika pencarian sudah sampai di pojok kanan bawah (habis)
	bool found = false;
	while ((current.x<=pcb.panjang)&&(current.y<=pcb.lebar)&&(found==false)){
		if ((pcb.routing[current.y-1][current.x-1]!=' ')&&(!visited[current.y-1][current.x-1])){
			found = true;
		} else if (current.x<pcb.panjang){
			//Jika posisi x belum sampai ujung kanan, tambahkan posisi x
			current.x++;
		} else if (current.x==pcb.panjang){
			//Jika posisi x sudah sampai ujung kanan, cek ke baris selanjutnya dari posisi paling kiri
			current.x = 1;
			current.y++;
		}
	}
	
	if (found==true){
		return current;
	} else {
		current.x = 100;
		current.y = 100;
		return current;
	}
}

short int AssignNode(short int drcindex1, short int drcindex2, short int routingindex1, short int routingindex2, nodelist_t drclist, nodelist_t routinglist){
	//Melakukan pencocokan node dari drclist dan routinglist-
	//Sesuai dengan index yang diperoleh : drcindex1, drcindex2, routingindex1, routingindex2 
	//Return 1 jika drcindex1 = routingindex1 dan drcindex2 = routingindex2
	//Return 0 jika drcindex1 = routingindex2 dan drcindex2 = routingindex1
	
	//KAMUS LOKAL
	short int d1r1,d1r2,d2r1,d2r2;
	short int d1,d2,r1,r2;
		
	//ALGORITMA
	//Melakukan perbandingan antara node pada drclist dan routinglist sesuai banyaknya komponen yang sama
	d1r1 = CountSameComponentTwoNode(drclist.node[drcindex1],routinglist.node[routingindex1]);
	d1r2 = CountSameComponentTwoNode(drclist.node[drcindex1],routinglist.node[routingindex2]);
	d2r1 = CountSameComponentTwoNode(drclist.node[drcindex2],routinglist.node[routingindex1]);
	d2r2 = CountSameComponentTwoNode(drclist.node[drcindex2],routinglist.node[routingindex2]);
	
	//Cek
	if ((d1r1>d1r2)&&(d2r2>d2r1)){
		//node drcindex1 sama dengan routingindex1, node drcindex2 sama dengan routingindex2
		return 1;
	} else if ((d1r2>d1r1)&&(d2r1>d2r2)){
		//node drcindex2 sama dengan routingindex1, node drcindex1 sama dengan routingindex1
		return 0;
	} else if (d1r1==d1r2){
		if (d2r2>d2r1){
			//node drcindex1 sama dengan routingindex1, node drcindex2 sama dengan routingindex2
			return 1;
		} else if (d2r2<d2r1){
			//node drcindex2 sama dengan routingindex1, node drcindex1 sama dengan routingindex1
			return 0;
		} else if (d2r2==d2r1){
			//Apabila jumlah komponen kedua node yang sama adalah sama
			//Cek dari jumlah komponen terhubungnya
			d1 = drclist.node[drcindex1].connected;
			d2 = drclist.node[drcindex2].connected;
			r1 = routinglist.node[routingindex1].connected;
			r2 = routinglist.node[routingindex2].connected;
			if ((d1>d2)&&(r1>r2)){
				//node drcindex1 sama dengan routingindex1, node drcindex2 sama dengan routingindex2
				return 1;
			} else if (((d1<d2)&&(r1<r2))||((d1>d2)&&(r1>r2))){
				//node drcindex1 sama dengan routingindex1, node drcindex2 sama dengan routingindex2
				return 1;
			} else if (((d1>d2)&&(r1<r2))||((d1<d2)&&(r1>r2))){
				//node drcindex1 sama dengan routingindex2, node drcindex2 sama dengan routingindex 1
				return 0;
			} else { //untuk semua kasus sama, udah gatau mau bandingin apa lagi
				return 1;
			}
		}
	} else if (d2r1==d2r2){
		if (d1r1>d1r2){
			//node drcindex1 sama dengan routingindex1, node drcindex2 sama dengan routingindex2
			return 1;
		} else if (d1r1<d1r2){
			//node drcindex2 sama dengan routingindex1, node drcindex1 sama dengan routingindex1
			return 0;
		} else if (d1r1==d1r2){
			//Apabila jumlah komponen kedua node yang sama adalah sama
			//cek dari jumlah komponen terhubungnya
			d1 = drclist.node[drcindex1].connected;
			d2 = drclist.node[drcindex2].connected;
			r1 = routinglist.node[routingindex1].connected;
			r2 = routinglist.node[routingindex2].connected;
			if ((d1>d2)&&(r1>r2)){
				//node drcindex1 sama dengan routingindex1, node drcindex2 sama dengan routingindex2
				return 1;
			} else if (((d1<d2)&&(r1<r2))||((d1>d2)&&(r1>r2))){
				//node drcindex1 sama dengan routingindex1, node drcindex2 sama dengan routingindex2
				return 1;
			} else if (((d1>d2)&&(r1<r2))||((d1<d2)&&(r1>r2))){
				//node drcindex1 sama dengan routingindex2, node drcindex2 sama dengan routingindex 1
				return 0;
			} else { //untuk kasus sama, udah gatau mau bandingin apa lagi
				return 1;
			}
		}
	}
}

void CheckRoute(koor_t koor, pcb_t pcb, bool visited[40][40], nodelist_t *routinglist, char *nodeName){
	//Melakukan pengecekan dari jalur pcb untuk simbol yang sama sesuai dengan matriks pcb.routing
	//Pengecekan dilakukan dengan algoritma DFS (Depth-First Search)
	//Output routinglist yang berisi list node beserta komponen yang terhubung
	
	//KAMUS LOKAL
	char simbol = pcb.routing[koor.y-1][koor.x-1];
	koor_t next = koor;
	
	//ALGORITMA
	visited[koor.y-1][koor.x-1]=true; //Posisi pada koordinat koor sudah dicek
	
	if (IsLayoutFree(pcb,koor)==false){
		//Apabila pada posisi ini terdapat komponen (terhubung pada jalur)
		//Cek apakah node ini sudah ada pada list atau tidak
		//Jika iya, masukkan ke komponen ke node tersebut
		//Jika tidak. buat node baru dan masukkan komponen ke node tersebut
		int index = SearchNodeListIndex(nodeName,*routinglist);
		if (index!=-1){
			//Masukkan nama komponen ke list node tersebut
			strcpy(routinglist->node[index].connect[routinglist->node[index].connected],pcb.layout[koor.y-1][koor.x-1]);
			routinglist->node[index].connected++;
		} else {
			//Buat list baru, masukkan komponen ke list node tersebut
			strcpy(routinglist->node[routinglist->size].name,nodeName);
			strcpy(routinglist->node[routinglist->size].connect[0],pcb.layout[koor.y-1][koor.x-1]);
			routinglist->node[routinglist->size].connected = 1;
			routinglist->size++;
		}
	}
	
	//Lakukan pengecekan untuk posisi setelahnya : atas, bawah, kiri, kanan -> menggunakan algoritma DFS (Depth-First Search)
	next = koor;
	if (koor.x!=pcb.panjang){
		if ((pcb.routing[koor.y-1][koor.x]==simbol)&&(!visited[koor.y-1][koor.x])){ //kanan
			next.x = koor.x+1;
			CheckRoute(next,pcb,visited,routinglist,nodeName); //rekursi
		}
	}
	next = koor;
	if (koor.x!=1){
		if ((pcb.routing[koor.y-1][koor.x-2]==simbol)&&(!visited[koor.y-1][koor.x-2])){ //kiri
			next.x = koor.x-1;
			CheckRoute(next,pcb,visited,routinglist,nodeName); //rekursi
		}
	}
	next = koor;
	if (koor.y!=pcb.lebar){
		if ((pcb.routing[koor.y][koor.x-1]==simbol)&&(!visited[koor.y][koor.x-1])){ //bawah
			next.y = koor.y+1;
			CheckRoute(next,pcb,visited,routinglist,nodeName); //rekursi
		}
	}
	next = koor;
	if (koor.y!=1){
		if ((pcb.routing[koor.y-2][koor.x-1]==simbol)&&(!visited[koor.y-2][koor.x-1])){ //atas
			next.y = koor.y-1;
			CheckRoute(next,pcb,visited,routinglist,nodeName); //rekursi
		}
	}
	
	//Catatan : tidak ada basis untuk rekursi ini
	//Akan berhenti ketika seluruh jalur dengan simbol yang sama dan terhubung sudah dicek dan ditemukan jalan buntu
	//Harus dilakukan pengembalian koordinasi kembali untuk backtrack ke posisi awal
	//Digunakan variabel next = koor untuk backtrack ke koordinat awal
}