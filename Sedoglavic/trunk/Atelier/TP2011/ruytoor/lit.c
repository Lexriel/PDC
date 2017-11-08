#include <stdio.h>

/* lit <pp.c 1>test 2>erreur*/

char clean(char c,char pc,char ac);
void addtab(int nbtab,char ac);

int main(void){
  
  char c;
  char pc;
  char ac;
  int nbtab;
 
  nbtab=0;
  c=getchar();
  while((ac=getchar())!=EOF){ 
    while(!(c=clean(c,pc,ac)))
      {
	c=ac;
	if((ac=getchar())==EOF)
	  return 0;
      }
             

    switch(c){

    case '\n': putchar(c);
      if(ac!='}')
	addtab(nbtab,ac);
      break;
      
    case '}':nbtab--;addtab(nbtab,ac);break;

    case '{':nbtab++;
      if (pc!='\n')
	{
	  putchar('\n');
	  addtab(nbtab-1,ac);
	}break;

    case '(':putchar(' ');break;
      
    case '=':putchar(' ');putchar(c);
      if(ac!=' '&&ac!='(')
	putchar(' ');
      break;
    }
    
    /* pour le int'\n'NomDeMethode (*) */
    if(nbtab==0){
      if(c==' '){
	putchar('\n');
	c='\n'; /* triche pour ne pas afficher le ' ' (zap le c!='\n'*/
      }
    }
    
    if((c!='\n') && (c!='='))
      putchar(c);
    pc=c;
    c=ac;
    
  }
  
  return 0;
}



void addtab(int nbtab,char ac){
  int i;
  for(i=0;i<nbtab;i++)
    putchar('\t');
  /* si vous n'aimez pas la taille de la tabulation on peut la change ici */
}


/* enleve les ' ' et '\n' en trop */
char clean(char c,char cp,char ac){

  if(c=='\n' && cp==c){
    return (char)0; 
  }
  if(c==' ' && (c==ac || cp=='\n' || ac==';' || ac=='(' || ac=='=' || cp=='=')){
    return (char)0; 
  }
  
  return c;
}
