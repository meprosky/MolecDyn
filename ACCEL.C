#include "define.h"

extern periodic2(float *, float *, float *, float, float, float);
extern void force(int, int, float, float *, float *, int, POTENCIAL ***);

/*******************
*
*   procedure void ACCEL
*
*******************/
void accel(_L        npart,
           ATOM      *Atom,
           float     **fx,
           float     **fy,
           float     **fz,
           float     Rcutt,
           float     *mastr2,
           float     px,
           float     py,
           float     pz,
           int       numpotintervals,
           POTENCIAL ***p)

{

int t;
_L i, j, npartm;
float xx, yy, zz, Frc, dUpot, r, rr, rdx, rdy, rdz;
POTENCIAL **pp;

*fx = (float *)malloc((npart+1)*sizeof(float));
ALOCERR(*fx);
*fy = (float *)malloc((npart+1)*sizeof(float));
ALOCERR(*fy);
*fz = (float *)malloc((npart+1)*sizeof(float));
ALOCERR(*fz);

npartm = npart - 1;
for( i = 1; i <= npart; i++){
	 (*fx)[i] = 0.;
	 (*fy)[i] = 0.;
	 (*fz)[i] = 0.;
	 }

     for( i = 1; i <= npartm; i++)
	  for( j = i + 1; j <= npart; j++)
	       {
	       xx = Atom[i].x - Atom[j].x;
	       yy = Atom[i].y - Atom[j].y;
	       zz = Atom[i].z - Atom[j].z;


               periodic2(&xx, &yy, &zz, px, py, pz);

	       rr = xx * xx + yy * yy + zz * zz;
	       r = sqrt(rr);

               if( r > Rcutt)
                   continue;

               force( Atom[i].t, Atom[j].t, r, &Frc, &dUpot,
                      numpotintervals, p);

	       rdx = Frc * xx;
	       rdy = Frc * yy;
	       rdz = Frc * zz;

	       (*fx)[i] -= rdx;
	       (*fy)[i] -= rdy;
	       (*fz)[i] -= rdz;

	       (*fx)[j] += rdx;
	       (*fy)[j] += rdy;
	       (*fz)[j] += rdz;
	       } /* for summary forces */

for( i = 1; i <= npart; i++){
     t = Atom[i].t;
     (*fx)[i] *= mastr2[t];
     (*fy)[i] *= mastr2[t];
     (*fz)[i] *= mastr2[t];
     }

}/* END  ACCEL */