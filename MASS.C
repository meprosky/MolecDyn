#include "define.h"
/******************
*
*   Function MAXATOMMASS()
*   ищет максимальную массу среди сортов атомов
*
*******************/
float maxatommass(float *mat)
{
float maxatom;
int i;

for(maxatom = 0.,i = 1; mat[i] > 0.; i++)
    if(mat[i] > maxatom)
       maxatom = mat[i];

mat[0] = maxatom;

return (maxatom * 1e-3 / Navo);
} /* END MAXATOMMASS */

/******************
*
*   Procedure RELATIONMASS()
*   вычисляет относ.массы
*
*******************/
void relationmass(float *mat,
                  float **massr,
                  float **mastr,
                  float **mastr2){
int i, num_typ;
float maxat;

for( i = 1; mat[i] > 0.; i++)
     ;

num_typ = i - 1;

*massr = (float *)malloc((num_typ+1)*sizeof(float));
ALOCERR(*massr);

*mastr =  (float *)malloc((num_typ+1)*sizeof(float));
ALOCERR(*mastr);

*mastr2 = (float *)malloc((num_typ+1)*sizeof(float));
ALOCERR(*mastr2);

maxat = mat[0];

for( i = 1; i <= num_typ; i++){
     *(*massr+i)  = mat[i] / maxat;
     *(*mastr+i)  = maxat  / mat[i];
     *(*mastr2+i) = 0.5 * *(*mastr+i);
     }
}