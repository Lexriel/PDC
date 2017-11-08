# include <stdio.h>       

int main(int argc, char *argv[], char **arge) {
	
   while(*arge)
      printf("%s\n",*(arge++)) ; 
  return 0;
}
