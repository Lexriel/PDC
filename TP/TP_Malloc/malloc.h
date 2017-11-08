# ifndef _MALLOC_H_
# define _MALLOC_H_
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# define TAILLE_BLOC 200
# define M_MXFAST 42
# define M_NMBLOCKS 69
# define FALSE 0
# define TRUE 1
# define FULL 2

typedef struct ListeChaine 
{
	struct ListeChaine *next;
	struct m_petitBloc *tab;
	int taille;
	char utilise;
	void *adresse;
} ListeChaine;

typedef struct m_petitBloc
{
	char utilise;
	void *adresse;
} t_petitBloc;


# define mmalloc(size) bam_malloc(size,__FILE__,__LINE__)

void *bam_malloc(size_t size, char *filename, unsigned line);

void mfree(void *adresse);

void mmallopt(int cmd, unsigned int val);

void *mrealloc(void *base, size_t size);

void *mcalloc(size_t nb_case, size_t taille_case);

void imprimerBiblio();

#endif
