#include "chaine.h"
#include <stdio.h>
#include <ctype.h>

int main ()
{   char s [64];
    struct chaine k;
    int c, i;

    c = getchar ();
    i = 0;
    while (! isspace (c))
    {   s [i] = c;
        c = getchar ();
	i += 1;
    }
    s [i] = '\0';

    init_chaine (&k);
    set_chaine_string (&k, s, format_Latin_1);
    imprimer_chaine (&k, format_UTF_8);
    putchar ('\n');
    clear_chaine (&k);
    return 0;
}
