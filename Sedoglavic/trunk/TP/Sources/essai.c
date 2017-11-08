int foo(int a,int b){
	return a ;
}

int main(void){
	/* une premi\`ere suite 
	   d'expressions  */
	int a = 2, b = a ; 
	/* une seconde */
	return foo(a, (a+=b, b+=3) ) ;
}
