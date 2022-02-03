/***************************************************************************
*  AMD.C                                                                   *
*              Main program of MOLECULAR DYNAMICS                          *
*                                                                          *
*              Mike Prohorsky  Petrozavodsk, Carelian Republics, Russia    *
*              Copyright(1995)                                             *
*                                                                          *
****************************************************************************/


#include "define.h"
#include "amd.h"
/*
#define f_ini      ch[1]
#define f_rezim    ch[2]
#define f_coor     ch[3]
#define f_pot      ch[4]
#define f_outcoor  ch[5]
#define f_en       ch[6]
#define f_bakcoor  ch[8]
#define f_baken    ch[9]
*/


float ForcConst;

void main(int argc, char **argv)
{

int t, cnt, num_typ;
int numpotintervals, nrez, numplace, idfp;

_L i, j, l, time; 
_L ndt, ndt_stop, npart, npartm;
_L nst_en_stop;
_L ndt_cnt, ndt_add, ndt_add_st, nst_file;

float *Vh_X, *Vh_Y, *Vh_Z, *fx, *fy, *fz, Ekoef;
float xx, yy, zz, rdx, rdy, rdz, Upot, dUpot;
float r, rr, Frc, Sv_X, Sv_Y, Sv_Z;
float dt, dt2, K_boltz_scal, Rcutt, Temper, realTemper;
float maxat, maxatom;
float px, py, pz;
float ScalConst, C3Nk, ScalVelKoef, EkinSum;
float *mat, *massr, *mastr, *mastr2, *Ekin, *ENER;
STRING   cl, ch[15], nfsave;
POTENCIAL ***p, **pp;
ATOM  *Atom;
REZIM *Rezim;

if( argc !=2){
    printf("\
 Programm of the Molecular Dynamics\n\
       Command line: amd [atrfile]\n");
    exit(1);
    }


     
openfile(argv[1], ch, &cnt, &ndt_add);

     
readrezim(f_rezim, &dt, &mat, &Rezim, &nrez, &nst_file);

     
maxatom = maxatommass(mat);

     
relationmass(mat, &massr, &mastr, &mastr2);


     
ndt = Rezim[nrez+1].time;

     
if( cnt == 1){     
     
    readinicoor(f_coor, &Atom, &npart, &num_typ, &numplace);

    createnergy(f_en, f_baken);

    nst_en_stop = 0;
     
    ndt_stop = 0;
     
    Temper = Rezim[1].Temper;
    }
else{
     
    cntreaddata(f_outcoor, &Atom, &npart, &num_typ, &numplace,
                &ndt_stop, &Temper, &fx, &fy, &fz,
                &Vh_X, &Vh_Y, &Vh_Z, maxatom, dt);
     
    nst_en_stop = EnergyStop(f_en);
    }

r=0;
Get_Param(ndt_stop, Rezim, nrez, &r, &Rcutt, &px, &py, &pz);
dt2 = dt * dt;

ScalConst =  dt2 * 1.e-24 / (maxatom * angstr * angstr);

ForcConst = (elch * elch / (4. * Pi * Dielconst)) * ScalConst / angstr;

K_boltz_scal = Kboltz * ScalConst;

Ekoef = 1. / (ScalConst * elch);

C3Nk = 3 * npart * K_boltz_scal;

/*
printf("ScalConst = %.4e\nForcConst = %.4e\n", ScalConst, ForcConst);
printf("Ekoef = %f\n", Ekoef);
printf("K_boltz_scal = %.4e\n", K_boltz_scal);
printf("C3Nk = %.4e\n", C3Nk );
getch();
*/

numpotintervals = readpot(f_pot, &p);
scalpot( numpotintervals, num_typ, ScalConst, p);
   
if( cnt == 1){
    maxwell( npart, num_typ, massr, Atom, Temper,
	     C3Nk, &Vh_X, &Vh_Y, &Vh_Z);

    accel( npart, Atom, &fx, &fy, &fz,
           Rcutt, mastr2, px, py, pz, numpotintervals, p);
    }

ENER = (float *)malloc(5*sizeof(float));
ALOCERR(ENER);
Ekin = (float *)malloc((num_typ+1)*sizeof(float));
ALOCERR(Ekin);

/***********************************************************************/
/*                                                                     */
/*                                                                     */
/*                                                                     */
/***********************************************************************/

npartm = npart - 1;
l = nst_en_stop;
ndt_cnt = ndt_stop + 1;
ndt_add_st = ndt_stop + ndt_add;
realTemper = Temper;

for( time = ndt_cnt; time <= ndt && time <= ndt_add_st; time++){

     printf("\ntime = %ld\n", time);

     for( i = 1; i <= npart; i++){

          Atom[i].x += (Vh_X[i] += fx[i]);
          Atom[i].y += (Vh_Y[i] += fy[i]);
          Atom[i].z += (Vh_Z[i] += fz[i]);

          periodic(Atom, i, px, py, pz);

	  fx[i] = 0.;
	  fy[i] = 0.;
	  fz[i] = 0.;
     }

     Upot = 0.;
     for( i = 1; i <= npartm; i++)
	  for( j = i + 1; j <= npart; j++){
	       xx = Atom[i].x - Atom[j].x;
	       yy = Atom[i].y - Atom[j].y;
	       zz = Atom[i].z - Atom[j].z;

               periodic2(&xx, &yy, &zz, px, py, pz);

	       rr = xx * xx + yy * yy + zz * zz;
	       r = sqrt(rr);

               if( r > Rcutt)
                   continue;

               force(Atom[i].t, Atom[j].t, r, &Frc, &dUpot,
                     numpotintervals, p);

               Upot += dUpot;

	       rdx = Frc * xx;
	       rdy = Frc * yy;
	       rdz = Frc * zz;

	       fx[i] -= rdx;
	       fy[i] -= rdy;
	       fz[i] -= rdz;

	       fx[j] += rdx;
	       fy[j] += rdy;
	       fz[j] += rdz;
               } /* for summary forces */

     for(i = 1; i <= npart; i++){

	  t = Atom[i].t;

          Vh_X[i] += (fx[i] *= mastr2[t]);
          Vh_Y[i] += (fy[i] *= mastr2[t]);
          Vh_Z[i] += (fz[i] *= mastr2[t]);
          }


if( RecEnCond(Rezim, nrez, time) || ScalCond(Rezim, nrez, time)){
    calcKinEn( Atom, num_typ, npart, massr,                      
               Vh_X, Vh_Y, Vh_Z, Ekin, &EkinSum);                
    realTemper = 2. * EkinSum / (3. * K_boltz_scal * npart);     
    }                                                            
                                                                 
      printf("Temper     : % 10.3f\n", Temper);
      printf("REALTemper : % 10.3f\n", realTemper);

      if( ScalCond(Rezim, nrez, time)){
          ScalVelKoef = sqrt(0.5 * C3Nk * Temper / EkinSum);
          Sv_X = 0.;
          Sv_Y = 0.;
          Sv_Z = 0.;
          for( i = 1; i <= npart; i++){
               t = Atom[i].t;
	       Sv_X += Vh_X[i] * massr[t];
	       Sv_Y += Vh_Y[i] * massr[t];
	       Sv_Z += Vh_Z[i] * massr[t];
               }
          printf("              %10s  %10s  %10s\n", "Px", "Py", "Pz");
          printf("BEFOR scaling: % 10.5e   % 10.5e   % 10.5e\n", Sv_X, Sv_Y, Sv_Z);

         Sv_X = 0.;
         Sv_Y = 0.;
         Sv_Z = 0.;
         for( i = 1; i <= npart; i++){
              t = Atom[i].t;
              Vh_X[i] *= ScalVelKoef;
              Vh_Y[i] *= ScalVelKoef;
              Vh_Z[i] *= ScalVelKoef;
              Sv_X += Vh_X[i] * massr[t];
              Sv_Y += Vh_Y[i] * massr[t];
              Sv_Z += Vh_Z[i] * massr[t];
              }
          printf("AFTER scaling: % 10.5e   % 10.5e   % 10.5e\n", Sv_X, Sv_Y, Sv_Z);
          }

     if( RecEnCond(Rezim, nrez,time)){
	 l++;
	 ENER[1] = Upot;
	 ENER[2] = EkinSum;
	 ENER[3] = EkinSum + Upot;
         energyfile( f_en, num_typ, time, l, ENER, Ekin, Ekoef);
         energyfile( f_baken, num_typ, time, l, ENER, Ekin, Ekoef);
	 }

      if( RecCoorCond(Rezim, nrez, time, nst_file,
                      ndt, ndt_add_st, nfsave, &idfp))

          if( idfp == 1){
              cntoutdata( nfsave, Atom, npart, num_typ, numplace, time,
                          Temper, fx, fy, fz,
                          Vh_X, Vh_Y, Vh_Z, maxatom, dt);
              }
          else if( idfp == 2){
              cntoutdata( f_outcoor, Atom, npart, num_typ, numplace,
                          time, Temper, fx, fy,
                          fz, Vh_X, Vh_Y, Vh_Z, maxatom,
                          dt);

              cntoutdata( f_bakcoor, Atom, npart, num_typ, numplace, time,
                          Temper, fx, fy, fz,
                          Vh_X, Vh_Y, Vh_Z, maxatom, dt);
              }
          else if( idfp == 3){
              cntoutdata( nfsave, Atom, npart, num_typ, numplace, time,
                          Temper, fx, fy, fz,
                          Vh_X, Vh_Y, Vh_Z, maxatom, dt);

              cntoutdata( f_outcoor, Atom, npart, num_typ, numplace,
                          time, Temper, fx, fy,
                          fz, Vh_X, Vh_Y, Vh_Z, maxatom,
                          dt);

              cntoutdata( f_bakcoor, Atom, npart, num_typ, numplace, time,
                          Temper, fx, fy, fz,
                          Vh_X, Vh_Y, Vh_Z, maxatom, dt);
              }

     Get_Param(time, Rezim, nrez, &Temper, &Rcutt, &px, &py, &pz);

  }/* for time */


freeallmemory(&p, numpotintervals, num_typ, &mat, &massr,
              &mastr, &mastr2, &Ekin, &Vh_X, &Vh_Y,
              &Vh_Z, &fx, &fy, &fz, &ENER,
              &Atom);

}/* end program MOLECULAR DYNAMICS  */