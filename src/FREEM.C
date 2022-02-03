#include "define.h"
/******************
*
*  Procedure FREEALLMEMORY
*  Освобождаем всю выделенную динамическую память
*
*******************/
void freeallmemory(POTENCIAL ****p,
                   int       numpotintervals,
                   int       num_typ,
                   float     **mat,
                   float     **massr,
                   float     **mastr,
                   float     **mastr2,
                   float     **Ekin,
                   float     **Vh_X,
                   float     **Vh_Y,
                   float     **Vh_Z,
                   float     **fx,
                   float     **fy,
                   float     **fz,
                   float     **ENER,
                   ATOM      **Atom){


int i, j;

for( i = 1; i <= numpotintervals; i++){
     for( j = 1; j <= num_typ; j++)
          free( *(*(*p+i)+j) );
     free( *(*p+i) );
     }

free(*p);

free(*mat);
free(*massr);
free(*mastr);
free(*mastr2);
free(*Ekin);
free(*Vh_X);
free(*Vh_Y);
free(*Vh_Z);
free(*fx);
free(*fy);
free(*fz);
free(*ENER);
free(*Atom);
}