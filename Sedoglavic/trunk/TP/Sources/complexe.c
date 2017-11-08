#include <stdio.h>

typedef struct Complexe {
  float partie_reelle ;
  float partie_imaginaire ;
} Complexe ;

void PrintComplexe ( Complexe a ){

  if (a.partie_reelle!=0)
    printf("%f",a.partie_reelle) ;

  if (a.partie_imaginaire>0)
    printf("+%f*I ",a.partie_imaginaire) ;

  if (a.partie_imaginaire<0)
    printf("-%f*I ",-a.partie_imaginaire) ;
}

Complexe  add ( Complexe a, Complexe b) {

  Complexe c ;

  c.partie_imaginaire = a.partie_imaginaire+b.partie_imaginaire ;
  c.partie_reelle = a.partie_reelle+b.partie_reelle ;
    
  return c ;
}

Complexe mul ( Complexe a, Complexe b) {

  Complexe c ;

  c.partie_reelle = a.partie_reelle*b.partie_reelle - a.partie_imaginaire*b.partie_imaginaire  ;
  c.partie_imaginaire = b.partie_reelle*a.partie_imaginaire+a.partie_reelle*b.partie_imaginaire ;
    
  return c ;
}

Complexe quo ( Complexe a, Complexe b) {

  Complexe d = {b.partie_reelle, -b.partie_imaginaire}  ;
  Complexe c = mul(a,d) ;

  d = mul(b,d) ;
 
  c.partie_reelle /= d.partie_reelle ;
  c.partie_imaginaire /= d.partie_reelle ;
    
  return c ;
}

int main(void){

  Complexe var1 = {1,4} ;
  Complexe var2 = {1,4} ;

  printf("La somme de ") ;  PrintComplexe(var1) ;
  printf(" et de ");  PrintComplexe(var2) ;
  printf(" est ") ;  PrintComplexe(add(var1,var2)) ;
  printf("\n") ;

  printf("La produit de ") ;  PrintComplexe(var1) ;  
  printf(" et de ");  PrintComplexe(var2) ;  
  printf(" est ") ;  PrintComplexe(mul(var1,var2)) ;
  printf("\n") ;

  printf("La quotient de ") ;  PrintComplexe(var1) ;
  printf(" et de ");  PrintComplexe(var2) ;
  printf(" est ") ;  PrintComplexe(quo(var1,var2)) ;
  printf("\n") ;

  return 0 ;
}
 
