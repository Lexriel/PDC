# include <stdio.h>       

int main(int argc, char *argv[]) {
  int i ;
  printf(" %d \n",argc) ; 
  for( ; argc > 0 ; argc--){
    printf(" %d ",argc) ;
    i = 0 ;
    while(argv[argc-1][i]!=0)
      printf("%c",argv[argc-1][i++]) ; 
    printf("\n") ;
  }
  return 0;
}
