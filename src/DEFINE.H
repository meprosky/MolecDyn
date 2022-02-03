#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define eV   1.60219e+19
#define elch 1.60219e-19
#define Navo 6.022e23   
#define angstr 1e-10    
#define Kboltz  1.38054e-23
#define Dielconst 8.8542e-12
#define Pi 3.14159          
#define getch()
#define cls()

#define f_rezim    ch[1]
#define f_coor     ch[2]
#define f_pot      ch[3]
#define f_outcoor  ch[4]
#define f_en       ch[5]
#define f_bakcoor  ch[8]
#define f_baken    ch[9]

#define max_elem 20
#define _U unsigned
#define _L long int

#define PRILINE(namf)  fgets(cl, 80, namf);\
		       printf("%s", cl)

#define FILERR(x, string) if( !x){\
                              printf("\nCan't open ile : %s\n", string);\
			      exit(1);\
                              }

#define ALOCERR(p)  if( !p){\
                         printf("\nAllocation memory error!!!\n");\
                         exit(1);\
                         }

#define clrscr()

/*
typedef float FLOATARR[20];
typedef int   INTARR[20];
*/
typedef char  STRING[255];


typedef struct{
        int t, p;
	float x; 
	float y;
	float z;
	}ATOM;

typedef struct{
	float A;
	float Ro;
	float C;
	float z1, z2;
	}POTENCIAL;




typedef struct{
	_L step;
                
	float dTemp;
	}TEMPER;


typedef struct{
        int type, place;
        float x,y,z;
        }BAZIS;

typedef struct{
        float x1,x2,y1,y2,z1,z2;
        }OBLPD;

typedef struct{
        float x, y, z;
        }OBLPER;

typedef struct{
        _L time, nst_iscal, nst_energy;
        float px, py, pz, Rcutt, Temper, dT;
        int fa;
        _L *fas;
        }REZIM;