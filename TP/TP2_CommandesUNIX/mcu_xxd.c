#include <stdio.h>
#include "mcu_macros.h"
#include "mcu_affiche_entier.h"
#include "mcu_readl.h"
#define OUTPUTLINESIZE 8+1+8*(4+1)+1+16

int main (int argc, char *argv[]){
  int i, j, d, nbcol, tmp;
  int c;
  int outputline[OUTPUTLINESIZE] = {'0','0','0','0','0','0','0',':'};
  int hexa[16];

  for(j=8; j<OUTPUTLINESIZE; j++)
    outputline[j]=' ';
 
  for(i=0; i<10; i++)
    hexa[i] = '0'+i;
  for(i=0; i<6; i++) 
    hexa[i+10] = 'a'+i;

  nbcol = 0 ; d = 9 ;
  while ((c=getchar()) != EOF){
    if(!(nbcol%16) && nbcol !=0){  
      d = 9;
      for(j=0; j<OUTPUTLINESIZE; j++) 
	putchar(outputline[j]);
      putchar('\n') ;
      for(j=8; j<OUTPUTLINESIZE; j++)
	outputline[j]=' ';
      tmp = nbcol;
      for(j=6 ; j != 0; j--){
	outputline[j] = hexa[tmp%16];
	tmp /= 16;
      }
    }
    outputline[d+nbcol%16] = hexa[c/16];
    outputline[d+1+nbcol%16] = hexa[c%16];    
    if (nbcol%2) d += 2 ; else d += 1; 
    if (( c > 31) && (c < 128))
      outputline[50+nbcol%16] = c;
    else outputline[50+nbcol%16] = '.';
    nbcol++;
  }
  if(nbcol % 16){  
    for(j=0; j<OUTPUTLINESIZE; j++) 
      putchar(outputline[j]);
    putchar('\n');
  }
  return 0;
}
