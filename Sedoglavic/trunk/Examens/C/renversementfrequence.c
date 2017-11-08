#include "renversementfrequence.h"
#include <stdio.h>
#include <stdlib.h>

struct cellule_s *
                analyseDeFrequence
                (char *txt) {
	register int    i;
	float           nbtotal;
	char            occurencelettres[255];
	struct cellule_s *head, *tmp;

	/* on commence par faire des statistiques */
	for (i = 0; i < 256; i++)
		occurencelettres[i] = 0;

	while (*txt)
		occurencelettres[(int) (*(txt++))]++;

	nbtotal = 0;
	for (i = 0; i < 256; i++)
		nbtotal += occurencelettres[i];

	/* on construit maintenant la chaine */
	head = 0;
	for (i = 0; i < 256; i++)
		if (occurencelettres[i]) {
			tmp = (struct cellule_s *) malloc(sizeof(struct cellule_s));
			tmp->next = head;
			tmp->caractere = (char) i;
			tmp->frequence = 100. * ((float) occurencelettres[i]) / nbtotal;
			tmp->listecirculaire = NULL;
			head = tmp;
		}
	return head;
}

struct cellule_s *
                TriSuivantFrequence
                (struct cellule_s ** oldhead) {
	struct cellule_s *newhead, *tmp, *newcell, *previouscell, *newend;
	float           minfreq;
	newhead = NULL;
	while (*oldhead)
		/* tant que la liste non triee est non vide */
	{
		tmp = *oldhead;
		newcell = tmp;
		previouscell = 0;
		/* on cherche la cellule de frequence minimale */
		minfreq = tmp->frequence;
		while (tmp->next) {
			if (tmp->next->frequence < minfreq) {
				minfreq = tmp->next->frequence;
				previouscell = tmp;
				newcell = tmp->next;
			}
			tmp = tmp->next;
		}
		/* on la retire de la liste */
		if (previouscell)
			previouscell->next = newcell->next;
		else
			*oldhead = newcell->next;
		/* on la rajoute a la fin de la liste triee */
		if (newhead) {
			newend->next = newcell;
			newend = newcell;
		} else
			newend = newhead = newcell;
	}
	return newhead;
}

struct pile_s  *
                initpile
                (void) {
	struct pile_s  *res = (struct pile_s *) malloc(sizeof(struct pile_s));
	res->sommet = 0;
	return res;
}

int
                empile
                (char entier, struct pile_s * mapile) {
	if (mapile->sommet == MaxPile)
		return 0;
	mapile->tab[mapile->sommet] = entier;
	mapile->sommet++;
	return 1;
}

int
                depile
                (struct pile_s * mapile, char *entier) {
	if (!mapile->sommet)
		return 0;
	mapile->sommet--;
	*entier = mapile->tab[mapile->sommet];
	return 1;
}

void
                construirecode
                (struct pile_s * pile, struct cellule_s * head) {
	int             n;
	struct cellulecode_s *tmp;

	while (head) {
		n = 1 + (int) head->frequence;
		while (n--) {
			tmp = (struct cellulecode_s *) malloc(sizeof(struct cellulecode_s));
			if (!depile(pile, &(tmp->caractere)))
				exit(2);

			if (!head->listecirculaire) {
				head->listecirculaire = tmp;
				tmp->next = head->listecirculaire;
			} else {
				tmp->next = head->listecirculaire->next;
				head->listecirculaire->next = tmp;
			}
		}
		head = head->next;
	}
}

void
                affichegrille
                (struct cellule_s * head) {
	struct cellulecode_s *tmp;
	while (head) {
		/* printf("\n %c %f ",head->caractere,head->frequence); */
		tmp = head->listecirculaire;
		if (tmp)
			do {
				/* printf("%c ",tmp->caractere) ; */
				tmp = tmp->next;
			}
			while (tmp != head->listecirculaire);
		head = head->next;
	}
	/* printf("\n"); */
}

void
                clean
                (struct cellule_s * head) {
	struct cellulecode_s *tmp;
	if (head) {
		clean(head->next);
		if (head->listecirculaire)
			while (head->listecirculaire->next != head->listecirculaire) {
				tmp = head->listecirculaire->next;
				head->listecirculaire->next = tmp->next;
				free(tmp);
			}
		free(head->listecirculaire);
		free(head);
	}
}

char           *
                codage
                (char *texte, struct cellule_s ** clef) {
	int             i;
	struct cellule_s *grille, *foo;
	char           *res, *tmp;
	struct pile_s  *pile = initpile();
	for (i = 0; texte[i]; i++);
	res = (char *) malloc(i);
	/* printf("Construction de la pile de caracteres\n") ; */
	for (i = 33; i < 140; i++)
		empile(i, pile);
	/* printf("Analyse du texte\n"); */
	grille = analyseDeFrequence(texte);
	affichegrille(grille);
	/* printf("Tri\n"); */
	grille = TriSuivantFrequence(&grille);
	affichegrille(grille);
	/* printf("Construction du code\n"); */
	construirecode(pile, grille);
	/* printf("affichage de la clef\n"); */
	affichegrille(grille);
	*clef = grille;

	/* le codage proprement dit */
	tmp = res;
	while (*texte) {
		foo = grille;
		while (foo->caractere != *texte)
			foo = foo->next;
		*tmp = foo->listecirculaire->caractere;
		foo->listecirculaire = foo->listecirculaire->next;
		tmp++;
		texte++;
	}

	return res;
}

int
                main
                (int argc, char **argv) {
	/* char * texte ="abracadabra" ; */

	struct cellule_s *clef;
	if (argc != 2) {
		printf("Usage: %s texteachiffre | xxd\n", *argv);
		return 1;
	}
	printf("%s\n", codage(argv[1], &clef));
	/* printf("destruction de la clef\n") ; */
	clean(clef);
	return 0;
}