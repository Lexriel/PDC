#include "types.h"
#include "erreur.h"
#include "transitiontable.h" 
#include "set.h"
#include <stdio.h>
#include <stdlib.h>



set_t *
create_set
(NODE *etiquette)
{
  set_t *res ;
  res = (set_t *) malloc(sizeof(set_t));
  res->etiquette = etiquette ;
  res->marque = NONMARQUER ;
  res->next = NULL ;
  return res ;
}

set_t *
copy_set
(set_t *set)
{
  return cup(set,NULL) ;
}

void
delete_set
(
 set_t *set
 )
{
  if(set)
  {		
    delete_set(set->next);
    free(set) ;
  }
}


int 
isempty
(set_t *set)
{
  return set?FALSE:TRUE ;
}

int 
recursiveaddtoset
(
 set_t **root,
 set_t *set
 )
{
  if(!(*root))
    {
      *root=set ;
      return TRUE ;
    }
  else
    {
      if((*root)->etiquette==set->etiquette)
	{
	  /* an cell already present is not inserted */
	  free(set) ;
	  return FALSE ; 
	}
      if((*root)->etiquette>set->etiquette)
	/* insert cell */
	{
	  set->next = *root ;
	  *root = set ;
	  return TRUE ;
	}
      else /* check linked list further */
	return recursiveaddtoset(&((*root)->next),set) ;
    }
  exit(FORBIDENCASE) ;
  return FALSE ;
}

set_t *
cup
(set_t *A, set_t *B)
{
  set_t *set ;
  
  if (A==NULL)
    {
      if (B==NULL)
	set = NULL ;
      else
	{
	  set = create_set(B->etiquette) ;
	  set->next = cup(A,B->next) ;
	}
    }
  else
    {
      if (B==NULL)
	{
	  set = create_set(A->etiquette) ;
	  set->next = cup(A->next,B) ;
	}
      else
	{
	  if (A->etiquette==B->etiquette)
	    {
	      set = create_set(A->etiquette) ;
	      set->next = cup(A->next,B->next) ;
	    }
	  else if (A->etiquette>B->etiquette)
	    {
	      set = create_set(B->etiquette) ;
	      set ->next = cup(A,B->next) ;
	    }
	  else 
	    {
	      set = create_set(A->etiquette) ;
	      set ->next = cup(A->next,B) ;
	    }
	}
    }
  return set ;
}

int 
addtoset
(set_t **root,NODE *label)
{
  return recursiveaddtoset(
			   root,
			   create_set(label)
			   );
}

set_t *
nextunmarkedstate
(
 set_t *set
 )
{
  while(set)
    {
      if(set->marque==NONMARQUER)
	  return set ;
      set = set->next ;
    }
  
  /* if there is no unmarked set, return null */
  return NULL ;
}
