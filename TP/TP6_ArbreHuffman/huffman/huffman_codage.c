# include <stdio.h>
# include <stdlib.h>

# define HUFFMANCODAGESIZE 20

typedef float freq_t[1<<8];
typedef char *codingtable_t[1<<8];
struct noeud_m{
  unsigned char lettre;
  float freq;
  int index;
  char codage[HUFFMANCODAGESIZE];
  struct noeud_m *fg, *fd;
};

struct foret_m{
  struct foret_m *next;
  struct noeud_m *arbre;
};

typedef struct foret_m *foret_t;
typedef struct noeud_m *arbrebinaire_t;

void frequence(freq_t, FILE *);
arbrebinaire_t construirecodage(freq_t);

void frequence(freq_t tab, FILE *file){
  long unsigned int nblettre; /* peut poser pb si le texte fait plus de 1<<64 lettres */
  unsigned char stck;
  int i;
  for(i=0; i<(1<<8); i++)
    tab[i] = 0;
  nblettre = 0;
  while(1){
    if (fread(&stck, sizeof(char), 1, file) == 0)
      break;
    tab[stck]++;
    nblettre++;		
  }
  for(i=0; i<(1<<8); i++)
    tab[i] /= nblettre; 
  return;
}

void insererdansforet(foret_t *foret,foret_t cellule){
  if((*foret) == NULL){
    *foret = cellule;
    return;
  }

  if (cellule->arbre->freq <= (*foret) -> arbre -> freq){
    cellule -> next = (*foret);
    *foret = cellule;
    return;
  }

  return insererdansforet(&((*foret)->next), cellule);
}

arbrebinaire_t construirecodage(freq_t tab){
  unsigned int i, j;
  foret_t foret, tmpforet;
  arbrebinaire_t tmparbre;
  foret = NULL;	
  /* construction de la forêt */
  for(i=0; i<(1<<8); i++) 
    if (tab[i] != 0){
      /* la foret est triée par orbre croissant des fréquences */
      tmpforet = (foret_t) malloc(sizeof(struct foret_m));
      tmpforet -> next = NULL;
      tmpforet -> arbre = (arbrebinaire_t) malloc(sizeof(struct noeud_m));
      tmpforet -> arbre -> lettre = i;
      tmpforet -> arbre -> freq = tab[i];
      tmpforet -> arbre -> fg = tmpforet -> arbre -> fd = NULL;
      tmpforet -> arbre -> index = 0;
      for(j=0; j<HUFFMANCODAGESIZE; j++)
	(tmpforet -> arbre -> codage)[j] = 0;
      insererdansforet(&foret,tmpforet);
    }

  while(1){
    if (foret->next == NULL){
      /* il n'y a plus qu'un arbre */
      tmparbre  = foret -> arbre;
      free(foret);
      return tmparbre;
    }
    /* il en reste au moins 2 arbres dans la for\^et */
    tmparbre = (arbrebinaire_t) malloc(sizeof(struct noeud_m));
    tmparbre -> index = 0;
    for(j=0; j<HUFFMANCODAGESIZE; j++) (tmparbre -> codage)[j] = 0;
    tmpforet = foret;
    foret = foret -> next;
    tmparbre -> fg = tmpforet -> arbre;
    free(tmpforet);
    tmpforet = foret;
    foret = foret -> next;
    tmparbre -> fd = tmpforet -> arbre;
    tmparbre -> freq = tmparbre -> fd -> freq + tmparbre -> fg -> freq;
    tmpforet -> arbre = tmparbre;
    tmpforet -> next = NULL;
    insererdansforet(&foret, tmpforet);
  }
  /* this should never happen */
  return NULL;
}

void tabledecodage(arbrebinaire_t arbre, FILE *file, codingtable_t tab){
  int i;
  if(arbre->fg == NULL && arbre->fd == NULL){
    fprintf(file, "\n%d=%s", arbre->lettre, arbre->codage);
    tab[arbre->lettre] = arbre->codage;
    return;
  }

  if(arbre->fg != NULL){
    if(arbre->fg->index == 0){
      for(i=0; i<=arbre->index; i++) 
	arbre->fg->codage[i] = arbre -> codage[i];
      (arbre->fg->index) = (arbre->index) + 1;
      arbre->fg->codage[arbre->index] = '1';
    }
    tabledecodage(arbre->fg, file, tab);
  }
  if (arbre->fd != NULL){
    if(arbre->fd->index == 0){
      for(i=0; i<=arbre->index; i++) 
	arbre->fd->codage[i] = arbre -> codage[i];
      (arbre->fd->index) = (arbre -> index) + 1;
      arbre->fd->codage[arbre->index] = '0';
    }
    tabledecodage(arbre->fd, file, tab);
  }
  return;
}

struct bit_buffer{
  unsigned char nextfreebyte; 
  unsigned char tampon; /* espace de stockage */
};

void positionner_bit(unsigned char *c,unsigned char pos,unsigned char bit){
  if (bit == '1')
    *c=(*c)|(1<<pos);
  else
    *c=(*c)&~(1<<pos);
  return;
}

void compressfile(FILE *file, codingtable_t tab, FILE *file2){
  char stck;
  struct bit_buffer buffer;
  unsigned int j;
  rewind(file);
  buffer.nextfreebyte = 0;
  while(1){
    if (fread(&stck, sizeof(char), 1, file) == 0){
      if((buffer.nextfreebyte%8)!=0)
	fwrite(&(buffer.tampon),sizeof(char),1,file2);
      break;
    }
    for(j=0; tab[(int) stck][j]; j++){
      positionner_bit(&(buffer.tampon), buffer.nextfreebyte, tab[(int)stck][j]);
      buffer.nextfreebyte++;
      if((buffer.nextfreebyte % 8) == 0){
	fwrite(&(buffer.tampon), sizeof(char), 1, file2);
	buffer.nextfreebyte = 0;
      }
    }
  }

  return;
}

int main(int argv, char **argc){
  FILE *file, *file2;
  freq_t freqtab;
  arbrebinaire_t Huffman;
  codingtable_t codtab;
  if(argv != 3)
    printf("Wrong number of parameters.\n %s filetocompress compressedfile\n", argc[0]);

  file = fopen(argc[1], "r");
  frequence(freqtab, file);

  Huffman = construirecodage(freqtab);
  file2 = fopen(argc[2], "w");
  fprintf(file2, "MAGICHUFFMAN");
  tabledecodage(Huffman, file2, codtab);
  fprintf(file2, ";\n");
  compressfile(file, codtab, file2);

  fclose(file);
  fclose(file2);

  return 0;
}
