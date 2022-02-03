#include "define.h"
/******************
*
*     procedure void SCALPOT
*     шкалирует потенциал те приводит к системе едениц используемых
*     внутри программы
*
******************/
void scalpot( int numpotintervals,
              int num_typ,
              float ScalConst,
              POTENCIAL ***p)
{
int i, j, k;

printf("begin SCALPOT\n");

for( i = 1; i <= numpotintervals; i++)
     for( j = 1; j <= num_typ; j++)
          for( k = 1; k <= num_typ+1-j; k++){
               printf("%.4e  ", (*(*(p + i) + j) + k)->A);
               (*(*(p + i) + j) + k)->A *= elch * ScalConst;
               (*(*(p + i) + j) + k)->C *= elch * ScalConst;
               printf("%.4e\n", (*(*(p + i) + j) + k)->A);
               }

printf("end SCALPOT\n");
getch();

}/*  END  SCALPOT  */