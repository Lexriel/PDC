#include <stdlib.h>
#define BUFFERSIZE 65536

int main(void){
 void *buffer ;
 int i,res ;
 res = posix_memalign(&buffer, 2*sizeof(void *), BUFFERSIZE);
 int *ptr = (int *) ptr ;
 if(res)
   for(i=0;i<BUFFERSIZE+10;i++)
	ptr[i]=0 ;
 return res ;
}
 

