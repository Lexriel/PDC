#define NULL 0
#define SIZE 10
#define TRUE 1
#define FALSE 0

/*
 * ---------------------------------------------------------------------------
 * ---
 */

static char     MEMOIRE[1024];

struct BlocHeader_m {
	unsigned int    isfree, size;
	struct BlocHeader_m *next;
	struct BlocHeader_m *previous;
};

typedef struct BlocHeader_m BlocHeader_t;

static BlocHeader_t *ROOT[SIZE];

void
Retirer(BlocHeader_t * ptr)
{

	if (ptr->previous)
		(ptr->previous)->next = ptr->next;
	else
		ROOT[ptr->size - 1] = ptr->next;

	if (ptr->next)
		(ptr->next)->previous = ptr->previous;

	return;
}

void
Inserer(BlocHeader_t * ptr)
{

	ptr->next = ROOT[ptr->size - 1];

	if (ptr->next)
		(ptr->next)->previous = ptr;

	ptr->previous = NULL;
	ROOT[ptr->size - 1] = ptr;

	return;
}

/*
 * ---------------------------------------------------------------------------
 * ---
 */

static void
SiamoisInit(void)
{

	register unsigned int i;

	/* Traitement du bloc de m\'emoire libre */

	BlocHeader_t   *tmp = (BlocHeader_t *) MEMOIRE;

	tmp->isfree = TRUE;
	tmp->size = SIZE;
	tmp->next = tmp->previous = NULL;

	/* Traitement du tableau de t\^etes de listes cha\^\i{}n\'ees */

	for (i = 0; i < SIZE - 1; i++)
		ROOT[i] = NULL;

	ROOT[i] = tmp;

	return;
}

/*
 * ---------------------------------------------------------------------------
 * ---
 */

void           *
SiamoisAlloc(unsigned int taille)
{

	register unsigned int i = 1;
	BlocHeader_t   *ptr, *siamois;

	/* Pour commencer, tenons compte de l'ent\^ete du bloc */
	taille += sizeof(BlocHeader_t) - 1;

	/*
	 * et calculons la puissance de 2 im\'ediatement sup\'erieure \`a
	 * taille
	 */

	while (taille /= 2)
		i++;

	taille = i;

	for (i = taille - 1; i <= SIZE; i++)
		if (ROOT[i])
			break;

	if (i > SIZE)
		return NULL;

	/*
	 * On retire le bloc que l'on vient de trouver de la liste des blocs
	 * libres correspondante
	 */
	ptr = ROOT[i];
	Retirer(ptr);

	while (i != taille - 1) {
		/* Ce bloc doit-il \^etre coup\'e en~$2$~?   */
		i--;
		(ptr->size)--;
		/* Cr\'eer une ent\^ete au bon endroit */
		siamois = (BlocHeader_t *) ((char *) ptr + (1 << (i + 1)));
		siamois->size = i + 1;
		siamois->isfree = TRUE;

		/* et adjoindre ce bloc \`a la bonne liste */
		Inserer(siamois);
	}

	/* Marquer le bloc ocmme allou\'e */
	ptr->isfree = FALSE;
	ptr->next = ptr->previous = NULL;

	return (void *) ((char *) ptr + sizeof(BlocHeader_t));
}

/*
 * ---------------------------------------------------------------------------
 * ---
 */

static void    *
EstSiamoisDe(void *ptr)
{

	/*
	 * On doit disposer de la taille du bloc qui est cod\'ee en t\^ete de
	 * ce dernier
	 */

	unsigned int    blocsize = ((BlocHeader_t *) ptr)->size;

	/* Pour obtenir la taille en octets du bloc */

	blocsize = 1 << (blocsize + 1);

	/* On ram\`ene l'adresse du bloc \`a 0 pour appliquer la formule */

	if ((((char *) ptr - MEMOIRE) % blocsize) == 0)
		return (void *) ((char *) ptr + blocsize / 2);
	else
		return (void *) ((char *) ptr - blocsize / 2);

	return NULL;
}

/*
 * ---------------------------------------------------------------------------
 * ---
 */

void
SiamoisFree(void *ptr)
{

	BlocHeader_t   *current = (BlocHeader_t *) ((char *) ptr - sizeof(BlocHeader_t));
	BlocHeader_t   *siamois = siamois = (BlocHeader_t *) EstSiamoisDe((void *) current);

	while (current->size != SIZE) {

		if (!siamois->isfree)
			break;
		/*
		 * On retire le siamois de la liste des blocs libres
		 * correspondantes
		 */
		Retirer(siamois);

		/* On consid\`ere le bloc courant */
		if (siamois < current)
			current = siamois;

		(current->size)++;
		siamois = (BlocHeader_t *) EstSiamoisDe((void *) current);
	}

	/* Le bloc courant est libre */
	current->isfree = TRUE;

	/*
	 * On ins\`ere le bloc courant dans la liste des blocs libres
	 * correspondantes
	 */
	Inserer(current);

	return;
}

/*
 * ---------------------------------------------------------------------------
 * ---
 */

int
main(void)
{

	char           *A, *B, *C, *D;
	register unsigned int i;

	SiamoisInit();

	A = (char *) SiamoisAlloc(70);
	for (i = 0; i < 70; i++)
		*(A + i) = 'a';

	B = (char *) SiamoisAlloc(35);
	for (i = 0; i < 35; i++)
		*(B + i) = 'b';

	C = (char *) SiamoisAlloc(80);
	for (i = 0; i < 80; i++)
		*(C + i) = 'c';

	SiamoisFree((void *) A);

	D = (char *) SiamoisAlloc(48);
	for (i = 0; i < 48; i++)
		*(D + i) = 'D';
	*(D + 53) = 1;
	SiamoisFree((void *) B);
	SiamoisFree((void *) D);
	SiamoisFree((void *) C);

	return 0;
}
