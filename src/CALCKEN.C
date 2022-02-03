#include "define.h"
/******************
*
*     procedure void CALCKINEN
*     вычисляет кинетическую энергию
*
*******************/
void calcKinEn( ATOM *Atom,
                int num_typ,
                _L npart,
                float *massr,
                float *Vh_X,
                float *Vh_Y,
                float *Vh_Z,
                float *Ekin,
                float *EkinSum)
{
_L i;
*EkinSum = 0;
for( i = 1; i <= num_typ; i++)
     Ekin[i] = 0.;
for( i = 1; i <= npart; i++)
     Ekin[ Atom[i].t ] += (Vh_X[i] * Vh_X[i] +
                           Vh_Y[i] * Vh_Y[i] +
                           Vh_Z[i] * Vh_Z[i]) *
                           massr[ Atom[i].t ] * 0.5;
for( i = 1; i <= num_typ; i++)
     *EkinSum += Ekin[i];

} /* END CALCKINEN */