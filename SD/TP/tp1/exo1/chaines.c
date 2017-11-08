#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define LMIN 8

int main ()
{   char* s;
    int l, i, c;

    s = (char*)malloc (LMIN * sizeof (char));
    assert (s != (char*)0);
    l = LMIN;

    i = 0;
    c = getchar ();
    while (! isspace (c))
    {   if (i >= l)
        {   s = (char*)realloc (s, (l + LMIN) * sizeof (char));
	    l += LMIN;
        }
        s [i] = (char)c;
        i += 1;
        c = getchar ();
    }
    if (i >= l)
    {   s = (char*)realloc (s, (l + LMIN) * sizeof (char));
	l += LMIN;
    }
    s [i] = '\0';
    printf ("%s\n", s);
    free (s);
    return 0;
}

