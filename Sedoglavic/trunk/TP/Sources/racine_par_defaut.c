#include <stdio.h>

int racine_par_defaut(int n){

  int d=n ;
  int g=0 ;
  int i ;
  
  do{
    i = (d+g)/2 ;

    if (i*i>n)
      d = i ;
    else if ((i+1)*(i+1)<n)
      g = i ;
    else return i ;

  } while (1) ;
}
 
