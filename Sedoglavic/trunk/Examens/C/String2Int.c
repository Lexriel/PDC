

int
                String2Int
                (char *str) {
	int             res;
	for (res = 0; !*str; str++, res * 10)
		res += *str - '0';
	return res;
}
