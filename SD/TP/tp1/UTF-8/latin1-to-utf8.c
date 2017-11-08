#include <stdlib.h>
#include <stdio.h>

/*
 * Le programme suivant convertit du Latin-1 en UTF-8.
 * Le codage iso 8859-1 (Latin-1) est composé des caractères :
 * 0x00 - 0x7f : les codes ASCII
 * 0xa0 - 0xff : des codes non-ASCII
 * 
 * L'équivalent UTF-8 s'obtient facilement ainsi:
 * les codes ASCII sont inchangés
 * les codes non ASCII xxxxxxxx -> 110000xx 10xxxxxx
 */

static void erreur (char* mesg)
{
    fprintf (stderr, "error: %s\n", mesg);
    exit (1);
}

int main (int argc, char** argv)
{   FILE* f;
    int c;

    if (argc != 2)
        erreur ("wrong number of arguments");
    f = fopen (argv [1], "r");
    if (f == NULL)
        erreur ("could not open file");
    while ((c = fgetc (f)) != EOF)
    {   if (c >= 0x80 && c < 0xa0)
	    erreur ("not latin-1");
	else if (c < 0x80)
	    printf ("%c", (char)c);
	else
	    printf ("%c%c", (char)(0xc0 | (c >> 6)), (char)(0x80 | (c & 0x3f)));
    }
    fclose (f);
    return 0;
}

