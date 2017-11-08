#include"bmp.h"
#include<stdio.h>

extern FILE *openBMP(const char *, BMPHeader_t **, char **) ;
extern int closeBMP(FILE *, BMPHeader_t *, char *) ;
extern int createBMP(const char *, BMPHeader_t *, char *) ;

BMPHeader_t *loadBMPHeader(FILE *) ;
int isBMPHeaderCorrect(BMPHeader_t *) ;
