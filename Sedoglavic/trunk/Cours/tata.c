#include <stdio.h>
#include <setjmp.h>
int main (void)
{
jmp_buf env;
int i = setjmp(env) ; /* au premier appel setjmp retourne 0 */
printf("i= %d\n",i);
if(i == 2) return 0 ;
longjmp(env,2) ; /* on branche sur setjmp en retournant 2 */
return 1 ; /* cette instruction n'est jamais ex\'ecut\'ee */
}
