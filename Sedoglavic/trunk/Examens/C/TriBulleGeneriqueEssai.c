#define NBEntier 12
#include <stdlib.h>
#include <stdio.h>
int            *
                loadintegers
                (unsigned int n) {
	int            *res;
	FILE           *rand;
	res = (int *) malloc(sizeof(int) * n);
	if (!(rand = fopen("/dev/random", "r")))
		exit(1);
	fread(res, sizeof(int), n, rand);
	fclose(rand);
	return res;
}
void
                printintegers
                (int *ptr, int size) {
	int             i;
	for (i = 0; i < size; i++)
		printf("%d \n", ptr[i]);
	printf("\n\n");
}

void
                TriBulle
                (int *tab, int tabsize) {
	int             i;
	int             tmp;
	for (tabsize--; tabsize; tabsize--)
		for (i = 0; i < tabsize; i++)
			if (tab[i] > tab[i + 1]) {
				tmp = tab[i];
				tab[i] = tab[i + 1];
				tab[i + 1] = tmp;
			}
	return;
}

#define CHOOSECELL(a,b,c) (((char *) a)+(b)*cellsize+(c))

void
                TriBulleGenerique
                (void *tab, int tabsize, int cellsize,
		 int (*compar) (void *, void *))
{
	int             i, j;
	char            tmp;
	for (tabsize--; tabsize; tabsize--)
		for (i = 0; i < tabsize; i++)
			if (compar((void *) CHOOSECELL(tab, i, 0), (void *) CHOOSECELL(tab, i + 1, 0)))
				for (j = 0; j < cellsize; j++) {
					tmp = *CHOOSECELL(tab, i, j);
					*CHOOSECELL(tab, i, j) = *CHOOSECELL(tab, i + 1, j);
					*CHOOSECELL(tab, i + 1, j) = tmp;
				}
	return;
}


int
                mycompar
                (void *a, void *b) {
	if (*((int *) a) > *((int *) b))
		return 1;
	return 0;
}

int
                main
                (int argc, char **argv) {
	int            *head = loadintegers(NBEntier);
	printf("L'ensemble de depart\n");
	printintegers(head, NBEntier);
	TriBulleGenerique(head, NBEntier, sizeof(int), mycompar);
	printf("L'ensemble trie\n");
	printintegers(head, NBEntier);
	return 0;
}