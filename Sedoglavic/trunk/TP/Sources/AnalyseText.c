#include<stdlib.h>
#include<stdio.h>
#include <errno.h>

typedef struct cellule{
  struct cellule *suivante ;
  char lettre ;
  long unsigned int frequence ;
} cellule ;

cellule * CreerCellule(char lettre){

  cellule * cell = (cellule *) malloc(sizeof(cellule)) ;

  cell->suivante = NULL   ; /* la cellule nouvellement cr\'ee
                             * ne pointe sur rien             */
  cell-> lettre    = lettre ;
  cell-> frequence = 1 ;
  return cell ;
}

void DetruireCellule( cellule * cell) {
  free( (void *) cell) ;
}

void InsererCellule( cellule * cell_a_inserer, 
                     cellule * cell_courante){
  cell_a_inserer -> suivante = cell_courante -> suivante ;
  cell_courante -> suivante = cell_a_inserer ;
}

cellule * ExtraireCellule (cellule * cell_mere){
  cellule * tmp ;
  tmp = cell_mere->suivante ;
  cell_mere -> suivante = tmp -> suivante ;
  return tmp ;
}

int main(int argc, char ** argv){

  char lettre ;
  FILE *foo ; /* foo repr\'esente le fichier d'entr\'ee */
  FILE *bar ; /* bar repr\'esente le fichier de sortie  */

  long unsigned int NbTotalLettres = 0 ;
  long unsigned int NbLettreDiff = 0 ;

  cellule *ListeChainee ;
  cellule *actual_cell ;

  if (argc!=3){
    printf("\n %s foo.txt bar.res \n",*argv) ;
    return -1 ;
  }

  foo = fopen(*(argv+1),"r") ;

  if (foo==NULL){ 
    perror("L'erreur suivante est survenue") ;
    return -1 ;
  }

  /* On se donne une racine qui ne contient pas de lettre pour cr\'eer
     de la liste cha\^\i{}n\'ee  */
  lettre = (char) 0 ;
  ListeChainee = CreerCellule(lettre) ;

  while(!feof(foo)){
    fscanf(foo,"%c",&lettre) ;

    /* v\'erifier  si  cette lettres  est d\'eja   pr\'esente  dans la
     * liste.  Pour   simplifier, on   impose  \`a  la  liste d'\^etre
     * ordonn\'ee suivant l'ordre lexicographique */
    actual_cell = ListeChainee ;

    while(1){
      if (actual_cell->lettre == lettre){
	actual_cell->frequence++ ; 
	break ; 
      }
      if(actual_cell->suivante==NULL || lettre<actual_cell->suivante->lettre){
	InsererCellule(CreerCellule(lettre),actual_cell) ;
	break ;
      }
      actual_cell = actual_cell->suivante ;
    }
  }

  fclose(foo) ; /* fermeture du fichier foo.txt */

  actual_cell = ListeChainee ;
  while(actual_cell!=NULL) {
    NbTotalLettres += actual_cell->frequence ;
    NbLettreDiff ++ ;
    actual_cell = actual_cell-> suivante ;
  }

  printf("Le fichier %s contient %lu caract\\\\`eres au total\n",
	 *(argv+1),NbTotalLettres) ;
  printf("pour %lu lettres diff\\\'erentes.\n",NbLettreDiff) ;

  bar = fopen(*(argv+2),"w") ;

  if (bar==NULL){ 
    perror("L'erreur suivante est survenue") ;
    return -1 ;
  }

  actual_cell = ListeChainee ;
  while(actual_cell!=NULL) {
    fprintf(bar,"%c %f\n",actual_cell-> lettre,
	    ((float) actual_cell->frequence)/((float)NbTotalLettres)) ;
    actual_cell = actual_cell-> suivante ;
  }

  fclose(bar) ;

  return 0 ;

}
 
