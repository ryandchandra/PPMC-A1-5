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

//Deklarasi semua fungsi yang digunakan dalam program
void NewProject(char *projectName, pcb_t *pcb);
void LoadProject(char *projectName, pcb_t *pcb, bool *isSuccess);

bool CheckTwoString(char *s1, char *s2);
bool IsResistorExist(char *R, pcb_t pcb);
bool IsCapacitorExist(char *C, pcb_t pcb);
bool IsJunctionExist(char *J, pcb_t pcb);

void MenuUtama(char *projectName, pcb_t *pcb);
void MainMenu(pcb_t *pcb);

short int PosisiKoma(char *s);
bool IsLayoutFree(pcb_t pcb, koor_t koor);
bool IsKeluar(char *s);
bool IsStringNumber(char *s);
bool IsComponentCorrect(char *s);
bool IsInsidePCB(pcb_t pcb, int koor_t koor);
bool IsDiagonal(koor_t titik1, koor_t titik2);
void ParseKoordinat(char *s, koor_t *koor, bool *isSuccess);
void InputTransistorCoordinate(pcb_t *pcb, bool *isQuit);
void InputRCJCoordinate(pcb_t *pcb, char component, int jarakmin, char *componentName, bool *isQuit);
void LayoutManual(pcb_t *pcb);

//Include semua library yang digunakan dalam program
//#include "lib/lib1.c"
#include "lib/lib2.c"
#include "lib/lib3.c"