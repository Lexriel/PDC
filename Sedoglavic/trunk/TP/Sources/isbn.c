#include <stdio.h>
#include <ctype.h>

int main(void) {
   int s, s2, i, fail;
   char str[100], *p;

   while (1 == scanf("%s", str)) {
      p = str;
      i = s = s2 = fail = 0;
      while (*p && !fail) {
         if (isdigit(*p)) {
            s += *p - '0';
            s2 += s;
            i++;
         } else if (*p == 'X') {
            s += 10;
            s2 += s;
            i++;
         } else if (*p != '-') {
            fail = 1;
         }
         p++;
      }
      if (i != 10 || s2%11) fail = 1;
      printf("%s is %scorrect.\n", str, fail ? "in" : "");
      scanf("%*[^\n]");
   }
   return 0;
}
 
