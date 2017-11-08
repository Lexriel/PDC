#include <stdio.h>
struct data_m
{
char chiffre ;
int iteration ;
char modulo ;
};
typedef struct data_m data_t ;
void
Traduction
(char *texte)
{
data_t data ;
char tab[10] = "  ADGJMPTW" ;
if(!*texte)
   return ;
if((*texte<'1' || *texte>'9') && *texte!='#')
   Traduction(texte+1) ;
data.chiffre = *texte;
data.iteration = 0 ;
if(*texte=='1')
  data.modulo = 1 ;
else 
  data.modulo=(*texte=='9' || *texte=='7')?4:3 ;
texte++ ;
while(1)
{
if(!*texte)
{ 
putchar(tab[data.chiffre-'0']+(data.iteration % data.modulo)) ;
break ;
}
if((*texte<'1' || *texte>'9') && *texte!='#')
{
  texte++ ;
  continue ;
}
if(*texte==data.chiffre)
{
  data.iteration++ ;
  texte++;
  continue ;
}
while(*texte=='#')
  texte++ ;
if(!*texte)
  continue ;
putchar(tab[data.chiffre-'0']+(data.iteration % data.modulo)) ;
if(*texte>'0' && *texte<'9'+1)
{
data.chiffre = *texte;
data.iteration = 0 ;
if(*texte=='1')
  data.modulo = 1 ;
else 
  data.modulo=(*texte=='9' || *texte=='7')?4:3 ;
}
texte++ ;
}
putchar('\n');
}
