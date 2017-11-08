#include<stdio.h>
#include<stdlib.h>

typedef struct Cellule {
	int             a;
	struct Cellule *next;
}               Cellule;

typedef Cellule *file;

void
ajouter(file a, int b)
{

	struct Cellule *tmp = (struct Cellule *) malloc(sizeof(struct Cellule));
	tmp->next = file;
	file = tmp
}

void
retirercell(file a, int b)
{

	file            tmp1 = a, tmp2 = a;
	if (tmp->a == b) {
		a = a->next;
		free(tmp);
	}
}

int
main()
{

	file            mafile = NULL;

	return 0;
}
