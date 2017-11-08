#define MAXPILE 100 

/* D\'efinition d'une pile */

struct Pas{
  int x ;
  int y ;
  int z ;
  int t ;
} ;

typedef struct Pas Pas_t ;

struct Pile{
  unsigned int hauteur ;
  Pas_t tab[MAXPILE] ;
}  ;

typedef struct Pile Pile_t ;

/* Les fonctions de manipulation de la pile */

Pas_t sommet(Pile_t *pile){

  return pile->tab[pile->hauteur-1] ;
}

void vider(Pile_t *pile){

  pile->hauteur=0 ;
}

void empiler(Pas_t element, Pile_t *pile){

  if (pile->hauteur<MAXPILE)
    pile->tab[pile->hauteur++] = element ;
  else /* Cette solution au d\'ebordement n'est pas bien rigoureuse */
    pile->tab[pile->hauteur] = element ;
}

Pas_t depiler(Pile_t *pile){
  if (pile->hauteur==0)
    return pile->tab[pile->hauteur] ;
  else 
    return pile->tab[--pile->hauteur] ;
}

int estVide(Pile_t *pile){
    return pile->hauteur==0 ;
}
 
