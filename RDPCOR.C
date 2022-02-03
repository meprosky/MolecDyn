#include "define.h"
/*******************
*
*  Procedure CNTREADDATA()
*  читает координаты скорости и силы при продолжении МД эксперимента
*
********************/
void cntreaddata( STRING namefile,
                  ATOM   **Atom,
                  _L     *npart,
                  int    *num_typ,
                  int    *numplace,
                  _L     *ndt_stop,
                  float  *Temper,
                  float  **fx, float **fy, float **fz,
                  float  **Vh_X, float **Vh_Y, float **Vh_Z,
                  float maxatom,
                  float dt)
{
_L i;
float maxat, koef;
STRING buf;
FILE *cor;

cor = fopen(namefile, "r");
FILERR(cor,namefile);

for( i = 0; i < 4; i++)
     fgets( buf, 100, cor);

fgets( buf, 100, cor);
fscanf(cor, "%ld%d%d", npart, num_typ, numplace);

fgets( buf, 100, cor);
fgets( buf, 100, cor);
fscanf(cor, "%ld", ndt_stop);

fgets( buf, 100, cor);
fgets( buf, 100, cor);
fscanf(cor, "%f", Temper);


*Atom = (ATOM  *)malloc((*npart + 1) * sizeof(ATOM ));
*Vh_X = (float *)malloc((*npart + 1) * sizeof(float));
*Vh_Y = (float *)malloc((*npart + 1) * sizeof(float));
*Vh_Z = (float *)malloc((*npart + 1) * sizeof(float));
*fx   = (float *)malloc((*npart + 1) * sizeof(float));
*fy   = (float *)malloc((*npart + 1) * sizeof(float));
*fz   = (float *)malloc((*npart + 1) * sizeof(float));

if( *Atom == NULL || *Vh_X == NULL || *Vh_Y == NULL ||
    *Vh_Z  == NULL || *fx   == NULL || *fy   == NULL || *fz   == NULL){
    printf("\nError alocation memory!\n");
    exit(1);
    }

fgets( buf, 100, cor);
fgets( buf, 100, cor);

for( i = 1; i <= *npart; i++)
     fscanf(cor, "%*ld%d%d%f%f%f",
                                  &(*Atom+i)->t,
                                  &(*Atom+i)->p,
                                  &(*Atom+i)->x,
                                  &(*Atom+i)->y,
                                  &(*Atom+i)->z);



koef = elch * dt * dt * 1.e-24 / (maxatom * angstr);

fgets( buf, 100, cor);
fgets( buf, 100, cor);
fgets( buf, 100, cor);

for( i = 1; i <= *npart; i++){
     fscanf(cor, "%*ld%*d%*d%e%e%e", *fx+i,
                                     *fy+i,
                                     *fz+i);

     (*fx)[i] *= koef;
     (*fy)[i] *= koef;
     (*fz)[i] *= koef;
     }



koef = dt * 1.e-12 / angstr;

fgets( buf, 100, cor);
fgets( buf, 100, cor);
fgets( buf, 100, cor);

for( i = 1; i <= *npart; i++){
     fscanf(cor, "%*ld%*d%*d%e%e%e", *Vh_X+i,
                                    *Vh_Y+i,
                                    *Vh_Z+i);

     (*Vh_X)[i] *= koef;
     (*Vh_Y)[i] *= koef;
     (*Vh_Z)[i] *= koef;
     }

printf("END READ DATA-COOR,FORCE,VEL\nPress any key\n");
fclose(cor);
}
/*** end CNTREADDATA ***/