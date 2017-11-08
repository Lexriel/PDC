#if ! defined (CHAINE_H)
#define CHAINE_H 1

/**********************************************************************
 * IMPLANTATION
 **********************************************************************/

#include "liste_char.h"

struct chaine
{
    struct liste_char L;
};

/**********************************************************************
 * PROTOTYPES DES FONCTIONS (TYPE ABSTRAIT)
 **********************************************************************/

extern void init_chaine (struct chaine*);
extern void clear_chaine (struct chaine*);
extern void ajout_en_queue (struct chaine*, char);
extern void print_chaine (struct chaine*);

#endif
