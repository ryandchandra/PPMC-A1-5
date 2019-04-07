//***********************************************************//
//                      [ Source Code ]
//
// Institution       : Institut Teknologi Bandung
// Name              : Johannes Felix Rimbun, Naila Amani, Ryan Dharma Chandra
// File Name         : lib.h
// Dependency        : stdio.h, stdlib.h, stdbool.h, string.h, math.h
// 					   lib1.c, lib2.c, lib3.c, lib4.c, lib5.c
// 					   lib6.c, lib7.c, lib8.c, lib9.c
//
// Description:
//     Please only write 64 characters maximum. If you write
// more than 64, please write it on the next line. Thanks!
//
// Status:
// 1. Johannes Felix Rimbun - 13217006 : lib1.c, lib4.c, lib9.c
// 2. Naila Amani - 13217012 : lib5.c, lib6.c, lib7.c
// 3. Ryan Dharma Chandra - 13217018 : lib2.c, lib3.c, lib8.c
//***********************************************************//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#define PANJANGMAX 40
#define LEBARMAX 40
#define PANJANGMIN 0
#define LEBARMIN 0

#define RMAX 4
#define CMAX 3
#define JMAX 3
#define TMAX 1

#define JARAKMINR 3
#define JARAKMINC 2
#define JARAKMINT 1
#define JARAKMINJ 0

#define LAYOUTEXTENSION "_layout.csv"
#define ROUTINGEXTENSION "_routing.csv"

typedef struct{
	char layout[LEBARMAX][PANJANGMAX][3];
	char routing[LEBARMAX][PANJANGMAX];
	int panjang, lebar;
	int countR, countC, countJ, countT;
	char R[RMAX][3], C[CMAX][3], J[JMAX][3], T;
} pcb_t;

typedef struct{
	int x,y;
} koor_t;

typedef struct{
	char komponen[10], node1[10], node2[10];
} element_drc_t;

typedef struct{
	element_drc_t element[20];
	int size;
} drc_t;

typedef struct{
	char name[10];
	char connect[10][3];
	int connected;
} node_t;

typedef struct{
	node_t node[50];
	int size;
} nodelist_t;

//Deklarasi semua fungsi yang digunakan dalam program
//lib1.c

//lib2.c
void NewProject(char *projectName, pcb_t *pcb);
void LoadProject(char *projectName, pcb_t *pcb, bool *isSuccess);
//lib3.c
void LayoutManual(pcb_t *pcb);
short int PosisiKoma(char *s);
bool IsLayoutFree(pcb_t pcb, koor_t koor);
bool IsKeluar(char *s);
bool IsStringNumber(char *s);
bool IsComponentCorrect(char *s);
bool IsInsidePCB(pcb_t pcb, koor_t koor);
bool IsDiagonal(koor_t titik1, koor_t titik2);
bool CheckTwoString(char *s1, char *s2);
bool IsResistorExist(char *R, pcb_t pcb);
bool IsCapacitorExist(char *C, pcb_t pcb);
bool IsJunctionExist(char *J, pcb_t pcb);
void ParseKoordinat(char *s, koor_t *koor, bool *isSuccess);
void InputTransistorCoordinate(pcb_t *pcb, bool *isQuit);
void InputRCJCoordinate(pcb_t *pcb, char component, int jarakmin, char *componentName, bool *isQuit);
//lib4.c

//lib5.c
void PrintLayout(pcb_t pcb);
void PrintRouting(pcb_t pcb);
//lib6.c
void ResetLayout(pcb_t pcb);
void ResetRouting(pcb_t pcb);
//lib7.c
void SaveLayout(char *filename, pcb_t pcb);
void SaveRouting(char *filename, pcb_t pcb);
//lib8.c
int SearchNodeListIndex(char *s, nodelist_t list);
int SearchComponentInNode(char *s, node_t node);
int SearchComponentInListFirst(char *s, nodelist_t list);
int SearchComponentInListSecond(char *s, nodelist_t list);
void ParseDRC(char *s, element_drc_t *drc);
void InitNodeList(nodelist_t *list);
int CountSameComponentTwoNode(node_t node1, node_t node2);
void CheckRoutingConnection(pcb_t pcb, nodelist_t *routinglist);
koor_t FindNextSymbol(koor_t current, pcb_t pcb, bool visited[40][40]);
short int AssignNode(short int drcindex1, short int drcindex2, short int routingindex1, short int routingindex2, nodelist_t drclist, nodelist_t routinglist);
void CheckRoute(koor_t koor, pcb_t pcb, bool visited[40][40], nodelist_t *routinglist, char *nodeName);
void DRC(pcb_t pcb);
//lib9.c

//Include semua library yang digunakan dalam program
#include "lib/lib1.c"
#include "lib/lib2.c"
#include "lib/lib3.c"
#include "lib/lib4.c"
#include "lib/lib5.c"
#include "lib/lib6.c"
#include "lib/lib7.c"
#include "lib/lib8.c"
#include "lib/lib9.c"
