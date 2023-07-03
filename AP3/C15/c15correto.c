#include <stdio.h>
#include <stdlib.h>

int inc(int a) {
  return a+1;
}

int main(int argc, char** argv) {
  int *a = (int *) malloc(sizeof(int));

  *a = 1;

  for(int i=1; i < 5; i++) {
     *a = inc(*a);
  }

  free(a);

  return 0;
}
