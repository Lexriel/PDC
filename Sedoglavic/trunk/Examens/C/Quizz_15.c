void
CalculAireRectangle(int longueur, int largeur, int AireRectangle)
{
	AireRectangle = longueur * largeur;
}

int
main(void)
{
	int             longueur = 5;
	int             largeur = 4;
	int             AireRectangle = 0;
	CalculAireRectangle(longueur, largeur, AireRectangle);
	return AireRectangle;
}
