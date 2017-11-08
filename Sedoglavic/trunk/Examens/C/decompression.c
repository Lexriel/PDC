#include<stdio.h>
#include<stdlib.h>

int
char2int(char **str)
{
	int             res;
	res = 0;
	for (; (**str >= '0') && (**str <= '9'); (*str)++)
		res = 10 * res + **str - '0';
	return res;
}

char           *
cmp2noncmp(char *cmp)
{
	char           *tmp, *res;
	int             lc, foo, bar;
	tmp = cmp;
	lc = 0;
	bar = 0;
	while (*tmp != 0) {
		foo = char2int(&tmp);
		while ((*tmp != 0) && (*tmp - '0' < 0 || *tmp - '9' > 0)) {
			tmp++;
			bar++;
		}
		lc += bar * foo;
	}
	res = (char *) malloc((lc + 1) * sizeof(char));
	bar = 0;
	while (*cmp != 0) {
		foo = char2int(&cmp);
		while (foo-- > 0) {
			tmp = cmp;
			while ((*tmp != 0) && (*tmp - '0' < 0 || *tmp - '9' > 0))
				*(res + bar++) = *(tmp++);
		}
		cmp = tmp;
	}
	*(res + bar) = 0;
	return res;
}

int
main(void)
{
	char            str[100];
	printf("Entrez la ch\\^aine compress\\'ee ");
	scanf("%s", str);
	printf("Le r\\'esultat est %s\n", cmp2noncmp(str));
	return 0;
}
