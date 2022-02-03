#include "define.h"

extern void calcKinEn(ATOM  *, int, _L, float *, float *,
                      float *, float *, float *, float *);

/*******************
*
*      procedure void MAXWELL
*
********************/
void maxwell(_L    npart,
             int   num_typ,
             float *massr,
             ATOM  *Atom,
             float Temper,
	     float C3Nk,
             float **Vh_X,
             float **Vh_Y,
             float **Vh_Z)

{

int n1, n2, n3, t;
_L i;
float Sp_X, Sp_Y, Sp_Z;

float u1, u2, v1, v2, s, R, Rsq, ScalKoef, EkinSum;
float *Vh;

float *Ekin;

*Vh_X = (float *)malloc((npart+1)*sizeof(float));
ALOCERR(*Vh_X);
*Vh_Y = (float *)malloc((npart+1)*sizeof(float));
ALOCERR(*Vh_Y);
*Vh_Z = (float *)malloc((npart+1)*sizeof(float));
ALOCERR(*Vh_Z);

n1 = npart;
n2 = 2 * npart;
n3 = 3 * npart;

Vh = (float *)malloc((n3 + 3) * sizeof(float ));
ALOCERR(Vh);
Ekin = (float *)malloc((num_typ+1)*sizeof(float));
ALOCERR(Ekin);

for( i = 1; i <= n3; i += 2){
	do{
	  u1 = rand() / (float)RAND_MAX;
	  u2 = rand() / (float)RAND_MAX;
	  v1 =  2 * u1-1;
	  v2 =  2 * u2-1;
	  s = v1 * v1 + v2 * v2;
	  }
	while(s > 1.);

     R = -2 * log(s) / s;
     Rsq = sqrt(R);
     Vh[i] = v1 * Rsq;
     Vh[i + 1] = v2 * Rsq;
    }

for( i = 1; i <= n1; i++ ){
     (*Vh_X)[i] = Vh[i];
     (*Vh_Y)[i] = Vh[i + n1];
     (*Vh_Z)[i] = Vh[i + n2];
     }

calcKinEn(Atom, num_typ, npart, massr, *Vh_X,
          *Vh_Y, *Vh_Z, Ekin, &EkinSum);

ScalKoef = sqrt(0.5 * C3Nk * Temper / EkinSum);

Sp_X = 0.;
Sp_Y = 0.;
Sp_Z = 0.;
for( i = 1; i <= n1; i++){
     t = Atom[i].t;
     (*Vh_X)[i] *= ScalKoef;
     (*Vh_Y)[i] *= ScalKoef;
     (*Vh_Z)[i] *= ScalKoef;
     Sp_X += (*Vh_X)[i] * massr[t];
     Sp_Y += (*Vh_Y)[i] * massr[t];
     Sp_Z += (*Vh_Z)[i] * massr[t];
     }

Sp_X /= npart;
Sp_Y /= npart;
Sp_Z /= npart;

for( i = 1; i <= n1; i++){
     t = Atom[i].t;
     (*Vh_X)[i] = ((*Vh_X)[i] * massr[t] -  Sp_X) / massr[t];
     (*Vh_Y)[i] = ((*Vh_Y)[i] * massr[t] -  Sp_Y) / massr[t];
     (*Vh_Z)[i] = ((*Vh_Z)[i] * massr[t] -  Sp_Z) / massr[t];
     }

Sp_X = 0.;
Sp_Y = 0.;
Sp_Z = 0.;

for( i = 1; i <= n1; i++){
     t = Atom[i].t;
     Sp_X += (*Vh_X)[i] * massr[t];
     Sp_Y += (*Vh_Y)[i] * massr[t];
     Sp_Z += (*Vh_Z)[i] * massr[t];
     }
printf("\ntime = 0\n");
printf("             %10s   %10s   %10s\n", "Px", "Py", "Pz");
printf("INIT impuls: %10.5e   %10.5e   %10.5e\n", Sp_X, Sp_Y, Sp_Z);

free(Vh);
free(Ekin);

}/* END MAXWELL  */