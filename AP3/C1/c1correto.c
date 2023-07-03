#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv){
  int i;
  //Tive que acrescentar (int *) por um problema em meu compilador que é de C++
  int *a = (int *) malloc(sizeof(int) * 10);
  if (!a) return -1; /*malloc failed*/
  for (i = 0; i < 10; i++){
    a[i] = i;
  }
  free(a);
  return 0;
}