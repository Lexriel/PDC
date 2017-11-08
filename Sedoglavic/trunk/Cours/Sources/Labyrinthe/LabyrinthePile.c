#include<stdlib.h>
#include"Labyrinthe.h"

int estVide(Pile_t *pile){  
    return (int) *pile ;
}

void empiler(Pas_t step, Pile_t *pile, char *chemin){
    cell_t *tmp = (cell_t *) malloc (sizeof(cell_t)) ;
    tmp->chemin = chemin ;
    tmp->pas = step ;
    tmp->next = *pile ;
    *pile = tmp ;
}

Pas_t depiler(Pile_t *pile){
    cell_t *tmp = *pile ;
    if (tmp==NULL) exit(0) ;
    Pas_t res = tmp->pas ;
    *pile = tmp->next ;
    free(tmp->chemin) ;
    free(tmp) ;
    return res ;
}
