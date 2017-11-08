#include <stdlib.h>

unsigned char *
merge
(unsigned char *string1, unsigned char *string2)
{
  unsigned char * str ;
  unsigned char res[256] ;
  int size,i ;
  if(!string1)
    return string2 ;
  if(!string2)
    return string1 ;
  size = 0;

do
    {
      if(*string1>*string2)
	  res[size]=*string2?*(string2++):*(string1++) ;
      
      else 
	{
	  if(*string1<*string2) 
	    res[size]=*string1?*(string1++):*(string2++) ;
	  else if(*string1==*(string2))
	    {
	      res[size]=*(string1++);
	      string2++ ;
	    }
	}
	size++ ;
	if((*string1=='\0') && (*string2=='\0'))
	  break ;
    }  while(1) ;
  
  res[size]=0 ;
  str = (unsigned char *)malloc(size*sizeof(char));
  for(i=0;i<=size;i++)
    str[i]=res[i] ;
  return str ;
}
