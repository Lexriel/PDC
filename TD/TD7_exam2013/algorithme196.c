# include <stdio.h>
# include <stdlib.h>

typedef struct cell *liste;
struct cell{
  int val;
  int pos;
  liste prev;
  liste next;
};

void insererEnTete(liste *l, int pos, int val){
  liste tmp;
  tmp = malloc(sizeof(struct cell));
  tmp->prev = NULL;
  tmp->next = *l;
  tmp->pos = pos;
  tmp->val = val;
  if (tmp->next)
    tmp->next->prev = tmp;
  *l = tmp;
  return;
}

/* int2liste */
liste convertionEntierListe(int n){
  liste res, tmp;
  int d, pos;
  res = NULL;
  pos = 1;
  while(n){
    d = n % 10;
    insererEnTete(&res, pos, d);
    pos++;
    n /= 10;
  }
  return res;
}

void afficherListe(liste l){
  while(l){
    printf("%d", l->val);
    l = l->next;
  }
  putchar('\n');
  return;
}

void freeListe(liste *l){
  if (*l == NULL)
    return;
  freeListe(&((*l)->next));
  free(*l);
  *l = NULL;
}

int palindrome(liste l){
  liste tete, queue;
  if (l == NULL)
    return 1;
  tete = l;
  queue = l;
  while (queue->next)
    queue = queue->next;
  while(1){
    if (tete->val != queue->val)
      return 0;
    if (tete->pos <= queue->pos)
      return 1;
    tete = tete->next;
    queue = queue->prev;
  }
  return 1;
}

liste inverseEtAdditionne(liste l){
  int pos, retenue, val;
  liste tmp, res, tete, queue;
  if (l == NULL)
    return NULL;
  tete = l;
  queue = l;
  while (queue->next)
    queue = queue->next;
  pos = 1;
  retenue = 0;
  res = NULL;
  while(1){
    val = tete->val + queue->val + retenue;
    if (val > 9){
      retenue = 1;
      val %= 10;
    }
    else
      retenue = 0;
    insererEnTete(&res, pos, val);
    tete = tete->next;
    queue = queue->prev;
    pos++;
    if (!tete && !queue){
      if (retenue)
	insererEnTete(&res, pos, 1);
      break;
    }
  }
  return res;
}


int main(int argc, char *argv[]){
  liste l, a;
  int n = 2015;
  if (argc > 1)
    n = atoi(argv[1]);
  l = convertionEntierListe(n);
  afficherListe(l);
  a = inverseEtAdditionne(l);
  afficherListe(a);
  freeListe(&l);
  freeListe(&a);

  return 0;
}
