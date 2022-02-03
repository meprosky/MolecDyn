#include "define.h"
/*******************
*
*     procedure CREATENERGY()
*     удаляет существующий файл с энергиями при старте МД эксперимента
*
********************/
void createnergy( STRING namefile1,
                   STRING namefile2)
{
FILE *ener, *ener0;
int i;
ener = fopen(namefile1, "w");
FILERR(ener, namefile1);
ener0 = fopen(namefile2, "w");
FILERR(ener0, namefile2);

for(i = 1; i<= 4; i++){
    fprintf(ener, "%s\n",  "*");
    fprintf(ener0, "%s\n", "*");
    }

fclose(ener);
fclose(ener0);
} /* END DELETEENERGYFILE */

/******************
*
*  Function ENERGYSTOP()
*  выясняет на каком шаге энергии прервали эксперимент
*
******************/
_L EnergyStop(STRING namefile){

_L i;
char buf[1024];
FILE *en;

en = fopen(namefile, "r");
FILERR(en, namefile);

for( i = 0; i < 4; i++)
     fgets(buf, 100, en);

     fgets(buf, 100, en);

for( i = 0; !feof(en); i++)
    fgets(buf, 1000, en);

fclose(en);
return (--i);
}

/******************
*
*     procedure void ENERGYFILE
*     записывает энергию (в eV) в файл
*
******************/
void energyfile( STRING namefile,
                 int num_typ,
                 _L time,
                 _L l,
                 float *ENER,
                 float *Ekin,
                 float Ekoef){
int i;
FILE *enf;

enf = fopen(namefile, "a");
FILERR(enf, namefile);

fprintf(enf, "%6ld %6ld  %8.5e  %8.5e  %8.5e  ", l, time,
        ENER[1] * Ekoef, ENER[2] * Ekoef, ENER[3] * Ekoef);
for( i = 1; i <= num_typ; i++)
     fprintf(enf, "%8.5e  ", Ekin[i] * Ekoef);
fprintf(enf, "\n");

fclose(enf);

} /* END  ENERGYFILE */