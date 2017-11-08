#include<stdlib.h>
#include<stdio.h>
#include"bmp.h"

/* --------------------------------------------------------------------------------------------

Cette fonction charge l'ent\^ete d'un fichier BMP d\'ej\`a ouvert.

Elle retourne un pointeur sur une structure de type BMPHeader_t.

Les valeurs de retour sont~:
   NULL en cas d'impossibilit\'e d'ouvrir le fichier~;
   un pointeur sur une structure de type BMPHeader_t.
*/

BMPHeader_t *loadBMPHeader(FILE *fichier){
  
  BMPHeader_t *res = (BMPHeader_t *) malloc(sizeof(BMPHeader_t)) ;
  
  if(    fscanf(fichier,"%2c",res->Identifier) +
	 fread(&(res->FileSize),4,6,fichier) +
	 fread(&(res->Planes),2,1,fichier) +
	 fread(&(res->BitsPerPixels),2,1,fichier) +
	 fread(&(res->Compression),4,6,fichier) 
	 != 
	 NBITEMS_BMPHEADER
	 ) return NULL ;
  
  return res ;
}

/* --------------------------------------------------------------------------------------------

Cette fonction v\'erifie l'ent\^ete d'un fichier BMP

Elle retourne~:
    1 si l'ent\^ete est correct~;
    0 sinon

*/

int isBMPHeaderCorrect(BMPHeader_t *header){

  if( header->Identifier[0]  != 'B' || 
      header->Identifier[1]  != 'M' 
      ){
    fprintf(stderr,"Attention : mauvaises lettres magiques\n") ;
     return 0 ;
  }
  if( header->BitmapDataSize != header->Width * header->Height * 3){
    fprintf(stderr,"Attention : la taille des donn\\'ees n'est pas correcte\n") ;
    return 0 ;
  }
	 
  if( header->BitsPerPixels  != 24 ){
    fprintf(stderr,"Attention : le codage des pixels n'est pas RGB\n") ;
    return 0 ;
  }

  if(header->Compression){
    fprintf(stderr,"Attention : fichier BMP compress\\'e\n") ;
    return 0 ;
  }

  return 1 ;
}

/* --------------------------------------------------------------------------------------------

cette fonction ouvre un fichier BMP.
De l'espace m\'emoire est r\'eserv\'e pour~:
    - l'ent\^ete (point\'ee par Header)~;
    - un tampon contenant les pixels (point\'e par Data).

Par la suite, on souhaite sauver le contour sous format BMP
L'ent\^ete sera utilis\'ee par la suite pour sauver le contour.
Les donn\'ees seront analys\'ees et utils\'ees pour sauver le contour.

Les valeurs de retour sont~:
   NULL en cas de pb~;
   un pointeur FILE associ\'e au fichier BMP
*/

FILE *openBMP(const char *path, BMPHeader_t **Header, char **Data){

  FILE *fd = NULL ;
  /* Ouvrons le fichier BMP */
  if(!(fd=fopen(path,"r"))){
    fprintf(stderr,"Ouverture du fichier impossible\n") ;
    return NULL ; 
  }
  /* Chargeons l'ent\^ete en m\'emoire */
  if(!(*Header=loadBMPHeader(fd))){
    fprintf(stderr,"Impossible de charger l'ent\\^ete en m\\'emoire\n") ;
    return NULL ;
   }
   if(!isBMPHeaderCorrect(*Header)){
    fprintf(stderr,"L'ent\\^ete n'est par correcte\n") ;
     return NULL ;
 }
  if(!(*Data = (char *) malloc((*Header)->BitmapDataSize))) 
    return NULL ;

  fread(*Data,(*Header)->BitmapDataSize,1,fd) ;
  
  return fd;
}

/* --------------------------------------------------------------------------------------------

Cette fonction ferme un fichier BMP.
De l'espace m\'emoire est lib\'er\'e~:
    - l'ent\^ete (point\'ee par Header)~;
    - un tampon de taille BUFSIZE contenant une partie des pixels
    (point\'e par Data).

Les valeurs de retour sont~:
   le retour de fclose~;
*/

int closeBMP(FILE *file, BMPHeader_t *Header, char *Data){
  
  free(Header) ;
  free(Data) ;

  return fclose(file) ;
}

/* --------------------------------------------------------------------------------------------

Cette fonction construit un un fichier BMP \`a partir
de l'ent\^ete (point\'ee par Header) et d'un buffer de pixels.

Les valeurs de retour sont~:
   -1 en cas de probl\`eme avec l'ouverture d'un fichier~;
   le retour de fclose~;
*/

int createBMP(const char * path, BMPHeader_t *Header, char *Data){ 

  FILE *fd = NULL ; 
   /* Ouvrons le fichier BMP */
   if((fd=fopen(path,"w"))==NULL) 
     return -1 ;

   if(!isBMPHeaderCorrect(Header))
     return -1 ; 
  
   fwrite(&(Header->Identifier),1,2,fd) ; 
   fwrite(&(Header->FileSize),4,6,fd) ;  
   fwrite(&(Header->Planes),2,1,fd) ; 
   fwrite(&(Header->BitsPerPixels),2,1,fd) ; 
   fwrite(&(Header->Compression),4,6,fd) ; 
   fwrite(Data,Header->BitmapDataSize,1,fd) ;

   return fclose(fd) ;
} 
