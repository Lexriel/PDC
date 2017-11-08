#include <stdio.h>

int Fibonacci(int i){
  if (i<=1) 
    return 1 ;
  else 
    return Fibonacci(i-1) + Fibonacci(i-2) ;
}

int main(void) {
  int n ;
  printf("Quel terme de la suite voulez vous calculer => ") ;
  scanf("%d",&n) ;
  printf("Votre calcul est\n");
  printf("Fib(%d) -> %d",n,Fibonacci(n)) ;
  return 0 ;
}




 
