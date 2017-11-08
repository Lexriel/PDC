#include <stdio.h>

int
main (void)
{ 
  char c;
  int cptacc = 0, cptif=0, i, verrou=0;
  /*
    verrou=-1 : Programme terminé
    verrou=0 : getchar() pas encore effectue
    verrou=1 : getchar() effectue

    cptacc : compte le nombre d'accolade sur l'ensemble du programme

    cptif : compte le nombre de parenthèse suivant un if
  */
  while (verrou != -1)
    {
      if(verrou == 0)
	{
	  c=getchar();
	  verrou=1;
	}
      switch (c)
	{
	case EOF :
	  {
	    verrou=-1;
	    break;
	  }
	case ';' :
	  {
	    putchar (c);
	    verrou=0;
	    putchar ('\n');
	    break;
	  }

	case '{':
	  {
	    putchar ('\n');
	    for (i = 0; i < cptacc; i++)
	      putchar ('\t');
	    putchar (c);
	    verrou=0;
	    putchar ('\n');
	    cptacc++;
	    break;
	  }
	case '}':
	  {
	    for (i = 0; i < cptacc - 1; i++)
	      putchar ('\t');
	    putchar (c);
	    verrou=0;
	    putchar ('\n');
	    cptacc--;
	    break;
	  }
	case '\n':
	  {
	    putchar ('\n');
	    verrou=0;
	    break;
	  }
	  /* traitement du else */
	case 'e':
	  {
	    putchar(c);
	    c=getchar();
	    verrou=1;
	    if (c=='l')
	      {
		putchar(c);
		c=getchar();
		if (c=='s')
		  {
		    putchar(c);
		    c=getchar();
		    if(c=='e')
		      {
			putchar(c);
			putchar('\n');
			verrou=0;
		      }
		  }
	      }
	    break;
	  }
	  /* traitement du if et du int */
	case 'i' :
	  {
	    putchar(c);
	    c=getchar();
	    verrou=1;
	    if(c=='f')
	      {
		putchar(c);
		c=getchar();
		if(c=='(')
		  {
		    cptif++;
		    putchar(c);
		  }
		while (cptif!=0)
		  {
		    c=getchar();
		    if(c=='(')
		      {
			cptif++;
			putchar(c);
		      }
		    else if(c==')')
		      {
			cptif--;
			putchar(c);
		      }
		    else
		      putchar(c);
		  }
		putchar('\n');
		verrou=0;
	      }
	    else if(c=='n')
	      {
		putchar(c);
		c=getchar();
		if(c=='t')
		  {
		    putchar(c);
		    verrou=0;
		    putchar(' ');
		  }
	      }
	    break;
	  }
	  /* traitement du char */
	case 'c' :
	  {
	    verrou=1;
	    putchar(c);
	    c=getchar();
	    if(c=='h')
	      {
		putchar(c);
		c=getchar();
		if(c=='a')
		  {
		    putchar(c);
		    c=getchar();
		    if(c=='r')
		      {
			putchar(c);
			verrou=0;
			putchar(' ');
		      }
		  }
	      }
	    break;
	  }
	default:
	  {
	    putchar (c);
	    verrou=0;
	    break;
	  }
	}
    }
  return 0;
}
