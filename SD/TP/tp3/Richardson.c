#include <stdio.h>
#include <math.h>

/*
 * Pour les besoins du TP, toutes les fonctions sont tournées comme 
 * des actions, bien que ce ne soit pas très naturel.
 */

typedef void fonction_derivable (double*, double);

/*
 * Affecte P(x) à *result. Evaluation par la méthode de Horner. 
 *                                      2    3        5        6
 *                  P := 3.5 + 2.7 x - x  + x  + 7.4 x  + 1.1 x
 */

void polynome (double* result, double x)
{/*
    double coeffs [] = { 3.5, 2.7, -1.0, 1.0, 0.0, 7.4, 1.1 };
  */
    double coeffs [] = { 0.0, 0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,1.0} ;
    int deg = sizeof (coeffs) / sizeof (double) - 1;
    int i;

    *result = coeffs [deg];
    for (i = deg - 1; i >= 0; i--)
	*result = *result * x + coeffs [i];
}

/*
 * Affecte l'intégrale de P(x) entre 0 et 1 à *result.
 * Méthode des trapèzes.
 */

void trapezes (double* result, double h)
{   double a, b, r;
    int i, n;

    a = 0.0;
    b = 1.0;
    n = (int)round ((b - a) / h);
    polynome (result, a);
    polynome (&r, b);
    *result += r;
    *result *= 0.5;
    for (i = 1; i < n; i++)
    {   polynome (&r, a + i*h);
	*result += r;
    }
    *result *= h;
}

/*
 * Affecte arc cosinus (x) à *result
 */

void arc_cosinus (double* result, double x)
{
    *result = acos (x);
}

/*
 * Applique la méthode de Richardson sur la fonction v passée en paramètre
 * Résultat dans *result
 */

void Richardson (double* result, fonction_derivable* v, 
					double h0, double r, int n)
{   double A[n][n];  /* matrice intermédiaire */
    double powr[n];  /* tableau de puissances de r */
    double h;
    int p, m;

    powr[0] = 1.0;
    v (&A[0][0], h0);
    for (p = 1; p < n; p++)
    {   powr[p] = powr[p-1] * r;
        h = powr[p] * h0;
        v (&A[p][0], h);
        for (m = 1; m <= p; m++)
            A[p][m] = (A[p][m-1] - powr[m]*A[p-1][m-1])/(1.0 - powr[m]);
    }
    *result = A[n-1][n-1];
}

#define N 8

int main ()
{   double r;
    int n;
/*
 * Premier exemple
 */
    for (n = 1; n < N; n++)
    {   Richardson (&r, &arc_cosinus, 1.0, 0.5, n);
	printf ("n = %d, acos (0) = %f\n", n, r);
    }
    printf ("\n");
/*
 * Deuxième exemple
 */
    for (n = 1; n < N; n++)
    {   Richardson (&r, &polynome, 1.0, 0.5, n);
	printf ("n = %d, P(0) = %f\n", n, r);
    }
    printf ("\n");
/*
 * Troisième exemple
 * Le troisième paramètre h0 doit valoir 1.
 */
    for (n = 1; n < N; n++)
    {   Richardson (&r, &trapezes, 1.0, 0.5, n);
	printf ("n = %d, int (P(x), x = 0..1) = %f\n", n, r);
    }
}

