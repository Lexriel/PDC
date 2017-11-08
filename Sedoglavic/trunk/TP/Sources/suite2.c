#include <stdio.h>

#define Coeff1Rec1 5
#define Coeff2Rec1 -3

#define Coeff1Rec2 2
#define Coeff2Rec2 -3

int main(void) {

  int  U0  ; 
  int  U1  ;
  int  V0  ; 
  int  V1  ;
  int   n  ;
  int   j  ;
  int  SU  ; 
  int  SV  ; 

  /* Les saisies au claviers */
  printf("Conditions initiales U0 ?") ;
  scanf("%d",&U0) ;
  printf("Conditions initiales U1 ?") ;
  scanf("%d",&U1) ;
  printf("Conditions initiales V0 ?") ;
  scanf("%d",&V0) ;
  printf("Conditions initiales V1 ?") ;
  scanf("%d",&V1) ;
  printf("Quel est l'entier n ?") ;
  scanf("%d",&n) ;
  
  /* calcul des termes des suites */
  for (j=1;j<n;j++) {
    SU = Coeff1Rec1*U1 + Coeff2Rec1*V0 ;
    SV = Coeff1Rec2*V1 + Coeff2Rec2*U0 ;
    U0 = U1 ;
    U1 = SU ;
    V0 = V1 ;
    V1 = SV ;

  }

  printf("Les %d iemes termes des suite U et V sont : %d et %d \n",j+1,U1,V1) ;

  return 1 ;
}


 
