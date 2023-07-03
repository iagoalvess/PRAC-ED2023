#include <iostream>
#include <cstdlib>
#include <ctime>

#include "filacircular.hpp"
#include "pilha.hpp"

int main() {
  srand(time(NULL)); // Inicialização do gerador de números aleatórios

  int n = 10;
  Pilha p(n);

  for (int i = 0; i < n; i++) {
    int valor = rand() % 10; // Gera um dígito aleatório de 0 a 9
    p.empilhar(valor);   // Coloca o dígito gerado na pilha
  }
  
  std::cout << "\nDesempilhando elementos:\n";

  while (!p.vazia()) {
    int valor = p.desempilhar(); // Desempilhando item por item
    std::cout << valor << " ";
  }

  std::cout << "\n";

  return 0;
}