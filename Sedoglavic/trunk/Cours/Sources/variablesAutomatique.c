#include<stdio.h>

char *foo(void){
    char str[31]="Pourquoi vais-je disparaitre~?" ;
    return str ;
}

int main(void){
   printf("%d %d %s\n",1,2,foo()) ;
   return 0;
}
