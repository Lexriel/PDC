# ifndef _QUICKSORT_INT_H_
# define _QUICKSORT_INT_H_

extern void afficherTableauInt(char nom[], int T[],unsigned int n);

extern void permuter_int(int *a, int *b);

extern int partitionner_int(int T[], int premier, int dernier, int pivot);

extern void qsort_int(int T[], int premier, int dernier);

extern void quicksort_int(int T[], int n);

extern void test_quicksort_int(char nom[], int T[], int n);

# endif
