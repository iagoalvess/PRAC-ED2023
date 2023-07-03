#include "fatorial.hpp"
#include "fibonacci.hpp"

#include <iostream>

int main() {
    int opcao, valor;

    do {
        std::cout << "Escolha uma opcao:" << std::endl;
        std::cout << "1 - Calcular fatorial" << std::endl;
        std::cout << "2 - Calcular fibonacci" << std::endl;
        std::cout << "0 - Sair" << std::endl;
        std::cin >> opcao;

        switch (opcao) {
            case 1:
                std::cout << "Digite um valor: ";
                std::cin >> valor;
                std::cout << "Fatorial recursivo de " << valor << " = " << fatorial_recursivo(valor) << std::endl;
                std::cout << "Fatorial iterativo de " << valor << " = " << fatorial_iterativo(valor) << std::endl;
                break;
            case 2:
                std::cout << "Digite um valor: ";
                std::cin >> valor;
                std::cout << "Fibonacci recursivo de " << valor << " = " << fibonacci_recursivo(valor) << std::endl;
                std::cout << "Fibonacci iterativo de " << valor << " = " << fibonacci_iterativo(valor) << std::endl;
                break;
            case 0:
                std::cout << "Saindo..." << std::endl;
                break;
            default:
                std::cout << "Opcao invalida!" << std::endl;
                break;
        }

    } while (opcao != 0);

    return 0;
}