#if ! defined (YALE_MATRIX_H)
#define YALE_MATRIX_H 1

#include "abr_matrix.h"
#include "hash_matrix.h"

/*
 * p = le nombre d'éléments non nuls
 * V et J sont de dimension p
 * I est de dimension m+1
 */

struct Yale_matrix {
    int m;
    int n;
    int p;
    double* V;
    int* I;
    int* J;
};

extern void init_Yale_abr_matrix 
                (struct Yale_matrix*, int, int, int, struct abr_matrix*);
extern void init_Yale_hash_matrix 
                (struct Yale_matrix*, int, int, int, struct hash_matrix*);
extern void clear_Yale_matrix (struct Yale_matrix*);
extern void afficher_Yale_matrix (struct Yale_matrix*);

#endif
