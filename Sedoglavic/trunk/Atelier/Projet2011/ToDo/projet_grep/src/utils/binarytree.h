#ifndef _BINARYTREE_H_
#define _BINARYTREE_H_ 1

/* node */
struct binarytree_node_m
{
  /* a value */
  void *value;
  /* left son */
  struct binarytree_node_m *ls;
  /* right son */
  struct binarytree_node_m *rs;
};
typedef struct binarytree_node_m *binarytree_node_t;

/* binarytree */
struct binarytree_m
{
  /* first node of the tree */
  binarytree_node_t root;
  /* size of the nodes value */
  int value_size;
  /* function to free nodes value */
  void(*free_value)(void *ptr);
};
typedef struct binarytree_m *binarytree_t;

typedef binarytree_node_t binarytreeiterator_t;

/*
  creates a node
*/
extern binarytree_node_t
createBinaryTreeNode (void *value, int size);

/*
  creates a new tree:
  [value_size] is the size of the values
  [free_value] is the free values function
  (default is void *free(void *ptr)  from stdlib.h)
*/
extern binarytree_t
newBinaryTree (int value_size);
extern binarytree_t
newBinaryTreeFreeFun (int value_size, void(*free_value)(void *ptr));

/*
  tests if the tree [t] is empty
  - 1 : empty
  - 0 : not empty
  - -1 : tree does not exists
*/
extern int
isEmptyBinaryTree (binarytree_t t);

/*
  tests if the iterator [i] is on a leaf (doesn't have any sons)
*/
extern int
isLeafBinaryTreeIterator (binarytreeiterator_t i);


/*
  deletes the tree [t] with all its links
  - 0 : deleted
  - -1 : tree does not exists  
*/
extern int
deleteBinaryTree (binarytree_t *t);

/*
  same as deleteTree but does not return anything
*/
extern void
clearBinaryTree (void *tree);


/*
  deletes the left/right son from the iterator [i] from the
  tree [t]
  - 0 : deleted
  - -1 : iterator is empty
  - -2 : tree does not exists  
*/
extern int
deleteLeftSonBinaryTreeIterator (binarytree_t t, binarytreeiterator_t i);
extern int
deleteRightSonBinaryTreeIterator (binarytree_t t, binarytreeiterator_t i);


/*
  returns a new iterator which point at the first value
  of the tree [t]
  returns NULL if tree is empty or not created
*/
extern binarytreeiterator_t
getBinaryTreeIterator (binarytree_t t);

/*
  clones *[value] and creates the tree [t]'s root
  returns:
  - 0 : OK
  - -1 : tree does not exists
*/
extern int
setRootValueBinaryTree (binarytree_t *t, void *value);

/*
  moves the iterator [i] to his left/right son.
  returns
  - 0 : OK
  - -1 : iterator is empty
*/
extern int
goToLeftSonBinaryTreeIterator (binarytreeiterator_t *i);
extern int
goToRightSonBinaryTreeIterator (binarytreeiterator_t *i);

/*
  clones *[value] and creates a new left/right son in the tree
  at the iterator [i]. the value size is taken from
  the source tree [t].
  returns:
  - 0 : OK
  - -1 : son already exists
  - -2 : iterator is empty
  - -3 : tree does not exists
*/
extern int
addLeftSonBinaryTreeIterator (binarytree_t t,
                              binarytreeiterator_t i,
                              void *value);
extern int
addRightSonBinaryTreeIterator (binarytree_t t,
                              binarytreeiterator_t i,
                              void *value);

/*
  clones tree [t2] on the left/right son in the tree [t]
  at the iterator [i].
  returns:
  - 0 : OK
  - -1 : son already exists
  - -2 : iterator is empty
  - -3 : a tree does not exists
*/
extern int
extendLeftSonBinaryTreeIterator (binarytree_t t,
                                 binarytreeiterator_t i,
                                 binarytree_t t2);
extern int
extendRightSonBinaryTreeIterator (binarytree_t t,
                                  binarytreeiterator_t i,
                                  binarytree_t t2);


/* clones a tree */
extern binarytree_t
cloneBinaryTree (binarytree_t t);

/*
  returns the value at the tree iterator [i]
*/
extern void *
getValueBinaryTreeIterator (binarytreeiterator_t i);

/*
  set the value at the tree iterator [i]
  returns:
  - 0 : OK
  - -1 : iterator is empty
*/
extern int
setValueBinaryTreeIterator (binarytree_t t,
                            binarytreeiterator_t *i,
                            void *value);


/*
  returns the values' size from the binary tree [t]
  returns:
  - the value size
  - -1 : if the tree does not exists
*/
extern int
getValueSizeBinaryTree (binarytree_t t);

/*
  print the tree [t] with the printing function [p]
*/
extern void
printBinaryTree (binarytree_t t, void(*p)(void *v));

#endif /* _BINARYTREE_H_ */
