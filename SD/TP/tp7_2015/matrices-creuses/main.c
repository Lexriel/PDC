#include <stdio.h>
#include "abr_matrix.h"
#include "hash_matrix.h"
#include "Yale_matrix.h"

static int h (int cle)
{
    return cle % N;
}

int main ()
{   struct abr_matrix* A;
    struct hash_matrix H;
    struct Yale_matrix Y, Z;
    struct coeff c;
    int i, m, n, p;

    A = (struct abr_matrix*)0;
    init_hash_matrix (&H, &h);
    scanf ("%d%d%d", &m, &n, &p);
    for (i = 0; i < p; i++)
    {   scanf ("%d%d%lf", &c.i, &c.j, &c.aij);
        A = ajouter_abr_matrix (A, c);
        ajouter_hash_matrix (&H, c);
    }
    printf ("abr_matrix:\n");
    afficher_abr_matrix (A);
    printf ("hash_matrix:\n");
    afficher_hash_matrix (&H);

    init_Yale_abr_matrix (&Y, m, n, p, A);
    init_Yale_hash_matrix (&Z, m, n, p, &H);
    printf ("Yale_matrix initialisee avec une abr_matrix\n");
    afficher_Yale_matrix (&Y);
    printf ("Yale_matrix initialisee avec une hash_matrix\n");
    afficher_Yale_matrix (&Z);

    clear_abr_matrix (A);
    clear_hash_matrix (&H);
    clear_Yale_matrix (&Y);
    clear_Yale_matrix (&Z);
    return 0;
}
