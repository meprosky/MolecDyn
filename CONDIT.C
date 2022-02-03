#include "define.h"
/******************
*
*  Function RECCOORCOND()
* 
*
******************/
int RecCoorCond(REZIM *Rezim,
                int nrez,
                _L time,
                _L nst_file,
                _L ndt,
                _L ndt_add_st,
                STRING namefile,
                int *idfp){

int i, j;
STRING buf;

*idfp = 0;

/* не забывать, что реальное число режимов больше nrez на 1 */


for( i = 1; i <= nrez; i++){
     if( time >= Rezim[i].time && time < Rezim[i+1].time)
         switch( Rezim[i].fa){
                 case -1 : break;

                 case  0 : if( !(time % Rezim[i].fas[1]))
                           *idfp = 1;
                           sprintf(buf, "%ld", time);
                           strcpy(namefile, buf);
                           strcat(namefile, ".rfr");
                           break;

                 default : for( j = 1; j <= Rezim[i].fa; j++)
                                if( time == Rezim[i].fas[j]){
                                    *idfp = 1;
                                    sprintf(buf, "%ld", time);
                                    strcpy(namefile, buf);
                                    strcat(namefile, ".rfr");
                                    }
                           break;
                 }
   }

if( !(time % nst_file) || time == Rezim[nrez+1].time || time == ndt_add_st)
    switch(*idfp){

       case 0: *idfp = 2;
               break;

       case 1: *idfp = 3;
               break;
       }



return ((idfp > 0)?1 : 0);
}


/*
time % nst_file == 0 || time == ndt || time == ndt_add_st){
nst_en_stop = l;
*/

/******************
*
*  Function RECENCOND()
*  проверяет нужно ли вычислять кинетическую эн. системы
*
******************/
int RecEnCond(REZIM *Rezim, int nrez, _L time){

int i;
for( i = 1; i <= nrez; i++)
     if( Rezim[i].nst_energy &&
         time >= Rezim[i].time && time < Rezim[i+1].time &&
         !(time % Rezim[i].nst_energy))
         return 1;

return 0;
}

/******************
*
*  Function SCALCOND()
*  проверяет нужно ли проводить шкалирование скоростей
*
******************/
int ScalCond( REZIM *Rezim, int nrez, _L time){

int i;
for( i = 1; i <= nrez; i++)
     if( Rezim[i].nst_iscal != 0 &&
         time >= Rezim[i].time && time < Rezim[i+1].time &&
         !(time % Rezim[i].nst_iscal))
         return 1;

return 0;
}