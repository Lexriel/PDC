#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "dico4lettres.h"
#define taille_mot 4 

#define parcouru 1
#define nonparcouru 0


void TriBulle(void){
  int i,j ;
  char *tmp ;

  for ( i=taille_dico-1 ; i >=0 ; --i)
    for ( j=1 ; j<=i ; j++) 
      if (strcmp(dico[j-1],dico[j])>0){
        tmp       = dico[j-1] ;
        dico[j-1] = dico[j] ;
        dico[j]   = tmp ;
      }
}

/* Cette procedure prend en argument deux chaines de caracteres 
   Elle renvoit 1 si les chaines ne different que par un caractere et 0 sinon */

int estSuccesseur(char a[4], char b[4]){

  int i,diff ;

  diff = 0 ;
  for(i=0;i<4;i++)
    if(a[i]-b[i]!=0)
      diff++ ;

  if (diff<2)
    return 1 ;
    
  return 0 ;
}

void CreeMatriceAdjacence(int **mat){

  int i,j ;

  // on parcours tous les mots du dictionnaires
  for(i=0; i<taille_dico;i++) 
    /* Pour chaque mots, on compare avec tout les autres mots pour savoir si ce 
       sont des successeurs. */
    for(j=i; j<taille_dico;j++) // la matrice d'incidence est symetrique
      mat[i][j]=estSuccesseur(dico[i],dico[j]) ;

 // il faut donc terminer par remplir le reste de la matrice
 for(i=1;i<taille_dico;i++)
	 for(j=0;j<i;j++)
		 mat[i][j]=mat[j][i] ;
}
//-----------------------------------------------------------------------------
/* Les fonctions de manipulation de la pile */

/* Definition d'une pile */

typedef struct Pile{

  unsigned int hauteur ;
  int tab[taille_dico] ;

} Pile ;

int sommet(Pile *pile){

  return pile->tab[pile->hauteur-1] ;
}

void vider(Pile *pile){

  pile->hauteur=0 ;
}

void empiler(int element, Pile *pile){

  if (pile->hauteur<taille_dico)
    pile->tab[pile->hauteur++]=element ;
  else /* Cette solution au debordement n'est pas bien rigoureuse */
    pile->tab[pile->hauteur]=element ;
}

int depiler(Pile *pile){
  if (pile->hauteur==0)
    return pile->tab[pile->hauteur] ;
  else 
    return pile->tab[--pile->hauteur] ;
}

int estVide(Pile *pile){
  
  return pile->hauteur==0 ;
}

// la fonction de parcours --------------------------------------------------------

int ConvertionMotIndice(char *mot1) {

  int i,gauche,droite,stop ;

  /* La recherche proprement dit */
  gauche = 1 ;
  droite = taille_dico ;
  do{
      i = (droite + gauche)/2 ;
      stop =strcmp(dico[i],mot1)  ;
      if (stop == 0) 
	return i ;
      else if (stop<0)
        gauche = i +1 ;
      else droite = i -1 ;
  } while ( gauche <= droite) ;

  return -1 ;
}

// la fonction chemin prend en argument
// l'indice du premier mot
// l'indice du second mot
// la matrice d'incidence du graphe associe au dictionnaire

int  CheminExiste(int sommet, int sommetdestination, int **mat) {

  Pile parcours ;

  int i ;
  int dejaparcouru[taille_dico] ;

  // initialisation de la pile
  parcours.hauteur = 0 ;

  /* il nous faut trouver les indices correspondant aux mots afin de pouvoir
     utiliser la matrice d'incidence  */

  // empilement du premier pas
  empiler(sommet,&parcours) ;

  // on construit un tableau des sommets deja parcouru
  for(i=0;i<taille_dico;i++) 
    dejaparcouru[i] = nonparcouru ;

  dejaparcouru[sommet] = parcouru ;

  do{

    sommet = depiler(&parcours) ;
    if (sommet==sommetdestination) 
      return 1 ;

    for(i=0;i<taille_dico;i++) 
      if (mat[sommet][i]!=0 && dejaparcouru[i]!=parcouru){
	dejaparcouru[i] = parcouru ;
	empiler(i,&parcours) ;
      }	
    
  } while (estVide(&parcours)!=1) ;

  return 0 ;
}


// main ---------------------------------------------------------------------------

int main(void){

  int **MatriceAdjacence ;
  int i,j ;
  char *mot1,*mot2 ;

  // On reserve de la place en memoire pour contenir le tableau
  MatriceAdjacence = (int **) malloc(taille_dico*sizeof(int *)) ;

  for (i=0;i<taille_dico;i++) 
    MatriceAdjacence[i] = (int *) malloc(taille_dico*sizeof(int)) ;

  // allocation pour les chaines de caracteres

  mot1 = (char *) malloc(4*sizeof(char)) ;
  mot2 = (char *) malloc(4*sizeof(char)) ;


  /* On va utiliser de la recherche dichotomique plus tard
     il nous faut donc trier notre tableau dico */
  TriBulle() ;

  CreeMatriceAdjacence(MatriceAdjacence) ;

  printf("Entrez le mot de depart => ") ;
  scanf("%s",mot1) ;

  if ((i = ConvertionMotIndice(mot1))==-1){
    printf("Le mot %s n'est pas dans le dictionnaire\n",mot1) ;
    exit(1);
  }

  printf("Entrez le mot d'arrivee => ") ;
  scanf("%s",mot2) ;

  if ((j = ConvertionMotIndice(mot2))==-1){
    printf("Le mot %s n'est pas dans le dictionnaire\n",mot2) ;
    exit(1);
  }

  switch(CheminExiste(i,j,MatriceAdjacence)){
  case 1 :
    printf("\n Felicitation, le chemin existe\n"); break ;
  case 0 :
    printf("\n ;-( ces mots ne peuvent etre lies\n"); break ;
  default : printf("\n Je ne comprend pas ce qui se passe\n") ; break;
  }
  return 0 ;
}
 
