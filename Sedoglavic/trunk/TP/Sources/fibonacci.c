#include <stdio.h>  /* pour afficher */

int main(void){

       int res,n,i ;  
       int U0 = 0  ;
       int U1 = 1  ;

       /* On collecte les donnees concernant le client */
       printf("Quelle terme voulez vous calculer ? ") ; 
       scanf("%d", &n);

       for (i=1 ; i<n ; i++) {
          res = U0 + U1 ;
          U0  = U1 ;
          U1  = res ;
       }
       /* L'affichage du resultat */
       printf("Le resultat est %d\n",U1) ;
       return 0 ;
}
 
