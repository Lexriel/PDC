#include<stdio.h>
void testzero(int j)
{
	if(j) return ; /* provoque la sortie */
	printf("test positif") ;
}

int main(void)
{	
	testzero(0);
	return 0 ;
}
