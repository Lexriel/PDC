#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FOO 15

void
Affichage(char *chn)
{
	int             i = 0;
	char           *b[FOO], *dest_ptr, *src_ptr;

	if (strlen(chn) < FOO) {
		fprintf(stderr, "A quoi sert ce test~?\n");
		return;
	}
	for (; i < FOO; i++) {
		if (!(b[i] = (char *) malloc(sizeof(char) * (15 + 1)))) {
			fprintf(stderr, "A quoi sert ce test~?\n");
			return;
		}
		for (dest_ptr = b[i], src_ptr = chn + i; (*src_ptr) != 0;)
			*dest_ptr++ = *src_ptr++;
		for (src_ptr = chn; src_ptr != chn + i;)
			*dest_ptr++ = *src_ptr++;
		*dest_ptr = 0;
	}

	for (i = 0; i < FOO; i++)
		printf("%s\n", b[i]);
}

int
main(void)
{
	Affichage("Le C c'est fun.");
	return 0;
}
