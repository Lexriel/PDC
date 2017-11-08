#include<stdio.h>
#include<string.h>
#include"bmp.h"
#define LAPSENS 100000
#define NORMGRAD 0
#define MAXNORMGRAD 32768

void Statistic(BMPHeader_t *Header, char pix[Header->Height][Header->Width][NBCOULEURS]){ 
  register unsigned int cmp, x, y ;
  register couleurs_t couleur ;
	
  int diffx, diffy ;
  unsigned int NormGrad[ MAXNORMGRAD ][NBCOULEURS] ;

  for( cmp=0 ; cmp<MAXNORMGRAD ; cmp++ )
    NormGrad[cmp][RED] = NormGrad[cmp][GREEN] = NormGrad[cmp][BLUE] = 0 ;

  for( y=1 ; y+1<Header->Height ; y++ )
     for( x=1 ; x+1<Header->Width ; x++ )
        for( couleur=0 ; couleur<3 ; couleur++ ){
            diffx = (pix[y][x+1][couleur]-pix[y][x-1][couleur])/2 ;	
            diffy = (pix[y+1][x][couleur]-pix[y-1][x][couleur])/2 ;	
	    NormGrad[ diffx*diffx+diffy*diffy ][couleur]++; 
        }

  FILE *file = fopen("essair.stat","w") ;

  fprintf(file,"stat := [[0,%d]",NormGrad[0][BLUE]) ;

  for( cmp=1 ; cmp<MAXNORMGRAD ; cmp++ )
    fprintf(file,",[%d,%d]",cmp,NormGrad[cmp][BLUE]) ;

  fprintf(file," ] : ") ;
  fclose(file) ;
}

char * Contour(BMPHeader_t *Header, char pix[Header->Height][Header->Width][NBCOULEURS]){ 
	char *Pict ;
	if( !( Pict= (char *) malloc(Header->BitmapDataSize) ) )
	   return NULL ;

  	register unsigned int cmp, x, y ;
  	register couleurs_t couleur ;
        int diffx, diffy ;

     	for( y=1 ; y+1<Header->Height ; y++ )
  	   for( x=1 ; x+1<Header->Width ; x++ )
              for( couleur=0 ; couleur<3 ; couleur++ ){
	         diffx = (pix[y][x+1][couleur]-pix[y][x-1][couleur])/2 ;	
	         diffy = (pix[y+1][x][couleur]-pix[y-1][x][couleur])/2 ;	
	         if( diffx*diffx+diffy*diffy > 300 )
		   *(Pict+NBCOULEURS*((y*Header->Width)+x)+couleur) = 0 ;
                 else *(Pict+NBCOULEURS*((y*Header->Width)+x)+couleur) = 255 ;
	      }

	return Pict ;
}

int main(int argc, char *argv[]){
  
  BMPHeader_t *Header ;
  char *Pict, *contour ;
  FILE *fp = openBMP(argv[1],&Header,&Pict) ;

  if(!fp) 
     return 1 ;
  
  Statistic(Header,Pict) ; 
  if( contour = Contour(Header,Pict) ){ 	 
     createBMP("contour.bmp", Header, contour) ; 
     free(contour) ;
  }
  return closeBMP(fp,Header,Pict) ;
}
