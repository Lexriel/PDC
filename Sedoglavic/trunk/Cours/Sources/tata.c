
void fct(int tab[2]){
	tab[0] = 1 ;
}

int main(void){
	int tab[2] = { 0,1} ;
	fct(tab) ;
	return tab[0] ;
}
