typedef enum {PIPE, STAR, LBRACE, RBRACE, CAR, END, DIESE} TOKEN;

TOKEN token;
char token_value;
char next_token();
void init_token(const char * s);
void init_token(const char * s);
