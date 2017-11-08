#include <stdio.h>
#define NbLignes 5

int main(void){

  int i,j ;

  printf("Affichage du carre d'etoiles\n");

  for(i=0;i<NbLignes;i++){
    for(j=0;j<NbLignes;j++)
      printf("*") ;
    printf("\n") ;
  }

  printf("Affichage du triangle inferieur droit\n");

  for(i=0;i<NbLignes;i++){
    for(j=0;j<NbLignes;j++)
      if (i<j)
	printf(" ") ;
      else printf("*") ;
    printf("\n") ;
  }

  printf("Affichage du triangle superieur gauche\n");

  for(i=0;i<NbLignes;i++){
    for(j=0;j<NbLignes;j++)
      if (i>j)
	printf(" ") ;
      else printf("*") ;
    printf("\n") ;
  }

  printf("Affichage du triangle superieur gauche\n");

  for(i=0;i<NbLignes;i++){
    for(j=0;j<NbLignes;j++)
      if (i >= NbLignes - j)
	printf(" ") ;
      else printf("*") ;
    printf("\n") ;
  }

  printf("Affichage du triangle inferieur droit\n");

  for(i=0;i<NbLignes;i++){
    for(j=0;j<NbLignes;j++)
      if (i+1 < NbLignes - j)
	printf(" ") ;
      else printf("*") ;
    printf("\n") ;
  }
  return 0 ;
}
 
