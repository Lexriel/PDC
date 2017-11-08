#include<stdio.h>

char           *
                ComplementBrin(char *);

int
                main
                (int argc, char **argv) {
	char           *res;
	if (argc != 2) {
		printf("%s affiche le compl\\'ement --- selon la r\\`egle de Watson et Krick ---\n", *argv);
		printf("d'une cha\\^ines de caract\\`eres fourni en param\\`etre du shell\n");
		return 1;
	}
	res = ComplementBrin(argv[1]);
	if (!res)
		return 1;

	printf("%s\n", res);
	return 0;
}
