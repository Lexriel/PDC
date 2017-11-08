typedef enum{ PIPE, STAR, LBRACE, RBRACE, LBRACKET, RBRACKET, CAR, END, DOT} TOKEN;
 TOKEN token;

 char token_value ;

/* a global pointer on the string encoding a regularexpression */
char *regularexpression ;

void next_token (void) ;
char nextchar (void) ;
