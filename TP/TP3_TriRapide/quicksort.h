# ifndef _QUICKSORT_H_
# define _QUICKSORT_H_

extern void permuter(void *a, void *b, int size);

extern int partitionner(void *base, int size, int premier, int dernier, int pivot, int (*compar) (const void *,const void *));

extern void my_qsort(void *base, int size, int premier, int dernier, int (*compar) (const void *,const void *));

extern void quicksort(void *base, int nelem, int size, int (*compar) (const void *,const void *));

# endif
