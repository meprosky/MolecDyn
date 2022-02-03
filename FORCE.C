#include "define.h"
extern float ForcConst;
extern POTENCIAL **definterpot( float, int, POTENCIAL ***);
/*******************
*
*  procedure void FORCE
*  вычисляет силу
*
*******************/
void force( int t1,
            int t2,
            float r,
            float *Frc,
            float *dUpot,
            int numpotintervals,
            POTENCIAL ***pglob)
{
  float A, Ro, C, CZ, rt, rt2;
  float K_van_der, K_born_maer;
  POTENCIAL **p;

  p = definterpot( r, numpotintervals, pglob);

  if( t1 > t2){
      int ct;
      ct = t1;
      t1 = t2;
      t2 = ct;
      }
  t2 = t2 - t1 + 1;

  rt = 1. / r;
  rt2 = rt * rt;

  CZ = ForcConst * (*(p+t1)+t2)->z1 * (*(p+t1)+t2)->z2;
  A  = (*(p+t1)+t2)->A;
  Ro = (*(p+t1)+t2)->Ro;
  C  = (*(p+t1)+t2)->C;

  K_born_maer = A * exp(-r / Ro);

  *dUpot = CZ * rt + K_born_maer;

  *Frc = (-CZ * rt2 - K_born_maer / Ro) * rt;

  if( C != 0.){
      float rt6;
      rt6 = rt2 * rt2 * rt2;
      K_van_der = C * rt6;
      *dUpot -= K_van_der;
      *Frc   += 6 * K_van_der * rt2;
      }

}/* END FORCE */