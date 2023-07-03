#include "fatorial.hpp"

int fatorial_recursivo(int n) {
    if (n == 0) {
        return 1;
    } else {
        return n * fatorial_recursivo(n - 1);
    }
}

int fatorial_iterativo(int n) {
    int resultado = 1;
    for (int i = 1; i <= n; i++) {
        resultado *= i;
    }
    return resultado;
}
