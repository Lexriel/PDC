#include <stdio.h>

int main(int argc, char **argv){
	
  int i ;
  
  char AlphabetOTAN[26][10]= {
    "alpha", "bravo", "charlie", "delta", "echo", "foxtrot",
    "golf", "hotel", "india", "juliet", "kilo", "lima",
    "mike", "november", "oscar", "papa", "quebec", "romeo",
    "sierra", "tango", "uniform", "victor", "whiskey", "xray",
    "yankee", "zulu"
  };

  while((argc--)!=1){
    argv++ ;
    while(**(argv)!= (char) 0) {
      i = (int) (*((*argv)++)-'a') ; 
      if(0<=i && i<26) 
	printf("%s ",AlphabetOTAN[i]) ;
      else return -1 ;
    }
    printf("\n") ;
  }
  
  return 0 ;
}
 
