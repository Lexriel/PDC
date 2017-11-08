int foo = 44 ; 
int *p_foo = &foo ;

short int bar = 44 ;
short int *p_bar = &bar;

void * p_qlcq = &foo  ;

int main(){

	 bar = *p_bar * 2 ;
	*p_foo += 4 ;

	foo = * (int *) p_qlcq ;
	return 0 ;
}
