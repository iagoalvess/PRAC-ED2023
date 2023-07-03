#ifndef FILACIRCULAR_H
#define FILACIRCULAR_H

#include <iostream>

class FilaCircular {
private:
  int capacidade;
  int *dados;
  int primeiro, ultimo;
  int tamanho;

public:
  FilaCircular(int cap);
  ~FilaCircular();

  bool vazia();
  bool cheia();

  void enfileira(int elemento);

  int desenfileira();
};

#endif