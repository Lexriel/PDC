#include <stdio.h>
#include <stdlib.h>

/*
 * Le programme suivant convertit de l'UTF-8 en Latin-1.
 * En fait, il fait plus que cela, puisqu'il teste si le fichier
 * en entrée est bien de l'UTF-8, puis teste que les codages correspondent
 * au Latin-1. On aurait pu réaliser un programme plus direct.
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
 * Dans le cas d'un codage sur 2 octets, la valeur formée par les bits x 
 *   doit être supérieure ou égale à 2 (sinon, on obtiendrait un code ASCII 
 *   codé sur 2 octets). Dit autrement, les octets 0xc0 et 0xc1 sont interdits.
 * La valeur ne doit pas dépasser 0x10ffff.
 * 
 * La conversion UTF-8 -> Latin-1 est facile.
 * Les codes ASCII sont inchangés.
 * Les codages UTF-8 de valeur comprise entre 0xa0 et 0xff correspondent
 * aux codages Latin-1 compris entre 0xa0 et 0xff.
 */

static void erreur (char* mesg)
{
    fprintf (stderr, "error: %s\n", mesg);
    exit (1);
}

/*
 * Décompose l'octet c (censé être le premier octet d'une séquence UTF-8).
 * L'entier *counter reçoit le nombre d'octets de la séquence.
 * Le long *code reçoit les bits de valeur.
 *
 * Par exemple, si c = 110xxxxx alors *counter = 2 et *code = xxxxx.
 */

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

/*
 * Ajoute les 6 derniers bits de « bits » à la fin de code.
 * Retourne la nouvelle valeur de code.
 */

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
/*
 * ASCII
 */
	    printf ("%c", (char)code);
	else if (counter == 1 || counter > 4)
	    erreur ("wrong leading octet");
	else if (counter == 2 && code <= 1)
/*
 * Code ASCII codé sur 2 octets
 */
	    erreur ("overlong ASCII encoding");
	else
	{   for (i = 1; i < counter; i++)
	    {	c = fgetc (f);
		if (c == EOF)
		    erreur ("unexpected end-of-file");
		if ((c & 0xc0) != 0x80)
/*
 * Les octets suivants doivent commencer par 10.
 */
		    erreur ("wrong trailing octet");
		code = append_6bits (code, c);
	    }
	    if (code > 0x10ffff)
/*
 * La valeur doit être <= 0x01ffff
 */
		erreur ("Unicode upper limit reached");
	    if (code < 0xa0 || code > 0xff)
/*
 * On a un codage UTF-8 valide. 
 * On teste si c'est du Latin-1.
 */
		erreur ("not Latin-1");
	    printf ("%c", (char)code);
	}
    }
    fclose (f);
    return 0;
}

