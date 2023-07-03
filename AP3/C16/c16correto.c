#include <stdio.h>
#include <stdlib.h>

int actual_calc(int a, int b){
  if (b == 0) {
    printf("Erro divisão por zero\n");
    return 1;
  }

  int c;
  c=a/b;
  return 0;
}

int calc(){
  int a;
  int b;
  a=13;
  b=0;
  actual_calc(a, b);
  return 0;
}

int main(){
  calc();
  return 0;
}
