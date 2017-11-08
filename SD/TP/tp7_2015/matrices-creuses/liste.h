#if ! defined (LISTE_H)
#define LISTE_H 1

#include "coeff.h"

struct maillon {
    struct coeff c;
    struct maillon* next;
};

#define NIL (struct maillon*)0

struct liste {
    struct maillon* tete;
    int nbelem;
};

extern void init_liste (struct liste*);
extern void insertion_liste (struct liste*, struct coeff);
extern void afficher_liste (struct liste);
extern void clear_liste  (struct liste*);

#endif
