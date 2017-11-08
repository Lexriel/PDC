#include <string.h>
#include <stdio.h>
#include "dico4lettres.h" // un entier taille_dico est defini ici

void TriBulle(void){
  int i,j ;
  char *tmp ;

  for ( i=taille_dico-1 ; i >=0 ; --i)
    for ( j=1 ; j<=i ; j++) 
      if (strcmp(dico[j-1],dico[j])>0){
        tmp       = dico[j-1] ;
        dico[j-1] = dico[j] ;
        dico[j]   = tmp ;
      }

}

void affichage(void){
  int i ;
  for ( i=0 ; i < taille_dico ; i++)
    printf("%s\n",dico[i]) ;
}

int main(void){
  printf("D\'ebut du tri\n") ;
  TriBulle();
  printf("Fin du tri\n") ;
  affichage() ;
  return 1 ;
}

 
