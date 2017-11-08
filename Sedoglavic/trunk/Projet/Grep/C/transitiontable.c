#include "types.h"
#include "erreur.h"
#include <stdlib.h>

static
transitiontable_t * 
create_transition_table_cell
(char letter, NODE * transition)
{
  transitiontable_t *res ;
  res = (transitiontable_t *)malloc(sizeof(transitiontable_t));
  res->letter = letter ;
  res->next = NULL ;
  res->transition = transition ; 
  return res ;
}

static
void
recursiveaddtotranstable
(
 transitiontable_t **table,
 transitiontable_t *cell
 )
{
if (!*table)
    {
      *table=cell ;
      return ;
    }
  
  if ((*table)->letter==cell->letter)
    {
      free(cell) ;
      return ;
    }

  if((*table)->letter>cell->letter)
    {
      cell->next = *table ;
      *table = cell ;
      return ;
    }
    
  recursiveaddtotranstable(
			   &((*table)->next),
			   cell
			   );
  return ;
}
  
void
addtotransitiontable
(
 transitiontable_t **table, 
 char letter,
 NODE *transition
 )
{
  transitiontable_t *res ;

  res = create_transition_table_cell(letter,transition) ;
  recursiveaddtotranstable(table,res) ;
  
  return ;
}

static
NODE *
recursivefindnexttransition
(
 transitiontable_t *table,
 char letter
 )
{
  if(!table)
    return NULL ;

  if(table->letter>letter)
    return NULL ;

  if(table->letter==letter)
      return table->transition ;

  return recursivefindnexttransition(
				     table->next,
				     letter
				     ) ;
}

NODE *
findnexttransition
(
 NODE *node,
 char letter
 )
{
  transitiontable_t *table ;

  if(!node)
    return NULL ;
  
  table = node->transitiontable ;

  return recursivefindnexttransition(
				     table,
				     letter
				     ) ;
}

NODE *
initialstate
(
 NODE * root,
 char letter
 )
{
  set_t *ptr ;
  if(!root)
    return NULL ;
  
  ptr=root->initial ;
  
  while(ptr)
    {
      switch(ptr->etiquette->type)
	{
	case EMPTY:
	case RANGE:
	case ALLBUT:
	case ANYLETTER:
	  return ptr->etiquette ; 
	case LETTER:
	  {
	    if(*ptr->etiquette->alphabet==letter)
	      return ptr->etiquette ;
	  } ; break ;
	default: exit(FORBIDENCASE);
	}

      ptr=ptr->next ;
    }
  
  return NULL ;
}
