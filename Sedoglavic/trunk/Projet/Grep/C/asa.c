#include "token.h"
#include "types.h"
#include "set.h"
#include <stdio.h>
#include <stdlib.h>

NODE *create_node (TYPENODE, char, NODE *);
NODE *expression (void);
NODE *expression_concatenation (void);
static NODE *expression_repetition (void);
static NODE *expression_simple (void);
static NODE *range (void);
static void parse_error (char *);

static
void
parse_error 
(char *s)
{
  fprintf (stderr, "Error parsing character %c in %s\n", 
	   token_value, s);
  exit (1);
}


NODE *
create_node 
(TYPENODE nodetype, char value, NODE * left)
/* the right node is handled after the call of this function
 * i.e. while the string is parsed, left child are constructed 
 * then right one are considered
 */
{
  NODE *node;
  node = (NODE *) malloc (sizeof (NODE));
  node->type = nodetype;
  node->alphabet = (unsigned char *) malloc(2*sizeof(char));
  (node->alphabet)[0] = value;
  (node->alphabet)[1] = '\0';
  node->left = left;
  node->right = NULL ;
  node->nul = 0 ;
  node->initial =  node->final =  node->nextstates= NULL ;
  return node;
}

NODE *
expression
(void)
{
  NODE *child, *node;
  child = expression_concatenation ();
  if (token == END)
    return child;
  if (child == NULL)
    parse_error ("expression");
  if (token == PIPE)
    {
      node = create_node (ALTER, 0, child);
      next_token ();
      if ((node->right = expression ()) == NULL)
	parse_error ("alternative expression");
      return node;
    }
  else
    return child;
  return NULL;
}


NODE *
expression_concatenation 
(void)
{
  NODE *child, *node;
  child = expression_repetition ();
  if (token == END)
    return child;
  if (child == NULL)
    parse_error ("concatenation");
  if ((token == LBRACE) || (token == CAR) || (token == LBRACKET))
    {
      node = create_node (CONCAT, 0, child);
      if ((node->right = expression_concatenation ()) == NULL)
	parse_error ("concatenation");
      return node;
    }
  else
    return child;
  return NULL;
}

static
NODE *
expression_repetition 
(void)
{
  NODE *child, *node;
  child = expression_simple ();
  if (token == END)
    return child;
  if (child == NULL)
    parse_error ("simple expression");
  if (token == STAR)
    {
      node = create_node (REPET,0, child);
      next_token ();
      return node;
    }
  else
    return child;
  return NULL;
}

static
NODE *
expression_simple 
(void)
{
  int cmptr ;
  NODE *node;
  switch (token)
    {
    case LBRACE:
      {
	next_token ();
	if ((node = expression ()) == NULL)
	  parse_error ("braces expression");
	if (token != RBRACE)
	  parse_error ("watching for an )");
	next_token ();
	return node;
      };
    case LBRACKET:
      {
	next_token ();
	if ((node = range ()) == (NODE *) NULL)
	  parse_error ("range expression");
	if (token != RBRACKET)
	  parse_error ("watching for an ]");
	next_token ();
	return node;
      };
    case DOT:
      {
	node = create_node(ANYLETTER,token_value,NULL);
	free(node->alphabet);
	node->alphabet = (unsigned char *) malloc(256*sizeof(char));
	for(cmptr=1;cmptr<256;cmptr++)
	  node->alphabet[cmptr-1] = (char) cmptr ;
	next_token() ;
	return node ;
      } ;
    case CAR: 
      {
	node = create_node(LETTER,token_value,NULL);
	next_token () ;
	return node ;
      };
    case END: return NULL;
    default: parse_error ("litteral");
    }
  return NULL;
}

static
NODE *
range 
(void)
{
  NODE *node;
  int i, nbletter;
  char predtokenvalue;
  unsigned char *set, *ptr ;

  set = (unsigned char *) malloc (256 * sizeof (char));

  for (i = 0; i < 256; i++)
    set[i] = FALSE;
  /* set[i] encode a boolean */
  nbletter = 0 ;

  node = (NODE *) malloc (sizeof (NODE));
  if (token_value == '^')
    {
      node->type = ALLBUT;
      token_value = nextchar ();
    }
  else
    node->type = RANGE;
  
  node->left = node->right = NULL;

  if (token_value == '-')
    parse_error ("range");
  if (token_value == RBRACKET)
    {
      predtokenvalue = ']';
      set[(int) token_value] = TRUE;
      nbletter++ ;
      token_value = nextchar ();
    }

  while ((token_value != ']')
	 && (token_value != 0))
    {
      if (token_value != '-')
	{
	set[(int) token_value] = TRUE;
	nbletter++ ;
	}
      else
	{
	  token_value = nextchar ();
	  if (token_value == ']')
	    {
	      set[(int) token_value] = TRUE;
	      nbletter++ ;
	    }
	  else
	    for (i=predtokenvalue; i <= token_value; i++)
	      {
		set[i] = TRUE;
		nbletter++ ;
	      }
	}
      predtokenvalue = token_value;
      token_value = nextchar ();
    }
  if (token_value == '\0')
    parse_error ("range expression");
  token = RBRACKET;


  if(node->type==ALLBUT)
    {
      for(i=1;i<256;i++)    
	set[i] = !set[i] ;
      nbletter = 255-nbletter ;
    }

  free(node->alphabet) ; /* free previously allocated memory */
  ptr = node->alphabet = (unsigned char *) malloc((nbletter+1)*sizeof(char)) ;

  for(i=1;i<256;i++)
    if(set[i])
      {
	*ptr = (char) i ;
	ptr++ ;
      }
  *ptr = 0 ;

  return node;
}

void
affiche_arbre
(NODE *node)
{
  switch(node->type)
    {
    case ALLBUT:
    case RANGE:
      {
	printf("[");
	printf("%s",node->alphabet) ;
	printf("]");
      } ; break ;
    case LETTER: printf("%c",node->alphabet[0]); break;
    case ALTER: 
      {
	printf("(");
	affiche_arbre(node->left);
	printf("|");
	affiche_arbre(node->right);
	printf(")");
      } ; break ;
    case REPET:
      {
	affiche_arbre(node->left);
	printf("*") ;
      } ; break ;
    case CONCAT:
      {
	affiche_arbre(node->left);
	affiche_arbre(node->right);
      }
    case EMPTY:  break ;
    default : printf("Type inconnu") ; exit(1) ; break ;
    }
}

void
cleanasa
(
 NODE *node
 )
{
  if(!node)
    return ;
 
  cleanasa(node->left) ;
  cleanasa(node->right) ;

  /* as we are using root->initial,
   * we do not delete this set
   */
  delete_set(node->final) ;
  delete_set(node->nextstates) ;
  node->final=node->nextstates=NULL ;
  return ;
}
