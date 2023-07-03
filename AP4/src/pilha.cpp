#include "pilha.hpp"

Pilha::Pilha(int capacidade) {
  fila1 = new FilaCircular(capacidade);
  fila2 = new FilaCircular(capacidade);

  tamanho = 0;
}

Pilha::~Pilha() {
  delete fila1;
  delete fila2;
}

bool Pilha::vazia() {
  return (tamanho == 0);
}

void Pilha::empilhar(int valor) {
  fila2->enfileira(valor);

  while(!fila1->vazia()) {
    fila2->enfileira(fila1->desenfileira());
  }

  FilaCircular *aux = fila1;
  fila1 = fila2;
  fila2 = aux;

  tamanho++;

  std::cout << "Digito " << valor << " empilhado!\n";
}

int Pilha::desempilhar() {
  if(!vazia()) {
    int elemento = fila1->desenfileira();
    tamanho--;
    return elemento;
  } else {
    std::cout << "Erro: pilha vazia!" << std::endl;
    exit(EXIT_FAILURE);
  }
}