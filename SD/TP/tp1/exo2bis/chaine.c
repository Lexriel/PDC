#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "chaine.h"

#define LMIN 8

void init_chaine (struct chaine* c)
{
    c->data = (char*)0;
    c->alloc = 0;
    c->size = 0;
}

void clear_chaine (struct chaine* c)
{
    free (c->data); /* correct même si data = 0 */
}

void concat_chaine_char (struct chaine* c, char a)
{
    if (c->size + 1 >= c->alloc)
    {   c->data = realloc (c->data, (c->size + LMIN) * sizeof (char));
        assert (c->data != (char*)0);
        c->alloc = c->size + LMIN;
    }
    c->data [c->size] = a;
    c->size += 1;
    c->data [c->size] = '\0';
}

void print_chaine (struct chaine* c)
{
    if (c->size == 0)
	printf ("\n"); /* attention à data = 0 */
    else
	printf ("%s\n", c->data);
}

