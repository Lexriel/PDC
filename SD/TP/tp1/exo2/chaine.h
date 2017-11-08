#if ! defined (CHAINE_H)
#define CHAINE_H 1

/**********************************************************************
 * IMPLANTATION
 **********************************************************************/

/*
 * Spécification de la structure de données
 * 
 * Une chaîne est une suite de caractères, éventuellement vide.
 *
 * Le champ size contient la longueur de la chaîne.
 * Quand size = 0, la chaîne est dite vide.
 * Dans ce cas, le champ data peut valoir zéro ou pointer vers une
 * zone allouée dynamiquement, commençant par '\0'.
 *
 * Dans ce qui suit, on suppose que le champ data est différent de zéro.
 *
 * le champ data pointe vers une zone allouée dynamiquement.
 *            il contient une chaîne au sens du langage C : terminée par '\0'.
 * le champ alloc contient le nombre de char alloués à data.
 * le champ size contient la longueur de la chaîne (le '\0' n'est pas compté).
 * On a toujours size + 1 <= alloc.
 */

struct chaine
{   char* data;
    int alloc;
    int size;
};

/**********************************************************************
 * PROTOTYPES DES FONCTIONS (TYPE ABSTRAIT)
 **********************************************************************/

extern void init_chaine (struct chaine*);
extern void clear_chaine (struct chaine*);
extern void concat_chaine_char (struct chaine*, char);
extern void print_chaine (struct chaine*);

#endif
