#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "liste_char.h"

void init_liste_char (struct liste_char* L)
{
    L->tete = (struct maillon_char*)0;
    L->nbelem = 0;
}

void ajouter_en_tete_liste_char (struct liste_char* L, char d)
{   struct maillon_char* nouveau;

    nouveau = (struct maillon_char*)malloc (sizeof (struct maillon_char));
    assert (nouveau != (struct maillon_char*)0);
/* appeler ici un éventuel constructeur pour nouveau->value */
    nouveau->value = d;       /* affectation de la valeur */
    nouveau->next = L->tete;
    L->tete = nouveau;
    L->nbelem += 1;
}

void clear_liste_char (struct liste_char* L)
{   struct maillon_char* courant;
    struct maillon_char* suivant;
    int i;

    courant = L->tete;
    for (i = 0; i < L->nbelem; i++)
    {   suivant = courant->next;
/* appeler ici un éventuel destructeur pour nouveau->value */
        free (courant);
        courant = suivant;
    }
}

static void retourner_liste_char (struct liste_char* L)
{   struct maillon_char *precedent, *courant, *suivant;
    int i;

    if (L->nbelem >= 2)
    {   courant = L->tete;
        suivant = courant->next;
        courant->next = (struct maillon_char*)0;
        for (i = 1; i < L->nbelem; i++)
        {   precedent = courant;
            courant = suivant;
            suivant = suivant->next;
            courant->next = precedent;
        }
        L->tete = courant;
    }
}

void set_liste_char (struct liste_char* dst, struct liste_char* src)
{   struct maillon_char* M;
    int i;

    if (dst != src)
    {   clear_liste_char (dst);
        init_liste_char (dst);
        M = src->tete;
        for (i = 0; i < src->nbelem; i++)
        {   ajouter_en_tete_liste_char (dst, M->value);
            M = M->next;
        }
        retourner_liste_char (dst);
    }
}

void extraire_tete_liste_char (char* d, struct liste_char* L)
{   struct maillon_char* tete;

    assert (L->nbelem != 0);
    tete = L->tete;
    *d = tete->value;      /* affectation */
    L->tete = tete->next;
    L->nbelem -= 1;
    free (tete);
}

void imprimer_liste_char (struct liste_char* L)
{   struct maillon_char* M;
    int i;

    printf ("[");
    M = L->tete;
    for (i = 0; i < L->nbelem; i++)
    {   if (i == 0)
            printf ("%c", M->value);
        else
            printf (", %c", M->value);
        M = M->next;
    }
    printf ("]\n");
}
