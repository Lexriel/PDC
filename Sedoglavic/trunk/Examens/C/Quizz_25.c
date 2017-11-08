#include <stdlib.h>
#include <stdio.h>


int
                String2Int
                (char *str) {
	int             res;
	for (res = 0; *str; str++)
		res = 10 * res + *str - '0';
	return res;
}

int
                main
                (int argc, char **argv) {
	int            *jeu;
	int             etat;
	int             i;
	int             tas;
	int             allumettes;

	if (!(argc - 1))
		return 1;

	jeu = (int *) malloc(argc * sizeof(int));

	for (i = 0; i < argc - 1; i++)
		jeu[i] = String2Int(argv[i + 1]);

	do {

		allumettes = 0;
		for (i = 0; i < argc - 1; i++) {
			allumettes += jeu[i];
			printf(" %d ", jeu[i]);
		}

		if (!allumettes)
			return 0;

		etat = 0;
		for (i = 0; i < argc - 1; i++)
			etat ^= jeu[i];

		if (!etat) {
			printf("Position perdante\n");
			return 0;
		}
		while (1) {
			printf("\n Choisissez un tas => ");
			scanf("%d", &tas);
			if (tas < 1 || tas > argc - 1)
				continue;
			printf("\n Nombre d'allumette(s) retiree(s) => ");
			scanf("%d", &allumettes);
			if (allumettes < 1 || allumettes > jeu[tas - 1])
				continue;
			jeu[tas - 1] -= allumettes;
			break;
		}

		for (i = 0; etat <= jeu[i]; i++);
		jeu[i] -= etat;

	}
	while (1);

	return 0;
}
