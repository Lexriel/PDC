#include<stdio.h>
#include <stdlib.h>
#include <time.h>
#include"bmp.h"


 float strtof(const char *, char **);

/* This prototype is necessary. By default gcc does not require
prototypes.  The default return type for a function is int, so strtof
returns 4 bytes worth of float (or 8 bytes worth of double in the case
of strtod) but the compiler is handling them as 4 bytes of int. */

char * Bruitage(
		float bruit, 
		BMPHeader_t *Header, 
		char pix[Header->Height][Header->Width][NBCOULEURS]
		){ 

	char *Pict ;

  	register unsigned int cmp, x, y ;
  	register couleurs_t couleur ;
	
	signed char pixelBruit = 0 ; 

	if( !( Pict= (char *) malloc(Header->BitmapDataSize) ) )
	   return NULL ;

	srand(time(NULL)); /* on initialise la
				 gra\^\i{}ne en utilisant une valeur
				 prise li\'e au temps */

	bruit *= 255/100 ;

     	for( y=1 ; y+1<Header->Height ; y++ )
  	   for( x=1 ; x+1<Header->Width ; x++ )
              for( couleur=0 ; couleur<3 ; couleur++ ){
		   *(Pict+NBCOULEURS*((y*Header->Width)+x)+couleur) = 
		     pix[y][x][couleur] + (int)  (bruit*rand()/(RAND_MAX+1.0));
	      }

	return Pict ;
}

int main(int argc, char *argv[]){
  
  BMPHeader_t *Header ;
  char *Pict, *bruit ;

  if(argc!=4){
    fprintf( stderr,
	    "%s <intensit\\'e du bruit (pourcentage)> <image originale> <image bruit\\'ee>\n",
	    argv[0] ) ;
    return -1 ;
  }

  FILE *fp = openBMP(argv[2],&Header,&Pict) ;

  if(!fp) 
     return 1 ;

  if( bruit = Bruitage(strtof(argv[1], NULL),Header,Pict) ){ 	 
     createBMP(argv[3], Header, bruit) ; 
     free(bruit) ;
  }
  return closeBMP(fp,Header,Pict) ;
}
