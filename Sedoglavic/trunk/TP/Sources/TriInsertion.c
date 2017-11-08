#include <string.h>
#include <stdio.h>
#include "dico4lettres.h" // un entier taille_dico est defini ici

void TriInsertion(void){
  int i,j ;
  char *tmp ;

  for ( i=0 ; i < taille_dico ; i++) {
    tmp = dico[i] ;
    j = i ;
    while (j>0 && strcmp(dico[j-1],tmp)>0)
      dico[j]=dico[--j];

    dico[j]=tmp ;
  }
}

void affichage(void){
  int i ;
  for ( i=0 ; i < taille_dico ; i++)
    printf("%s\n",dico[i]) ;
}

int main(void){
  printf("D\'ebut du tri\n") ;
  TriInsertion();
  printf("Fin du tri\n") ;
  affichage() ;
  return 1 ;
}
 
