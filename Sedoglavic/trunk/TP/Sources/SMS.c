#include "stdio.h"
#include "stdlib.h"
#define MAX 100

void 
traduction
(char code[MAX])
{
  
  int i,j ;
  char trad[MAX] ;

  i = j = 0 ;

  while(code[j]!=0){

    switch(code[j]){
    case '#' : j++ ; continue ; break ;
    case '1' : trad[i] =' ' ; break ;
    case '2' : trad[i] ='a' ; break ;
    case '3' : trad[i] ='d' ; break ;
    case '4' : trad[i] ='g' ; break ;
    case '5' : trad[i] ='j' ; break ;
    case '6' : trad[i] ='m' ; break ;
    case '7' : trad[i] ='p' ; break ;
    case '8' : trad[i] ='t' ; break ;
    case '9' : trad[i] ='w' ; break ;
    default : printf("Erreur dans la chaine\n") ; exit(-1) ;
    }  

    j++ ;
    while(code[j-1]==code[j]) {
      trad[i]++ ;
      j++ ;
    } 
    i++ ;
  }
  trad[i] = 0 ;
  printf("La traduction est %s\n",trad) ;
}

int main(void){

  char code[MAX];

  printf("Saisir le code a traduire => ");
  scanf("%s",code) ;
  traduction(code) ;
  return 0 ;
} 
 
