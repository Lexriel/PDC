# ifndef _TYPES_H_
# define _TYPES_H_
# define FAUX 0
# define VRAI (!FAUX)


typedef int bool;           /* définition d'un type booléen */


/* Definition du type bloc */
typedef struct bloc_s Bloc;
struct bloc_s{
  void* adresse_espace_alloue;    /* adresse d'espace alloué */
  int   taille;                   /* taille  d'espace alloué */
  bool  est_libre;                /* l'espace mémoire est-il libre ? */
  Bloc* next;                     /* pointe sur le bloc suivant */
  Bloc* prev;                     /* pointe sur le bloc precédent */
};

# define sizeBloc (sizeof(Bloc))

#endif
