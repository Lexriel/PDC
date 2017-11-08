#ifndef TOKEN_INCLUDE
#define TOKEN_INCLUDE
typedef enum{ PIPE, STAR, LBRACE, RBRACE, LBRACKET, RBRACKET, CAR, END} TOKEN;

extern TOKEN token;
extern TOKEN token_value;
extern void next_token(void);
extern void readcar(void);
#endif
