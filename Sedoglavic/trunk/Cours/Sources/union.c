
union t_nombre{
  
  int entier ;

  struct complexe {
    float re ;
    float im ;
  } ;

  char symbol[20] ;

}  foo,bar = { .entier = 999 } ;


int main(){

	foo=bar;

  return 0 ;
}
