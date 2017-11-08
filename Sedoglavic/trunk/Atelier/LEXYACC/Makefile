
essai: lex.yy.c y.tab.c 
	gcc -o essai lex.yy.c y.tab.c
lex.yy.c: essai.flex
	flex essai.flex
y.tab.c: essai.y
	yacc -d essai.y
	
