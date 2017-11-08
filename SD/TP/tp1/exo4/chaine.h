#if ! defined (CHAINE_H)
#define CHAINE_H 1

#include "liste_caractere.h"

/**********************************************************************
 * IMPLANTATION
 **********************************************************************/

struct chaine
{   struct liste_caractere L;
};

/**********************************************************************
 * PROTOTYPES DES FONCTIONS (TYPE ABSTRAIT)
 **********************************************************************/

extern void init_chaine (struct chaine*);
extern void clear_chaine (struct chaine*);
extern void set_chaine_string (struct chaine*, char*, enum type_format);
extern void imprimer_chaine (struct chaine*, enum type_format);
extern int nb_octets_chaine (struct chaine*);
extern int nb_caracteres_chaine (struct chaine*);

#endif
