#if ! defined (ABR_MATRIX_H)
#define ABR_MATRIX_H 1

#include <stdbool.h>
#include "coeff.h"

struct abr_matrix {
    struct coeff valeur;
    struct abr_matrix* gauche;
    struct abr_matrix* droit;
};

extern void clear_abr_matrix (struct abr_matrix*);
extern struct abr_matrix* ajouter_abr_matrix (struct abr_matrix*, struct coeff);
extern void afficher_abr_matrix (struct abr_matrix*);

#endif
