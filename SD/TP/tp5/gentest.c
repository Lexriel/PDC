#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void usage (char* s)
{
    fprintf (stderr, "usage: %s trie | equilibre | aleatoire\n", s);
    exit (1);
}

#define N 32

#define RECURSIF
#undef RECURSIF
#if defined (RECURSIF)
static void equilibre (int n, int w)
{
    printf ("%d\n", n);
    if (w > 1)
    {   equilibre (n - w/2, w/2);
        equilibre (n + w/2, w/2);
    }
}
#else
static void equilibre (int n)
{   int w, b, i, k;
    b = n;
    w = 1;
    for (k = n; k >= 1; k /= 2)
    {   for (i = 0; i < w; i++)
            printf ("%d\n", b + i*(2*b));
        b /= 2;
        w *= 2;
    }
}
#endif

static void aleatoire (int n)
{   int i, p;
    int T [n];
    for (i = 0; i < n; i++)
        T [i] = i;
    p = n;
    while (p > 1)
    {   i = drand48 () * p;
        printf ("%d\n", T [i]);
        T [i] = T [p];
        p -= 1;
    }
}

int main (int argc, char** argv)
{
    if (argc != 2)
        usage (argv [0]);
    if (strcmp (argv [1], "trie") == 0)
    {   int i;
        for (i = 1; i < N; i++)
            printf ("%d\n", i);
    } else if (strcmp (argv [1], "equilibre") == 0)
#if defined (RECURSIF)
        equilibre (N / 2, N / 2);
#else
        equilibre (N / 2);
#endif
    else if (strcmp (argv [1], "aleatoire") == 0)
        aleatoire (N);
    else
        usage (argv [0]);
    printf ("-1\n");
}

