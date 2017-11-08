
int
                maxi_tableau
                (int tab[], int taille) {
	int             res;
	int             i;

	for (res = i = 0; i < taille; i++)
		if (tab[res] < tab[i])
			res = i;

	return res;
}
