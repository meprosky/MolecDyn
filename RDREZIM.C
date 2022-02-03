#include "define.h"
/******************
*
*  Procedure READREZIM()
*  читает из файла режим проведения эксперимента
*
******************/
void readrezim(STRING namefile,
               float *dt,
               float **mat,
               REZIM **Rezim,
               int *nrez,
               _L *nst_file){

int i, j, num_typ;
STRING buf;
FILE *rez;

rez = fopen(namefile, "r");
FILERR(rez, namefile);

for( i = 0; i < 4; i++)
     fgets(buf, 100, rez);

fgets(buf, 100, rez);
fscanf(rez, "%f", dt);

fgets(buf, 100, rez);
fgets(buf, 100, rez);
fgets(buf, 100, rez);
fscanf(rez, "%*s%d", &num_typ);

*mat = (float *)malloc((num_typ + 2) * sizeof(float));
ALOCERR(mat);

for( i = 1; i <= num_typ; i++)
     fscanf(rez, "%*d%*s%f", &*(*mat+i));

*(*mat + num_typ + 1) = -1.;  /* признак конца массива */

fgets(buf, 100, rez);
fgets(buf, 100, rez);
fgets(buf, 100, rez);
fscanf(rez, "%ld", nst_file);

fgets(buf, 100, rez);
fgets(buf, 100, rez);
fscanf(rez, "%*s%d", nrez);

*Rezim = (REZIM *)malloc( (*nrez + 1) * sizeof(REZIM));
ALOCERR(*Rezim);

fgets(buf, 100, rez);
fgets(buf, 100, rez);
for( i = 1; i <= *nrez; i++){
     fscanf(rez, "%*ld%ld%f%f%f%f%f%f%ld%ld%d", &(*Rezim+i)->time,
                                                &(*Rezim+i)->px,
                                                &(*Rezim+i)->py,
                                                &(*Rezim+i)->pz,
                                                &(*Rezim+i)->Rcutt,
                                                &(*Rezim+i)->Temper,
                                                &(*Rezim+i)->dT,
                                                &(*Rezim+i)->nst_iscal,
                                                &(*Rezim+i)->nst_energy,
                                                &(*Rezim+i)->fa);


     switch( (*Rezim+i)->fa){
             case -1: break;

             case  0: (*Rezim+i)->fas =
                      (_L *)malloc( 2 * sizeof(_L));
                      ALOCERR((*Rezim+i)->fas);
                      fscanf(rez, "%ld", &((*Rezim+i)->fas[1]));
                      break;

             default: (*Rezim+i)->fas =
                      (_L *)malloc( ((*Rezim+i)->fa + 1) * sizeof(_L));
                      ALOCERR((*Rezim+i)->fas);
                      for( j = 1; j <= (*Rezim+i)->fa; j++)
                           fscanf(rez, "%ld", &((*Rezim+i)->fas[j]));
                      break;
             }
     }

(*nrez)--;

fclose(rez);
}