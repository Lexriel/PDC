#include <stdio.h>
#include <stdlib.h>
#include "liste_caractere.h"

void init_liste_caractere (struct liste_caractere* L)
{
    L->tete = (struct maillon_caractere*)0;
    L->nbelem = 0;
}

void clear_liste_caractere (struct liste_caractere* L)
{   struct maillon_caractere* courant;
    struct maillon_caractere* suivant;
    int i;

    courant = L->tete;
    for (i = 0; i < L->nbelem; i++)
    {   suivant = courant->next; /* on consulte courant->next avant */
	clear_caractere (&courant->value);
        free (courant);          /* d'exécuter l'instruction free ! */
        courant = suivant;
    }
}

/*
 * Cette fonction est locale au module liste_caractere.
 * Avant : L = [a1, a2, ..., an]. Après : L = [an, ..., a2, a1]
 */

static void retourner_liste_caractere (struct liste_caractere* L)
{   struct maillon_caractere *precedent, *courant, *suivant;
    int i;

    if (L->nbelem >= 2)
    {   courant = L->tete;
        suivant = courant->next;
        courant->next = (struct maillon_caractere*)0;
        for (i = 1; i < L->nbelem; i++)
        {   precedent = courant;
            courant = suivant;
            suivant = suivant->next;
            courant->next = precedent;
        }
        L->tete = courant;
    }
}

void set_liste_caractere 
		(struct liste_caractere* dst, struct liste_caractere* src)
{   struct maillon_caractere* M;
    int i;

    if (dst != src)
    {   clear_liste_caractere (dst);
        init_liste_caractere (dst);
        M = src->tete;
        for (i = 0; i < src->nbelem; i++)
        {   ajouter_en_tete_liste_caractere (dst, &M->value);
            M = M->next;
        }
        retourner_liste_caractere (dst);
    }
}

void ajouter_en_tete_liste_caractere 
		(struct liste_caractere* L, struct caractere* d)
{   struct maillon_caractere* nouveau;

    nouveau = (struct maillon_caractere*)malloc 
				(sizeof (struct maillon_caractere));
    set_caractere (&nouveau->value, d);
    nouveau->next = L->tete;

    L->tete = nouveau;
    L->nbelem += 1;
}

void ajouter_en_queue_liste_caractere 
		(struct liste_caractere* L, struct caractere* d)
{   struct maillon_caractere* nouveau;
    struct maillon_caractere* prec;
    struct maillon_caractere* cour;

    nouveau = (struct maillon_caractere*)malloc 
				(sizeof (struct maillon_caractere));
    set_caractere (&nouveau->value, d);
    nouveau->next = (struct maillon_caractere*)0;

    if (L->tete == (struct maillon_caractere*)0)
        L->tete = nouveau;
    else
    {   prec = L->tete;
        cour = prec->next;
        while (cour != (struct maillon_caractere*)0)
        {   prec = cour;
            cour = cour->next;
        }
        prec->next = nouveau;
    }
    L->nbelem += 1;
}

