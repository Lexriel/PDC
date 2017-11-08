long unsigned int
catalan
(unsigned int n)
{	
	long unsigned int res ;
        register unsigned int i ;
	fprintf(stderr,"calcul de catalan(%d)\n",n) ;
	if(!n)
		return 1 ;

	for(res=i=0;i<n;i++)
		res += catalan(i)*catalan(n-1-i) ;

	return res ; 
}

