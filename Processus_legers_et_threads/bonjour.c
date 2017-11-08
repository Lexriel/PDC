/**********************************************************************
 * bonjour.c
 *
 *
 * gcc -Wall bonjour.c -o bonjour -pthread
 *
 *  (François lemaire)  <lemaire@lifl.fr> 
 * Time-stamp: <2014-06-03 16:31:19 francois>
 ***********************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <pthread.h>
#include <unistd.h>

void* bonjour(void *arg) {
  int i;
  i = *((int *)arg);
  free(arg);
  printf("Bonjour %d!\n", i);
  
  pthread_exit(NULL);
}

int main(int argc, char *argv[]) {

  int i;
  int *arg;
  pthread_t ths[5];

  for (i=0;i<5;i++) {
    arg = (int*)malloc(sizeof(int));
    *arg = i;
    if (pthread_create(&ths[i], NULL, bonjour, (void*)arg)) {
      fprintf(stderr, "Erreur de création");
      exit(EXIT_FAILURE);
    }
  }

  for (i=0;i<5;i++) {
    pthread_join(ths[i], NULL);
  }

  
  exit(EXIT_SUCCESS);
}


