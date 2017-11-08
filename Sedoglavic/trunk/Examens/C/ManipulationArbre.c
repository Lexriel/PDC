#include <stdlib.h>


typedef struct data_m data_t;

typedef struct cellule_m cellule_t;

typedef cellule_t *racine_t;

struct data_m {
	int             i;
};

struct cellule_m {
	data_t          data;
	char           *string;
	cellule_t      *filsgauche;
	cellule_t      *filsdroit;
};

cellule_t      *
CreerCellule(data_t data, char *string)
{
	register unsigned int i;

	cellule_t      *res = (cellule_t *) malloc(sizeof(cellule_t));

	res->data = data;
	res->filsgauche = res->filsdroit = NULL;

	for (i = 0; *(string + i); i++);
	res->string = (char *) malloc(i + 1);

	*((res->string) + i) = 0;
	for (; i >= 0; i--)
		*((res->string) + i) = *(string + i);

	return res;
}

void
DetruireCellule(cellule_t * cellule)
{
	free(cellule->string);
	free(cellule);
}

int
DetruireArbre(cellule_t * cellule)
{
	int             nb = 1;

	if (!(cellule->filsgauche))
		nb += DetruireArbre(cellule->filsgauche);

	if (!(cellule->filsdroit))
		nb += DetruireArbre(cellule->filsdroit);

	DetruireCellule(cellule);

	return nb;
}
