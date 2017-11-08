%{
#include <stdio.h>
#include <string.h>
 
void 
yyerror
(const char *str)
{
        fprintf(stderr,"error: %s\n",str);
}
 
int 
yywrap
(void)
{
        return 1;
} 
  
int
main
(void)
{
        yyparse();
} 

%}

%token SPACE COMMENTSTART COMMENTSTOP WORD NEWLINE
%%

code:
	|
	comments
	|
	statement
	;

comments:
	COMMENTSTART commentstatements COMMENTSTOP
	;

commentstatements: 
	| 
	statement 
	| 
	comments
	;

statement: 
	| WORD | SPACE | NEWLINE
	;
	



