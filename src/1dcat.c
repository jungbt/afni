/*****************************************************************************
  This software is copyrighted and owned by the Medical College of Wisconsin.
  See the file README.Copyright for details.
******************************************************************************/

#include "mrilib.h"

#define MAXIM 1024

int main( int argc , char * argv[] )
{
   int nim , ii , jj , kk , nx ;
   MRI_IMAGE ** inim ;
   float * far ;

   /*-- help? --*/

   if( argc < 2 || strcmp(argv[1],"-help") == 0 ){
     printf("Usage: 1dcat a.1D b.1D ...\n"
            "where each file a.1D, b.1D, etc. is an ASCII file of numbers\n"
            "arranged in rows and columns.\n"
            "The row-by-row catenation of these files is written to stdout.\n"
            "You can use a column subvector selector list on the inputs,\n"
            "as in\n"
            "  1dcat 'fred.1D[0,3,7]' ethel.1D > ricky.1D\n"
           ) ;
      exit(0) ;
   }

   /* read input files */

   nim = argc-1 ;
   inim = (MRI_IMAGE **) malloc( sizeof(MRI_IMAGE *) * nim ) ;
   for( jj=0 ; jj < nim ; jj++ ){
      inim[jj] = mri_read_1D( argv[jj+1] ) ;
      if( inim[jj] == NULL ){
         fprintf(stderr,"** Can't read input file %s\n",argv[jj+1]) ;
         exit(1) ;
      }
      if( jj > 0 && inim[jj]->nx != inim[0]->nx ){
         fprintf(stderr,
                 "** Input file %s doesn't match first file %s in length!\n",
                 argv[jj+1],argv[1]) ;
         exit(1) ;
      }
   }

   nx = inim[0]->nx ;
   for( ii=0 ; ii < nx ; ii++ ){
      for( jj=0 ; jj < nim ; jj++ ){
         far = MRI_FLOAT_PTR(inim[jj]) ;
         for( kk=0 ; kk < inim[jj]->ny ; kk++ ){
            printf(" %g", far[ii+kk*nx] ) ;
         }
      }
      printf("\n") ;
   }

   exit(0) ;
}
