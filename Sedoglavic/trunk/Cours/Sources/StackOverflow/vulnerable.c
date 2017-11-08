#include <stdio.h>
#define TAILLE 88

void lecture(FILE *flux){

  char tampon[TAILLE] ;
  unsigned int foo = 0 ;

  while ( (tampon[foo++]=fgetc(flux)) !='\xF8') ;
    /* tout le probl\`eme est l\`a */
}

int main(){
  FILE *fichier = fopen("piege","r") ;
  lecture(fichier) ;
  fclose(fichier) ;
  return 0 ;
}
