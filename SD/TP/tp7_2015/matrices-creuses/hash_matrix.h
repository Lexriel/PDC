#if ! defined (HASH_MATRIX_H)
#define HASH_MATRIX_H 1

#include "liste.h"

#define N 3

typedef int fonction_hachage (int);

struct hash_matrix {
    struct liste tab [N];
    fonction_hachage* h;
};

extern void init_hash_matrix (struct hash_matrix*, fonction_hachage*);
extern void ajouter_hash_matrix (struct hash_matrix*, struct coeff);
extern void clear_hash_matrix (struct hash_matrix*);
extern void afficher_hash_matrix (struct hash_matrix*);

#endif
