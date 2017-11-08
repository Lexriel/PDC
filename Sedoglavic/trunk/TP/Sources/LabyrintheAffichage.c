#include <stdio.h>

#define ferme  0
#define ouvert 1
#include "LabyrintheExemple.h" 

void affichage(void){
  int i,j ;
  
  for(i=0;i<largeur;i++){
    for(j=0;j<longueur;j++)
      if (petitlab[j][i]==ferme)
        printf("X") ;
      else printf(" ") ;
    printf("\n") ;
  }
}

int main(void){
  affichage();
  return 0 ;
}
 
