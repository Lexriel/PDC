#include "list.h"

#include <stdlib.h>


typedef unsigned char uchar;


/*
  delete a link [l] and its value with [free_value] function
  - 0 : OK
  - -1 : link does not exists
*/
int
deleteLinks (link_t *l, void(*free_value)(void *ptr));

















list_t
newList (int value_size)
{
  return newListFreeFun (value_size,free);
}


list_t
newListFreeFun (int value_size, void(*free_value)(void *ptr))
{
  list_t tmp;
  /* if the value size is not correct */
  if (value_size <= 0)
    return NULL;
  /* alloc list */
  tmp = (list_t) malloc (sizeof(struct list_m));
  /* check alloc */
  if (!tmp) exit(1);
  /* init vars */
  tmp->head = NULL;
  tmp->value_size = value_size;
  tmp->free_value = free_value;
  return tmp;
}

int
isEmptyList (list_t l)
{
  /* if list does not exists */
  if (!l)
    return -1;
  /* if list not empty */
  if (l->head)
    return 0;
  /* the list is empty */
  return 1;
}

void
clearList (void *list)
{
  deleteList ((list_t*)list);
}

int
deleteList (list_t *l)
{
  /* if list does not exists */
  if (!(*l) )
    return -1;
  /* delete all links */
  deleteLinks (&((*l)->head), (*l)->free_value);
  /* free list */
  free (*l);
  (*l) = NULL;
  return 0;
}

int
deleteLinks (link_t *l, void(*free_value)(void *ptr))
{
  /* if links does not exists */
  if (!(*l))
    return -1;
  /* delete next links */
  deleteLinks (&((*l)->next),free_value);
  /* free link's value */
  free_value ((*l)->value);
  /* free this link */
  free ( *l );
  (*l) = NULL;
  return 0;
}

listiterator_t
getListIterator (list_t l)
{
  listiterator_t i;
  /* if the list does not exists */
  if (!l)
    return NULL;
  /* if the list is empty */
  if (!l->head)
    return NULL;
  i = (listiterator_t) l->head;
  return i;
}

int
addValueList (list_t l, void *value)
{
  link_t link;
  /* if list does not exists */
  if (!l)
    return -1;
  /* if list not empty */
  if (l->head)
    {
      /* move to the end of the list */
      link = l->head;
      while (link->next)
        link = link->next;
      link->next = (link_t) malloc (sizeof(struct link_m));
      /* check alloc */
      if (!link->next) exit(1);
      link = link->next;
    }
  /* if empty */
  else
    {
      /* create a new link */
      l->head = (link_t) malloc (sizeof(struct link_m));
      /* check alloc */
      if (!l->head) exit(1);
      link = l->head;
    }
  link->value = NULL;
  link->next = NULL;
  /* alloc value */
  link->value = (uchar*) malloc (l->value_size);
  /* check alloc */
  if (!link->value) exit(1);
  /* copy value to the link */
  {
    int i;
    for (i = 0; i < l->value_size; i++)
      *(((uchar*)(link->value)) + i) = *(((uchar*)value) + i);
  }
  return 0;
}

int
removeListValueAt (list_t *l, int index)
{
  link_t link;
  /* if list does not exists */
  if (!(*l))
    return -3;
  /* if empty list */
  if (!(*l)->head)
    return -2;
  /* wrong index */
  if (index < 0)
    return -1;
  /* go to the first link */
  link = (*l)->head;
  /* if index = 0 */
  if (!index)
    {      
      (*l)->head = link->next;
    }
  /* if index > 0 */
  else
    {
      link_t prev;
      /* browse until we reach the index -1 */
      while ( index-- != 1  &&  link->next )
        link = link->next;
      /* if there's no more next, then wrong index */
      if ( !link->next )
        return -1;
      /* change the previous' next and destroy the good one */
      prev = link;
      link = link->next;
      prev->next = link->next;
    }
  (*l)->free_value (link->value);
  free (link);
  return 0;
}

void *
getListIteratorValue (listiterator_t i)
{
  /* if iterator empty */
  if (!i)
    return NULL;
  /* if not empty, returns the value */
  return (i->value);
}

void *
getListValueAt (list_t l, int index)
{
  link_t link;
  /* if list does not exists */
  if (!l)
    return NULL;
  /* if empty list */
  if (!l->head)
    return NULL;
  /* wrong index */
  if (index < 0)
    return NULL;
  /* go to the first link */
  link = l->head;
  /* try to move to the good link */
  while ( index--   &&  link )
    link = link->next;
  /* if current link is NULL */
  if (!link)
    return NULL;
  /* return the link value */
  return link->value;
}

listiterator_t
nextListIterator (listiterator_t *i)
{
  /* if iterator empty */
  if (!(*i))
    return NULL;
  /* if not empty, go next */
  (*i) = (*i)->next;
  return (*i);
}

int
getListSize (list_t l)
{
  int i;
  link_t link;
  /* if list does not exists */
  if (!l)
    return -1;
  /* if list is empty */
  if (!l->head)
    return 0;
  /* move and count until the end */
  i = 1;
  link = l->head;
  link = link->next;
  while (link)
    {
      link = link->next;
      i++;
    }
  /* return size */
  return i;
}

void
printList (list_t l, void(*print)(void *v))
{
  if ( ! isEmptyList (l) )
    {
      listiterator_t i;
      i = getListIterator (l);
      do {
        print ( getListIteratorValue (i) );
      }while(nextListIterator (&i));
    }
  return;
}
