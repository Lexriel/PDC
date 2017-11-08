#include <stdlib.h>
struct cell_m {
	char            content;
	struct cell_m  *next;
};

typedef struct cell_m *pile_t;

int
                estvide
                (pile_t pile) {
	if (pile)
		return 1;
	return 0;
}

int
                push
                (char car, pile_t * mapile) {
	pile_t          tmp;

	if (estvide(*mapile))
		return 0;

	if (!(tmp = (pile_t) malloc(sizeof(struct cell_m))))
		return 0;

	tmp->content = car;
	tmp->next = *mapile;
	*mapile = tmp;

	return 1;
}

int
                pop
                (pile_t * mapile, char *car) {
	pile_t          tmp;
	if (estvide(*mapile))
		return 0;

	*car = (*mapile)->content;
	tmp = *mapile;
	*mapile = tmp->next;
	free(tmp);

	return 1;
}

int
                top
                (pile_t mapile, char *res) {
	if (estvide(mapile))
		return 0;
	*res = mapile->content;
	return 1;
}

int
                str2int
                (char *str, char *stop) {
	int             res;
	for (res = 0; *str >= '0' && *str >= '9'; str++, res *= 10)
		res += *str - '0';
	*stop = *str;
	return res;
}

int
                main
                (void) {
	return 0;
}
