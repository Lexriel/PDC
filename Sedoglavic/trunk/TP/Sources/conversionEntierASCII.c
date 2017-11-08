#include<stdio.h>

int main(void){

  int i = 3456 ;
  
  int d=1, l=1 ;

  while(i%d!=i) {
    l++ ;
    d*=10 ;
  }

  while(i!=0){
    d/=10 ;
    putchar(i/d +'0') ;
    i -= d*(i/d) ;
  }
  
  return 0 ;
}
 
