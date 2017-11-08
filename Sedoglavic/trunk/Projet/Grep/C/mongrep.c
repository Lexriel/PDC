#include "types.h"
#include "asa.h"
#include "automate.h"
#include "transitiontable.h"
#include "token.h"
#include <stdio.h>

#define MAXLINE 1024

int
main 
(int argc, char **argv)
{
  int i ;
  int match ;
  char line[MAXLINE] ;
  char c, *ptr ;
  NODE *next, *racine  ;
  /* 
     Construction of an abstract syntax tree associated to a regular
     expression encoded by the string argv[1]
  */
  if(argv[1])
    regularexpression = argv[1];
  else 
    {
      fprintf(stderr,"Usage: %s regexp < inputfile\n",*argv);
      return 1;
    }
  next_token ();
  racine = create_node( CONCAT,0,expression ()) ;
  racine->right = create_node(EMPTY,0,NULL) ;
#ifdef VERBOSE
  affiche_arbre(racine);
  printf("\n");
#endif

  construction_automate(racine);
  cleanasa(racine) ;
  
  do  
    {	
      /* load a line */
      i = 0 ;
      do  
 	{ 
 	  c = getchar() ; 

 	  line[i++]=c ; 

 	  if( c=='\n' 
	      || c==EOF ) 
	    break ; 
	  
 	} 
      while(1) ; 
      
      line[i] = 0 ;
      /* analyse this line */
      match = FALSE ;  
      for( i = 0 ; line[i] ; i++ )  
 	{  
  	  if(match)  
  	    break ;  
	 next = racine ; 
 	 ptr = line+i ; 
 	  do 
 	    { 
	      next = findnexttransition(next, *ptr) ; 

 	      if(!next) 
 		break ; 

 	      if( next->type == EMPTY ) 
 		{ 
 		  match = TRUE  ;
 		  break ; 
 		}
	      
	      ptr++ ;
 	      
 	    } 
 	  while(1) ; 
 	} 
      if(match) 
	 { 
 	  for(i = 0 ; line[i] ; i++) 
 	    putchar(line[i]) ; 
 	} 
       
       if( c == EOF ) 
	 break ; 
    } 
  while(1) ; 
  
  return 0;
}
