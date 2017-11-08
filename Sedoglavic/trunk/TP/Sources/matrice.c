#include <stdio.h>

/* On ne s'interesse qu'a des matrices carree et 
   on note le nombre de colonnes par N           */

#define N 2  

/* On se construit une fonction qui ne retourne rien 
   mais qui affiche notre resultat */

void affichage(float M[N][N]){

  int i,j ;

  /* affichage */
  for(i=0;i<N;i++) {
    printf("[") ;
    for(j=0;j<N;j++) {
      printf(" %f ",M[i][j])  ;
    }
    printf("]\n") ;
  }
}

/* La fonction principale */

int main(void) {
  
  float M1[N][N] ; /* On definit nos matrices */ 
  float M2[N][N] ; /* d'entree                */
 
  float MP[N][N] ; /* Pour stocker le produit  */

  int i,j,k  ;     /* des indices pour nos matrices */

  /* saisie des matrices */
  printf("Saisie de la premiere matrice\n") ;

  for(i=0;i<N;i++)
    for(j=0;j<N;j++) {
      printf("Coefficient de la %d ieme ligne et %d ieme colone ? ",i+1,j+1) ;
      scanf("%f",&M1[i][j]) ;
    }
  
  affichage(M1) ;

  printf("Saisie de la seconde matrice\n") ;

  for(i=0;i<N;i++)
    for(j=0;j<N;j++) {
      printf("Coefficient de la %d ieme ligne et %d ieme colone ? ",i+1,j+1) ;
      scanf("%f",&M2[i][j]) ;
    }
  affichage(M2) ;
  /* Remarquons que l'on duplique du code et que cela devrait etre 
     evite en utilisant une fonction (cf. cours a venir)         */
  
  /* initialiser MP a zero */
  for(i=0;i<N;i++)
    for(j=0;j<N;j++) 
      MP[i][j] = 0 ;

  /* multiplication naive de nos matrices */ 
  for(i=0;i<N;i++)
    for(j=0;j<N;j++)
      for(k=0;k<N;k++)
	MP[i][j]+=M1[i][k]*M2[k][j] ;

  printf("Produit de nos deux matrices\n") ;

    affichage(MP) ;

  return 1 ;
}
 
