
typedef int fct_t(int) ;
typedef fct_t * fctp1_t ;
typedef int (*fctp2_t)(int) ; /* sans utiliser fct_t */

 fct_t fct ; 

int
main
(void)
{
 fctp1_t ftcpv1 ;
    fctp2_t ftcpv2 ;
    fct_t * ftcpv3 ;
    ftcpv1 = fct ;
    ftcpv2 = fct ;
    ftcpv3 = fct ;
	return ftcpv1(1) + ftcpv2(1) + ftcpv3(1);
}

int
fct
(int a)
{
	return a+1 ;
}
