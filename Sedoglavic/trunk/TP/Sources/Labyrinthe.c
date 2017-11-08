#include <stdio.h>
#include <stdlib.h>

#define ferme  0
#define ouvert 1
#define parcouru 2
#define SortieDuLabyrintheReussie 1
#define PasDeSortieDuLabyrinthe 0
#define longueur 70
#define largeur 30
#define MaxPile longueur*largeur/2

/* Les variables globales */

/* D\'efinition du labyrinthe */

char lab[longueur][largeur] ;
   
/* D\'efinition d'une pile */

struct Pas_m{

  /* On suppose implicitement que la longueur et la largeur  */
  /* sont inf\'erieures \`a ... */
  int x ;
  int y ;
  int z ;
  int t ;
} ; 

typedef struct Pas_m Pas ;

struct Pile_m{
  unsigned int hauteur ;
  Pas tab[MaxPile] ;
} ; 

typedef struct Pile_m Pile ;

Pile Parcours ;

/* Les fonctions de manipulation de la pile */

Pas sommet(Pile *pile){

  return pile->tab[pile->hauteur-1] ;
}

void vider(Pile *pile){

  pile->hauteur=0 ;
}

void empiler(Pas element, Pile *pile){

  if (pile->hauteur<MaxPile)
    pile->tab[pile->hauteur++]=element ;
  else /* Cette solution au d\'ebordement n'est pas bien rigoureuse */
    pile->tab[pile->hauteur]=element ;
}

Pas depiler(Pile *pile){
  if (pile->hauteur==0)
    return pile->tab[pile->hauteur] ;
  else 
    return pile->tab[--pile->hauteur] ;
}

int estVide(Pile *pile){
  
  return pile->hauteur==0 ;
}

/* Les fonctions de construction et d'affichage du labyrinthe */

void affichage(){
  int i,j ;
  system("clear") ; /* un appel syst\`eme pour enjoliver l'affichage */  
  for(i=0;i<largeur;i++){
    for(j=0;j<longueur;j++)
      switch(lab[j][i]){
      case ferme : printf("X") ; break ;
      case ouvert : printf(" ") ; break ;
      case parcouru : printf(".") ; break ;
      default : printf("?") ; break ;
      }
    printf("\n") ;
  }
}

void contruireLab(float prob){
  int i,j ;
  int choix = 0 ;

  /* La fonction rand renvoit un entier aleatoire entre 0 et  RAND_MAX */
  int lim = (int) (prob*(float) RAND_MAX) ;

  do {
    /* Pour corser le jeu, on change la graine du 
       g\'en\'erateur d'entiers al\'eatoires */
    srand(rand());

    /* On remplit le tableau */
    for(i=1;i<largeur-1;i++)
      for(j=1;j<longueur-1;j++)
	if (rand()>lim)
	  lab[j][i] = ferme ;
	else lab[j][i] = ouvert ;
    
    /* On s'occupe de l'entr\'ee et de la sortie */
    lab[0][1]=ouvert;
    lab[longueur-1][largeur-2]=ouvert;

    affichage() ;

    /* On demande \`a l'utilisateur s'il est d'accord */
    printf("\n Voulez vous ce labyrinthe ? (0 non, 1 oui) ");
    scanf("%d",&choix) ;
  } while (choix==0);
}

/* La fonction de parcours */

/* Cette fonction retourne 1 si on est sorti du labyrinthe */

char parcourir(){
  
  Pas considere,avenir ;
  int z,t ;

  do{
    considere = depiler(&Parcours) ;

    if (considere.z==longueur-1 && considere.t==largeur-2)

      return SortieDuLabyrintheReussie ; /* C'est gagn\'e on est sorti */

    if (lab[considere.z][considere.t]==ouvert){
      /* Si le pas considere est possible */
      
      lab[considere.z][considere.t]=parcouru; /* On le marque comme parcouru */
      
      avenir.x=considere.z ; /* On prepare les pas a empilers */
      avenir.y=considere.t ;

      /* Par chance, on n'a pas \`a consid\'erer un tore car les bords */
      /* du labyrinthe sont infranchissables. */      
      t=considere.t;
      for(z=considere.z-1;z<considere.z+2;z++)
	if(lab[z][t]== ouvert){
	  avenir.z = z ;
	  avenir.t = t ;
	  empiler(avenir,&Parcours) ;
	}
      z=considere.z;
      for(t=considere.t-1;t<considere.t+2;t++)
	if(lab[z][t]== ouvert){
	  avenir.z = z ;
	  avenir.t = t ;
	  empiler(avenir,&Parcours) ;
	}
    }
    affichage() ;
  } while (estVide(&Parcours)!=1) ;

  return PasDeSortieDuLabyrinthe ;
}

/* La fonction principale */
int main(){
  
  Pas Premier ;

  contruireLab(0.73) ;

  /* Initialisation de la pile */
  Parcours.hauteur=0 ;

  /* Construction du premier pas */
  Premier.x = 0 ;
  Premier.y = 1 ;
  Premier.z = 1 ;
  Premier.t = 1 ;

  empiler(Premier,&Parcours) ;

  /* On considere que l'entr\'ee est parcouru */
  lab[0][1]=parcouru ;

  /* Parcours et analyse du r\'esultat */
  switch(parcourir()){
  case SortieDuLabyrintheReussie :
    printf("\n F\\'elicitation, vous \\^etes sorti\n"); 
    break ;
  case  PasDeSortieDuLabyrinthe :
    printf("\n ;-( ce labyrinthe n'a pas de sortie\n"); break ;
  default : printf("\n Je ne comprend pas ce qui se passe\n") ; break;
  }
  return 0 ;
}
 
