#include "chaine.h"
#include <stdio.h>
#include <ctype.h>

int main ()
{   struct chaine s;
    int c;

    init_chaine (&s);
    c = getchar ();
    while (! isspace (c))
    {   ajout_en_queue (&s, (char)c);
	c = getchar ();
    }
    print_chaine (&s);
    clear_chaine (&s);
    return 0;
}
