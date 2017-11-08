#include <stdio.h>

int main(void){

  int jour ;

  /* On collecte un entier correspondant a un jour */
  printf("Le jour de la semaine (entrer un entier, lundi = 1) ? ") ;
  scanf("%d", &jour);
  
  /* La partie de conditionnelle proprement dite */
  switch(jour){
  case 1 : printf("Monday\n") ; break ;
  case 2 : printf("Tuesday\n") ; break ;
  case 3 : printf("Wednesday\n") ; break ;
  case 4 : printf("Thursday\n") ; break ;
  case 5 : printf("Friday\n") ; break ;
  case 6 : printf("Saturday\n") ; break ;
  case 7 : printf("Sunday\n") ; break ;
  default : printf("N'existe pas\n") ; break ;
  }
  return 0 ;
}
 
