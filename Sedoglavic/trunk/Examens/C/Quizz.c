int            *p;
int             tab[5] = {1, 2, 3, 4, 5};
struct foo {
	int             a;
	int            *b;
}               bar, *pbar = &bar;

int
main()
{

	p = tab + 2;
	p[1] = p[0] + tab[6];
	/* tab = p + 3 ;  */
	*(tab + 4) += *(tab + 3);
	/* *(pbar+4) = tab + 1 ; */
	pbar->b = &*(p + tab[2]);
	(*pbar).a = (p + tab[2])[2];
	/* pbar->b = &(*(p+3)+tab[1]) ; */
	p = &tab[2] + *(*pbar).b;
	return 0;

}