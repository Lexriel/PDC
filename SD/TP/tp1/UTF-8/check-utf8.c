#include <stdio.h>
#include <stdlib.h>

static void erreur (char* mesg)
{
    fprintf (stderr, "error: %s\n", mesg);
    exit (1);
}

static void process_leading_octet (int* counter, long* code, int c)
{   int cpt, bits, mask;

    cpt = 0;
    bits = c & 0xff;
    mask = 0x80;
    while ((bits & mask) != 0 && bits != 0)
    {	bits ^= mask;
	cpt += 1;
	mask >>= 1;
    }

    *counter = cpt;
    *code = (int)bits;
}

static long append_6bits (long code, int bits)
{
    return (code << 6) | (long)(bits & 0x3f);
}

int main (int argc, char** argv)
{   FILE* f;
    long code;
    int c, counter, i;

    if (argc != 2)
	erreur ("wrong number of arguments");
    f = fopen (argv [1], "r");
    if (f == NULL)
	erreur ("could not open file");
    while ((c = fgetc (f)) != EOF)
    {
	process_leading_octet (&counter, &code, c);
	if (counter == 0)
	{   if (c < 0x20 || c == 0x7f)
		printf ("ascii control character: %lx\n", code);
	    else if (c >= '0' && c <= '9')
		printf ("ascii digit: %c\n", (char)code);
	    else if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		printf ("ascii letter: %c\n", (char)code);
	    else
		printf ("ascii punctuation: %c\n", (char)code);
	} else if (counter == 1 || counter > 4)
	    erreur ("wrong leading octet");
	else if (code <= 1)
	    erreur ("overlong encoding");
	else
	{   for (i = 1; i < counter; i++)
	    {	c = fgetc (f);
		if (c == EOF)
		    erreur ("unexpected end-of-file");
		if ((c & 0xc0) != 0x80)
		    erreur ("wrong trailing octet");
		code = append_6bits (code, c);
	    }
	    if (code > 0x10ffff)
		erreur ("Unicode upper limit reached");
	    printf ("%d octets UTF-8 character: %lx\n", counter, code);
	}
    }
    fclose (f);
    return 0;
}

