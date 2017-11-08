#if ! defined (CARACTERE_H)
#define CARACTERE_H 1

/**********************************************************************
 IMPLANTATION
 **********************************************************************/

enum type_format { format_Latin_1, format_UTF_8 };

/*
 * Un caractère est stocké dans le tableau d'octets au format UTF-8.
 * La suite d'octets est stockée dans le champ octet.
 * Le nombre d'octets est stocké dans le champ nb_octets.
 * Le tableau d'octets n'est pas terminé par '\0'
 */

#define NBMAX_OCTETS 8
struct caractere
{   unsigned char octets [NBMAX_OCTETS];
    int nb_octets;
};

/**********************************************************************
 TYPE ABSTRAIT (prototypes des fonctions)
 **********************************************************************/

extern void init_caractere (struct caractere*);
extern void clear_caractere (struct caractere*);
extern void set_caractere (struct caractere*, struct caractere*);
extern void set_caractere_string 
			(struct caractere*, int*, char*, enum type_format);
extern int nb_octets_caractere (struct caractere*);
extern void imprimer_caractere (struct caractere*, enum type_format);

#endif
