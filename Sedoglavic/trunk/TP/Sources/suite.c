#include <stdio.h>

#define InitCond0 1.0 
#define InitCond1 0.9 
#define CoeffRec1 2.0
#define CoeffRec2 -0.99

int main(void) {

  float  U0 = InitCond0 ; 
  float  U1 = InitCond1 ;
  
  int j ;
	
  float  S  ; 

  /* calcul des termes des suites */
  for (j=1;j<1000;j++) {
    S = CoeffRec1*U1 + CoeffRec2*U0 ;
    U0 = U1 ;
    U1 = S  ;
    printf("Le %d ieme terme de la suite U est %f\n",j+1,U1) ;
  }

  return 1 ;
}


 
