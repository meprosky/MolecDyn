#include "define.h"
/******************
*
*   Procedure GET_PARAM()
*  
*
*******************/
void Get_Param(_L time,
               REZIM *Rezim,
               int   nrez,
               float *Temper,
               float *Rcutt,
               float *px,
               float *py,
               float *pz){

int i;
for( i = 1; i <= nrez; i++){
     if( time >= Rezim[i].time && time < Rezim[i+1].time){
         *Rcutt = Rezim[i].Rcutt;
	 *Temper += Rezim[i].dT;
	 *px = Rezim[i].px;
         *py = Rezim[i].py;
         *pz = Rezim[i].pz;
	 if( Rezim[i].Temper > 0. && time == Rezim[i].time)
             *Temper = Rezim[i].Temper;
         break;
         }
     }
}