#include "filacircular.hpp"

FilaCircular::FilaCircular(int cap) {
  capacidade = cap;
  dados = new int [capacidade];
  primeiro = 0;
  ultimo = -1;
  tamanho = 0;
}

FilaCircular::~FilaCircular() {
  delete[] dados;
}

bool FilaCircular::vazia() {
  return (tamanho == 0);
}

bool FilaCircular::cheia() {
  return (tamanho == capacidade);
}

void FilaCircular::enfileira(int elemento) {
  if(!cheia()) {
    ultimo = (ultimo + 1) % capacidade;
    dados[ultimo] = elemento;
    tamanho ++;
  } else {
    std::cout << "Erro: fila cheia!" << std::endl;
    exit(EXIT_FAILURE);
  }
}

int FilaCircular::desenfileira() {
  if(!vazia()) {
    int elemento = dados[primeiro];
    primeiro = (primeiro + 1) % capacidade;
    tamanho--;
    return elemento;
  } else {
    std::cout << "Erro: fila vazia!" << std::endl;
    exit(EXIT_FAILURE);
  }
}