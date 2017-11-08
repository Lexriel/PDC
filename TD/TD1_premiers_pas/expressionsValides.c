# include <stdio.h>
# include <stdlib.h>

int main(){
  int A = 20; 
  int B = 5;
  int C = -10;
  int D = 2;
  int X = 12;
  int Y = 15;
  int temp;

  printf("(5*X + 2*3*B/4) = %d\n", 5*X + 2*3*B/4);
  getchar();
  printf("(A += X+2)  = %d\n", A += X+2);
  A = 20;
  getchar();
  printf("(A \%= D++) = %d ; D = %d\n", A %= D++, D);
  D--; A = 20;
  getchar();
  printf("(A \%= ++D) = %d ; D = %d\n", A %= ++D, D);
  D--; A = 20;
  getchar();
  printf("((X++)*A + C) = %d, X = %d\n", (X++)*A + C, X);
  X--;
  getchar();
  printf("(A-A == B-B) = %d\n", A-A == B-B);
  getchar();
  printf("(!(X-D+C) || D) = %d\n", !(X-D+C) || D);
  getchar();
  printf("(A && B || !0) = %d\n", A && B || !0);
  getchar();
  printf("( (1<<(2<<1)) == ((1<<2)<<1) ) = %d\n", (1<<(2<<1)) == ((1<<2)<<1));

  return 0;
}
