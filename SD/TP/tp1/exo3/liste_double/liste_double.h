#if ! defined (LISTE_DOUBLE_H)
#define LISTE_DOUBLE_H 1

/**********************************************************************
 * IMPLANTATION
 **********************************************************************/

struct maillon_double
{   double value;
    struct maillon_double* next;
};

struct liste_double
{   struct maillon_double* tete;
    int nbelem;
};

/**********************************************************************
 * PROTOTYPES DES FONCTIONS (TYPE ABSTRAIT)
 **********************************************************************/

extern void init_liste_double (struct liste_double*);
extern void clear_liste_double (struct liste_double*);
extern void set_liste_double (struct liste_double*, struct liste_double*);
extern void ajouter_en_tete_liste_double (struct liste_double*, double);
extern void extraire_tete_liste_double (double*, struct liste_double*);
extern void imprimer_liste_double (struct liste_double*);
#endif
