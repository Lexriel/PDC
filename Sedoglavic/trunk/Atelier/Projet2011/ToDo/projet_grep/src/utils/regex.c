#include "regex.h"
#include "binarytree.h"
#include <stdlib.h>

binarytree_node_t car (char * );

/* typedef enum */
/*   {  */
/*     ERROR, */
/*     PIPE, */
/*     STAR, */
/*     LBRACE, */
/*     RBRACE, */
/*     CAR, */
/*     END */
/*   } TOKEN; */
#define charsize sizeof(char)

/*
  expr ::= ens expr |
  ens ::= '(' expr ')' repet or | car repet or
  repet ::= "*" |
  or ::= "|" ens |
  car ::= tout sauf "|", "*", "(", ")"
        | "\|" | "\*" | "\(" | "\)"

  (a|b)*abb

  aaabaaabb
*/

/*
  returns:
     ()
  ch
     ()
*/
binarytree_node_t
ens (char * regex)
{
  binarytree_node_t tmp;
  int gap,count;
  gap = 1;
  count = 1;
  tmp = car (regex);
  if (tmp == NULL)
    {
      switch (regex[0])
        {
        case '(':
          tmp = expr (regex + gap);
          /* TODO */
          
          break;
        default:
          return NULL;
          break;
        }
    }
  return tmp;  
}

/*
  returns:
     ()
  *
     ()
*/
binarytree_node_t
repet (char * regex)
{
  binarytree_node_t tmp;
  switch (regex[0])
    {
    case '*':
      tmp = createBinaryTreeNode (regex,charsize);
      return tmp;
      break;
    default:
      return NULL;
      break;
    }
}

/*
  returns:
     right
  |
     ens
*/
binarytree_node_t
or (char * regex, binarytree_node_t right)
{
  binarytree_node_t tmp;
  switch (regex[0])
    {
    case '|':
      tmp = createBinaryTreeNode (regex, charsize);
      if (tmp == NULL)
        return NULL;
      tmp->rs = right;
      tmp->ls = ens (regex + 1);
      return tmp;
      break;
    case '\0':
    default:
      return NULL;
      break;
    }
  /* return NULL; */
}

/*
  returns:
     ()
  c
     ()
*/
binarytree_node_t
car (char * regex)
{
  binarytree_node_t tmp;
  switch (regex[0])
    {
      /* bad state */
    case '\0':
    case '|':
    case '*':
    case '(':
    case ')':
      return NULL;
      break;
      /* good state \... */
    case '\\':
      switch (regex[1])
        {
          /* good escape characters */
        case '|':
        case '*':
        case '(':
        case ')':
          tmp = createBinaryTreeNode (regex+1, charsize);
          return tmp;
          break;
          /* bad states */
        default:
          return NULL;
          break;
        }
      break;
      /* good states, simple characters */
    default:
      ;
      break;
    }
  return tmp;
}

int
RegexMatchesWith (const char * regex, const char *string)
{
  return 0;
}
