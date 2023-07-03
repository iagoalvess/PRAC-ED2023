#include "fibonacci.hpp"

int fibonacci_recursivo(int n) {
    if (n == 0 || n == 1) {
        return n;
    } else {
        return fibonacci_recursivo(n - 1) + fibonacci_recursivo(n - 2);
    }
}

int fibonacci_iterativo(int n) {
    if (n == 0 || n == 1) {
        return n;
    }

    int fib1 = 0, fib2 = 1, resultado;
    for (int i = 2; i <= n; i++) {
        resultado = fib1 + fib2;
        fib1 = fib2;
        fib2 = resultado;
    }

    return resultado;
}