#if ! defined (CHAINE_H)
#define CHAINE_H 1

#include "liste_char.h"

/**********************************************************************
 * IMPLANTATION
 **********************************************************************/

struct chaine
{   struct liste_char L;
};

/**********************************************************************
 * PROTOTYPES DES FONCTIONS (TYPE ABSTRAIT)
 **********************************************************************/

extern void init_chaine (struct chaine*);
extern void clear_chaine (struct chaine*);
extern void concat_chaine_char (struct chaine*, char);
extern void print_chaine (struct chaine*);

#endif
