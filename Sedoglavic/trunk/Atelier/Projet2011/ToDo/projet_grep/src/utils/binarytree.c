#include "binarytree.h"

#include <stdio.h>
#include <stdlib.h>


typedef unsigned char uchar;

#define memcpy(dest,src,size)                   \
  {                                             \
    int _i_;                                    \
    for (_i_ = 0;                               \
         _i_ < (size) / sizeof(uchar);          \
         _i_++)                                 \
      *(((uchar*)(dest)) + _i_) =               \
        *(((uchar*)(src)) + _i_);               \
  }


/*
  delete a node [n] and its value with [free_value] function
  - 0 : OK
  - -1 : node does not exist
*/
int
deleteBinaryTreeNodes (binarytree_node_t *n, void(*free_value)(void *ptr));

/*
  creates a node
*/
binarytree_node_t
createBinaryTreeNode (void *value, int size);

/*
  clones nodes
*/
binarytree_node_t
cloneBinaryTreeNodes (binarytree_t t, binarytree_node_t n);










binarytree_t
newBinaryTree (int value_size)
{
  return newBinaryTreeFreeFun ( value_size, free);
}

binarytree_t
newBinaryTreeFreeFun (int value_size, void(*free_value)(void *ptr))
{
  binarytree_t tmp;
  /* if the value size is not correct */
  if (value_size <= 0)
    return NULL;
  /* alloc binary tree */
  tmp = (binarytree_t) malloc (sizeof(struct binarytree_m));
  /* check alloc */
  if (!tmp) exit(1);
  /* init vars */
  tmp->root = NULL;
  tmp->value_size = value_size;
  tmp->free_value = free_value;
  return tmp;
}

int
isEmptyBinaryTree (binarytree_t t)
{
  /* if tree does not exist */
  if (!t)
    return -1;
  /* if tree is not empty */
  if (!t->root)
    return 0;
  /* tree is empty */
  return 1;
}

int
isLeafBinaryTreeIterator (binarytreeiterator_t i)
{
  /* if iterator is empty */
  if (!i)
    return -1;
  /* return 1 if leaf else 0 */
  return (i->ls == NULL && i->rs == NULL);
}

void
clearBinaryTree (void *tree)
{
  deleteBinaryTree ((binarytree_t*)tree);
}

int
deleteBinaryTree (binarytree_t *t)
{
  /* if tree does not exist */
  if (!(*t))
    return -1;
  /* delete all nodes */
  deleteBinaryTreeNodes (&((*t)->root), (*t)->free_value);
  /* free tree */
  free (*t);
  (*t) = NULL;
  return 0;
}

int
deleteLeftSonBinaryTreeIterator (binarytree_t t, binarytreeiterator_t i)
{
  /* if tree does not exist */
  if (!t)
    return -2;
  /* if iterator is empty */
  if (!i)
    return -1;
  if (i->ls)
    deleteBinaryTreeNodes (&(i->ls),t->free_value);
  return 0;
}

int
deleteRightSonBinaryTreeIterator (binarytree_t t, binarytreeiterator_t i)
{
  /* if tree does not exist */
  if (!t)
    return -2;
  /* if iterator is empty */
  if (!i)
    return -1;
  if (i->rs)
    deleteBinaryTreeNodes (&(i->rs),t->free_value);
  return 0;
}

int
deleteBinaryTreeNodes (binarytree_node_t *n, void(*free_value)(void *ptr))
{
  /* if node does not exist */
  if (!(*n))
    return -1;
  /* delete left son */
  if ( (*n)->ls )
    deleteBinaryTreeNodes ( &((*n)->ls), free_value);
  if ( (*n)->rs )
    deleteBinaryTreeNodes ( &((*n)->rs), free_value);
  /* free node's value */
  free_value ((*n)->value);
  /* free this node */
  free (*n);
  (*n) = NULL;
  return 0;
}

binarytree_node_t
createBinaryTreeNode (void *value, int size)
{
  binarytree_node_t tmp;
  /* alloc */
  tmp = (binarytree_node_t) malloc (sizeof(struct binarytree_node_m));
  /* check alloc */
  if (!tmp) exit(1);
  /* create value */
  tmp->value =
    (uchar*) malloc(size / sizeof(uchar));
  /* check alloc again */
  if (!tmp->value) exit(1);
  /* clone the value to the node */
  memcpy (tmp->value, value, size);
  /* init sons */
  tmp->ls = NULL;
  tmp->rs = NULL;
  return tmp;
}

binarytreeiterator_t
getBinaryTreeIterator (binarytree_t t)
{
  binarytreeiterator_t i;
  /* if the tree does not exist */
  if (!t)
    return NULL;
  /* if the tree is empty */
  if (!t->root)
    return NULL;
  i = (binarytreeiterator_t) t->root;
  return i;
}

int
setRootValueBinaryTree (binarytree_t *t, void *value)
{
  /* if tree does not exist */
  if (!(*t))
    return -2;
  /* if root already exists */
  if ((*t)->root)
    return -1;
  ((*t)->root) = createBinaryTreeNode (value, (*t)->value_size);
  return 0;
}

int
goToLeftSonBinaryTreeIterator (binarytreeiterator_t *i)
{
  if (!(*i))
    return -1;
  (*i) = (*i)->ls;
  return 0;
}

