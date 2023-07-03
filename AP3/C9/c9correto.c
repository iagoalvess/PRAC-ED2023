 #include <stdlib.h>

void f(void) {

int* x = (int *) malloc(10 * sizeof(int));
x[9] = 0; 
free(x);
}

int main(void) {

f();

return 0;
}