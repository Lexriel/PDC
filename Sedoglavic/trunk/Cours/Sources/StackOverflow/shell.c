
#include <stdio.h>
  char *name[2] ;

      int main(void){
         name[0] = "/bin/sh" ;
         name[1] = NULL ;
	 execve(name[0],name,NULL) ;
      }
