#include "define.h"
/******************
*
*  Procedure PERIODIC()
*  проверка на период.условия и меняет соотв. коор. атомов
*
******************/
void periodic(ATOM *Atom, _L i, float px, float py, float pz){

if( Atom[i].x < 0.) Atom[i].x += px;
if( Atom[i].y < 0.) Atom[i].y += py;
if( Atom[i].z < 0.) Atom[i].z += pz;
if( Atom[i].x > px) Atom[i].x -= px;
if( Atom[i].y > py) Atom[i].y -= py;
if( Atom[i].z > pz) Atom[i].z -= pz;
}

/******************
*
*  Procedure PERIODIC2()
*  проверка на период.условия и меняет соотв. эффект. расст. для выч-я
*  сил и потенциалов
******************/
void periodic2(float *xx,
               float *yy,
               float *zz,
               float px,
               float py,
               float pz){

float  px2, py2, pz2;

px2 = 0.5  * px;
py2 = 0.5  * py;
pz2 = 0.5  * pz;

if(*xx < -px2) *xx += px;
if(*xx >  px2) *xx -= px;

if(*yy < -py2) *yy += py;
if(*yy >  py2) *yy -= py;

if(*zz < -pz2) *zz += pz;
if(*zz >  pz2) *zz -= pz;
}