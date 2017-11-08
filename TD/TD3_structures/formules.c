# include <stdio.h>
# include <stdlib.h>
# include <string.h>

# define NAME_LG 16     /* longueur d'un id de variable */
# define NVARS 32       /* nombre de variables */

struct var_s{
  char  v_name[NAME_LG]; /* nom de la variable */
  float v_val;           /* et sa valeur */
};

static struct var_s vars[NVARS]; /* table des symboles */
static unsigned int nvars = NVARS;

/* Les termes */
enum term_type_e {VAL_T, ID_T}; /* 2 types de termes */

struct term_s{
  enum term_type_e t_type;
  union{
    float t_val;
    char  t_var[NAME_LG];
  } t_term;
};

/* Les termes sans union anonyme */
/*union term_v_u {
  float t_val;
  char  t_var[NAME_LG];
  };

  struct term_s {
  enum  term_type_e t_type;  discriminant 
  union term_v_u    t_term;  partie variable
  }; */

float value_of_var(char *var){
  int i;
  /* si var coincide avec l'une des vars de la table, on peut déterminer sa valeur */
  for (i=0; i<nvars; i++){
    if (!strcmp(vars[i].v_name, var))
      return vars[i].v_val;
  }
  printf("valeur inconnue\n");
  exit(EXIT_FAILURE);
}

float value_of_term(struct term_s t){
  switch(t.t_type){
  case ID_T :
    return t.t_term.t_val;
  case VAL_T :
    return value_of_var(t.t_term.t_var);
  }
  printf("dans du code inaccessible\n");
  exit(EXIT_FAILURE);
}


/* QUESTION 2*/
enum op_e {NONE_OP, SUM_OP, MUL_OP, DIV_OP};

struct form_s{
  struct term_s f_operand1;
  enum   op_e   f_operator;
  union{
    struct term_s f_term;
    int           f_coeff;
  }             f_operand2;
};


/* QUESTION 3*/
float value_of_formula(struct form_s f){
  switch (f.f_operator){
  case NONE_OP:
    return value_of_term(f.f_operand1);
  case SUM_OP:
    return value_of_term(f.f_operand1) + value_of_term(f.f_operand2.f_term);
  case MUL_OP:
    return value_of_term(f.f_operand1) * f.f_operand2.f_coeff;
  case DIV_OP:
    return value_of_term(f.f_operand1) / f.f_operand2.f_coeff;
  }
  exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]){
  
}
