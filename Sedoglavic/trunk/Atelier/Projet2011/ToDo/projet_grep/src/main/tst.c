#include <stdio.h>
#include "binarytree.h"

void
printChar (void *vchar)
{
  printf ("%c",*((char*)(vchar)));
}

int
main (int argc, char *argv[])
{
  binarytree_t t,t2,t3;
  binarytreeiterator_t i,i3;
  char c;
  t = t2 = t3 = NULL;
  i = i3 = NULL;

  printBinaryTree (t, printChar);
  t = newBinaryTree(sizeof(char));
  printBinaryTree (t, printChar);

  c = 'a';
  setRootValueBinaryTree (&t,&c);
  i = getBinaryTreeIterator (t);
  printf ("t:\n");
  printBinaryTree (t, printChar);
  printf ("is leaf: %d\n",isLeafBinaryTreeIterator(i));

  c = 'b';
  addRightSonBinaryTreeIterator (t, i, &c);
  printf ("t:\n");
  printBinaryTree (t, printChar);
  printf ("i is leaf: %d\n",isLeafBinaryTreeIterator(i));

  t2 = cloneBinaryTree (t);
  printf ("%p %p\n",(void*)t,(void*)t2);
  printf ("t2:\n");
  printBinaryTree (t2, printChar);

  deleteRightSonBinaryTreeIterator (t,i);
  printf ("t:\n");
  printBinaryTree (t, printChar);
  printf ("i is leaf: %d\n",isLeafBinaryTreeIterator(i));

  c = 'c';
  addLeftSonBinaryTreeIterator (t, i, &c);
  goToLeftSonBinaryTreeIterator (&i);
  c = 'd';
  addRightSonBinaryTreeIterator (t, i, &c);
  printf ("t:\n");
  printBinaryTree (t, printChar);
  printf ("i is leaf: %d\n",isLeafBinaryTreeIterator(i));


  t3 = cloneBinaryTree (t);
  i3 = getBinaryTreeIterator (t3);
  goToLeftSonBinaryTreeIterator (&i3);
  goToRightSonBinaryTreeIterator (&i3);
  printf ("extend t3 with t2 at i3:\n");
  extendLeftSonBinaryTreeIterator (t3, i3, t2);
  printf ("t3:\n");
  printBinaryTree (t3,printChar);
  printf ("t2:\n");
  printBinaryTree (t2,printChar);

  c = 'e';
  setValueBinaryTreeIterator (t3,&i3,&c);
  printf ("t3:\n");
  printBinaryTree (t3,printChar);

  deleteBinaryTree(&t);
  deleteBinaryTree(&t2);
  deleteBinaryTree(&t3);


  return 0;
}
