# ifndef _STRUCTNOBEL_H_
# define _STRUCTNOBEL_H_
# include "macros.h"

void lireParametre(char param[], int n, int line[], int pos);

void remplirNomine(Nomine *nobel, int line[]);

void afficheNomine(Nomine nobel);

int ConstruireTableaux(Nomine *nobels);

/* int CompareNomineParDateDeNaissance(Nomine *nobel1, Nomine *nobel2); */
int CompareNomineParDateDeNaissance(const void *nobel1, const void *nobel2);

# endif
