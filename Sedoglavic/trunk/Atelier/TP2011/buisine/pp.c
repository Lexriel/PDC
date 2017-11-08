#include <stdio.h>
#include <stdlib.h>

int
main
(void)
{
  int nbrAcc;
  int nbrPar;  
  int cpt;
  char c;
  int prob;
  enum {ETAT_COMM,ETAT_NORMAL,ETAT_DIESE,ETAT_COMM_ENT,ETAT_COMM_SOR,ETAT_LIGNE} etat = ETAT_LIGNE;
  
  prob = nbrAcc = nbrPar = 0;

  while ((c = getchar()) != EOF){
    switch(etat){
    case ETAT_LIGNE:
      switch(c){
      case '#':
	etat= ETAT_DIESE;
	break;
      case '\n':
      case ' ':	break;
      case '\t':break;
      case '/':
	etat = ETAT_COMM_ENT;
	break;
      
      default:	
	for(cpt=0;cpt<nbrAcc;cpt++)
	  putchar('\t');
	etat = ETAT_NORMAL;
      }
      break;
    case  ETAT_NORMAL:
      switch (c){ 
      case '#':	
	etat= ETAT_DIESE;
	break;
	
      case '/': 
	etat = ETAT_COMM_ENT;   
	break;
      case '}':
	
	nbrAcc--;
	putchar ('\n');
	for(cpt=0;cpt<nbrAcc;cpt++)
	  putchar('\t');
	if (nbrAcc < 0) 
	  prob = 1; 
	putchar ('}');
	putchar ('\n');
	etat = ETAT_LIGNE;
	break;
	
      case '{':
	putchar ('\n');
	for(cpt=0;cpt<nbrAcc;cpt++)
	  putchar('\t');
      	nbrAcc++;
	putchar ('{');
	putchar ('\n');

	etat = ETAT_LIGNE;
	break;
	
      case '(':
	
	nbrPar++;
	break;
	
      case ')':
	
	nbrPar--;
	if(nbrPar<0)
	  prob = 1;
	break;
	
      case '\n' :
	
	putchar ('\n');
	
	etat = ETAT_LIGNE;
	break;
	
      case ';':
	
	  putchar(';');
	  putchar('\n');
	  etat = ETAT_LIGNE;
	
      }

    
	break;

    case  ETAT_COMM_ENT: 
      switch (c){
      case '*' :etat = ETAT_COMM; putchar('\n');  break;

      default :etat = ETAT_NORMAL;  break;
      }
      putchar('/');
      break;

    case ETAT_COMM_SOR:
        switch(c){
	case '/' : 
	  
	 
	  putchar('/');
	  putchar('\n');
	  etat = ETAT_LIGNE;
	  
	  break;
	  
	default:
	  etat = ETAT_NORMAL;
	}
	break;
  
    case ETAT_COMM: 
      switch (c){
      case '*' :
	etat = ETAT_COMM_SOR;
	break;
      case '\n':
	putchar('*');
	putchar('/');
	putchar('\n');
	putchar('/');
	putchar('*');
	
      }
      break;
	

    
    
    case ETAT_DIESE:
      switch (c){
      case '>' : 
	putchar(c);
	putchar('\n');
	etat= ETAT_LIGNE;
      }
      break;
    }
    switch(etat){
    case ETAT_COMM_ENT:
    case ETAT_LIGNE:
      break;       
    default:
      putchar(c);
    }
    /*printf("\n car: %c etat: %d \n",c ,etat);*/  

  }
  if (nbrPar != 0 || nbrAcc!= 0 || prob)
    exit(EXIT_SUCCESS);
  return 0;
}
  


	
	
	

	
	
