#include "define.h"
/*********************
*
*   procedure OPENFILE
*
***********************/
void openfile( STRING namefile,
               STRING *ch,
               int *cnt,
               _L *ndt_add ){
int i;
FILE *atr, *cntf;

atr = fopen(namefile, "r");
FILERR(atr, namefile);

for( i = 1; feof(atr) == NULL; i++)
     fscanf(atr, "%s", ch+i);

printf("Input\n");
printf("  Propeties      : %-s\n", ch[1]); /*  f_rezim    ch[1]  */
printf("  Coordinates    : %-s\n", ch[2]); /*  f_coor     ch[2]  */
printf("  Potentials     : %-s\n", ch[3]); /*  f_pot      ch[3]  */

printf("Outout\n");
printf("  Coordinates    : %-s\n", ch[4]); /*  f_outcoor  ch[4]  */
printf("  Energies       : %-s\n", ch[5]); /*  f_en       ch[5]  */

strcpy(f_bakcoor, f_outcoor);  
*(f_bakcoor + 0) = '_';      

strcpy(f_baken, f_en);     /* f_baken    ch[9] */
*(f_baken + 0) = '_';


*cnt = ( (cntf = fopen(f_outcoor, "r") ) == NULL ) ? 1 : 0;
if( !*cnt)
    fclose(cntf);

if( *cnt)                   /* 0 - continue 1 - new */
    printf("\nWARNING !! The begining new experiment...");
else
    printf("\nWARNING !! The calculation was continued...");

printf("\nAll OK(y/n)? ");
if( (i = getchar()) != 'y' && i != 'Y'){
    printf("\nThe program molecular dynamics was broken !");
    exit(1);
    }

printf("\nAdd step - ");
scanf("%ld", ndt_add);

fclose(atr);
}/* END procedure OPENFILE */