#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/*
 * F. Boulier. Octobre 2011, Janvier 2012
 *
 * Le programme suivant teste si un document respecte le format UTF-8.
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

static void append_byte (struct character* c, unsigned char byte)
{
    c->bytes [c->nbbytes] = byte;
    c->nbbytes += 1;
}

static void print_character (struct character* c)
{   int i;

    for (i = 0; i < c->nbbytes; i++)
	printf ("%c", c->bytes [i]);
}

static void dump_character (struct character* c)
{   int i;

    for (i = 0; i < c->nbbytes; i++)
        printf (" %2x", c->bytes [i]);
}

/*
 * Imprime un caractère erroné.
 */

static void erreur (struct character* c, char* mesg, bool verbose)
{
    if (verbose)
    {   printf ("[%s:", mesg);
	dump_character (c);
        printf ("]");
    } else
    {   struct character replacement_char;
/* Le caractère: � */
	replacement_char.bytes [0] = 0xef;
	replacement_char.bytes [1] = 0xbf;
	replacement_char.bytes [2] = 0xbd;
	replacement_char.nbbytes = 3;
	print_character (&replacement_char);
    }
}

/*
 * Décompose l'octet c (censé être le premier octet d'une séquence UTF-8).
 * L'entier *counter reçoit le nombre de bits de contrôle à 1
 * Le long *code reçoit les bits de valeur.
 *
 * Par exemple, si c = 110xxxxx alors *counter = 2 et *code = xxxxx.
 * Si c = 0xxxxxxx (code ASCII) alors *counter = 0 et code = c.
 */

static void process_leading_byte (int* counter, long* code, unsigned char c)
{   int cpt, bits, mask;

    cpt = 0;
    bits = c;
    mask = 0x80;                /* 1000 0000 binaire */
/* 
 * Invariants de boucle : 
 * - mask comporte un seul bit à 1
 * - bits est égal à c, sans les bits à 1, situés plus à gauche que mask
 * - cpt est égal au nombre de bits à 1 de c, situés plus à gauche que mask
 */
    while ((bits & mask) != 0)  /* tq bits comporte un bit à 1 face à mask */
    {   bits ^= mask;           /* effacer ce bit */
        cpt += 1;
        mask >>= 1;             /* décaler d'une position vers la droite
                                   l'unique bit à 1 de mask */
    }
    *counter = cpt;
    *code = (long)bits;
}

/*
 * Ajoute les 6 derniers bits de byte à la fin de code.
 * Retourne la nouvelle valeur de code.
 */

static long append_6bits (long code, unsigned char byte)
{
    return (code << 6) | (long)(byte & 0x3f);
}

static void usage (char* exec)
{
    fprintf (stderr, "usage: %s [-v] file-name\n", exec);
    exit (1);
}

int main (int argc, char** argv)
{   FILE* f;
    long code;
    struct character ch, chcopy;
    int c, counter, i, maxlen, nberr;
    bool verbose, continuation_byte, ok;

    if (argc < 2)
	usage (argv [0]);
    verbose = argc == 3;
    f = fopen (argv [argc-1], "r");
    if (f == NULL)
    {	fprintf (stderr, "could not open file\n");
    	usage (argv [0]);
    }

    maxlen = 0;
    nberr = 0;
    while ((c = fgetc (f)) != EOF)
    {   init_character (&ch);
	append_byte (&ch, (unsigned char)c);
	process_leading_byte (&counter, &code, c);
	if (counter == 0)
	{   if (maxlen < 1)
	    {	maxlen = 1;
		chcopy = ch;
	    }
/* Un code ASCII. C'est un caractère UTF-8 valide */
	    print_character (&ch);
	} else if (counter == 1)
	{   erreur (&ch, "single continuation byte", verbose);
	    nberr += 1;
	} else
	{   continuation_byte = true;
	    ok = true;
/* Lit les continuation bytes */
	    for (i = 1; i < counter && c != EOF && ok; i++)
	    {	c = fgetc (f);
		if (c == EOF)
		{   erreur (&ch, "unexpected end-of-file", verbose);
		    nberr += 1;
		    ok = false;
/* Provoque une sortie de boucle au prochain tour */
		}
		if ((c & 0xc0) != 0x80)
		{   continuation_byte = false;
		    ok = false;
		    ungetc (c, f);
		} else
		{   append_byte (&ch, (unsigned char)c);
		    code = append_6bits (code, (unsigned char)c);
		}
	    }
/* Un caractère codé sur counter octets a été lu */
	    if (! continuation_byte)
	    {	erreur (&ch, "missing continuation byte", verbose);
		nberr += 1;
	    } else if (ch.bytes [0] == 0xc0 || ch.bytes [0] == 0xc1 ||
	    		(ch.bytes [0] == 0xe0 && code < 0x800) ||
			(ch.bytes [0] == 0xf0 && code < 0x10000))
	    {	erreur (&ch, "overlong encoding", verbose);
		nberr += 1;
	    } else if (counter > 4)
	    {	erreur (&ch, "encoding on more than 4 bytes", verbose);
		nberr += 1;
	    } else if (code > 0x10ffff)
	    {   erreur (&ch, "upper limit exceeded", verbose);
		nberr += 1;
	    } else if (code >= 0xd800 && code <= 0xdfff)
	    {   erreur (&ch, "UTF-16 surrogates", verbose);
		nberr += 1;
	    } else if ((code >= 0xfdd0 && code <= 0xfdef) ||
				(code & 0xffff) == 0xfffe ||
				(code & 0xffff) == 0xffff)
	    {	erreur (&ch, "noncharacter", verbose);
		nberr += 1;
	    } else
	    {   if (maxlen < counter)
		{   maxlen = counter;
		    chcopy = ch;
	    	}
/* Un caractère UTF-8 valide mais non ASCII a été lu */
		print_character (&ch);
	    }
	}
    }
    if (verbose)
    {	printf ("longest encoding: %d bytes [", maxlen);
	if (maxlen > 0)
	    print_character (&chcopy);
	printf ("] ");
	dump_character (&chcopy);
	printf ("\n");
	printf ("number of errors: %d\n", nberr);
    }
    fclose (f);
    return nberr == 0 ? 0 : 1;
}

