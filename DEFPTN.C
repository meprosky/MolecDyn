#include "define.h"
/******************
*
*  procedure POTENCIAL **DEFINTERPOT
*
******************/
POTENCIAL  **definterpot( float r,
                          int numpotintervals,
                          POTENCIAL ***p){
int i;
for( i = 1; i <= numpotintervals; i++)
     if( r >= (**(p+i))->A && r <= (**(p+i))->Ro)
         return (*(p + i));
} /* END DEFINTERPO */