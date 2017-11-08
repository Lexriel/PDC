#include <stdio.h>

#define Taux_conversion 6.55957 
#define Stop            0

int main(void) {
  float francs ;
  float euros  ;
  int   stop   ;

  do {
    printf("Somme en francs a convertir => ") ; 
    scanf("%f",&francs) ;

    euros = francs/Taux_conversion ;

    printf("Cette somme corresponds a %f euros\n",euros) ;
    printf("Stop ou encore (0 pour stop, autre entier pour encore) ") ;
    scanf("%d",&stop) ;

  } while(stop!=Stop) ;

  return 0 ;
     
}


 
