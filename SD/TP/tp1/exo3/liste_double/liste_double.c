#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "liste_double.h"

void init_liste_double (struct liste_double* L)
{
    L->tete = (struct maillon_double*)0;
    L->nbelem = 0;
}

void ajouter_en_tete_liste_double (struct liste_double* L, double d)
{   struct maillon_double* nouveau;

    nouveau = (struct maillon_double*)malloc (sizeof (struct maillon_double));
    assert (nouveau != (struct maillon_double*)0);
/* appeler ici un éventuel constructeur pour nouveau->value */
    nouveau->value = d;       /* affectation de la valeur */
    nouveau->next = L->tete;
    L->tete = nouveau;
    L->nbelem += 1;
}

void clear_liste_double (struct liste_double* L)
{   struct maillon_double* courant;
    struct maillon_double* suivant;
    int i;

    courant = L->tete;
    for (i = 0; i < L->nbelem; i++)
    {   suivant = courant->next;
/* appeler ici un éventuel destructeur pour nouveau->value */
        free (courant);
        courant = suivant;
    }
}

static void retourner_liste_double (struct liste_double* L)
{   struct maillon_double *precedent, *courant, *suivant;
    int i;

    if (L->nbelem >= 2)
    {   courant = L->tete;
        suivant = courant->next;
        courant->next = (struct maillon_double*)0;
        for (i = 1; i < L->nbelem; i++)
        {   precedent = courant;
            courant = suivant;
            suivant = suivant->next;
            courant->next = precedent;
        }
        L->tete = courant;
    }
}

void set_liste_double (struct liste_double* dst, struct liste_double* src)
{   struct maillon_double* M;
    int i;

    if (dst != src)
    {   clear_liste_double (dst);
        init_liste_double (dst);
        M = src->tete;
        for (i = 0; i < src->nbelem; i++)
        {   ajouter_en_tete_liste_double (dst, M->value);
            M = M->next;
        }
        retourner_liste_double (dst);
    }
}

void extraire_tete_liste_double (double* d, struct liste_double* L)
{   struct maillon_double* tete;

    assert (L->nbelem != 0);
    tete = L->tete;
    *d = tete->value;      /* affectation */
    L->tete = tete->next;
    L->nbelem -= 1;
    free (tete);
}

void imprimer_liste_double (struct liste_double* L)
{   struct maillon_double* M;
    int i;

    printf ("[");
    M = L->tete;
    for (i = 0; i < L->nbelem; i++)
    {   if (i == 0)
            printf ("%f", M->value);
        else
            printf (", %f", M->value);
        M = M->next;
    }
    printf ("]\n");
}
