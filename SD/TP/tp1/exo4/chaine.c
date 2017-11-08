#include <stdio.h>
#include <stdlib.h>
#include "chaine.h"

void init_chaine (struct chaine* c)
{
    init_liste_caractere (&c->L);
}

void clear_chaine (struct chaine* c)
{
    clear_liste_caractere (&c->L);
}

/*
 * Affecte à *c la chaîne de caractères s, qui est au format f
 */

void set_chaine_string (struct chaine* c, char* s, enum type_format f)
{   struct caractere k;
    int i, n;

    clear_chaine (c);
    init_chaine (c);
    i = 0;
    while (s [i] != '\0')
    {   init_caractere (&k);
	set_caractere_string (&k, &n, s+i, f);
	ajouter_en_queue_liste_caractere (&c->L, &k);
	i += n;
    }
}

void imprimer_chaine (struct chaine* c, enum type_format f)
{   struct maillon_caractere* M;

    for (M = c->L.tete; M != (struct maillon_caractere*)0; M = M->next)
        imprimer_caractere (&M->value, f);
}

int nb_octets_chaine (struct chaine* c)
{   struct maillon_caractere* M;
    int n;

    n = 0;
    for (M = c->L.tete; M != (struct maillon_caractere*)0; M = M->next)
        n += nb_octets_caractere (&M->value);
    return n;
}

int nb_caracteres_chaine (struct chaine* c)
{
    return c->L.nbelem;
}