int
goToRightSonBinaryTreeIterator (binarytreeiterator_t *i)
{
  if (!(*i))
    return -1;
  (*i) = (*i)->rs;
  return 0;
}

int
addSonBinaryTreeIterator (binarytree_t t,
                          binarytreeiterator_t i,
                          void *value,
                          char o)
{
  /* if tree does not exist */
  if (!t)
    return -3;
  /* if iterator is empty */
  if (!i)
    return -2;
  if (o == 'l')
    {
      /* if son already exists */
      if (i->ls)
        return -1;
      i->ls = createBinaryTreeNode (value, t->value_size);
    }
  else if (o == 'r')
    {
      /* if son already exists */
      if (i->rs)
        return -1;
      i->rs = createBinaryTreeNode (value, t->value_size);
    }
  return 0;
}

int
addLeftSonBinaryTreeIterator (binarytree_t t,
                              binarytreeiterator_t i, 
                              void *value)
{
  return addSonBinaryTreeIterator (t,i,value,'l');
}

int
addRightSonBinaryTreeIterator (binarytree_t t,
                               binarytreeiterator_t i, 
                               void *value)
{
  return addSonBinaryTreeIterator (t,i,value,'r');
}

int
extendSonBinaryTreeIterator (binarytree_t t,
                             binarytreeiterator_t i,
                             binarytree_t t2,
                             char o)
{
  binarytree_t tmp;
  /* if trees do not exist */
  if (!t || !t2)
    return -3;
  /* if iterator is empty */
  if (!i)
    return -2;
  if (o == 'l')
    {
      /* if son already exists */
      if (i->ls)
        return -1;
      tmp = cloneBinaryTree (t2);
      i->ls = cloneBinaryTreeNodes (tmp,tmp->root);
    }
  else if (o == 'r')
    {
      /* if son already exists */
      if (i->rs)
        return -1;
      tmp = cloneBinaryTree (t2);
      i->rs = cloneBinaryTreeNodes (tmp,tmp->root);
    }
  free (tmp);
  return 0;  
}

int
extendLeftSonBinaryTreeIterator (binarytree_t t,
                                 binarytreeiterator_t i,
                                 binarytree_t t2)
{
  return extendSonBinaryTreeIterator (t, i, t2, 'l');
}

int
extendRightSonBinaryTreeIterator (binarytree_t t,
                                 binarytreeiterator_t i,
                                 binarytree_t t2)
{
  return extendSonBinaryTreeIterator (t, i, t2, 'r');
}

binarytree_t
cloneBinaryTree (binarytree_t t)
{
  binarytree_t tmp;
  tmp = newBinaryTreeFreeFun (t->value_size,t->free_value);
  /* clone nodes */
  tmp->root = cloneBinaryTreeNodes (t, t->root);
  return tmp;
}

binarytree_node_t
cloneBinaryTreeNodes (binarytree_t t, binarytree_node_t n)
{
  binarytree_node_t tmp;
  if (!n || !t)
    return NULL;
  /* clone nodes */
  tmp = createBinaryTreeNode (n->value, t->value_size);
  tmp->ls = cloneBinaryTreeNodes (t,n->ls);
  tmp->rs = cloneBinaryTreeNodes (t,n->rs);
  return tmp;
}

void *
getValueBinaryTreeIterator (binarytreeiterator_t i)
{
  /* if iterator empty */
  if (!i)
    return NULL;
  /* if not empty, returns the value */
  return (i->value);
}

int
setValueBinaryTreeIterator (binarytree_t t,
                            binarytreeiterator_t *i,
                            void *value)
{
  /* if iterator is empty */
  if (!(*i))
    return -1;
  /* delete value if necessary */
  if ((*i)->value)
    {
      t->free_value ((*i)->value);
      (*i)->value = NULL;
    }
  /* create value */
  ((*i)->value) =
    (uchar *) malloc (t->value_size / sizeof(uchar));
  /* check alloc */
  if (!(*i)->value) exit(1);
  /* clone the value */
  memcpy ((*i)->value, value, t->value_size);
  /* done */
  return 0;
}

int
getValueSizeBinaryTree (binarytree_t t)
{
  /* if tree does not exist */
  if (!t)
    return -1;
  /* returns the value size */
  return t->value_size;
}

void
printBinaryTreeNodes (binarytree_node_t n, void(*p)(void *v), int i)
{
  int j;
  if (n)
    {
      printBinaryTreeNodes (n->rs,p,i+1);
      for (j = 0; j < i; j++)
        printf ("   ");
      p(n->value); printf ("\n");
      printBinaryTreeNodes (n->ls,p,i+1);
    }
  else
    {
      for (j = 0; j < i; j++)
        printf ("   ");
      printf ("()\n");
    }
}
/* void */
/* printBinaryTreeNodes (binarytree_node_t n, void(*p)(void *v)) */
/* { */
/*   printf ("("); */
/*   if (n) */
/*     { */
/*       p(n->value); */
/*       printf (","); */
/*       printBinaryTreeNodes (n->ls, p); */
/*       printf (","); */
/*       printBinaryTreeNodes (n->rs, p); */
/*     } */
/*   printf (")"); */
/* } */

void
printBinaryTree (binarytree_t t, void(*p)(void *v))
{
  /* if the tree does not exist */
  if (!t)
    return;
  printBinaryTreeNodes (t->root, p, 0);
  /* printf ("\n"); */
}
