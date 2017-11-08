#include <stdio.h>
#include <stdlib.h>


#define AUTHOR Tristan Cavelier

#define NB_CHAR_INDENT 4

void
putspaces(int n)
{
  register int i;
  for ( i = 0; i < n; i += 1)
    putchar(' ');
}

void
err(const char *s)
{
  register int i;
  for ( i = 0; s[i] != '\0'; i ++)
    putc (s[i], stderr);
}

int
main (void)
{
  int exit;

  int indent;
  int parent;
  char c;

  enum {
    DEFAULT,
    DEFAULT_SPACE,
    NEWLINE,
    END_INSTRUCTION,
    PREPROCESSOR,
    PREPROCESSOR_ESCAPE,
    COMMENT,
    COMMENT_SLASH,
    COMMENT_SLASH_NEWLINE,
    COMMENT_ETOILE,
    COMMENT_NEWLINE,
    COMMENT_END,
    STRING,
    STRING_ESCAPE,
    CHAR,
    CHAR_ESCAPE
  }
  etat;

  exit = EXIT_SUCCESS;

  etat = NEWLINE;
  indent = 0;
  parent = 0;
  
  while ( (c = getchar()) != EOF )
    {
      switch( etat )
        {
        case CHAR_ESCAPE:
          switch ( c )
            {
            default:
              putchar (c);
              etat = CHAR;
              break;
            }
          break;
        case CHAR:
          switch ( c )
            {
            case '\\':
              putchar (c);
              etat = CHAR_ESCAPE;
              break;
            case '\'':
              putchar (c);
              etat = DEFAULT;
              break;
            default:
              putchar (c);
              break;
            }
          break;
        case STRING_ESCAPE:
          switch ( c )
            {
            default:
              putchar (c);
              etat = STRING;
              break;
            }
          break;          
        case STRING:
          switch ( c )
            {
            case '\\':
              putchar (c);
              etat = STRING_ESCAPE;
              break;
            case '"':
              putchar (c);
              etat = DEFAULT;
              break;
            default:
              putchar (c);
              break;
            }
          break;
        case COMMENT_ETOILE:
          switch ( c )
            {
            case '/':
              putchar (c);
              etat = END_INSTRUCTION;
              break;
            case '\n':
              putchar (' ');
              putchar ('*');
              putchar ('/');
              putchar (c);
              putspaces (indent);
              putchar ('/');
              putchar ('*');
              putchar (' ');
              etat = COMMENT_NEWLINE;
              break;
            default:
              putchar (c);
              etat = COMMENT;
              break;
            }
          break;
        case COMMENT_NEWLINE:
          switch ( c )
            {
            case ' ':
            case '\t':
              break;
            default:
              putchar (c);
              etat = COMMENT;
              break;
            }
          break;
        case COMMENT:
          switch ( c )
            {
            case '\n':
              putchar (' ');
              putchar ('*');
              putchar ('/');
              putchar (c);
              putspaces (indent);
              putchar ('/');
              putchar ('*');
              putchar (' ');
              etat = COMMENT_NEWLINE;
              break;
            case '*':
              putchar (c);
              etat = COMMENT_ETOILE;
              break;
            default:
              putchar (c);
              break;
            }
          break;
        case COMMENT_SLASH:
          switch ( c )
            {
            case '*':
              putchar ('\n');
              putspaces (indent);
              putchar ('/');
              putchar (c);
              etat = COMMENT;
              break;
            case '/':
              putchar ('/');
              break;
            case '\n':
              putchar ('/');
              putchar (c);
              etat = NEWLINE;
              break;
            case ' ':
            case '\t':
              putchar ('/');
              putchar (c);
              etat = DEFAULT_SPACE;
              break;
            default:
              putchar ('/');
              putchar (c);
              etat = DEFAULT;
              break;
            }
          break;
        case COMMENT_SLASH_NEWLINE:
          switch ( c )
            {
            case '*':
              putspaces (indent);
              putchar ('/');
              putchar (c);
              etat = COMMENT;
              break;
            case '/':
              putspaces (indent);
              putchar ('/');
              etat = COMMENT_SLASH;
              break;
            case '\n':
              putspaces (indent);
              putchar ('/');
              putchar (c);
              etat = NEWLINE;
              break;
            case ' ':
            case '\t':
              putspaces (indent);
              putchar ('/');
              putchar (c);
              etat = DEFAULT_SPACE;
              break;
            default:
              putspaces (indent);
              putchar ('/');
              putchar (c);
              etat = DEFAULT;
              break;
            }
          break;
        case PREPROCESSOR:
          switch ( c )
            {
            case '\\':
              putchar (c);
              break;
            case '\n':
              putchar (c);
              etat = NEWLINE;
              break;
            default:
              putchar (c);
              break;
            }
          break;
        case PREPROCESSOR_ESCAPE:
          switch ( c )
            {
            default:
              putchar (c);
              etat = PREPROCESSOR;
              break;
            }
          break;
        case END_INSTRUCTION:
          switch ( c )
            {
            case ';':
              putchar ('\n');
              putspaces (indent);
              putchar (c);
              break;
            case ' ':
            case '\t':
              break;
            case ')':
              putchar (c);
              parent --;
              if ( parent < 0 )
                {
                  err ( "Parenthese fermante en trop !\n");
                  parent = 0;
                }
              etat = DEFAULT;
              break;
            case '(':
              putchar ('\n');
              putspaces (indent);
              putchar (c);
              parent ++;
              etat = DEFAULT;
              break;
            case '{':
              putchar ('\n');
              putspaces (indent);
              putchar (c);
              indent += NB_CHAR_INDENT;
              putchar ('\n');
              etat = NEWLINE;
              break;
            case '}':
              putchar ('\n');
              indent -= NB_CHAR_INDENT;
              if ( indent < 0 )
                {
                  err ( "Accolade fermante en trop !\n");
                  indent = 0;
                }
              putspaces (indent);
              putchar (c);
              putchar ('\n');
              etat = NEWLINE;
              break;
            case '/':
              etat = COMMENT_SLASH;
              break;
            case '\n':
              putchar (c);
              etat = NEWLINE;
              break;
            default:
              putchar ('\n');
              putspaces (indent);
              putchar (c);
              etat = DEFAULT;
              break;
            }
          break;
        case NEWLINE:
          switch ( c )
            {
            case ')':
              putchar (c);
              parent --;
              if ( parent < 0 )
                {
                  err ("Parenthese fermante en trop !\n");
                  parent = 0;
                }
              etat = DEFAULT;
              break;
            case '(':
              putchar (c);
              parent ++;
              etat = DEFAULT;
              break;
            case ';':
              putspaces (indent);
              putchar (c);
              if ( !parent )
                etat = END_INSTRUCTION;
              else
                etat = DEFAULT;
              break;
            case '\'':
              putspaces (indent);
              putchar (c);
              etat = CHAR;
              break;
            case '"':
              putspaces (indent);
              putchar (c);
              etat = STRING;
              break;
            case '{':
              putspaces (indent);
              putchar (c);
              indent += NB_CHAR_INDENT;
              /* putchar ('\n'); */
              break;
            case '}':
              indent -= NB_CHAR_INDENT;
              if ( indent < 0 )
                {
                  err ("Accolade fermante en trop !\n");
                  indent = 0;
                }
              putspaces (indent);
              putchar (c);
              /* putchar ('\n'); */
              break;
            case ' ':
            case '\t':
              break;
            case '\n':
              putchar (c);
              break;
            case '/':
              etat = COMMENT_SLASH_NEWLINE;
              break;
            case '#':
              putchar (c);
              etat = PREPROCESSOR;
              break;
            default:
              putspaces (indent);
              putchar (c);
              etat = DEFAULT;
              break;
            }
          break;
        case DEFAULT_SPACE:
          switch ( c )
            {
            case ')':
              putchar (c);
              parent --;
              if ( parent < 0 )
                {
                  err ("Parenthese fermante en trop !\n");
                  parent = 0;
                }
              etat = DEFAULT;
              break;
            case '(':
              putchar (c);
              parent ++;
              etat = DEFAULT;
              break;
            case ';':
              putchar (c);
              if ( !parent )
                etat = END_INSTRUCTION;
              else
                etat = DEFAULT;
              break;
            case '\'':
              putchar (' ');
              putchar (c);
              etat = CHAR;
              break;
            case '"':
              putchar (' ');
              putchar (c);
              etat = STRING;
              break;
            case '{':
              putchar ('\n');
              putspaces (indent);
              putchar (c);
              indent += NB_CHAR_INDENT;
              putchar ('\n');
              etat = NEWLINE;
              break;
            case '}':
              putchar ('\n');
              indent -= NB_CHAR_INDENT;
              if ( indent < 0 )
                {
                  err ("Accolade fermante en trop !\n");
                  indent = 0;
                }
              putspaces (indent);
              putchar (c);
              putchar ('\n');
              etat = NEWLINE;
              break;
            case ' ':
            case '\t':
              break;
            case '/':
              putchar (' ');
              etat = COMMENT_SLASH;
              break;
            default:
              putchar (' ');
              putchar (c);
              etat = DEFAULT;
              break;
            }
          break;
        case DEFAULT:
          switch ( c )
            {
            case ')':
              putchar (c);
              parent --;
              if ( parent < 0 )
                {
                  err ("Parenthese fermante en trop !\n");
                  parent = 0;
                }
              break;
            case '(':
              putchar (c);
              parent ++;
              break;
            case ';':
              putchar (c);
              if ( !parent )
                etat = END_INSTRUCTION;
              break;
            case '\'':
              putchar (c);
              etat = CHAR;
              break;
            case '"':
              putchar (c);
              etat = STRING;
              break;
            case '{':
              putchar ('\n');
              putspaces (indent);
              putchar (c);
              indent += NB_CHAR_INDENT;
              putchar ('\n');
              etat = NEWLINE;
              break;
            case '}':
              putchar ('\n');
              indent -= NB_CHAR_INDENT;
              if ( indent < 0 )
                {
                  err ("Accolade fermante en trop !\n");
                  indent = 0;
                }
              putspaces (indent);
              putchar (c);
              putchar ('\n');
              etat = NEWLINE;
              break;
            case ' ':
            case '\t':
              etat = DEFAULT_SPACE;
              break;
            case '\n':
              putchar (c);
              etat = NEWLINE;
              break;
            case '/':
              putspaces (indent);
              etat = COMMENT_SLASH;
              break;
            default:
              putchar (c);
              break;
            }
          break;
        default:
          break;
        }
    }
  /* Test des erreurs! */
  switch ( etat )
    {
    case COMMENT:
    case COMMENT_ETOILE:
    case COMMENT_NEWLINE:
      err ("Commentaire non ferme !\n");
      break;
    default:
      break;
    }
  if ( parent > 0 )
    err ("Parenthese(s) fermante(s) manquant !\n");
  if ( indent > 0 )
    err ("Accolade(s) fermante(s) manquant !\n");

  return exit;
}
