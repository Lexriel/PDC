#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/*
 * F. Boulier. Octobre 2011
 *
 * Le programme suivant imprime un caractère UTF-8 à partir de sa valeur
 * http://en.wikipedia.org/wiki/UTF-8
 * http://en.wikipedia.org/wiki/Unicode [surrogates, noncharacters]
 * 
 * Un caractère UTF-8 est codé sur 1 à 4 octets.
 * Il a une valeur entre 0x00 et 0x10ffff.
 * 
 * Un caractère codé sur 1 octet est un code ASCII entre 0x00-0x7f
 * 
 * Si un caractère est codé sur 2, 3 ou 4 octets, alors chaque
 * octet est composé d'une suite de bits de contrôle, puis de
 * bits destinés à former la valeur du caractère.
 * 
 * Soit un caractère codé par n octets (2 <= n <= 4).
 * Le premier octet commence par n bits à 1, suivi d'un 0, suivi de 7-n bits
 * de valeur. Les autres octets commencent par 10, suivi de 6 bits de valeur.
 * La valeur du caractère s'obtient en concaténant les bits de valeur.
 * 
 * 2 octets. Codage: 110xxxxx 10yyyyyy. Valeur: xxx xxyyyyyy
 * 3 octets. Codage: 1110xxxx 10yyyyyy 10zzzzzz. Valeur: xxxxyyyy yyzzzzzz
 * 4 octets. Codage: 11110xxx 10yyyyyy 10zzzzzz 10wwwwww.
 *           Valeur: xxxyy yyyyzzzz zzwwwwww
 * 
 * Certains codages sont interdits:
 * 
 * Le codage d'une valeur doit se faire sur un nombre minimal d'octets
 * - Les premiers octets 0xc0 et 0xc1 sont interdits (ils donneraient lieu
 *   à un code ASCII sur deux octets)
 * - Si le premier octet est 0xe0, la valeur finale doit être >= 0x800
 * - Si le premier octet est 0xf0, la valeur finale doit être >= 0x10000
 * La valeur ne doit pas dépasser 0x10ffff.
 * Les valeurs comprises entre 0xd800 et 0xdfff sont réservées pour coder
 *   de l'UTF-16. Elles ne correspondent à aucun caractère UTF-8. On les
 *   appelle « UTF-16 surrogates ».
 * Il existe 66 valeurs pour des non-caractères : 0xfdd0-0xfdef et les 34
 *   valeurs terminant par 0xfffe et 0xffff (de 0xfffe, 0xffff à 0x10fffe, 
 *   0x10fff). http://en.wikipedia.org/wiki/Unicode [noncharacters]
 *
 * Remarque : le caractère € est le seul caractère naturel pour des
 * Français, qui soit codé sur trois octets.
 */

#define NBMAX_BYTES 8
struct character
{   unsigned char bytes [NBMAX_BYTES];
    int nbbytes;
};

static void init_character (struct character* c)
{
    c->nbbytes = 0;
}

static void print_character (struct character* c)
{   int i;

    for (i = 0; i < c->nbbytes; i++)
	printf ("%c", c->bytes [i]);
}

static void set_character_value (struct character* c, unsigned int val)
{   unsigned int v;
    int i, m, n;

    if ((val & 0x7f) == val)
    {	c->nbbytes = 1;
	c->bytes [0] = val;
    } else
    {   n = 1;
        v = val;
        while (v > 0x1f)
        {   n += 1;
	    v >>= 6;
        }
	c->nbbytes = n;
	m = 0;
	for (i = 0; i < n; i++)
	    m = (m >> 1) | 0x80;
	c->bytes [0] = m | v;
        v = val;
	for (i = n-1; i >= 1; i--)
	{   c->bytes [i] = (v & 0x3f) | 0x80;
	    v >>= 6;
	}
    }
}

static void usage (char* exec)
{
    fprintf (stderr, "usage: %s code-hexa\n", exec);
    exit (1);
}

int main (int argc, char** argv)
{
    struct character ch;
    int val;

    if (argc != 2)
	usage (argv [0]);

    init_character (&ch);
    if (sscanf (argv [1], "%x", &val) != 1)
	usage (argv [0]);

    set_character_value (&ch, val);
    print_character (&ch);
    printf ("\n");

    return 0;
}

