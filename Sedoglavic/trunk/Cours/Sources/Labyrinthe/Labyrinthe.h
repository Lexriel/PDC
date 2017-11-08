#define FERME 0
#define OUVERT 1 
#define PARCOURU 2

struct Pas{
  int x ;
  int y ;
} ;

typedef struct Pas Pas_t ;

struct cell{
  Pas_t pas ;
  struct cell * next ;
  char *chemin ;
} ;

typedef struct cell cell_t ;

typedef cell_t * Pile_t ;

