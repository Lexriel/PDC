#include <stdlib.h>
#include <stdio.h>
#include "types.h"
#include "erreur.h"
#include "set.h"
#include "transitiontable.h"
#include "mstring.h"

static
void
preliminaire
(NODE *node)
{
  set_t *i, *ptr ;

  if (node->left)
    preliminaire(node->left);
  if (node->right)
    preliminaire(node->right);

  switch(node->type)
    {
    case EMPTY:
      {
	free(node->alphabet);
	node->alphabet = (unsigned char *) "\0" ;
	node->final = node->initial = create_set(node) ;
	node->nul = TRUE ;
      } ; break ;
    case ANYLETTER: 
    case ALLBUT:
    case RANGE:
    case LETTER:
      {
	/* alphabet was already defined during the creation of these
	   node */
	node->final = node->initial = create_set(node) ;
	node->nul = FALSE ;
      } ; break ;
    case ALTER:
      {
	node->alphabet = merge(
			       node->left->alphabet,
			       node->right->alphabet
			       );
	node->initial=cup(
			  node->left->initial,
			  node->right->initial
			  );
	node->final=cup(
			node->left->final,
			node->right->final
			);

	node->nul = (node->left)->nul
	  || (node->right)->nul ;
      } ; break ; 
    case CONCAT:
      {
	node->alphabet = merge(
			       node->left->alphabet,
			       node->right->alphabet
			       );
	/* construction of initial states */
	if (node->left->nul)
	  node->initial=cup(
	  		    node->left->initial,
			    node->right->initial
			    );
	else 
	  node->initial = copy_set(node->left->initial) ;
	
	/* construction of final states */
	if (node->right->nul) 
	  node->final=cup(
	                  node->left->final,
			  node->right->final
			  );
	else 
	  node->final = copy_set(node->right->final);
	
	i = node->left->final ;
	while(i)
	  {
	    ptr = node->right->initial ;
	    while(ptr)
	      {
		addtoset(
			 &(i->etiquette->nextstates),
			 ptr->etiquette 
			 ) ;
		
		ptr= ptr->next ;
	      }
	    i = i->next ;
	  }
	node->nul = node->left->nul
	  && node->right->nul ;
      } ; break ; 

    case REPET:
      {
	node->alphabet = node->left->alphabet ;
	node->final = copy_set(node->left->final) ;
	node->initial = node->left->initial ;
	node->nul = TRUE ;
	i=node->final ;
	while(i)
	  { /* on prend les \'el\'ements de initial(n) */
	    ptr = node->initial ;
	    while(ptr)
	      {
		/* insert them in nextstates(i) */
		addtoset(
			 &(i->etiquette->nextstates),
			 ptr->etiquette
			 );
		ptr=ptr->next ;
	      }
	    i=i->next ;
	  }
      } ; break ;
    }
  return ;
}

void
construction_automate
(NODE *node)
{
  unsigned char c ;
  unsigned char *a ; 
  set_t * Detat, * ptr, * ptr2 ;

  Detat = NULL ;
  preliminaire(node);

  /* Add initial(root) to DEtat */
  ptr=node->initial ;
  if(!ptr)
    {
      fprintf(stderr,"no initial state in initial(root)");
      exit(NOINITIALROOT);
    }
   
  while(ptr)
    {
    for(a=ptr->etiquette->alphabet ; *a ; a++) 
	addtotransitiontable(
			     &(node->transitiontable),
			     *a,
			     ptr->etiquette
			     ) ;
      recursiveaddtoset(
			&Detat,
			copy_set(ptr)
			);
      ptr = ptr->next ;
    }

  while((ptr=nextunmarkedstate(Detat)))
    {
      ptr->marque = MARQUER ;
      ptr2=ptr->etiquette->nextstates;
      while(ptr2)
	{
	  recursiveaddtoset(
			    &Detat,
			    copy_set(ptr2)
			    ) ;
        switch(ptr2->etiquette->type)
	{
	case EMPTY:
	{
	for(c=255;c;c--)
		addtotransitiontable(
				     &(ptr->etiquette->transitiontable),
				      c ,
				     ptr2->etiquette
				     ) ;
	} ; break ;
	default :
	      for(a=ptr2->etiquette->alphabet ; *a ; a++) 
		addtotransitiontable(
				     &(ptr->etiquette->transitiontable),
				     *a,
				     ptr2->etiquette
				     ) ;
	};	
	  ptr2=ptr2->next ;	      
	}
    }
  
  return ;

}