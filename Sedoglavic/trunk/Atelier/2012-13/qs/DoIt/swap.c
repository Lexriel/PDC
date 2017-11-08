/* lefils valentin */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void swap (void *const a, void *const b, size_t size)
{
   void *const temp = malloc(size);
   memcpy(temp, a, size);
   memcpy(a, b, size);
   memcpy(b, temp, size);

   free(temp);
}
