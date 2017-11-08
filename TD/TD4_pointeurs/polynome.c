# include <stdio.h>
# include <stdlib.h>
# include <strings.h>
# include <math.h>

struct monome_s
{
  int coeff;
  int degre;
};
typedef struct monome_s monome_t;


typedef struct poly_s *polynome_t;
struct poly_s {
  monome_t mono;
  polynome_t next;
};


void inc_poly_recursive(polynome_t p)
{
  if (!p)		
    return;
  p->mono.degre++;
  inc_poly_recursive(p->next);
}


void inc_poly_iterative(polynome_t p)
{
  while (p)
    {
      p->mono.degre++;
      p = p->next;
    }
}


int valeur_poly(polynome_t p, int valeur)
{
  if (p)
    return p->mono.coeff * pow(valeur, p->mono.degre) + valeur_poly(p->next, valeur);
  else
    return 0;
}

void print_poly_recursive(polynome_t p)
{
  if (!p)
    return;
  /* le monome */
  printf("%d", p->mono.coeff);
  if (p->mono.degre == 1)
    printf("x");
  else if (p->mono.degre > 1)
    printf("x^%d", p->mono.degre);
  
  /* la suite */
  if (p->next)
    printf(" + ");
  print_poly_recursive(p->next);
}

void print_poly(polynome_t p)
{
  print_poly_recursive(p);
  printf("\n");
}


void free_poly(polynome_t p)
{
  if (!p)
    return;
  free_poly(p->next);
  free(p);
}

polynome_t read_poly()
{
  polynome_t p = NULL;
  int coeff, status;

  while((status = scanf("%d", &coeff)) != EOF){
    if (!status){
      getchar();
      continue;
    }
    if (coeff){
      polynome_t new = malloc(sizeof(struct poly_s));
      if (!new){
	free_poly(p);
	printf("p a été libéré.\n");
	return NULL;
      }
      new->mono.coeff = coeff;
      new->mono.degre = -1; /* va être incrémenté */
      new->next = p;
      p = new;
    }
    inc_poly_recursive(p);
  }
  
  return p;
}

void add_monome(monome_t m, polynome_t *p)
{
  polynome_t new = malloc(sizeof(struct poly_s));
  new->mono = m;
  new->next = *p;
  *p = new;
}

polynome_t add_monome2(monome_t m, polynome_t p)
{
  polynome_t new = malloc(sizeof(struct poly_s));
  new->mono = m;
  new->next = p;

  return(new);
}

/* principe :
  * si on a déjà un monôme q du même degré que m dans pp
    - on additionne les coefficients de m et de q dans q
    - si le coefficient obtenu vaut 0, on enlève q de pp 
  * sinon
    - allouer de la mémoire pour un monôme
    - l'insérer dans pp de sorte à ce que pp aient ses
      monômes classé dans l'ordre croissant de ses degrés */
polynome_t ajouter_monome(monome_t m, polynome_t *pp)
{
  polynome_t q, prev, next, new;
  int ajoute;
  ajoute = 0;
  if (!m.coeff)
    return *pp;
  prev = NULL;
  q = *pp;
  /* Recherche du monome dans *pp */
  while (q){
    next = q->next;
    if (q->mono.degre == m.degre){
      q->mono.coeff += m.coeff;
      ajoute = 1;
      if (q->mono.coeff == 0){
	free(q);
	if (prev)
	  prev->next = next;
	else
	  *pp = next;
      }
      break;
    }
    prev = q;
    q = q->next;
  }
  if (ajoute == 1)
    return *pp;
  
  /* Ajout du monome si non trouvé */
  if (ajoute == 0){
    prev = NULL;
    q = *pp;
    while (q && (q->mono.degre < m.degre)){
      prev = q;
      q = q->next;
    }

    new = malloc(sizeof(struct poly_s));
    new->mono.degre = m.degre;
    new->mono.coeff = m.coeff;
    new->next = q;
    if (prev)
      prev->next = new;
    else
      *pp = new;

    return *pp;
  }
}


int main(int argc, char* argv[])
{
  polynome_t p, q;
  monome_t m;
  int valeur;

  p = malloc(5 * sizeof(struct poly_s));

  p->mono.degre = 4;
  p->mono.coeff = 1;
  p->next = p+1;
  
  (p+1)->mono.degre = 2;
  (p+1)->mono.coeff = 2;
  (p+1)->next = p+2;

  (p+2)->mono.degre = 1;
  (p+2)->mono.coeff = 4;
  (p+2)->next = p+3;

  (p+3)->mono.degre = 0;
  (p+3)->mono.coeff = 5;
  (p+3)->next = NULL;

  print_poly(p);

  inc_poly_recursive(p);
  print_poly(p);

  valeur = 1;
  printf("P(%d) = %d\n", valeur, valeur_poly(p,valeur));

  printf("Entrez les coefficients d'un polynome :\n");
  q = read_poly();

  printf("Voici votre polynome :\n");
  print_poly(q);

  m.coeff = -3;
  m.degre = 3;
  ajouter_monome(m, &q);
  printf("q après ajout de m :\n");
  print_poly(q);



  m.coeff = -1;
  m.degre = 4;
  add_monome(m, &p);
  print_poly(p);

  m.coeff = 3;
  m.degre = 6;
  p = add_monome2(m, p);
  print_poly(p);

  free(p); /* déclaré avec un malloc directement */

  //free_poly(q); /* déclaré avec plusieurs malloc */
  printf("q a été libéré.\n");


  return 0;
}
