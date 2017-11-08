#if ! defined (LISTE_CARACTERE_H)
#define LISTE_CARACTERE_H 1

/**********************************************************************
 * IMPLANTATION
 **********************************************************************/

#include "caractere.h"

struct maillon_caractere
{   struct caractere value;
    struct maillon_caractere* next;
};

struct liste_caractere
{   struct maillon_caractere* tete;
    int nbelem;
};

/**********************************************************************
 * PROTOTYPES DES FONCTIONS (TYPE ABSTRAIT)
 **********************************************************************/

extern void init_liste_caractere (struct liste_caractere*);
extern void clear_liste_caractere (struct liste_caractere*);
extern void set_liste_caractere 
			(struct liste_caractere*, struct liste_caractere*);
extern void ajouter_en_tete_liste_caractere 
			(struct liste_caractere*, struct caractere*);
extern void ajouter_en_queue_liste_caractere 
			(struct liste_caractere*, struct caractere*);

#endif

