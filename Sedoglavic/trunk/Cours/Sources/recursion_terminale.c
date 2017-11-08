
unsigned int
recur_fact
(unsigned int n, unsigned int result)
{
	if (n==0)
		return 1u ;
        if (n==1)
	       return result ;

	return recur_fact(n-1,n*result);
}

int
main
(void)
{
	unsigned int res ;
	res = recur_fact(10,1);
	return res ;
}
