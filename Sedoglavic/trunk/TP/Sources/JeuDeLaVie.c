#include <stdio.h>
#include <stdlib.h>


#define NX 40 
#define NY 20 
#define SautDeLigne    printf("\n")
#define CoinDuPlan     printf("+") 
#define BordHorizontal printf("-")
#define BordVertical   printf("|")
#define CelluleMorte   printf(" ")
#define CelluleVivante printf("X") 

int main(void){

  /* Le plan du jeu est represente par un tableau bidimensionnel */
  int PlanDeJeu[NX][NY] ;
  
  /* Pour preparer l'etape suivante, on doit considerer une copie */
  int PlanDeJeu2[NX][NY] ;

  int X,Y ;
  int regle ;

  enum booleen {Faux,Vrai} stop=Faux ;
  enum Etat {Mort,Vivant} etat ;

  /* Initialisation du plan de jeu */
  for(X=0;X<NX;X++)
    for(Y=0;Y<NY;Y++)
      /*       PlanDeJeu[X][Y]=Mort ; */{
      if (random() > random())
	PlanDeJeu[X][Y]=Mort ;
      else PlanDeJeu[X][Y]=Vivant ;
    }

  /* Pour initialiser le jeu, on propose a l'utilisateur de remplir 
     des cellules du plan */
/*   do{

     printf("Donnez les coordonnees d'une cellule vivante\n") ; 
     printf("X (1..%d) => ",NX) ; 
     scanf("%d",&X) ; 
     printf("Y (1..%d) => ",NY) ; 
     scanf("%d",&Y) ; 
     PlanDeJeu[(X-1)%NX][(Y-1)%NY]=Vivant ; */

     /* Les restes de divisions euclidienne % evitent de sortir du tableau. 
        On retire 1 pour respecter les conventions de C */ 

  /*     printf("Stop ou encore (stop=%d,encore=%d) =>",Vrai,Faux) ; 
     scanf("%d",&stop) ; 
   } while (stop!=Vrai) ; */

  /* Execution du jeu */
  stop=Faux ;
  do{
    /* Affichage du plan de jeu */
    CoinDuPlan ;
    for(X=0;X<NX;X++) 
      BordHorizontal ;
    CoinDuPlan ;
    SautDeLigne ;
    for(Y=0;Y<NY;Y++){
      BordVertical ;
      for(X=0;X<NX;X++)
	if(PlanDeJeu[X][Y]==Vivant)
	  CelluleVivante ;
	else CelluleMorte ;
      BordVertical ;
    SautDeLigne ;
    }
    CoinDuPlan ;
    for(X=0;X<NX;X++) 
      BordHorizontal ;
    CoinDuPlan ;
    SautDeLigne ;
    
    /* Transition d'un etat au suivant */
    for(Y=1;Y<=NY;Y++)
      for(X=1;X<=NX;X++){
	regle = PlanDeJeu[(X-1)%NX][(Y-1)%NY] +
	  PlanDeJeu[(X-1)%NX][Y%NY] +
	  PlanDeJeu[(X-1)%NX][(Y+1)%NY] +
	  PlanDeJeu[X%NX][(Y-1)%NY] + 
	  PlanDeJeu[X%NX][(Y+1)%NY] +
	  PlanDeJeu[(X+1)%NX][(Y-1)%NY] +
	  PlanDeJeu[(X+1)%NX][Y%NY] +
	  PlanDeJeu[(X+1)%NX][(Y+1)%NY] ;

	if(regle==3)
	  PlanDeJeu2[X%NX][Y%NY]=Vivant ;
	else if(regle<=1 || regle >=4)
	  PlanDeJeu2[X%NX][Y%NY]=Mort ;
	else PlanDeJeu2[X%NX][Y%NY]=PlanDeJeu[X%NX][Y%NY] ;
      }

    for(X=0;X<NX;X++)
      for(Y=0;Y<NY;Y++)
	PlanDeJeu[X][Y]=PlanDeJeu2[X][Y] ;

    printf("Stop ou encore (stop=%d,encore=%d) =>",Vrai,Faux) ;
    scanf("%d",&stop) ;
  } while (stop!=Vrai) ;
  return 0 ;
}
 
