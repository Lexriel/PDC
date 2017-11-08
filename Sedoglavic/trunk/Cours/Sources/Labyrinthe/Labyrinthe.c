#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include"Labyrinthe.h"
#include"LabyrintheExemple.h"

extern void empiler(Pas_t, Pile_t *, char *);
extern Pas_t depiler(Pile_t *) ;
extern int estVide(Pile_t *) ;

char * concat(char *old,char depl){
  int taille ;
  char *res = old ;

  if (!old){
    res = (char *) malloc(2) ;
    *res = depl ;
    *(res+1) = 0 ;
    return res ;
  }
    
  for( taille=0 ; *res ; taille++,res++ ) ;
  
  res = (char *) malloc(taille+1); 

  for(taille=0 ; *old ; old++,taille++) 
    *(res+taille) = *old ;

  *(res+taille++) = depl ;
  *(res+taille) = 0 ;

  return res ;
}

void affichage(char lab[LONGUEUR][LARGEUR]){
  int i,j ;
  
  for(i=0;i<LARGEUR;i++){
    for(j=0;j<LONGUEUR;j++)
      switch(lab[j][i]){
      case FERME : printf("X") ; break ;
      case OUVERT : printf(" ") ; break ;
      case PARCOURU : printf("o") ; break ;
      default : printf("?") ; break ;
      }
    printf("\n") ;
  }
}

void mystrcpy(char **dest, char *str){
  int i ;
  char * tmp = str ;

  if(*dest) 
    free(*dest) ;
  
  if (!tmp)
    *dest = NULL ;
  else {
    for( i=0 ; *tmp ; i++,tmp++ ) ;
  
    *dest = (char *) malloc(i+1); 
    for(i=0 ; *str ; str++) 
      *(*dest+i++) = *str ;
      *(*dest+i) = 0 ;
  }
}

char * parcourir(Pile_t *pile, char lab[LONGUEUR][LARGEUR]){
  
  Pas_t pos,nextpos ;
  Pas_t pas[4] = {{-1,0},{1,0}, {0,1},{0,-1}} ;
  char dep[4] = {'w','e','s','n'} ;
  char *path = NULL;
  int i ;
 
  do{
    mystrcpy(&path,(*pile)->chemin) ;
    pos = depiler(pile) ;

    if (pos.x==LONGUEUR-1 && pos.y==LARGEUR-2)
      return path ; /* C'est gagn\'e on est sorti */

    for(i=0; i<4 ; i++){
      nextpos.x = pos.x+pas[i].x ; /* On pr\'epare les pas \`a empiler */	      
      nextpos.y = pos.y+pas[i].y ;
      if (lab[nextpos.x][nextpos.y]==OUVERT){ /* Si le pas consid\`ere est possible */
	lab[nextpos.x][nextpos.y]=PARCOURU; /* On le marque comme parcouru */
	empiler(nextpos,pile,concat(path,dep[i])) ;
	affichage(lab) ;
	printf("\n") ;
      }
    }
  } while (estVide(pile)) ;
  
  return 0 ;
}

int main(void){

  char *path = "" ;
  /* Le  premier pas */
  Pas_t PointDeDepart = {.x = 0 ,.y = 1 } ;

  Pile_t mapile = NULL ; 

  empiler(PointDeDepart, &mapile, path) ;

  /* On considere que l'entr\'ee est parcouru */
  petitlab[PointDeDepart.x][PointDeDepart.y]=PARCOURU ;

  /* Parcours et analyse du resultat */
  path = parcourir(&mapile,petitlab) ;
  if( path )
    printf("\n Felicitation, vous \\^etes sorti par le chemin %s\n",path); 
  else
    printf("\n ;-( ce labyrinthe n'a pas de sortie\n"); 

  return 0 ;
}
