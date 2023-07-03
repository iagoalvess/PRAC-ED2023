#ifndef PILHA_H
#define PILHA_H

#include "filacircular.hpp"

class Pilha {
private:
  FilaCircular *fila1, *fila2;

  int tamanho;

public:
  Pilha(int capacidade);
  ~Pilha();

  bool vazia();

  void empilhar(int valor);

  int desempilhar();
};

#endif