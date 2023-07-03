#include "memlog.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int *gerarVetorAleatorio(int tamanho) {
  int *vetor = (int *)malloc(tamanho * sizeof(int));
  LEMEMLOG(sizeof(int), tamanho * sizeof(int), 1); // Registro de leitura de vetor

  // Semente para geração de números aleatórios
  srand(time(NULL));

  for (int i = 0; i < tamanho; ++i) {
    // Gera um número aleatório entre 1 e 100
    vetor[i] = rand() % 100 + 1;
  }

  return vetor;
}

void insertionSort(int arr[], int n) {
  for (int i = 1; i < n; i++) {
    int key = arr[i];
    int j = i - 1;

    while (j >= 0 && arr[j] > key) {
      arr[j + 1] = arr[j];
      ESCREVEMEMLOG((j + 1) * sizeof(int), sizeof(int), 3); // Registro de escrita de elemento no vetor
      j = j - 1;
    }
    arr[j + 1] = key;
    ESCREVEMEMLOG((j + 1) * sizeof(int), sizeof(int), 3); // Registro de escrita de elemento no vetor
  }
}

int main() {
  const int tamanho_vetor = 100;

  iniciaMemLog("memlog.txt"); // Inicializa o registro de acessos

  int *vetor = gerarVetorAleatorio(tamanho_vetor);

  ESCREVEMEMLOG(0, tamanho_vetor * sizeof(int), 2); // Registro de escrita de vetor

  insertionSort(vetor, tamanho_vetor);

  free(vetor);

  finalizaMemLog(); // Finaliza o registro de acessos

  return 0;
}
