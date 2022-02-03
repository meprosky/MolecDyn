#include "define.h"
/******************
*
*     procedure int READPOT
*     читает коэффициенты потенциалов взаимодействия
*     возвращает число интервалов расстояний
*
******************/
int readpot(STRING nfpot, POTENCIAL ****p){

int i, j, k, num_typ, numpotintervals, typat, numats;
STRING st;
FILE *pot;

pot = fopen(nfpot, "r");
FILERR(pot, nfpot);

for( i = 0; i < 4; i++)
     fgets(st, 100, pot);

fscanf(pot, "%*s%d%*s%d", &numpotintervals, &num_typ);

/*
printf("Num_intr : %d\n", numpotintervals);
printf("Num_typ  : %d\n", num_typ);
*/

fgets(st,100,pot);
fgets(st,100,pot);

*p = (POTENCIAL ***)malloc((numpotintervals+1)*sizeof(POTENCIAL **));
ALOCERR(*p);

for( i = 0; i <= numpotintervals; i++){
     *(*p+i) = (POTENCIAL **)malloc((num_typ+1)*sizeof(POTENCIAL *));
     ALOCERR( *(*p+i) );
     for( j = 0; j <= num_typ; j++){
          *(*(*p+i)+j) = (POTENCIAL *)
                         malloc((num_typ+2-j)*sizeof(POTENCIAL));
          ALOCERR( *(*(*p+i)+j) );
          }
     }

for( i = 1; i <= numpotintervals; i++){
     fgets(st,100,pot);

     fscanf(pot, "%*s%f%f", &(**(*p+i))->A, &(**(*p+i))->Ro);

     /*
     printf("***************************************************\n");
     printf("INTERVAL%3d : %8.5f  %8.5f\n",
             i, (**(*p+i))->A, (**(*p+i))->Ro);
     printf("***************************************************\n");
     */


     fgets(st,100,pot);
     fgets(st,100,pot);

     for( j = 1; j <= num_typ; j++){
          fgets(st, 100, pot);  /*  ATOM: [A] */

          fscanf(pot, "%*s%d%*s%d", &typat, &numats); /* TYPE, ROW*/
          printf("TYPAT: %3d\nROW  : %3d\n", typat, numats);


          for( k = 1; k <= numats; k++){
               fscanf(pot, "%*s%f%f%f%f%f", &(*(*(*p+i)+j)+k)->A,
                                            &(*(*(*p+i)+j)+k)->Ro,
                                            &(*(*(*p+i)+j)+k)->C,
                                            &(*(*(*p+i)+j)+k)->z1,
                                            &(*(*(*p+i)+j)+k)->z2);

               printf("%8.5f  %8.5f  %8.5f  % 8.5f  % 8.5f\n",
                                         (*(*(*p+i)+j)+k)->A,
                                         (*(*(*p+i)+j)+k)->Ro,
                                         (*(*(*p+i)+j)+k)->C,
                                         (*(*(*p+i)+j)+k)->z1,
                                         (*(*(*p+i)+j)+k)->z2);
               }

          /*printf("\n");*/

          fgets(st, 100, pot);
          fgets(st, 100, pot);
          /*getch();*/
          }
     }


return numpotintervals;
}  /* END READPOT */