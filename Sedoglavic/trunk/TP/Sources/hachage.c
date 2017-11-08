#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define N 113
#define b 128
#define TailleTable 200
#define Vide -2 
#define PasDeCollision -1

typedef struct cellule{
  char *nom ;
  unsigned int tel ;
  int collision ;
} cellule ;

cellule table[TailleTable] ;

int FinDeTable = N+1 ;

int hachage(char *str){

  int res = 0 ;

  while(*str!=0)
    res = (res*b + *(str++)) % N  ;

  return res ;
}

int Rechercher(char *str){

  int res = hachage(str) ;

  if(table[res].nom==NULL) return -1 ;

  while(strcmp(table[res].nom,str)){
    res = table[res].collision ;
    if (res==PasDeCollision) 
      return -1 ;
  }

  return table[res].tel ;
      
}

void Inserer(char * str, unsigned int tel){

  unsigned int i = hachage(str) ;
  
  if(table[i].collision == Vide){
    /* Si l'indice est libre */
    table[i].nom = (char *) malloc(strlen(str)) ;
    table[i].tel = tel ;
    strcpy(table[i].nom,str) ;
    table[i].collision = PasDeCollision ;
  }
  else{
    int j = FinDeTable ;
    while(table[j].collision != Vide ) 
      j ++ ;
    table[j].nom = (char *) malloc(strlen(str)) ;
    strcpy(table[j].nom,str) ;
    table[j].collision = table[i].collision ;
    table[i].collision = j ;
    table[j].tel = tel ;
  }
}

int main(void){

  int i ;
  for(i=0;i< TailleTable ; i++)
    table[i].collision = -2 ;

  char *str = (char *) malloc(100) ;
  char *fin = "fin" ;
  while(1){
    printf("entrer la cha\\^ine => ");
    scanf("%s",str) ;
    if (!strcmp(str,fin)) break ;
    printf("la clef est %d\n",hachage(str));
    printf("entrer le num\\'ero => ");
    scanf("%d",&i) ;
    Inserer(str,i) ;
  }

  while(1){
    printf("entrer la cha\\^ine \\`a chercher=> ");
    scanf("%s",str) ;
    if (!strcmp(str,fin)) break ;
    printf("Le num\\'ero est %d\n",Rechercher(str)) ;
  }

  return 0 ;
}
 
