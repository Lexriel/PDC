
void           *
                bsearch
                (
                       const void *key, const void *base, int nel, int size,
		 int (*compar) (const void *, const void *)
)
{
	int             ordre;
	void           *res;

	nel--;

	while (1) {
		/* comparaison de la clef avec l'\'el\'ement courant */
		res = (void *) (((char *) base) + size * nel / 2);
		ordre = compar(key, res);

		if (!ordre)
			return res;

		/* la condition d'arret */
		if (!nel)
			break;

		nel /= 2;

		if (ordre > 0)
			base = res;
	}

	return NULL;
}
