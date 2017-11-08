#include <stdio.h>

int main(void){

   float  Poids, Taille, Indice ;

   printf("Entrez votre poids (en kg) => ");
   scanf("%f",&Poids);
   printf("Entrez votre taille (en m) => ");
   scanf("%f",&Taille) ;

   Indice = Poids/(Taille*Taille) ;

   printf("Votre indice de masse corporelle est %f \n",Indice) ;

   printf("D'apres la classification de l'OMS, vous etes ");

   if (Indice < 18.5)
     printf("maigre.") ;
   else if ( Indice > 25.0)
     printf("en surpoids.") ;
   else printf("de constitution normale.") ;
   printf("\n");

   return 0 ;
} 
 
