#define NB 37 

long unsigned int
catalan2
(unsigned int n)
{	
	long unsigned int res ;
        register unsigned int i ;
	static long unsigned int catalannumber[NB] ;
	static unsigned int next2compute ;

	if(!n)
		res = 1 ;
	else 
		res = 0 ;

	for(i=0;i<n;i++)
		res += ((i<next2compute)?catalannumber[i]:catalan(i))
			*((n-1-i<next2compute)?catalannumber[n-1-i]:catalan(n-1-i)) ;

	catalannumber[next2compute++] = res ;
	return res ; 
}

