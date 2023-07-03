#include "ConjuntoDisjunto.hpp"

ConjuntoDisjunto::ConjuntoDisjunto() {
  // Construtor padrão
}

ConjuntoDisjunto::~ConjuntoDisjunto() {
  delete[] pai;
  delete[] tamanho;
}

void ConjuntoDisjunto::makeSet(long elemento) {
  contador = elemento;
  pai = new int[elemento];
  tamanho = new int[elemento];

  for (int i = 0; i < elemento; i++) {
    pai[i] = i;     // Cada elemento é o seu próprio pai inicialmente
    tamanho[i] = 1; // Cada conjunto possui inicialmente apenas um elemento
  }
}

void ConjuntoDisjunto::unionSet(long elementoA, long elementoB) {
  long raizA = findSet(elementoA);
  long raizB = findSet(elementoB);

  if (raizA == raizB) {
    return; // Os elementos já estão no mesmo conjunto
  }

  // Faz a raiz do menor conjunto apontar para a raiz do maior conjunto
  if (tamanho[raizA] < tamanho[raizB]) {
    pai[raizA] = raizB;
    tamanho[raizB] += tamanho[raizA];
  }
  else {
    pai[raizB] = raizA;
    tamanho[raizA] += tamanho[raizB];
  }

  contador--; // Decrementa o número de conjuntos após a união
}

long ConjuntoDisjunto::findSet(long elemento) {
  long raiz = elemento;

  // Encontra a raiz do conjunto
  while (raiz != pai[raiz]) {
    raiz = pai[raiz];
  }

  // Aplica a compressão de caminho para otimização
  while (elemento != raiz) {
    long novoPai = pai[elemento];
    pai[elemento] = raiz;
    elemento = novoPai;
  }

  return raiz;
}