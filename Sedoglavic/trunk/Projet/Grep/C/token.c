#include <stdio.h>
#include "token.h"


char nextchar (void)
{
  return *(regularexpression++);
}

void next_token (void)
{
  token_value = nextchar ();
  switch (token_value)
    {
    case 0:
      token = END;
      break;
    case '.':
      token = DOT ;
      break;
    case '|':
      token = PIPE;
      break;
    case '*':
      token = STAR;
      break;
    case '(':
      token = LBRACE;
      break;
    case ')':
      token = RBRACE;
      break;
    case '[':
      token = LBRACKET;
      break;
    case ']':
      token = RBRACKET;
      break;
    case '\\':
      token = CAR;
      token_value = nextchar ();
    default:
      token = CAR;
    }
}
