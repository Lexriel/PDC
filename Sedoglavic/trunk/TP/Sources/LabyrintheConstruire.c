#include <stdio.h>
#include <stdlib.h>
#include "LabyrintheAffichage.h"

char lab[longueur][largeur] ;

void contruireLab(float prob){
  int i,j ;
  int choix = 0 ;

  /* La fonction rand renvoit un entier aleatoire entre 0 et  RAND_MAX */
  int lim = (int) (prob*(float) RAND_MAX) ;

  do {
    /* Pour corser le jeu, on change la graine du 
       generateur d'entiers aleatoires */
    srand(rand());

    /* On remplit le tableau */
    for(i=1;i<largeur-1;i++)
      for(j=1;j<longueur-1;j++)
        if (rand()>lim)
          lab[j][i] = ferme ;
        else lab[j][i] = ouvert ;
    
    /* On s'occupe de l'entree et de la sortie */
    lab[0][1]=ouvert;
    lab[longueur-1][largeur-2]=ouvert;

    affichage() ;

    /* On demande a l'utilisateur s'il est d'accord */
    printf("\n Voulez vous ce labyrinthe ? (0 non, 1 oui) ");
    scanf("%d",&choix) ;
  } while (choix==0);

}

int main(void){
  
  contruireLab(0.6) ;
  affichage();
  return 1 ;
}
 
