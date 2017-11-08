#include <stdio.h>
#include <stdlib.h>

struct noeud_m{
  unsigned char lettre;
  struct noeud_m *fg;
  struct noeud_m *fd;
};

typedef struct noeud_m *arbrebinaire_t;

char teste_bit(unsigned char c, unsigned int pos){
  return (c&(1<<pos))?'1':'0';
}

int ConstruireArbre(unsigned char c, arbrebinaire_t arbre, unsigned char *str){
  switch(*str){
  case '\n':
    arbre->lettre= c;
    return 0==1;
  case ';' :
    arbre->lettre= c;
    return 1==1;
  case '1' :{
    if (arbre->fg == NULL){
      arbre -> fg = (arbrebinaire_t) malloc(sizeof(struct noeud_m));
      arbre -> fg -> fg = arbre -> fg -> fd = NULL;
    }
    return ConstruireArbre(c, arbre->fg, str+1);
  }
  case '0' :{
    if (arbre -> fd == NULL ){
      arbre -> fd = (arbrebinaire_t) malloc(sizeof(struct noeud_m));
      arbre -> fd -> fg = arbre -> fd -> fd = NULL;
    }
    return ConstruireArbre(c, arbre->fd, str+1);
  }
  default : exit(2); /* fichier mal formé */
  }

  exit(3); /* this should never happen */
}

int main(int argc, char **argv){
  FILE *file;
  unsigned int j;
  arbrebinaire_t Huffman, tmp;
  unsigned char stck;
  unsigned char *tampon; 
  unsigned long tamponsize;
  tampon = (unsigned char *) malloc(20 * sizeof(unsigned char));
  Huffman = (arbrebinaire_t) malloc(sizeof(struct noeud_m));
  Huffman -> fg = Huffman -> fd = NULL;
  if (argc != 2)
    printf("Wrong number of parameters.\n %s filetodecompress\n",argv[0]);
  file = fopen(argv[1], "r");
  getline((char **) &tampon, &tamponsize, file); /* on lit le magic number */
  while(1){
    fscanf(file,"%d",&j);
    getline((char **) &tampon, &tamponsize, file);
    if (ConstruireArbre(j, Huffman, tampon+1) == (1==1))
      break;
  }
  tmp = Huffman;
  while(1){
      if (fread(&stck, sizeof(char), 1, file) == 0)
	break;
      for(j=0; j<8; j++){
	if ((tmp->fg == NULL) && (tmp->fd == NULL)){
	  putchar(tmp->lettre);
	  tmp = Huffman;
	}
	if (teste_bit(stck, j) =='1')
	  tmp = tmp-> fg;
	else
	  tmp = tmp -> fd;
      }
  } 
  fclose(file);
  return 0;
}
