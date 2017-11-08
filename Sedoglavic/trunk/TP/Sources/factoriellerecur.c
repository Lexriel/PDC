#include <stdio.h> 

unsigned long int factorielle(unsigned long int n){

  if(n==1)
    return 1 ;
  else
    return n*factorielle(n-1) ;
}

int main(void){

       int n ;

       /* On collecte les donnees concernant le client */
       printf("Quelle factorielle voulez vous calculer ? ") ; 
       scanf("%d", &n);

       /* L'affichage du resultat */
       printf("Le resultat est %lu\n",factorielle(n)) ;
       return 0 ;
}
 
