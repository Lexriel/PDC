#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char *int2string(int i){
  
  int d=1, l=1 ;
  while(i%d!=i) {
    l++ ;
    d*=10 ;
  }

  char *res = (char *) malloc(l*sizeof(char)) ;
  
  int j = 0 ;

  while(i!=0){
    d/=10 ;
    *(res+j++) = i/d +'0' ;
    i -= d*(i/d) ;
  }
  
  *(res+j) = 0 ;
  return res ;
}

char * noncmp2cmp(char *noncmp){

  char *tmp1=noncmp ;
  char *tmp2=noncmp+1 ;
-
  while(*tmp1!=0) {
    int nbrep = 1 ;
  
    int lmotif = 1 ;

    strncmp(tmp1,tmp2,1) ;
  }
  
  char * res ;

	
  return res ;
}

int main(void){

  return 0 ;
}
 
