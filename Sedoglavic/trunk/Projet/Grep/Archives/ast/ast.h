typedef enum{ ALTER, CONCAT, REPET, LETTER, RANGE, ALLBUT} TYPENODE;
typedef struct node {
  TYPENODE type;
  char value;
  char *set;
  struct node*left, *right; } NODE;

extern NODE *expr(void);
extern NODE *concat(void);
extern NODE *repet(void);
extern NODE *simple(void);
extern NODE *parse_range(void);

