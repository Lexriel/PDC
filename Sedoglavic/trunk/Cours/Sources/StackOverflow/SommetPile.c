#include<stdio.h>

unsigned int SommetPile(){
  __asm__("movl %ebp,%eax") ;
}

int main(void){ 		 
  printf("%lu\n",SommetPile()) ; 
  return 0 ;			 
}                                 
