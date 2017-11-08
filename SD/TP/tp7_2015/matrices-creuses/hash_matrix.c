#include "hash_matrix.h"

void init_hash_matrix (struct hash_matrix* H, fonction_hachage* h)
{   int i;
    H->h = h;
    for (i = 0; i < N; i++)
        init_liste (&H->tab [i]);
}

void clear_hash_matrix  (struct hash_matrix* H)
{   int i;
    for (i = 0; i < N; i++)
        clear_liste (&H->tab [i]);
}

void ajouter_hash_matrix (struct hash_matrix* H, struct coeff c)
{   int i;
    i = H->h (c.i);
    insertion_liste (&H->tab [i], c);
}

void afficher_hash_matrix (struct hash_matrix* H)
{   int i;
    for (i = 0; i < N; i++)
        afficher_liste (H->tab [i]);
}


