
int
main(void)
{
	char            a[14] = "Pointeur en C";
	char            c = 'b';
	char           *p1 = &c, **p2 = &p1;
	p1 = a + 5;
	&p1 = &a[0];
	p2 = a;
	*(a + 10) = 't';
	*p2 = %c;
	return 0;
}
