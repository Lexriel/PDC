#include <stdio.h>
#include <stdlib.h>
#include "abr_matrix.h"
#include "Yale_matrix.h"

static void fill_Yale_abr_matrix 
                (struct Yale_matrix* Y, int* i, struct abr_matrix* A)
{
    if (A != (struct abr_matrix*)0)
    {   fill_Yale_abr_matrix (Y, i, A->gauche);
        Y->V [*i] = A->valeur.aij;
        Y->I [A->valeur.i + 1] += 1;
        Y->J [*i] = A->valeur.j;
        *i += 1;
        fill_Yale_abr_matrix (Y, i, A->droit);
    }
}

void init_Yale_abr_matrix
        (struct Yale_matrix* Y, int m, int n, int p, struct abr_matrix* A)
{   int i;
    Y->m = m;
    Y->n = n;
    Y->p = p;
    Y->V = (double*)malloc (p * sizeof(double));
    Y->I = (int*)malloc ((m + 1) * sizeof(int));
    Y->J = (int*)malloc (p * sizeof(int));
    for (i = 0; i <= m; i++)
        Y->I [i] = 0;
    i = 0;
    fill_Yale_abr_matrix (Y, &i, A);
    for (i = 2; i <= m; i++)
        Y->I [i] += Y->I [i-1];
}

void init_Yale_hash_matrix
        (struct Yale_matrix* Y, int m, int n, int p, struct hash_matrix* H)
{   int i, k, y;
    struct maillon* M;

    Y->m = m;
    Y->n = n;
    Y->p = p;
    Y->V = (double*)malloc (p * sizeof(double));
    Y->I = (int*)malloc ((m + 1) * sizeof(int));
    Y->J = (int*)malloc (p * sizeof(int));
    for (i = 0; i <= m; i++)
        Y->I [i] = 0;
    y = 0;
    for (i = 0; i < m; i++)
    {   k = H->h (i);
        M = H->tab [k].tete;
        while (M != NIL)
        {   if (M->c.i == i)
            {   Y->V [y] = M->c.aij;
                Y->I [i+1] += 1;
                Y->J [y] = M->c.j;
                y += 1;
            }
            M = M->next;
        }
    }
    for (i = 2; i <= m; i++)
       Y->I [i] += Y->I [i-1];
}
 
void afficher_Yale_matrix (struct Yale_matrix* Y)
{   int i;

    printf ("V = [");
    for (i = 0; i < Y->p-1; i++)
        printf ("%f, ", Y->V [i]);
    printf ("%f]\n", Y->V [Y->p-1]);
    printf ("I = [");
    for (i = 0; i < Y->m; i++)
        printf ("%d, ", Y->I [i]);
    printf ("%d]\n", Y->I [Y->m]);
    printf ("J = [");
    for (i = 0; i < Y->p-1; i++)
        printf ("%d, ", Y->J [i]);
    printf ("%d]\n", Y->J [Y->p-1]);
}

void clear_Yale_matrix (struct Yale_matrix* Y)
{
    free (Y->V);
    free (Y->I);
    free (Y->J);
}

