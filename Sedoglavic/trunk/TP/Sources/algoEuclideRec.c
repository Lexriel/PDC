#include <stdio.h>

int pgcd(int a, int b){

  if(b==0) 
    return a ; // pgcd(a,0) est egal a a
  else 
    return pgcd(b,a%b) ; /* pgcd(a,b) est egal a pgcd(b,a%b)
                            avec a%b, le reste de la division
                            euclidienne de a par b           */
}

int main (void) {
        int  A, B ;

        printf("Entrer A => ");
        scanf("%d",&A) ;
        printf("Entrer B => ");
        scanf("%d",&B) ; 

        printf("Le pgcd est %d\n",pgcd(A,B)) ;
        return 0 ;
}
 
