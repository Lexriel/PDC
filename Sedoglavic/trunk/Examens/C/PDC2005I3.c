int
foo(int a)
{
	a = a * 2;
	return a + 3;
}

int
bar(int *b)
{
	*b = (*b) * 3;
	return *b + 7;
}

int
foobar(int *c)
{
	return foo(bar(c));
}


int
barfoo(int d)
{
	int             t;
	t = foo(d);
	return bar(&t);
}


int
main()
{

	int             a, b, c, d, ra, rb, rd, rc;

	a = 10;
	b = 20;
	c = 50;
	d = 70;
	ra = foo(a);
	rb = bar(&b);
	rc = foobar(&c);
	rd = barfoo(d);

	printf(" %d %d %d %d %d %d %d %d \n", a, b, c, d, ra, rb, rc, rd);

	return 0;
}
