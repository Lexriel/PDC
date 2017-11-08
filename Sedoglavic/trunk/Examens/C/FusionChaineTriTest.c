#include<stdio.h>

char           *FusionTrieeDe2Chaines(char *, char *);
int
                main
                (int argc, char **argv) {
	if (argc != 3) {
		printf("%s affiche la fusion tri\\'ee de deux cha\\^ines\n", *argv);
		printf("fournies en param\\`etre du shell\n");
		return 1;
	}
	printf("%s\n", FusionTrieeDe2Chaines(argv[1], argv[2]));
	return 0;
}
