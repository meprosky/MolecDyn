#include "define.h"
/******************
*
*  Procedure INITIAL()
*  читает из файла область периодичности и массы атомов
*
******************/
void initial( STRING namefile, float *dt, OBLPER *OblPer, float **mat){

STRING buf;
int i, num_typ;
FILE *ini;

ini = fopen(namefile, "r");
FILERR(ini, namefile);

for( i = 0; i < 4; i++)
     fgets(buf, 100, ini);

fgets(buf, 100, ini);
fscanf(ini, "%e", dt);

fgets(buf, 80, ini);
fgets(buf, 80, ini);
fscanf(ini, "%*s%d", &num_typ);

*mat = (float *)malloc((num_typ + 2) * sizeof(float));
ALOCERR(mat);

for( i = 1; i <= num_typ; i++)
     fscanf(ini, "%*d%*s%f", &*(*mat+i));

*(*mat + num_typ + 1) = -1.;  /* признак конца массива */

fclose(ini);
}