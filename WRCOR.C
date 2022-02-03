#include "define.h"
/*******************
*
* Procedure  CNTOUTDATA()
* записывает координаты, скорости и силы
*
********************/
void cntoutdata( STRING namefile,
                 ATOM   *Atom,
                 _L     npart,
                 int    num_typ,
                 int    numplace,
                 _L     ndt_stop,
                 float  Temper,
                 float  *fx,
                 float  *fy,
                 float  *fz,
                 float  *Vh_X,
                 float  *Vh_Y,
                 float  *Vh_Z,
                 float  maxatom,
                 float dt)

{
float koef;
_L i;
FILE *midf;


clrscr();
printf("Write file %s\n", namefile);

midf = fopen(namefile, "w");
FILERR(midf,namefile);


for( i = 0; i < 4; i++)
     fprintf( midf, "%s\n", "*");

fprintf(midf, "%6s %3s %3s\n", "npart", "num_typ", "numplace");
fprintf(midf, "%6ld %3d %3d\n", npart, num_typ, numplace);

fprintf(midf, "ndt_stop\n");
fprintf(midf, "%ld\n", ndt_stop);

fprintf(midf, "Temper\n");
fprintf(midf, "%.3f\n", Temper);

fprintf(midf, "Coordinates\n");
for( i = 1; i <= npart; i++)
     fprintf(midf, "%6ld %3d %3d  % 15f  % 15f  % 15f\n",
             i,
             Atom[i].t,
             Atom[i].p,
             Atom[i].x,
             Atom[i].y,
             Atom[i].z);


/* силы выводятся в размерности eV/s */

koef  = maxatom * angstr / (dt * dt * 1.e-24 * elch);
fprintf(midf, "\nForces\n");
for( i = 1; i <= npart; i++)
     fprintf(midf, "%6ld %3d %3d   % 15e  % 15e  % 15e\n",
             i,
             Atom[i].t,
             Atom[i].p,
             fx[i] * koef,
             fy[i] * koef,
             fz[i] * koef);


/* скорость выводиться в m/s */
koef = angstr / (dt * 1.e-12);
fprintf(midf, "\nVelocities\n");
for( i = 1; i <= npart; i++)
     fprintf(midf, "%6ld %3d %3d  % 15e  % 15e  % 15e\n",
             i,
             Atom[i].t,
             Atom[i].p,
             Vh_X[i] * koef,
             Vh_Y[i] * koef,
             Vh_Z[i] * koef);


fclose(midf);
printf("END Write file %s\n", namefile);

} /* END CNTOUTDATA */