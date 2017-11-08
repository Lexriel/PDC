#include<stdlib.h>
#include<stdio.h>

typedef struct cellule{
  struct cellule *suivante ;
  long unsigned int entier ;
} cellule ;

cellule * CreerCellule(long unsigned int NbPremier){

  cellule * cell = (cellule *) malloc(sizeof(cellule)) ;

  cell->suivante = NULL   ; /* la cellule nouvellement cr\'ee
                             * ne pointe sur rien             */
  cell-> entier  = NbPremier ;
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

int main(void){

  long unsigned int i,j ;
  cellule *ListeChainee ;
  cellule *actual_cell ;
  cellule *tmp_cell ;

  printf("Entrez la borne pour le crible ") ;
  scanf("%lud",&i) ;

  if(i<2){
    printf("Soyez plus ambitieux\n") ;
    return -1 ;
  }
  
  ListeChainee = CreerCellule(2) ;
  actual_cell = ListeChainee ;

  j=3 ;
  while(j<=i){
    InsererCellule(CreerCellule(j), actual_cell) ;
    actual_cell=actual_cell->suivante ;
    j++ ;
  }

  actual_cell = ListeChainee ;
  while(actual_cell!=NULL){
    
    tmp_cell = actual_cell ;
    while(tmp_cell->suivante!=NULL){
      if ((tmp_cell->suivante)->entier%actual_cell->entier==0)
	DetruireCellule(ExtraireCellule(tmp_cell)) ;
      else tmp_cell = tmp_cell->suivante ;
    }
    actual_cell = actual_cell->suivante ;
  }

  actual_cell = ListeChainee ;
  while(actual_cell!=NULL){
    printf("%lu \n",actual_cell->entier) ;
    actual_cell = actual_cell->suivante ;
  }
  return 1 ;
}
 
