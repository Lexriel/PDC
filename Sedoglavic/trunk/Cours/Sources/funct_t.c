
int fct(int foo){

	return foo ;
}

int (*fct_t)(int) = fct ;

int i = 1 ;

int main(){

	i = fct(i) + (*fct_t)(i) ; 
	return 0 ;
}
