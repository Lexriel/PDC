#include <stdio.h>
#include <stdlib.h>
#define NBCASE 3

typedef struct position_t{

  int grille[NBCASE][NBCASE] ;
  char *solution ;
  int casevide[2] ;

} position_t ;

typedef struct cellule_t{

  struct position_t state ;
  struct cellule_t *next ;

} cellule_t ;

typedef struct file_t{
  struct cellule_t *tail, *head ;
} file_t ;

void initfile (struct file_t *file){

  file->tail = file->head = NULL ;
}

int estvide(struct file_t *file){
  return !(file->tail || file->head) ;
}

struct cellule_t * creercellule(struct position_t * pos){

  struct cellule_t * tmp = (struct cellule_t *) malloc(sizeof(struct cellule_t)) ;

  tmp->next = NULL ;
  tmp->state = *pos ;

  return tmp ;
}

void ajouter(struct file_t *file, struct cellule_t *cell){

  if(estvide(file))
    file->head = file->tail = cell ;
  else{
    cell->next = file->tail ;
    file->tail = cell ;
  }
}

void supprimer(struct file_t *file){

   struct cellule_t *pt = file->tail;

  if (pt==file->head){
    free(pt->state.solution) ;
    free(pt) ;
    file->tail = file->head = NULL ;
  }
  else{
    for(; pt->next!=file->head ; pt=pt->next) ;
    
    free(file->head->state.solution) ;
    free(file->head) ;
    pt->next = NULL ;
    file->head = pt ;
  }
}

struct position_t * examiner(struct file_t *file){

  return &(file->head->state) ;
}

int gagne(struct position_t *pos){

  int i ;
  int res = 1 ;

  for( i=0 ; ( (i<NBCASE*NBCASE-1) && res) ; i++ )
    res = res && (pos->grille[i/NBCASE][i%NBCASE] == i+1) ;

  return res ;

}

char * concat(char *old,char depl){
  int taille ;
  char *res ;

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

char * deplacementpossible(int casevide[]){

  char *res = NULL ;

  if(casevide[0]) 
    res = concat(res,'h') ;

  if(casevide[1]) 
    res = concat(res,'g') ;

  if(casevide[0] != NBCASE-1) 
    res = concat(res,'b') ;

  if(casevide[1] != NBCASE-1) 
    res = concat(res,'d') ;

  return res ;

}

struct position_t nouvelleposition(struct position_t res, char depl){

  int H=0,V=0;

  switch(depl){
  case 'h' :  V = 1  ; break ;
  case 'g' :  H = -1 ; break ;
  case 'd' :  H = 1  ; break ;
  case 'b' :  V = -1 ; break ;
  default: exit(2) ; 
  }

  res.grille[res.casevide[0]][res.casevide[1]] = 
    res.grille[res.casevide[0]-V][res.casevide[1]+H] ;
	
  res.casevide[0] -= V ;
  res.casevide[1] += H ;
  
  res.grille[res.casevide[0]][res.casevide[1]] = 0 ;

  res.solution = concat(res.solution,depl) ;

  return res ;
}

int sontegales(struct position_t *pos1, struct position_t *pos2){

  int i ;
  int res = 1 ;

  for( i=0 ; ((i<NBCASE*NBCASE-1) && res) ; i++ )
    res = res && 
      ( pos1->grille[i/NBCASE][i%NBCASE] == 
	pos2->grille[i/NBCASE][i%NBCASE]   ) ;
  return res ;
}

char * solve(struct position_t taquin){

  struct file_t file ;
  struct position_t *pos ;
  char *stck ;

  initfile (&file) ;
  ajouter(&file,creercellule(&taquin)) ;

  do {
    pos = examiner(&file) ;
    if(gagne(pos))
      return pos->solution ;
    
    stck = deplacementpossible(pos->casevide) ;

    while(*stck) {
      taquin = nouvelleposition(*pos,*stck) ;
      ajouter(&file,creercellule(&taquin)) ;
      stck ++ ;
    } 
    supprimer(&file) ;
    
  } while(1) ;  
}

int main(){

  struct position_t initiale =
    {
      .grille = { {1 , 0 ,2}, {3 ,4 ,5}, {6 ,7 , 8} } ,
      .solution = NULL ,
      .casevide = { 0,0} 
    } ;

  printf("La solution est %s \n",solve(initiale)) ;
  return 0 ;
}
