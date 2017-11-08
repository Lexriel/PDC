/* liste_point.h */

#if ! defined (LISTE_POINT_H)
#define LISTE_POINT_H 1

#include "point.h"

struct maillon_point {
    struct point value;
    struct maillon_point* next;
};

#define NIL (struct maillon_point*)0

struct liste_point {
    struct maillon_point* tete;
    int nbelem;
};

extern void init_liste_point (struct liste_point*);
extern void ajouter_en_tete_liste_point (struct liste_point*, struct point);
extern void extraire_tete_liste_point (struct point*, struct liste_point*);
extern void premier_element_liste_point (struct point*, struct liste_point*);
extern void deuxieme_element_liste_point (struct point*, struct liste_point*);
extern void clear_liste_point  (struct liste_point*);

#endif

