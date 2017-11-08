# include <stdio.h>

int main()
{
  char c;

  printf("Rentrer un caractère : ");
  c = getchar();
  printf("Le caractère entré est :");
  putchar(c);
  printf("\n");

  return 0;
}
