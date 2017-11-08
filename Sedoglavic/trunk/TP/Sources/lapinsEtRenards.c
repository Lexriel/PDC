#include <stdio.h>

int main(void){

   int stop,j ;
   int nbannee = 200 ;

   int nblapin, nbrenard ;

   int tauxlapin ;
   float Stck ; /* une variable de stockage pour rendre les calculs
                   lisible                                          */
   do{

      nblapin  = 38195 ;
      nbrenard = 200 ;

      printf("Entrer le taux de reproduction des lapins (1,2, etc.) => ") ;
      scanf("%d",&tauxlapin) ;

      for(j=1;j<nbannee;j++){

         /* calcul du nombre de lapin */
         Stck = 1.0-((float) nblapin)/100000.0- (float) nbrenard/5000.0 ;
         Stck = ((float) tauxlapin)*Stck ;
         nblapin = (int) (((float) nblapin)*Stck) ;

         /* on prepare le calcul du nombre de renard */
         Stck = ((float) nblapin)/1000.0 ;

         if (4.0<Stck) Stck = 4.0 ;

         /* calcul du nombre de renard */
         Stck = 1.0-((float) nbrenard)/25000.0+Stck ;
         nbrenard = (int) (((float) nbrenard)*Stck/4.0) ;

         /* affichage */
         printf("Il y a %d lapins et %d renards.\n",nblapin,nbrenard);
      }

      printf("Encore une simulation (1 encore, 0 stop) ? ") ;
      scanf("%d",&stop) ;

   } while(stop != 0) ;

	return 0 ;
}
 
