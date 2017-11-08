#include <stdio.h>
#include <stdlib.h>

enum {ETAT_DBT_LIGNE, ETAT_NORMAL } etat = ETAT_DBT_LIGNE;

void indentation(int indent){
  int i;
  for(i=0; i<indent; i++){
    putchar('\t');
  }
}

int
main()
{
  int c;
  int indent=0;
  
  while ((c=getchar()) != EOF) {
    switch (etat) {
    case ETAT_DBT_LIGNE:
      switch (c) {
      case ' ':
      case '\t':

	break;
      default:
	indentation(indent);
	putchar(c);
	etat = ETAT_NORMAL;
	break;
      }
      break;
    case ETAT_NORMAL:
      switch (c) {
      case '{':
	putchar('\n');
	indentation(indent);
	putchar('{');
	putchar('\n');
	indent++;
	etat=ETAT_DBT_LIGNE;
	break;
      case '}':
	putchar('\n');
	indentation(indent);
	putchar('}');
	putchar('\n');
	indent--;
	etat=ETAT_DBT_LIGNE;
      case '\n':
	putchar('\n');
	etat=ETAT_DBT_LIGNE;
	break;
      default :
	putchar(c);
	break;
      }
    }
  }
  exit(EXIT_SUCCESS);
}
