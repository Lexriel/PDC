#include <stdio.h>  /* pour afficher */

int main(void){

       unsigned long int fact=1 ;
       int      i    ;
       int      n    ;

       /* On collecte les donnees concernant le client */
       printf("Quelle factorielle voulez vous calculer ? ") ; 
       scanf("%d", &n);

       for (i=1 ; i<n+1 ; i++)
	 fact = fact*i ;

       /* L'affichage du resultat */
       printf("Le resultat est %lu\n",fact) ;

       return 0 ;
}

 
