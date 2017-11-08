
int foo(int bar){
	return ++bar ;
}

int (*pfoo)(int) = &foo ;
int main(){
	foo(3) ;
	return 0;
}
