#include <stdio.h>

int main ()
{   FILE* f;
    int n;
    char type, ident [32];

    f = fopen ("main.sym", "r");
    n = fscanf (f, "%c %s\n", &type, ident);
    while (n == 2)
    {   printf ("type = %c, ident = %s\n", type, ident);
        n = fscanf (f, "%c %s\n", &type, ident);
    }
    fclose (f);
}

