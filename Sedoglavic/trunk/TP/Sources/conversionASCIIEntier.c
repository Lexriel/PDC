#include<stdio.h>

int main(void){

  int res = 0 ;
  char c ;

  while((c=getchar())!='\n')
    res = (int) (c-'0') + res*10 ;

  return res ;
}
