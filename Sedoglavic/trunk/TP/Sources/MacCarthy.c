#include <stdio.h>

int MacCarthy (int) ;

int main (void) {
  int n ;
  enum Type_choix {stop, encore} choix=encore ;

  while (choix==encore){
    printf("Entrer l'entier n => ") ;
    scanf("%d",&n) ; 
    printf("Pour %d, la fonction 91 de MacCarthy vaut %d\n",n,MacCarthy(n)) ;
    printf("Encore un calcul (1=encore, 0=stop) ? ") ;
    scanf("%d",&choix) ; // Attention a l'abus sur le type de choix 
  }
  return 1 ;
}

int MacCarthy (int n) {
  if(n>100)
    return(n-10);
  else return(MacCarthy(MacCarthy(n+11))) ;
}
 
