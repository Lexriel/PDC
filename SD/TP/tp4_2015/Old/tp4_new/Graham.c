#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

struct point {
    double x; /* abscisse */
    double y; /* ordonnée */
    char c;   /* identificateur */
};

/* 
 * On veut trier les sommets par angle polaire croissant.
 * Retourne -1, 0, 1 suivant que A est avant B, aligné avec B ou après B.
 */

int angle_croissant (struct point* A, struct point* B)
{   double d = A->y * B->x - A->x * B->y;
    return d < 0 ? -1 : d > 0 ? 1 : 0;
}

/*
 * Retourne true si le chemin O -> A -> B fait un virage à gauche en A,
 */

bool tourne_a_gauche (struct point* O, struct point* A, struct point* B)
{   double d = (A->y - O->y) * (B->x - O->x) - (A->x - O->x) * (B->y - O->y);
    return d < 0;
}

#define N 10
#define MAX_COORDINATES 100
#define SCENARIO 78738

int main ()
{   struct point T[N];
    struct point* E[N];
    FILE* f;
    int i, e;

    srand48 (SCENARIO);
/* On crée N points. Le point A est en (0,0) */
    T[0].x = 0;
    T[0].y = 0;
    T[0].c = 'A';
    for (i = 1; i < N; i++)
    {   T[i].x = drand48 () * MAX_COORDINATES;
        T[i].y = drand48 () * MAX_COORDINATES;
        T[i].c = 'A' + i;
    }
/* On les enregistre dans "points.dat" */
    f = fopen ("points.dat", "w");
    assert (f != NULL);
    for (i = 0; i < N; i++)
        fprintf (f, "%f %f %c\n", T[i].x, T[i].y, T[i].c);
    fclose (f);
/* On les trie par angle polaire croissant */
    qsort (T+1, N-1, sizeof (struct point), 
           (int (*) (const void*, const void*))&angle_croissant);
    for (i = 0; i < N; i++)
        printf ("%c ", T[i].c);
    printf ("\n");
/* On ne gère pas le cas de deux points alignés */
    for (i = 1; i < N-1; i++)
        assert (angle_croissant (&T[i], &T[i+1]) != 0);
/* On stocke dans E les adresses des sommets de l'enveloppe convexe de T */
    E[0] = &T[0];
    E[1] = &T[1];
    E[2] = &T[2];
    e = 2;
    for (i = 3; i < N; i++)
    {   
/* On peut montrer que e est toujours >= 1 */
        while (! tourne_a_gauche (E[e-1], E[e], &T[i]))
            e -= 1;
        e += 1;
        E[e] = &T[i];
    }
/* On enregistre ces sommets dans "enveloppe.dat" */
    f = fopen ("enveloppe.dat", "w");
    assert (f != NULL);
    fprintf (f, "%f %f\n", E[0]->x, E[0]->y);
    for (i = e; i >= 0; i--)
        fprintf (f, "%f %f\n", E[i]->x, E[i]->y);
    fclose (f);
/* plot [-10:100][-10:100] "points.dat" with labels, "enveloppe.dat" with lines */
    return 0;
}
