#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include "liste.h"

void init_liste (struct liste* L)
{
    L->tete = NIL;
    L->nbelem = 0;
}

static bool est_inferieur (struct coeff a, struct coeff b)
{
    return a.j < b.j || (a.j == b.j && a.i < b.i);
}

void insertion_liste (struct liste* L, struct coeff c)
{   struct maillon *M, *P;

    M = (struct maillon*)malloc (sizeof (struct maillon));
    M->c = c;

    if (L->tete == NIL || est_inferieur (c, L->tete->c))
    {   M->next = L->tete;
        L->tete = M;
    } else
    {   P = L->tete;
        while (P->next != NIL && est_inferieur (P->next->c, c))
            P = P->next;
        M->next = P->next;
        P->next = M;
    }
    L->nbelem += 1;
}

void afficher_liste (struct liste L)
{   struct maillon* M;

    printf ("[");
    M = L.tete;
    while (M != NIL)
    {   printf ("A[%d,%d] = %f", M->c.i, M->c.j, M->c.aij);
        M = M->next;
        if (M != NIL)
            printf (", ");
    }
    printf ("]\n");
}

void clear_liste  (struct liste* L)
{   struct maillon *M, *N;
    int i;

    M = L->tete;
    for (i = 0; i < L->nbelem; i++)
    {   N = M->next;
        free (M);
        M = N;
    }
}


