#include <string.h>
#include <stdio.h>
#include "dico4lettres.h" // un entier taille_dico est defini ici

void TriShell(void){
  int i = 1,j, k ;
  char *tmp ;

  while(i <= taille_dico)
    i = 3*i+1 ;
  
  while (i>1){
    i = i/3 ;
    for ( j=i ; j<taille_dico ; j++) 
      if (strcmp(dico[j],dico[j-i])<0){
        tmp       = dico[j] ;
        k = j ;
        while(k>=i && strcmp(dico[k-i],tmp)>0){
          dico[k] = dico[k-i] ;
          k=k-i ;
        }
        dico[k]   = tmp ;
      }
  }
}

void affichage(void){
  int i ;
  for ( i=0 ; i < taille_dico ; i++)
    printf("%s\n",dico[i]) ;
}

int main(void){
  printf("D\'ebut du tri\n") ;
  TriShell();
  printf("Fin du tri\n") ;
  affichage() ;
  return 1 ;
}
 
