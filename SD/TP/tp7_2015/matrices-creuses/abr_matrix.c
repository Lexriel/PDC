#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "abr_matrix.h"

void clear_abr_matrix (struct abr_matrix* A)
{
    if (A != (struct abr_matrix*)0)
    {   clear_abr_matrix (A->gauche);
        clear_abr_matrix (A->droit);
        free (A);
    }
}

static bool est_inferieur (struct coeff a, struct coeff b)
{
    return a.i < b.i || (a.i == b.i && a.j < b.j);
}

/*
 * On suppose que x n'est pas déjà dans A
 */

struct abr_matrix* ajouter_abr_matrix (struct abr_matrix* A, struct coeff c)
{   struct abr_matrix *feuille;
    struct abr_matrix *pred, *succ;

    feuille = (struct abr_matrix*)malloc (sizeof (struct abr_matrix));
    assert (feuille != (struct abr_matrix*)0);
    feuille->valeur = c;
    feuille->gauche = (struct abr_matrix*)0;
    feuille->droit = (struct abr_matrix*)0;

    if (A == (struct abr_matrix*)0)
        return feuille;
    else
    {   pred = (struct abr_matrix*)0;
        succ = A;
        while (succ != (struct abr_matrix*)0)
        {   pred = succ;
            if (est_inferieur (succ->valeur, c))
                succ = succ->droit;
            else
                succ = succ->gauche;
        }
/*
 * Il ne reste plus qu'à mettre feuille à gauche ou à droite de pred
 */
        if (est_inferieur (pred->valeur, c))
            pred->droit = feuille;
        else
            pred->gauche = feuille;
        return A;
    }
}

void afficher_abr_matrix (struct abr_matrix* A)
{
    if (A != (struct abr_matrix*)0)
    {   afficher_abr_matrix (A->gauche);
        printf ("A[%d,%d] = %f\n", A->valeur.i, A->valeur.j, A->valeur.aij);
        afficher_abr_matrix (A->droit);
    }
}
