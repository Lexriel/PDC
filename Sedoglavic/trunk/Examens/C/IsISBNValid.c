
int
IsISBNValid
(char *isbn)
{
	int s1,s2,cnt_digit ;
	cnt_digit=s1=s2=0 ;
	
	while(*isbn)
	{
		if (*isbn >= '0' && *isbn <= '9')
		{
		  cnt_digit ++ ;
		  s1 += *isbn -'0' ;
		  s2 += s1 ;
		/* incr\'ementation du pointeur isbn */
		isbn ++ ;
		continue ;
		}
		if (*isbn=='X')
		{ 
	       	  cnt_digit ++ ;
		  s1 += 10 ;
                  s2 += s1 ;
		/* incr\'ementation du pointeur isbn */
		isbn ++ ;
		continue ;
                }
                if (*isbn=='-')
                {
		/* incr\'ementation du pointeur isbn */
		isbn ++ ;
		continue ;
		} 
		return 1 ; /* erreur dans le code ISBN */
	}
	if(cnt_digit == 10)
		return (s2 % 11 != 0) ;
	return 1 ;
}
int
main
(int argc, char **argv)
{
	if(argc!=2)
		return 1 ;	
	return IsISBNValid(argv[1]) ;
}
