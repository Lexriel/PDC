#include<stdio.h>
#include<stdlib.h>

struct string_p {
	char           *string;	/* un pointeur sur un espace m\'emoire */
	unsigned int    stringsize;	/* de taille stringsize */
};
typedef struct string_p string_t;

struct GaussInt_p {
	unsigned int    reel;
	unsigned int    im;
};

typedef struct GaussInt_p GaussInt_t;

int
ScanInt
(int b, unsigned int *res)
{
int c ;
*res = 0;
while( ((c=getchar)!=EOF || c!=(int) '\n') && ( (c=c-(int) '0')>-1 && c <=b))
{
  *res *=b;
  *res += c ;
};
   return c+'0' ;
}

int
ScanString
(char *s, unsigned int stringsize)
{
	while(1)
	{
		if (!stringsize)
			return 1;
		*s = (char) getchar();
     		switch(*s)
     		{		
     			case EOF  : ;
     			case '\n' : *s = 0 ;
     			case 0    : break ;
     		} ;
     		s++ ;
     		stringsize-- ;
	} ;

	return 0;
}

int
mscanf(const char *format,...)
{

	enum {
		INIT, DIRECTIVE, GAUSS
	}               etat = INIT;
	int             tmp, base = 0;
	int            *ptr = (int *) &format + 1;

	while (*format) {
		switch (etat) {
		case INIT:
			if (*format == '%')
				etat = DIRECTIVE;
			else
				return 0;
			break;
		case DIRECTIVE:
			switch (*format) {
			case 'c':{
					*((char *) ptr) = (char) getchar();
					ptr++;
					etat = INIT;
				};
				break;
			case 's':{
					if (ScanString(((string_t *) ptr)->string,
					  ((string_t *) ptr)->stringsize))
						return 0;
					ptr++;
					etat = INIT;
				};
				break;
			case 'G':
				etat = GAUSS;
				break;
			default:
				return 0;
			};
			break;
		case GAUSS:{
				switch (*format) {
				case 'b':
					base = 2;
					break;
				case 'd':
					base = 10;
					break;
				default:
					return 0;
				};

				tmp = ScanInt(base, &((GaussInt_t *) ptr)->reel);

				if (tmp != '+')
					return 0;

				tmp = ScanInt(base, &((GaussInt_t *) ptr)->im);

				if (tmp != 'I')
					return 0;

				ptr++;
				etat = INIT;
			};
			break;
		default:
			return 0;
		}
		format++;
	}
	return 1;
}

int
main(void)
{
	char            tab[8];
	string_t        chaine;
	char            tab2[8];
	string_t        chaine2;

	GaussInt_t      essai;
	char            c;

	chaine.string = tab;
	chaine.stringsize = 8;

	chaine2.string = tab2;
	chaine2.stringsize = 8;

	printf("test caractere\n");
        if(!mscanf("%c",&c))
          printf("probleme avec le caractere\n") ;
        else  printf("%c\n",c) ;


        if(!mscanf("%Gd",&essai))
          printf("probleme avec l'entier de gauss decimal\n") ;
        else   printf("%u + %u \n",essai.reel,essai.im) ;

        if(!mscanf("%s",&chaine))
          printf("probleme avec la chaine\n") ;
        else printf("%s\n ",chaine.string) ;

	printf("char, string, gaussint, string\n") ;
	mscanf("%c%s%Gd%s", &c, &chaine2, &essai, &chaine);
	printf("%c | %s | %u + %u | %s\n", c, chaine2.string, essai.reel, essai.im, chaine.string);

	return 0;
}
