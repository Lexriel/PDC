#include <stdio.h>
#include "abr.h"
#define allouer (struct noeud *) malloc(sizeof(struct noeud))
                              
void init (Abr *a) {                          
  *a = NULL ;             
}                          

void inserer (Abr *a, int v){
  if (! *a) {
    *a = allouer ;
    (*a)->v = v ;
    (*a)->fg = (*a)->fd = 0 ;
  } else if (v <= (*a)->v)
    inserer (& (*a)->fg, v) ;
  else
    inserer (& (*a)->fd, v) ;
}

void inserer_iter(Abr *a, int v) {
  enum {droite, gauche} direction;
  Abr pere = NULL, current = *a;
  while (current) {
    pere = current;
    if (v <= current->v) {
      direction = gauche;
      current = current->fg;
    } else { direction = droite;
    current = current->fd; }
    
    if (pere) 
      if (direction == gauche)
	current = pere->fg = allouer ;
      else current = pere->fd = allouer ;
    else current = *a = allouer ;
    current->v = v;
    current->fg = current->fd = NULL;
  }
}

void imprimer_croissant (Abr a){        
  if (a) {                            
    imprimer_croissant (a->fg) ;      
    printf ("%d\n", a->v) ;           
    imprimer_croissant (a->fd) ;      
  }                                    
}

void imprimer_decroissant (Abr a){        
  if (a) {                            
    imprimer_croissant (a->fd) ;      
    printf ("%d\n", a->v) ;           
    imprimer_croissant (a->fg) ;      
  }                                    
}


int main(int argc, char *argv[]) {
  char order = 0;
  Abr a;
  
  if (!(strcmp(argv[1], "-r"))) {
    order=1;
    argc-=1; argv+=1;
  }
  init(&a);
  while (--argc) inserer(&a, atoi(*++argv));
  if (order)
    imprimer_decroissant(a);
  else
    imprimer_croissant(a);
}
