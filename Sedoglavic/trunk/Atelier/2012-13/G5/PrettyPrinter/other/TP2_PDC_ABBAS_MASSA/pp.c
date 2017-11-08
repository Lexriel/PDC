#include<stdio.h>
#include<stdlib.h>
#define TABULATION '\t'

int
pp()
{
  int nbrIndent,i,nbrAcolade,comBienFerme, pbAcolade;
  char c;
  enum{ETAT_DEBUT_LIGNE, ETAT_NORMAL, ETAT_DEBUT_COM_EN_DEBUT_LIGNE, ETAT_DEBUT_COM_NORMAL, ETAT_COMMENTAIRE, ETAT_FIN_COM, ETAT_CHAINE_CARACTERE} etat = ETAT_DEBUT_LIGNE;
  nbrIndent = 0;
  nbrAcolade = 0;
  comBienFerme = 1;
  pbAcolade = 0;
  
  while((c=getchar()) != EOF){
    switch (etat) {
    case ETAT_DEBUT_LIGNE :
      switch (c) {
      case ' ':break;
      case '\t':break;
      case '\n':break;
      case '{' :
	putchar('\n');
	for(i=0;i<nbrIndent;i++){putchar(TABULATION);}
	putchar('{');
	putchar('\n');
	nbrIndent++;
	nbrAcolade++; break;
      case '}' :
	putchar('\n');
	nbrIndent--;
	for(i=0;i<nbrIndent;i++){putchar(TABULATION);}
	putchar('}');
	putchar('\n');
	nbrAcolade--; break;
      case '/':
	etat = ETAT_DEBUT_COM_EN_DEBUT_LIGNE; break;
      case '"':
	putchar('"');
	etat = ETAT_CHAINE_CARACTERE;
      default:
	for(i=0;i<nbrIndent;i++){putchar(TABULATION);}
	putchar(c);
	etat = ETAT_NORMAL; break;
      }
      break;
    case ETAT_NORMAL :
      switch (c){
      case '\n':
	putchar('\n');
	etat = ETAT_DEBUT_LIGNE; break;
      case '{':
	putchar('\n');
	for(i=0;i<nbrIndent;i++){putchar(TABULATION);}
	putchar('{');
	putchar('\n');
	nbrIndent++;
	nbrAcolade++;
	etat = ETAT_DEBUT_LIGNE; break;
      case '/':
	etat = ETAT_DEBUT_COM_NORMAL; break;
      case '}':
	putchar('\n');
	nbrIndent--;
	for(i=0;i<nbrIndent;i++){putchar(TABULATION);}
	putchar('}');
	putchar('\n');
	nbrAcolade--;
	etat = ETAT_DEBUT_LIGNE; break;
      case ';':
	putchar(c);
	putchar('\n');
	etat = ETAT_DEBUT_LIGNE; break;
      case '"' :
	etat = ETAT_CHAINE_CARACTERE;
      default:
	putchar(c); break;
      }
      break;
    case ETAT_DEBUT_COM_EN_DEBUT_LIGNE :
      switch (c) {
      case '*' :
	comBienFerme = 0;
	etat = ETAT_COMMENTAIRE;
	putchar('\n');
	for(i=0;i<nbrIndent;i++){putchar(TABULATION);}
	putchar('/');
	putchar('*'); break;
      default :
	etat = ETAT_NORMAL;
	for(i=0;i<nbrIndent;i++){putchar(TABULATION);}
	putchar('/');
	putchar(c); break;
      }
      break;
    case ETAT_DEBUT_COM_NORMAL:
      switch (c) {
      case '*' :
	comBienFerme = 0;
	etat = ETAT_COMMENTAIRE;
	putchar('\n');
	for(i=0;i<nbrIndent;i++){putchar(TABULATION);}
	putchar('/');
	putchar('*'); break;
      default :
	etat = ETAT_NORMAL;
	putchar('/');
	putchar(c); break;
      }
      break;

    case ETAT_COMMENTAIRE:
      switch (c){
      case '*':
	putchar('*');
	etat = ETAT_FIN_COM; break;
      case '\n' :
	putchar('*');
	putchar('/');
	putchar('\n');
	for(i=0;i<nbrIndent;i++){putchar(TABULATION);}
	putchar('/');
	putchar('*'); 
	while(c == '\t' || c == ' ' || c =='\n'){c = getchar();}
	putchar(' '); 
	putchar(c); break;
      default :
	putchar(c); break;
      }
      break;
    case ETAT_FIN_COM :
      switch(c) {
      case '/':
	comBienFerme = 1;
	putchar('/');
	putchar('\n');
	etat = ETAT_DEBUT_LIGNE; break;
      default :
	putchar(c);
	etat = ETAT_COMMENTAIRE; break;
      }
      break;
    case ETAT_CHAINE_CARACTERE :
      switch(c){
      case '"' :
	putchar('"');
	etat = ETAT_NORMAL; break;
      default :
	putchar(c);break;
      }
      break;
    }
    if(nbrAcolade < 0){
      pbAcolade = 1 ;
    }
  }
  if(!comBienFerme){
    fprintf(stderr ,"%s error\n", "Commentaire mal ferme");
    exit(EXIT_FAILURE);
  } 
  if (pbAcolade || nbrAcolade != 0) {
    fprintf(stderr, "%s error\n", "Acolade non valide");
    exit(EXIT_FAILURE);
  }
  exit(EXIT_SUCCESS);
}

    
