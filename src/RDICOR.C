#include "define.h"
/******************
*
*   Procedure READINICOOR
*   читает координаты кластера при старте МД эксперимента
*
******************/
void readinicoor( STRING namefile,
                  ATOM   **Atom,
                  _L     *npart,
                  int    *num_typ,
                  int    *numplace){

_L i;
STRING st;
FILE *cor;

cor = fopen(namefile, "r");
FILERR(cor, namefile);

for( i = 0; i < 4; i++)
     fgets(st, 100, cor);

fgets(st, 100, cor);
fscanf(cor, "%ld%d%d", npart, num_typ, numplace);

*Atom = (ATOM *)malloc((*npart + 1) * sizeof(ATOM));
ALOCERR(*Atom);


fgets(st, 100, cor);
fgets(st, 100, cor);
for( i = 1; i <= *npart; i++)
     fscanf( cor, "%*ld%d%d%f%f%f",
              &(*Atom+i)->t,
              &(*Atom+i)->p,
              &(*Atom+i)->x,
              &(*Atom+i)->y,
              &(*Atom+i)->z);

fclose(cor);
} /* END READINICOOR */