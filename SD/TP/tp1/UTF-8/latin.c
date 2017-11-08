#include <stdio.h>

int main ()
{   FILE* f;
    int i;

    f = fopen ("table-latin1", "w");
    for (i = 160; i < 256; i++)
	fprintf (f, "%c", (char)i);
    fclose (f);
}

