#include <stdio.h>

typedef struct Rationnel {
  int numerateur ;
  int denominateur ;
} Rationnel ;

Rationnel normal (Rationnel a) {

  Rationnel b ;
  int  A = a.numerateur ;
  int  B = a.denominateur ;
  int  R ;

  while (B != 0) {
    R = A % B ;
    A = B ;	
    B = R ;
  } ;

  b.numerateur = a.numerateur / A ;
  b.denominateur = a.denominateur / A ;
	
  return b ;
}

void PrintRationnel ( Rationnel a ){

  printf("%d/%d",a.numerateur,a.denominateur) ;
}

Rationnel add ( Rationnel a, Rationnel b) {

  Rationnel c ;

  c.numerateur = a.numerateur*b.denominateur + 
                 b.numerateur*a.denominateur  ;
  c.denominateur = a.denominateur*b.denominateur ;
    
  return normal(c) ;
}

Rationnel mul ( Rationnel a, Rationnel b) {

  Rationnel c ;

  c.numerateur = a.numerateur*b.numerateur  ;
  c.denominateur = a.denominateur*b.denominateur ;
    
  return normal(c) ;
}

Rationnel quo ( Rationnel a, Rationnel b) {

  Rationnel c ;

  c.numerateur = a.numerateur*b.denominateur  ;
  c.denominateur = a.denominateur*b.numerateur ;
    
  return normal(c) ;
}

int main(void){

  Rationnel var1 = {1,4} ;
  Rationnel var2 = {1,4} ;

  printf("La somme de ") ;  PrintRationnel(var1) ;
  printf(" et de ");  PrintRationnel(var2) ;
  printf(" est ") ;  PrintRationnel(add(var1,var2)) ;
  printf("\n") ;

  printf("La produit de ") ;  PrintRationnel(var1) ;  
  printf(" et de ");  PrintRationnel(var2) ;  
  printf(" est ") ;  PrintRationnel(mul(var1,var2)) ;
  printf("\n") ;

  printf("La quotient de ") ;  PrintRationnel(var1) ;
  printf(" et de ");  PrintRationnel(var2) ;
  printf(" est ") ;  PrintRationnel(quo(var1,var2)) ;
  printf("\n") ;

  return 1 ;
}
 
