POTENCIAL  **definterpot(float     r,
                         int       numpotintervals,
                         POTENCIAL ***p);

void force( int       t1,
            int       t2,
            float     r,
            float     *Frc,
            float     *dUpot,
            int       numpotintervals,
            POTENCIAL ***pglob);

void accel( _L        npart,
            ATOM      *Atom,
            float     **fx,
            float     **fy,
            float     **fz,
            float     Rcutt,
            float     *mastr2,
            float     px,
            float     py,
            float     pz,
            int       numpotintervals,
            POTENCIAL ***p);

void calcKinEn( ATOM  *Atom,
                int   num_typ,
                _L    npart,
                float *massr,
                float *Vh_X,
                float *Vh_Y,
                float *Vh_Z,
                float *Ekin,
                float *EkinSum);


void createnergy( STRING namefile1,
                  STRING namefile2);

_L EnergyStop(STRING namefile);

void energyfile( STRING namefile,
                 int    num_typ,
                 _L     time,
                 _L     l,
                 float  *ENER,
                 float  *Ekin,
                 float  Ekoef);


void Get_Param(_L    time,
               REZIM *Rezim,
               int   nrez,
               float *Temper,
               float *Rcutt,
               float *px,
               float *py,
               float *pz);

float maxatommass(float *mat);





int RecCoorCond(REZIM  *Rezim,
                int    nrez,
                _L     time,
                _L     nst_file,
                _L     ndt,
                _L     ndt_add_st,
                STRING namefile,
                int    *idfp);

int RecEnCond(REZIM *Rezim,
              int   nrez,
              _L    time);

int ScalCond( REZIM *Rezim,
              int   nrez,
              _L    time);


void relationmass(float *mat,
                  float **massr,
                  float **mastr,
                  float **mastr2);

void maxwell(_L    npart,
             int   num_typ,
             float *massr,
             ATOM  *Atom,
             float Temper,
	     float C3Nk,
             float **Vh_X,
             float **Vh_Y,
             float **Vh_Z);

void openfile( STRING namefile,
               STRING *ch,
               int    *cnt,
               _L     *ndt_add);

void periodic(ATOM   *Atom,
              _L     i,
              float  px,
              float  py,
              float  pz);

void periodic2(float  *xx,
               float  *yy,
               float  *zz,
               float  px,
               float  py,
               float  pz);

void readinicoor( STRING namefile,
                  ATOM   **Atom,
                  _L     *npart,
                  int    *num_typ,
                  int    *numplace);

void cntreaddata( STRING namefile,
                  ATOM   **Atom,
                  _L     *npart,
                  int    *num_typ,
                  int    *numplace,
                  _L     *ndt_stop,
                  float  *Temper,
                  float  **fx,
                  float  **fy,
                  float  **fz,
                  float  **Vh_X,
                  float  **Vh_Y,
                  float  **Vh_Z,
                  float  maxatom,
                  float  dt);

void readrezim(STRING namefile,
               float  *dt,
               float  **mat,
               REZIM  **Rezim,
               int    *nrez,
               _L     *nst_file);

void scalpot( int       numpotintervals,
              int       num_typ,
              float     ScalConst,
              POTENCIAL ***p);

void cntoutdata( STRING namefile,
                 ATOM   *Atom,
                 _L     npart,
                 int    num_typ,
                 int    numplace,
                 _L     ndt_stop,
                 float  Temper,
                 float  *fx,
                 float  *fy,
                 float  *fz,
                 float  *Vh_X,
                 float  *Vh_Y,
                 float  *Vh_Z,
                 float  maxatom,
                 float  dt);

int readpot(STRING nfpot, POTENCIAL ****p);

void freeallmemory(POTENCIAL ****p,
                   int       numpotintervals,
                   int       num_typ,
                   float     **mat,
                   float     **massr,
                   float     **mastr,
                   float     **mastr2,
                   float     **Ekin,
                   float     **Vh_X,
                   float     **Vh_Y,
                   float     **Vh_Z,
                   float     **fx,
                   float     **fy,
                   float     **fz,
                   float     **ENER,
                   ATOM      **Atom);