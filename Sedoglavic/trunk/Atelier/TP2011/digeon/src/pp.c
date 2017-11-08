/* TP2 PDC */
/* Benjamin Digeon */

#include<stdio.h>
#include<stdlib.h>;

void 
indent
(int nbr)
{
	int i;
	for(i=0;i<nbr;i++)
	{
		putchar('\t');
	}
}

int 
main
(void)
{
    char c,tmp;
    int debut_ligne = 1;
    int indent_courante = 0;
	int mode_commentaire = 0;
	int mode_chaines = 0;
	int mode_directive = 0;
	
    while((c=getchar())!=EOF)
    {
    	if(mode_chaines == 1)
    	{
    		if(c=='"')
    		{
    			putchar(c);
    			mode_chaines=0;	
    		}
    		else putchar(c);	
    	}
    	else if(mode_directive == 1)
    	{
    		if(c=='\n')
    		{
    			putchar(c);
    			mode_directive=0;
    			debut_ligne=1;
    		}
    		else putchar(c);
    	}
    	else
    	{
	    	switch(c)
	    	{
	    		case '{':
	    			debut_ligne = 0;
	    			if(mode_commentaire == 1)
	    			{		
	    				putchar(c);
	    			}
	    			else
	    			{
	    				putchar('\n');
	    				indent(indent_courante);
	    				putchar(c);
	    				putchar('\n');
	    				indent_courante++;
	    				debut_ligne=1;
	    			}	
	    			break;
	    		case '}':
	    			debut_ligne = 0;
	    			if(mode_commentaire == 1)
	    			{		
	    				putchar(c);
	    			}
	    			else
	    			{
	    				indent_courante--;
	    				putchar('\n');
	    				indent(indent_courante);
	    				putchar(c);
	    				putchar('\n');
	    			}
	    			break;
	    		case '\n':
	    			if(mode_commentaire == 1)
	    			{
	    				putchar('*');
	    				putchar('/');
	    				putchar(c);
	    				indent(indent_courante);
	    				putchar('/');
	    				putchar('*');
	    			}
	    			else
	    			{
	    				putchar(c);
	    			}
	    			debut_ligne = 1;
	    			break;
				case '/':
					debut_ligne = 0;
					if((tmp=getchar())=='*')
					{
						mode_commentaire = 1;
						putchar('\n');
						indent(indent_courante);
						putchar(c);
						putchar(tmp);
					}
					else
					{
						putchar(c);
						putchar(tmp);
					}
					break;
				case '*':
					debut_ligne = 0;
					if((tmp=getchar())=='/')
					{
						mode_commentaire = 0;
						putchar(c);	
						putchar(tmp);
					}
					else
					{
						putchar(c);
						putchar(tmp);	
					}
					break;
				case ' ':
					if(debut_ligne == 0)
					{
						putchar(c);
					}
					break;
				case '\t':
					if(debut_ligne == 0)
					{
						putchar(c);
					}
					break;
				case '"':
					putchar(c);
					mode_chaines=1;
					break;
				case '#':
					if(debut_ligne == 1)
					{
						putchar(c);
						mode_directive = 1;
					}
					else
					{
						putchar(c);
					}
					break;
	    		default:
	    			if(debut_ligne == 1)
	    			{
	    				indent(indent_courante);	
	    			}
	    			debut_ligne = 0;
	    			putchar(c);
	    			break;
	    	}
    	}
    }
    if(mode_commentaire == 1)
    {
    	fprintf(stderr,"Commentaire mal fermé");
    }	
    return(EXIT_SUCCESS);
}
