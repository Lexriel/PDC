#include <stdlib.h>
#define TRUE (1==1)
#define FALSE !TRUE

struct truematrix_m {
	unsigned int    nblig;
	unsigned int    nbcol;
	int            *body;
};

union matrix_m {
	int             zero;
	struct truematrix_m matrix;
};

typedef struct truematrix_m truematrix_t;
typedef union matrix_m *matrix_t;

matrix_t
makenullmatrix
(void) {
	matrix_t        res;
	res = (matrix_t) malloc(sizeof(union matrix_m));
	res->zero = TRUE;
	return res;
}

matrix_t
makematrix
(int nblig, int nbcol) {
	matrix_t        res;

	if (nblig <= 0 || nbcol <= 0)
		return NULL;

	res = (matrix_t) malloc(sizeof(union matrix_m));
	res->matrix.nblig = nblig;
	res->matrix.nbcol = nbcol;
	res->matrix.body = (int *) malloc(nblig * nbcol * sizeof(int));
	res->zero = FALSE;

	return res;
}

void
                killmatrix
                (matrix_t mat) {
	if (!mat)
		return;

	if ((mat->zero == FALSE) && mat->matrix.body)
		free(mat->matrix.body);
	free(mat);
}

matrix_t
addmatrix
(matrix_t a, matrix_t b) {
	int             pos, i, j, nblig, nbcol, null;
	int            *body;
	matrix_t        res;
	if (!a || !b)
		/* a ou b n'est pas valide, la somme n'est pas valide */
		return NULL;

	if (a->zero)
		return b;
	if (b->zero)
		return a;

	nblig = a->matrix.nblig;
	nbcol = a->matrix.nbcol;
	if (!((nblig == b->matrix.nblig) &&
	      (nbcol == b->matrix.nbcol)))
		return NULL;

	body = (int *) malloc(nblig * nbcol * sizeof(int));

	for (i = 0; i < nblig; i++)
		for (j = 0; j < nbcol; j++) {
			pos = i * nbcol + j;
			body[pos] = a->matrix.body[pos] + b->matrix.body[pos];
		}

	null = TRUE;
	for (i = 0; i < nblig; i++)
		for (j = 0; j < nbcol; j++) {
			pos = i * nbcol + j;
			null = null && !body[pos];
		}

	if (null) {
		free(body);
		return makenullmatrix();
	}
	res = (matrix_t) malloc(sizeof(union matrix_m));
	res->matrix.nblig = nblig;
	res->matrix.nbcol = nbcol;
	res->matrix.body = body;
	res->zero = FALSE;
	return res;
}

int
                main
                (void) {
	return 0;
}
