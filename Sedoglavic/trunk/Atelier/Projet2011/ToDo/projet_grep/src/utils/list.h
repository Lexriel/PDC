#ifndef _LIST_H_
#define _LIST_H_ 1

/* link */
struct link_m
{
  /* a value */
  void *value;
  /* the next link */
  struct link_m *next;
};
typedef struct link_m *link_t;

/* list */
struct list_m
{
  /* first link of the list */
  link_t head;
  /* size of the links value */
  int value_size;
  /* function to free links value */
  void(*free_value)(void *ptr);
};
typedef struct list_m *list_t;

typedef link_t listiterator_t;



/*
  creates a new list:
  [value_size] is the size of the values
  [free_value] is the free values function
  (default is void *free(void *ptr)  from stdlib.h)
*/
extern list_t
newList (int value_size);
extern list_t
newListFreeFun (int value_size, void(*free_value)(void *ptr));

/*
  tests if the list [l] is empty
  - 1 : empty
  - 0 : not empty
  - -1 : list does not exists
*/
extern int
isEmptyList (list_t l);

/*
  deletes the list [l] with all its links
  - 0 : deleted
  - -1 : list does not exists  
*/
extern int
deleteList (list_t *l);

/*
  same as deleteList but does not return anything
*/
extern void
clearList (void *list);

/*
  returns a new iterator which point at the first value
  of the list [l]
  returns NULL if list is empty or not created
*/
extern listiterator_t
getListIterator (list_t l);

/*
  clones *[value] and adds it on the list [l]
  returns:
  - 0 : OK
  - -1 : list does not exists
*/
extern int
addValueList (list_t l, void *value);

/*
  removes the value at the index [index]
  returns:
  - 0 : ok
  - -1 : wrong index
  - -2 : empty list
  - -3 : list does not exists
*/
extern int
removeListValueAt (list_t *l, int index);


/*
  returns the value at the list iterator [i]
*/
extern void *
getListIteratorValue (listiterator_t i);

/*
  returns the value at index [index]
  if wrong index, it returns NULL
*/
extern void *
getListValueAt (list_t l, int index);

/*
  returns the size of the list [l] or -1 if list does
  not exists
*/
extern int
getListSize (list_t l);

/*
  moves the list iterator [i] to the next value
  if it was on the last value, [i] becomes NULL.
  changes and returns the iterator [i]
*/
extern listiterator_t
nextListIterator (listiterator_t *i);


/*
  print the list [l] with his printing function [print]
*/
extern void
printList (list_t l, void(*print)(void *v));

#endif /* _LIST_H_ */
