#include<stdio.h>
#include <stdlib.h>
 
float strtof(const char *, char **);

int main(int argc, char *argv[]){
  printf("%f\n", strtof(argv[1], NULL)) ;  
  return 0 ;
}
