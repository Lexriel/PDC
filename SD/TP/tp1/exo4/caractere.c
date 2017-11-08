#include <stdio.h>
#include "caractere.h"

void init_caractere (struct caractere* k)
{
    k->nb_octets = 0;
}

void clear_caractere (struct caractere* k)
{
}

/*
 * Affecte src � dst
 */

void set_caractere (struct caractere* dst, struct caractere* src)
{
    *dst = *src;
}

int nb_octets_caractere (struct caractere* k)
{
    return k->nb_octets;
}

/*
 * D�compose l'octet c (cens� �tre le premier octet d'une s�quence UTF-8).
 * L'entier *counter re�oit le nombre de bits de contr�le � 1
 * Le long *code re�oit les bits de valeur.
 *
 * Par exemple, si c = 110xxxxx alors *counter = 2 et *code = xxxxx.
 * Si c = 0xxxxxxx (code ASCII) alors *counter = 0 et code = c.
 */

static void analyse_premier_octet (int* counter, long* code, unsigned char c)
{   int cpt, bits, mask;

    cpt = 0;
    bits = c;
    mask = 0x80;                /* 1000 0000 binaire */
/* 
 * Invariants de boucle : 
 * - mask comporte un seul bit � 1
 * - bits est �gal � c, sans les bits � 1, situ�s plus � gauche que mask
 * - cpt est �gal au nombre de bits � 1 de c, situ�s plus � gauche que mask
 */
    while ((bits & mask) != 0)  /* tq bits comporte un bit � 1 face � mask */
    {   bits ^= mask;           /* effacer ce bit */
        cpt += 1;
        mask >>= 1;             /* d�caler d'une position vers la droite
                                   l'unique bit � 1 de mask */
    }
    *counter = cpt;
    *code = (long)bits;
}

/*
 * Affecte le premier caract�re de la cha�ne t, qui est au format f, 
 * au caractere *k. Le nombre d'octets lus est affect� � *nb_octets.
 */

void set_caractere_string 
	(struct caractere* k, int* nb_octets, char* t, enum type_format f)
{   unsigned char* s = (unsigned char*)t;
    int i, counter;
    long code;

    i = 0;
    switch (f)
    {   case format_Latin_1:
            if ((s [i] & 0x80) == 0)
            {   
/*
 * Les ASCII sont cod�s sur 1 octet.
 */
		k->octets [0] = s [i];
		k->nb_octets = 1;
	    } else
	    {   
/*
 * Les non ASCII sont cod�s sur 2 octets.
 */
		k->octets [0] = 0xc0 | (s [i] >> 6);
		k->octets [1] = 0x80 | (s [i] & 0x3f);
		k->nb_octets = 2;
	    }
	    *nb_octets = 1;
	    break;
	case format_UTF_8:
/*
 * Il n'y a donc aucune conversion � faire.
 * La seule information utile : counter
 */
	    analyse_premier_octet (&counter, &code, s [i]);
	    k->octets [0] = s [i];
	    i += 1;
	    while (i < counter)
	    {   k->octets [i] = s [i];
		i += 1;
	    }
	    k->nb_octets = counter == 0 ? 1 : counter;
	    *nb_octets = k->nb_octets;
	    break;
    }
}

/*
 * Imprime le caractere *k sur la sortie standard, dans le format f
 */

void imprimer_caractere (struct caractere* k, enum type_format f)
{   int i;

    switch (f)
    {   case format_Latin_1:
            if (k->nb_octets == 1)
		putchar (k->octets [0]);
	    else
	        putchar (((k->octets [0] & 0x03) << 6) | 
			  (k->octets [1] & 0x3f));
            break;
        case format_UTF_8:
	    for (i = 0; i < k->nb_octets; i++)
		putchar (k->octets [i]);
	    break;
    }
}

