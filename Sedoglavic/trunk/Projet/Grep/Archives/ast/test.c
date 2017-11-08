#include<stdio.h>
#include "ast.h"
#include "token.h"

void print_ast(NODE *root, int level) {
  int i;
  if (root!=NULL) {
    for (i=0; i<level; i++) printf("  ");
    switch (root->type) {
      case ALTER: printf("|\n"); break;
      case CONCAT: printf(".\n"); break;
      case REPET: printf("*\n"); break;
      case LETTER: printf("%c\n", root->value); break;
      case RANGE: printf("[");
                  for (i=0; i<256;i++) if (root->set[i]==1) printf("%c", i);
                  printf("]\n"); break;
      case ALLBUT: printf("[^");
                   for (i=0; i<256;i++) if (root->set[i]==1) printf("%c", i);
                   printf("]\n"); 
    }
    level+=2;
    print_ast(root->left, level);
    print_ast(root->right, level);
  }
}
  
main() {

NODE *root;

next_token();

root=expr();

print_ast(root, 0);

}
