#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"readl.h"
#include"tools.h"
#include"automate.h"

int main(int argc, char **argv){
	char chaine[MAXLINE], *tmp, *t;
	int test, i;
	char_list **deb;
	automate *aut;
	
	*deb = cons_lc(argv[1][0]);
	for(i=0; i<strlen(argv[1]); i++)
		ajouter_lc(*deb, cons_lc(argv[1][i]));
		
	/*on cree un nouvel automate avec le mot à tester */
	aut = automate_new(0,cons_lc(argv[1][strlen(argv[1])]),deb);
	
	/*si le mot est accepter alors chercher s'il se touve dans le texte */
	if(accepte(argv[1], aut) != 0){	
	
		test = readl(chaine);
		tmp = chaine;
	

		for(; *tmp; tmp++){
		t = strstr(tmp,argv[1]);
		if(t != NULL){
			fprintf(stdout, "%s", chaine);
			break;
		}
		}
		
	}


	return 0;
}
