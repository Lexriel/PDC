/* BERTON Edouard */

#include <stdio.h>
#include <stdlib.h>

void
indenter
(int n)
{
  int i;
  for(i = 0; i < n; i++) {
    putchar(' ');
    putchar(' ');
    putchar(' ');
    putchar(' ');
  }
}

int
main
()
{
  char c;
  int indent = 0;
  
  enum {
    ETAT_DBT_LIGNE,
    ETAT_NORMAL,
    ETAT_CROISILLON,
    ETAT_COM_OUVRANT,
    ETAT_COM_FERMANT,
    ETAT_COMMENTAIRE
  } etat = ETAT_DBT_LIGNE;
  
  while((c = getchar()) != EOF)
    {
      switch (etat)
	{
	case ETAT_DBT_LIGNE:
	  switch (c)
	    {
	    case '\n':
	      putchar('\n');
	      break;
	    case ' ':
	    case '\t':
	      break;
	    case '#':
	      putchar('#');
	      etat = ETAT_CROISILLON;
	      break;
	    case '{':
	      indenter(indent);
	      putchar('{');
	      putchar('\n');
	      indent++;
	      etat=ETAT_DBT_LIGNE;
	      break;
	    case '}':
	      indent--;
	      indenter(indent);
	      putchar('}');
	      etat=ETAT_DBT_LIGNE;
	      break;
	    default:
	      indenter(indent);
	      putchar(c);
	      etat = ETAT_NORMAL;
	      break;
	    }
	  break;
			
	case ETAT_NORMAL:
	  switch (c)
	    {
	    case '\n': 
	      putchar('\n');
	      etat = ETAT_DBT_LIGNE;
	      break;
	    case '{':
	      putchar('\n');
	      indenter(indent);
	      putchar('{');
	      putchar('\n');
	      indent++;
	      etat=ETAT_DBT_LIGNE;
	      break;
	    case '}':
	      putchar('\n');
	      indent--;
	      indenter(indent);
	      putchar('}');
	      etat=ETAT_DBT_LIGNE;
	      break;
	    case '/':
	      etat=ETAT_COM_OUVRANT;
	      break;
	    default :  
	      putchar(c);
	      break;
	    }
	  break;
	case ETAT_CROISILLON:
	  switch (c)
	    {
	    case '\n': 
	      putchar('\n');
	      etat = ETAT_DBT_LIGNE;
	      break;
	    default :
	      putchar(c);
	      break;
	    }
	  break;

	case ETAT_COM_OUVRANT:
	  switch (c)
	    {
	    case '*': 
	      putchar('\n');
	      indenter(indent);
	      putchar('/');
	      putchar('*');
	      etat = ETAT_COMMENTAIRE;
	      break;
	    default :
	      putchar('/');
	      putchar(c);
	      etat = ETAT_NORMAL;
	      break;
	    }
	  break;

	case ETAT_COMMENTAIRE:
	  switch (c)
	    {
	    case '*': 
	      etat = ETAT_COM_FERMANT;
	      break;
	    case '\n':
	      putchar('*');
	      putchar('/');
	      putchar('\n');
	      indenter(indent);
	      putchar('/');
	      putchar('*');
	      break;
	    default :
	      putchar(c);
	      break;
	    }
	  break;

	case ETAT_COM_FERMANT:
	  switch (c)
	    {
	    case '/':
	      putchar('*');
	      putchar('/');
	      etat = ETAT_NORMAL;
	      break;
	    default :
	      putchar('*');
	      putchar(c);
	      etat = ETAT_COMMENTAIRE;
	      break;
	    }
	  break;

	}
    }
  if(!indent)
    return (EXIT_SUCCESS);
  else
    return (EXIT_FAILURE);
}
