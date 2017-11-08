#include<stdio.h>
#include<stdlib.h>

int main(int argc, char *argv[]){
  int i ;
  
  if(argc!=2)
    return 1 ;

  FILE *fichier = fopen("piege","w") ;
  i = atoi(argv[1]) ;
  for(;i>0;i--)
    fputc('a',fichier) ;

  fputc('\xF8',fichier) ;
  fclose(fichier) ;
  return 0 ;
}
