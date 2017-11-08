#include <stdio.h>
#include <stdlib.h>
#include "chaine.h"

#define LMIN 8

void init_chaine (struct chaine* c)
{
    init_liste_char (&c->L);
}

void clear_chaine (struct chaine* c)
{
    clear_liste_char (&c->L);
}

void concat_chaine_char (struct chaine* c, char a)
{
    ajouter_en_queue_liste_char (&c->L, a);
}

void print_chaine (struct chaine* c)
{
    imprimer_liste_char (&c->L);
}

