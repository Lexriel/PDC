#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <assert.h>

/*
 * Représentation élémentaire d'un polynôme. 
 * On pourrait, au minimum, rajouter le degré !
 */

struct poly
{   double* T;  /* le tableau des coefficients */
    bool free;  /* free = true signifie que T a été alloué par malloc */
    int n;      /* la taille du tableau */
};

void init_poly (struct poly* A, int n)
{
    A->T = (double*)malloc (n * sizeof (double));
    assert (A->T != (double*)0);
    A->n = n;
    A->free = true;
}

void init2_poly (struct poly* A, double* T, int n)
{
    A->T = T;
    A->n = n;
    A->free = false;
}

void clear_poly (struct poly* A)
{
    if (A->free)
	free (A->T);
}

/*
 * L'impression d'un polynôme est plus subtile qu'on ne le croit :-)
 * On suppose que les doubles sont en fait des entiers
 */

void print_poly (struct poly* A)
{   long c;
    int i;
    bool b;

    b = false;
    for (i = A->n - 1; i >= 0; i--)
    {   if (A->T[i] != 0.0)
	{   if (A->T[i] > 0) 
	    {   if (b) printf (" + "); 
	    } else 
	    {   if (b) printf (" - "); else printf ("-");
	    }
	    b = true;
	    if (A->T[i] > 0) c = (long)A->T[i]; else c = (long) - A->T[i];
	    if (i == 0)
	        printf ("%ld", c);
	    else if (i == 1)
	    {   if (c != 1) printf ("%ld*x", c); else printf ("x");
	    } else
	    {   if (c != 1) printf ("%ld*x^%d", c, i); else printf ("x^%d", i);
	    }
	}
    }
    printf ("\n");
}

/*
 * R = A + B
 */

int add_poly (struct poly* R, struct poly* A, struct poly* B)
{   int i; int c = 0;
    i = 0;
    while (i < A->n && i < B->n)
    {   R->T[i] = A->T[i] + B->T[i];
	i += 1;
        c += 1;
    }
    while (i < A->n)
    {	R->T[i] = A->T[i];
	i += 1;
    }
    while (i < B->n)
    {   R->T[i] = B->T[i];
	i += 1;
    }
    while (i < R->n)
    {   R->T[i] = 0.0;
        i += 1;
    }
    return c;
}

/*
 * R = A - B
 */

int sub_poly (struct poly* R, struct poly* A, struct poly* B)
{   int i, c = 0;
    i = 0;
    while (i < A->n && i < B->n)
    {   R->T[i] = A->T[i] - B->T[i];
	i += 1;
        c += 1;
    }
    while (i < A->n)
    {	R->T[i] = A->T[i];
	i += 1;
    }
    while (i < B->n)
    {   R->T[i] = - B->T[i];
	i += 1;
        c += 1;
    }
    while (i < R->n)
    {   R->T[i] = 0.0;
        i += 1;
    }
    return c;
}

/*
 * R = A * B par la méthode élémentaire
 */

int mul_poly (struct poly* R, struct poly* A, struct poly* B)
{   int a, b, c = 0;
    for (a = 0; a < R->n; a++)
        R->T[a] = 0.0;
    for (a = 0; a < A->n; a++)
        for (b = 0; b < B->n; b++)
        {   R->T[a+b] = R->T[a+b] + A->T[a] * B->T[b];
            c += 2;
        }
    return c;
}

/*
 * R = A * B par la méthode de Karatsuba
 */

int Karatsuba (struct poly* R, struct poly* A, struct poly* B)
{   struct poly R0, R1, R2, A0, A1, B0, B1, tmpA, tmpB;
    int i, p, q, c = 0;
/*
 * L'algorithme élémentaire est utilisé pour les cas de base
 */
    if (A->n == 1 || B->n == 1)
	c += mul_poly (R, A, B);
    else
    {
	if (A->n < B->n)
	    p = A->n/2;
	else
	    p = B->n/2;
/*
 * Découper les polynômes A et B en deux se fait en temps constant 
 */
	init2_poly (&A0, A->T, p);
	init2_poly (&A1, A->T + p, A->n - p);
	init2_poly (&B0, B->T, p);
	init2_poly (&B1, B->T + p, B->n - p);
/*
 * Les polynômes R0 et R2 sont des sous-tableaux de R.
 * On évite ainsi deux recopies de tableaux.
 */
	init2_poly (&R0, R->T, 2*p-1);
	init2_poly (&R2, R->T + 2*p, A->n + B->n - 1 - 2*p);
        c += Karatsuba (&R0, &A0, &B0);
        c += Karatsuba (&R2, &A1, &B1);
/*
 * À ce stade, R = R0 + x^(2*p)*R2. On calcule maintenant R1.
 */
	if (A0.n > A1.n) q = A0.n; else q = A1.n;
	init_poly (&tmpA, q);
	c += add_poly (&tmpA, &A0, &A1);
	if (B0.n > B1.n) q = B0.n; else q = B1.n;
	init_poly (&tmpB, q);
	c += add_poly (&tmpB, &B0, &B1);
	q = tmpA.n + tmpB.n - 1;
	if (q < R0.n) q = R0.n;
	if (q < R2.n) q = R2.n;
	init_poly (&R1, q);
        c += Karatsuba (&R1, &tmpA, &tmpB);
        c += sub_poly (&R1, &R1, &R0);
        c += sub_poly (&R1, &R1, &R2);
/*
 * R = R + x^p*R1
 */
        R->T[2*p-1] = 0;
        for (i = 0; i < R1.n; i++)
        {   R->T[p+i] = R->T[p+i] + R1.T[i];
            c += 1;
        }

	clear_poly (&A0);
	clear_poly (&A1);
	clear_poly (&B0);
	clear_poly (&B1);
	clear_poly (&R0);
	clear_poly (&R1);
	clear_poly (&R2);
	clear_poly (&tmpA);
	clear_poly (&tmpB);
    }
    return c;
}

int main ()
{   struct poly A, B, R;
    int i, n, N, c;

    srand48 ((long)421);

    N = 2050;              /* taille des polynômes */
    init_poly (&A, N);
    init_poly (&B, N);
    init_poly (&R, 2*N-1);
    for (i = 0; i < N; i++)
    {	A.T [i] = floor (10.0 * drand48 () - 5.0);
	B.T [i] = floor (10.0 * drand48 () - 5.0);
    }
    for (n = 1; n < N/2; n++)
    {	A.n = n;
	B.n = n;
        c = mul_poly (&R, &A, &B);
        printf ("%d %d\n", n, c);
/*        print_poly (&R);      */
	c = Karatsuba (&R, &A, &B);
/*	print_poly (&R);        */
    }
/*
    printf ("\n\nMultiplication de polynômes aléatoires de taille croissante\n");
    printf ("par la méthode élémentaire, puis par celle de Karatsuba.\n");
    printf ("Si le programme est correct, on doit voir des polynômes de\n");
    printf ("taille de plus en plus grande, affichés deux fois chacun.\n\n");
    printf ("Lors du TP, vous pouvez supprimer ces affichages.\n\n");
 */
}
