#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "liste_point.h"

void init_liste_point (struct liste_point* L)
{
    L->tete = NIL;
    L->nbelem = 0;
}

void ajouter_en_tete_liste_point (struct liste_point* L, struct point A)
{
    struct maillon_point* M;
/* 1 */
    M = (struct maillon_point*)malloc (sizeof (struct maillon_point));
    assert (M != NIL);
/* 2 */
    M->value = A;
    M->next = L->tete;
/* 3 */
    L->tete = M;
/* 4 */
    L->nbelem += 1;
}

/*
 * Cette fonction na pas été faite en cours
 */

void extraire_tete_liste_point (struct point* A, struct liste_point* L)
{   struct maillon_point* M;

    assert (L->nbelem >= 1);
    M = L->tete;
    L->tete = M->next;
    L->nbelem -= 1;
    *A = M->value;
    free (M);
}

void premier_element_liste_point (struct point* A, struct liste_point* L)
{   struct maillon_point* M;

    assert (L->nbelem >= 1);
    M = L->tete;
    *A = M->value;
}

void deuxieme_element_liste_point (struct point* A, struct liste_point* L)
{   struct maillon_point* M;

    assert (L->nbelem >= 2);
    M = L->tete->next;
    *A = M->value;
}

void clear_liste_point  (struct liste_point* L)
{   struct maillon_point *M, *N;
    int i;

    M = L->tete;
    for (i = 0; i < L->nbelem; i++)
    {   N = M->next;
/* Manque un appel au destructeur de point */
        free (M);
        M = N;
    }
}


