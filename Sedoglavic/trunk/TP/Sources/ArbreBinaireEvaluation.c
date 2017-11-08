#include <stdlib.h>
#include <stdio.h>

/*

commencer par l'evaluation 

puis completer avec du Baur Strassen 

L'evaluation de variable retourne EXIT_FAILURE

*/

struct noeud_s{
  struct cellule_s *gauche ;
  struct cellule_s *droit  ;
} ;

union contenu_s{
  int entier            ;
  char *variable        ;
  struct noeud_s *noeud ;
} ;

/* on construit un wrapper generique 
 * pour noeud et feuille */

struct cellule_s{
  int (*operation)(struct cellule_s*) ;
  union contenu_s contenu ;
} ;

typedef struct cellule_s cellule_t ;
typedef struct noeud_s   noeud_t   ;
typedef union  contenu_s contenu_t ;

/* Creation d'une feuille */

int evaluerEntier(cellule_t *cell){
  return cell->contenu.entier ;
}

int evaluerVariable(cellule_t *cell){
  printf("On ne peut evaluer des variables\n") ;
  exit(EXIT_FAILURE) ;
  return 0 ;
}

cellule_t * creerEntier(int a){
  cellule_t *res = (cellule_t *) malloc(sizeof(cellule_t)) ;
  res->operation = evaluerEntier ;
  res->contenu.entier = a ;
  return res ;
}

/* Creation d'un noeud */

cellule_t *createnode(cellule_t *g, cellule_t *d, int (*op)(cellule_t *)){

  cellule_t *node = (cellule_t *) malloc(sizeof(cellule_t)) ;
  node->operation=op ;
  node->contenu.noeud = (noeud_t *) malloc(sizeof(noeud_t)) ;
  node->contenu.noeud->gauche = g ;
  node->contenu.noeud->droit  = d ;
  return node ;
}

/* les operations */

int eval(cellule_t *cell){
  return cell->operation(cell) ;
}

int mul(cellule_t *cell) {

  cellule_t *gauche, * droit ;
  gauche = cell->contenu.noeud->gauche ;
  droit  = cell->contenu.noeud->droit ;

  return gauche->operation(gauche) * droit->operation(droit) ;
}

int add(cellule_t *cell) {

  cellule_t *gauche, * droit ;
  gauche = cell->contenu.noeud->gauche ;
  droit  = cell->contenu.noeud->droit ;

  return gauche->operation(gauche) + droit->operation(droit) ;
}

/* liberation de m\'emoire */

void freeArbre(cellule_t * cell){

  if(cell->operation==evaluerEntier)
    free(cell) ;
  else {
    freeArbre(cell->contenu.noeud->gauche) ;
    freeArbre(cell->contenu.noeud->droit) ;
  }
}

int main(void){
  cellule_t * douze = creerEntier(12) ;
  cellule_t * deux  = creerEntier(2) ;
  cellule_t * aaa   = createnode(douze,deux,add) ;
  cellule_t * bbb   = createnode(deux,aaa,mul) ;
  int a =  eval(bbb) ;
  
  free(bbb) ;
  return a ;
}

/* questions 

faire un parseur

on donne les definitions en francais et a eux de donner noeud_s, cellule_s, contenu_s

Dans la fonction add:

pourquoi passer cellule_t *cell en parametre et pas cellule_t cell.

critiquer l'usage memoire de cette fonction.

critiquer la fonction freeArbre dans l'utilisation
free(deux)
eval(aaa)

faire un truc qui d'un arbre ecris un programme ;

*/
