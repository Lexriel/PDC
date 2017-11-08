/* #define LIFO */

#define NULL 0
#define BUFFERSIZE 65536

static char     buffer[BUFFERSIZE];

void           *alloc(unsigned int);
void            free(void *);

#ifdef LIFO
static char    *nextfreebyte = buffer;

void           *
alloc(unsigned int n)
{
	if (nextfreebyte + n <= buffer + BUFFERSIZE) {
		nextfreebyte += n;
		return nextfreebyte - n;
	} else
		return NULL;
}

void
free(void *ptr)
{
	if ((char *) ptr >= buffer && (char *) ptr <= buffer + BUFFERSIZE)
		nextfreebyte = ptr;
}
#else

struct freelist_m {
	void           *ptr;
	unsigned int    size;
	struct freelist_m *next;
};

typedef struct freelist_m freelist_t;

#endif

int
main(void)
{

	return 0;
}
