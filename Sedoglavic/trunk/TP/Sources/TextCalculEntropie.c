#include<stdio.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>
#include<errno.h>
#define TailleGroupeLettres 8

char longueurLettres = 1 ;

/* Les types et les  fonctions permettant la manipulation  d'une liste
   cha\^\i{}n\'ee */

typedef struct cellule_t{
  struct cellule_t *suivante ;
  char *lettres ;
  long unsigned int frequence ;
} cellule_t ;

cellule_t * CreerCellule(char *lettres, char longueurLettres){

  cellule_t * cell = (cellule_t *) malloc(sizeof(cellule_t)) ;

  cell->suivante = NULL   ; /* la cellule nouvellement cr\'ee
                             * ne pointe sur rien             */
  cell-> lettres = (char *) malloc((longueurLettres+1)*sizeof(char)) ;
  cell-> lettres = strcpy(cell-> lettres, lettres) ;
  
  cell-> frequence = 1 ;
  return cell ;
}

void DetruireCellule( cellule_t * cell ) {
  free( (void *) cell->lettres) ;
  free( (void *) cell) ;
}

void DetruireListe(cellule_t * tete){
  cellule_t * cell = tete -> suivante ;
  while(tete->suivante == NULL){
    tete->suivante = cell -> suivante ;
    DetruireCellule(cell) ;
  }
}

void InsererCellule( cellule_t * cell_a_inserer, 
                     cellule_t * cell_courante ){
  cell_a_inserer -> suivante = cell_courante -> suivante ;
  cell_courante -> suivante = cell_a_inserer ;
}

cellule_t * ExtraireCellule (cellule_t * cell_mere){
  cellule_t * tmp ;
  tmp = cell_mere->suivante ;
  cell_mere -> suivante = tmp -> suivante ;
  return tmp ;
}

/* Les    fonctions permettant de mettre    \`a  jour et d'analyser la
   structure de  donn\'ee    utilis\'ee    pour  compter    le  nombre
   d'occurences de lettres */

void ModifierListeChainee(cellule_t *cell, char *pattern){

  /* v\'erifier si pattern est d\'ej\`a pr\'esent dans la liste.  Pour
   * simplifier,  on impose \`a  la  liste d'\^etre ordonn\'ee suivant
   * l'ordre lexicographique */

  while(1){
    if (strcmp(cell->lettres,pattern)==0){
      cell->frequence++ ; 
      break ; 
    }
    if(cell->suivante==NULL || strcmp(pattern,cell->suivante->lettres)<0){
      InsererCellule(CreerCellule(pattern,longueurLettres), cell) ;
      break ;
    }
    cell = cell->suivante ;
  }
}

void  LectureGroupeLettres(int i, FILE *foo, char * strg ){

  int j=0 ;
  while(i>0 && !feof(foo)){
    fscanf(foo,"%c",strg+j) ;
    i-- ; j++ ;
  }
  *(strg+j+1) = 0 ;
  
  if (!feof(foo)){
    fseek(foo,2-j,SEEK_CUR) ;
  }
}

int main(int argc, char ** argv){

  char *patterns ; 

  FILE *foo ; /* foo repr\'esente le fichier d'entr\'ee */

  long unsigned int NbTotalLettres = 0 ;
  long unsigned int NbLettreDiff = 0 ;
  double frequence, tmp ;
  double entropieSource = 0 ;

  cellule_t *ListeChainee ;
  cellule_t *actual_cell  ;

  if (argc!=3){
    printf("\n %s foo.txt bar.res \n",*argv) ;
    return -1 ;
  }

  ListeChainee = CreerCellule("",longueurLettres) ;

  while(longueurLettres <TailleGroupeLettres) {

    foo = fopen(*(argv+1),"r") ;
    if (foo==NULL){ 
      perror("L'erreur suivante est survenue") ;
      return -1 ;
    }

    patterns = (char *) malloc((2*longueurLettres+1)*sizeof(char)) ;

    while(!feof(foo)){
      fgets(patterns,2*longueurLettres,foo) ;

      LectureGroupeLettres(longueurLettres,foo,patterns) ;

      ModifierListeChainee(ListeChainee,patterns) ;
    }
    
    fclose(foo) ; /* fermeture du fichier foo.txt */

    foo = fopen(*(argv+2),"w") ;

    if (foo==NULL){ 
      perror("L'erreur suivante est survenue") ;
      return -1 ;
    }

    actual_cell = ListeChainee ;
    while(actual_cell!=NULL) {
      NbTotalLettres += actual_cell->frequence ;
      NbLettreDiff ++ ;
      actual_cell = actual_cell-> suivante ;
    }
    
    printf("Le fichier %s contient %lu caract\\`eres au total\n",
	   *(argv+1),NbTotalLettres) ;
    printf("pour %lu lettres diff\\'erentes.\n",NbLettreDiff) ;
    
    actual_cell = ListeChainee ;
    while(actual_cell!=NULL) {
      frequence = ((double) actual_cell->frequence)/((double) NbTotalLettres) ;
      tmp = -log(frequence) ;
      entropieSource += frequence*tmp ;
      fprintf(foo,"%s\t %f\t %f\n",actual_cell-> lettres,
	      frequence,tmp) ;
      actual_cell = actual_cell-> suivante ;
    }
    fprintf(foo,"\n Entropie~: %f \n",entropieSource/longueurLettres) ;
    printf("\n Entropie~: %f \n",entropieSource/longueurLettres) ;
    /* destruction de la liste cha\^\i{}n\'ee */
    DetruireListe(ListeChainee) ;

    longueurLettres++ ;
    free( (void *) patterns) ;
  }
  fclose(foo) ;

  return 0 ;
}
 
