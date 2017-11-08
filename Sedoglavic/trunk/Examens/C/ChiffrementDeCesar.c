#include<stdlib.h>
#include<stdio.h>

char           *
                chiffrer_cesar
                (char *clair, int decalage) {
	int             i;
	char           *chiffre;

	for (i = 0; clair[i]; i++);

	chiffre = (char *) malloc(i + 1);

	for (i = 0; clair[i]; i++)
		chiffre[i] = clair[i] + decalage;

	return chiffre;
}


int
                maxi_tableau
                (float tab[], int taille) {
	int             res;
	int             i;

	for (res = i = 0; i < taille; i++)
		if (tab[res] < tab[i])
			res = i;
	return res;
}



char
                calcul_frequence
                (char *texte, float frequences_calculees[]) {
	register int    i;
	float           nbtotal;
	char            occurencelettres[255];
	/* on commence par faire des statistiques */
	for (i = 0; i < 256; i++)
		occurencelettres[i] = 0;

	while (*texte)
		occurencelettres[(int) (*(texte++))]++;

	nbtotal = 0;
	for (i = 0; i < 255; i++)
		nbtotal += occurencelettres[i];

	for (i = 0; i < 255; i++)
		frequences_calculees[i] = 100. * ((float) occurencelettres[i]) / nbtotal;

	return (char) maxi_tableau(frequences_calculees, 255);
}

int
                decalage_moyen
                (char *texte, float *langue) {
	char            lettre;
	float           frequencetexte[255];
	lettre = calcul_frequence(texte, frequencetexte);
	decalage = lettre - maxi_tableau(langue, 255);
	return decalage;
}

int
                main
                (int argc, char **argv) {
	int             i;
	float           frequence[256];
	if (argc != 4) {
		printf("usage: %s [cdg] texte decalage \n", argv[0]);
		return 1;
	}
	switch (argv[1][0]) {
	case 'c':
		printf("%s\n", chiffrer_cesar(argv[2], atoi(argv[3])));
		break;
	case 'd':
		printf("%s\n", chiffrer_cesar(argv[2], -atoi(argv[3])));
		break;
	case 'g':
		printf("%c\n", calcul_frequence(argv[2], frequence));
		break;
	default:
		printf("c pour code, d pour decode, g pour deviner\n");
	}

	return 0;
}
