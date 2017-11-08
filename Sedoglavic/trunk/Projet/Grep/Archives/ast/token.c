#include <stdio.h>

typedef enum{ PIPE, STAR, LBRACE, RBRACE, LBRACKET, RBRACKET, CAR, END} TOKEN;

TOKEN token;
char token_value;

void readcar(void) {
  token_value=getchar();
}

void next_token(void) {
  char c=getchar();
  token_value=c;
  if ((c==EOF) || (c == '\n')) token=END;
  else {
    switch(c) {
      case '|': token=PIPE; break;
      case '*': token=STAR; break;
      case '(': token=LBRACE; break;
      case ')': token=RBRACE; break;
      case '[': token=LBRACKET; break;
      case ']': token=RBRACKET; break;
      case '\\':
        token=CAR;
        token_value=getchar();
      default: token=CAR;
    }
  }
}
