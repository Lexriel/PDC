#include "CarreMagique.h"

int
main
(void)
{
	
	unsigned int tab[TABSIZE][TABSIZE] = {{2,7,6},{10,5,1},{4,3,8}} ;

	return EstMagique(tab,TABSIZE) ;
}
