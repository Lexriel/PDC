#include <stdio.h>
#include "token.h"
#include "ast.h"

void parse_error(char *s) {
  fprintf(stderr, "Error parsing character %c in %s\n", token_value, s);
  exit(1);
}

NODE *expr(void);
NODE *concat(void);
NODE *repet(void);
NODE *simple(void);

NODE *expr(void) {
  NODE *child, *node;
  child=concat();
  if (token==END) return child;
  if (child==NULL) parse_error("expression");
  if (token==PIPE) {
    node=(NODE *)malloc(sizeof(NODE));
    node->type=ALTER;
    node->value='\0';
    node->left=child;
    next_token();
    if ((node->right=expr())==NULL) parse_error("alternative expression");
    return node;
  } else return child;
}
    
NODE *concat(void) {
  NODE *child, *node;
  child=repet();
  if (token==END) return child;
  if (child==NULL) parse_error("concatenation");
  if ((token==LBRACE) || (token==CAR) || (token == LBRACKET)) {
    node=(NODE *)malloc(sizeof(NODE));
    node->type=CONCAT;
    node->value='\0';
    node->left=child;
    if ((node->right=concat())==NULL) parse_error("concatenation");
    return node;
  } else return child;
}

NODE *repet(void) {
  NODE *child, *node;
  child=simple();
  if (token==END) return child;
  if (child==NULL) parse_error("simple expression");
  if (token==STAR) {
    node=(NODE *)malloc(sizeof(NODE));
    node->type=REPET;
    node->value='\0';
    node->left=child;
    node->right=NULL;
    next_token();
    return node;
  } else return child;
}

NODE *simple(void) {
  NODE *child, *node;
  if (token==LBRACE) {
    next_token();
    if ((child=expr())==NULL) parse_error("braces expression");
    if (token != RBRACE) parse_error("watching for an )");
    next_token();
    return child;
  }
  if (token==LBRACKET) {
    next_token();
    if ((child=parse_range())==NULL) parse_error("range expression");
    if (token != RBRACKET) parse_error("watching for an ]");
    next_token();
    return child;
  }
  if (token==END) return NULL;
  if (token!=CAR) parse_error("litteral");
  node=(NODE *)malloc(sizeof(NODE));
  node->type=LETTER;
  node->value=token_value;
  node->left=node->right=NULL;
  next_token();
  return node;
}

NODE *parse_range() {
  NODE *node;
  char *set=(char *)malloc(256*sizeof(char));
  int i;
  char predtokenvalue;

  for (i=0;i<=256; i++) set[i]=0;


  node=(NODE *)malloc(sizeof(NODE));
  if (token_value=='^') {
    node->type=ALLBUT;
    readcar();
  }
  else node->type=RANGE;
  node->left=node->right=NULL;
  if (token_value=='-') parse_error("range");
  if (token_value==RBRACKET) {
    predtokenvalue=']';
    set[token_value]=1;
    readcar();
  }
  
  while ((token_value != ']') && (token_value != EOF) && (token_value != '\n')){
    if (token_value != '-') 
       set[token_value]=1;
     else {
       readcar();
       if (token_value== ']')
         set[token_value]=1;
       else
         for (i=predtokenvalue; i<=token_value; i++)
           set[i]=1;
    } 
    predtokenvalue=token_value;
    readcar();
  }
  if ((token_value == EOF) || (token_value == '\n')) parse_error("range expression");
  token=RBRACKET;
  node->set=set;
  
  return node;
}
