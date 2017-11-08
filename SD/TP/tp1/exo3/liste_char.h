#if ! defined (LISTE_CHAR_H)
#define LISTE_CHAR_H 1

/**********************************************************************
 * IMPLANTATION
 **********************************************************************/

struct maillon_char
{   char value;
    struct maillon_char* next;
};

struct liste_char
{   struct maillon_char* tete;
    int nbelem;
};

/**********************************************************************
 * PROTOTYPES DES FONCTIONS (TYPE ABSTRAIT)
 **********************************************************************/

extern void init_liste_char (struct liste_char*);
extern void clear_liste_char (struct liste_char*);
extern void set_liste_char (struct liste_char*, struct liste_char*);
extern void ajouter_en_tete_liste_char (struct liste_char*, char);
extern void ajouter_en_queue_liste_char (struct liste_char*, char);
extern void imprimer_liste_char (struct liste_char*);

#endif

