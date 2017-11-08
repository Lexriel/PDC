#include <string.h>
#include <stdio.h>
#include "dico4lettres.h" 
// " " indique que l'on cherche dans le repertoire courant

int PlusPetitElement(int g){
  int pos = g ;

  for( g++ ; g<taille_dico ; g++)
    if (strcmp(dico[g],dico[pos])<0)
      pos = g ;

  return pos ;
}

void TriSelection(void){

  int min,i ;
  char *tmp ;
  
  for( i=0 ; i < taille_dico ; i++ ) {
    min = PlusPetitElement(i) ;
    /* on fait l'echange */
    tmp       = dico[min] ;
    dico[min] = dico[i]   ;
    dico[i]   = tmp       ;
  }  
}

void affichage(void){
  int i ;
  for ( i=0 ; i < taille_dico ; i++)
    printf("%s\n",dico[i]) ;
}

int main(void){
  printf("D\'ebut du tri\n") ;
  TriSelection();
  printf("Fin du tri\n") ;
  affichage() ;
  return 1 ;
}
 
