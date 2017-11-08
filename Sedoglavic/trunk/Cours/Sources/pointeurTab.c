
int tab[2] = { 1, 2 } ;

int *p = tab ;

int main(){

	tab[1] = tab[0] ;
	*(p+1) = *p ;
	return 0 ;
}
