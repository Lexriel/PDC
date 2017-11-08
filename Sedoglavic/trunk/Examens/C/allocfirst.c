#define BUFFERSIZE 65536
#define NULL 0
#define TRUE 1
#define FALSE 0

static char     buffer[BUFFERSIZE];

struct freelist_m {
	unsigned        isfree;
	unsigned int    size;
	struct freelist_m *next;
	struct freelist_m *previous;
};

typedef struct freelist_m freelist_t;

freelist_t     *Head;

static void
AllocatorInit(void)
{

	/* Construire l'ent\^ete du seul bloc existant  */
	freelist_t     *ptr = (freelist_t *) buffer;
	ptr->isfree = TRUE;
	ptr->size = BUFFERSIZE;
	ptr->next = NULL;
	ptr->previous = NULL;

	/* Construire la liste des blocs libres */
	Head = ptr;
	return;
}

void           *
alloc(unsigned int taille)
{

	freelist_t     *ptr = Head, *newbloc;

	while ((ptr->size < taille + sizeof(freelist_t))
	       || ptr->isfree == FALSE) {
		if (!ptr->next)
			return NULL;
		ptr = ptr->next;
	}

	ptr->isfree = FALSE;

	if (!(ptr->size < 2 * sizeof(freelist_t) + taille)) {
		/* Construire la nouvelle ent\^ete */
		newbloc = (freelist_t *) ((char *) ptr + sizeof(freelist_t) + taille);
		newbloc->isfree = TRUE;
		newbloc->size = ptr->size - taille - sizeof(freelist_t);
		newbloc->next = ptr->next;
		if (ptr->next)
			ptr->next->previous = newbloc;
		newbloc->previous = ptr;
		ptr->next = newbloc;
		ptr->size -= newbloc->size;
	}
	return (void *) ((char *) ptr + sizeof(freelist_t));
}

void
free(void *ptr)
{

	freelist_t     *entete = (freelist_t *) ((char *) ptr - sizeof(freelist_t));

	entete->isfree = TRUE;

	if (entete->next && (entete->next)->isfree == TRUE) {
		/*
		 * Si la fusion avec la cellule suivante est possible, on y
		 * va
		 */
		entete->size += entete->next->size;
		entete->next = entete->next->next;
	}
	if (entete->previous && (entete->previous)->isfree == TRUE) {
		/*
		 * Si la fusion avec la cellule pr\'ec\'edente est possible,
		 * on y va
		 */
		entete->previous->size += entete->size;
		entete->previous->next = entete->next;
	}
	return;
}

int
main(void)
{
	AllocatorInit();

	char           *A = (char *) alloc(1000);
	char           *B = (char *) alloc(2000);
	char           *C = (char *) alloc(3000);

	free(B);

	char           *D = (char *) alloc(500);

	free(C);
	free(A);
	free(D);

	return 0;
}