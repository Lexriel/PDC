#if ! defined (LISTE_DOUBLE_H)
#define LISTE_DOUBLE_H 1

/**********************************************************************
 * IMPLANTATION
 * 
 * Spécification de l'implantation
 * 
 * Implantation des listes simplement chaînées de doubles
 * 
 * Les maillons sont alloués dynamiquement. 
 * Le champ next du dernier maillon vaut (struct maillon_double*)0
 * 
 * Le champ tete d'une liste pointe vers le premier maillon
 * Le champ nbelem est égal au nombre de maillons de la liste
 * La liste vide est codée par (tete, nbelem) = ((struct maillon_double*)0, 0)
 *
 * Des listes distinctes ont des maillons distincts (pas de maillon partagé).
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

/* 
 * Constructeur. Initialise son paramètre à la liste vide 
 */

extern void init_liste_double (struct liste_double*);

/* 
 * Destructeur 
 */

extern void clear_liste_double (struct liste_double*);

/* 
 * Affecte une copie de src à dst 
 */

extern void set_liste_double 
        (struct liste_double* dst, struct liste_double* src);

/* 
 * Ajout d'un double en tête de liste 
 */

extern void ajouter_en_tete_liste_double (struct liste_double*, double);

/* 
 * Affecte à *d la valeur du premier élément de L et supprime cet élément de L. 
 * La liste L est supposée non vide.
 */

extern void extraire_tete_liste_double (double* d, struct liste_double* L);

/* 
 * Impression. 
 */

extern void imprimer_liste_double (struct liste_double*);
#endif
