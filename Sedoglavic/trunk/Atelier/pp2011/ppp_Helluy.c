#include <stdio.h>
#include <stdlib.h>
#define TAB 4

int
main ()
{
  char c;
  int indent = 0;
  int i = 0;
  char quote = 0;
  c = getchar();
  do  
  {
      switch(c){
	case '\t':
		break;
	case '\'':
		putchar(c);
		quote =~quote;
		break;
	case '"':
		putchar(c);
		quote =~quote;
		break;
	case '\n':
		putchar(c);
		for(i=0;i<indent*TAB;i++)
			putchar(' ');
//		putchar('9');
		break;
	case '{':
		if(!quote){
			putchar('\n');

			for(i=0;i<indent*TAB;i++)
				putchar(' ');
			putchar('{');
			
			putchar('\n');
			indent++;
			for(i=0;i<indent*TAB;i++)
				putchar(' ');
			
		}
		break;
	case '}':
		if(!quote){
			indent--;
			putchar('\n');
			for(i=0;i<indent*TAB;i++)
				putchar(' ');
			putchar('}');
		}
		break;
     	default: 
	  	putchar (c);
		break;
	}
      c = getchar();
    } while ( c != EOF);
  return EXIT_SUCCESS;
}
