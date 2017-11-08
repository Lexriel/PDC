#include <stdio.h>  /* pour afficher et saisir au clavier scanf */

#define Prix_Mineur     1.0   /* les constantes <<en dur>> sont definies ici */
#define Prix_Retraite   2.0   /* le preprocesseur remplacera le nom chaque   */
#define Prix_Normal     3.0   /* fois qu'il le rencontrera par la suite      */
#define Reduction       0.8

#define Age_Mineur      18
#define Age_Retraite    65

#define Vrai            1

int main(void){
  
  int    Age    ;      /* variable locale stockant l'age */
  int    Carte  ;      /* 1 si carte, 0 sinon */
  float  APayer ;      /* variable locale stockant le resultat */
  
  /* On collecte les donnees concernant le client */
  printf("Age du client ? ") ; /* on affiche la chaine a l'ecran */
  scanf("%d", &Age);
  printf("Le client a-t-il une carte ? ") ;
  scanf("%d", &Carte);
  
  /* La partie de conditionnelle proprement dite */
  
  if (Age < Age_Mineur)
    APayer = Prix_Mineur ;  /* remarquer l'utilisation d'une constante */
  else if (Age > Age_Retraite)
    APayer = Prix_Retraite ;
  else APayer = Prix_Normal ;
  
  if ( Carte == Vrai )
    APayer = APayer*Reduction ;
  
  /* L'affichage du resultat */
  printf("La somme a payer est %f\n",APayer) ;

  return 1 ;
}
 
