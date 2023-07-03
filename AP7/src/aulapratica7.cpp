#include <aulapratica7.hpp>

int *gerarVetorAleatorio(int tamanho) {
  int *vetor = new int[tamanho];

  // Semente para geração de números aleatórios
  std::srand(std::time(nullptr));

  for (int i = 0; i < tamanho; ++i) {
    // Gera um número aleatório entre 1 e 100
    vetor[i] = std::rand() % 100 + 1;
  }

  return vetor;
}

// Função para ajustar um heap máximo
void maxHeapify(int vet[], int tamanho, int root) {
  int largest = root;       // Inicializa o maior elemento como a raiz
  int left = 2 * root + 1;  // Filho esquerdo
  int right = 2 * root + 2; // Filho direito

  // Se o filho esquerdo é maior que a raiz
  if (left < tamanho && vet[left] > vet[largest]) {
    largest = left;
  }

  // Se o filho direito é maior que o maior até agora
  if (right < tamanho && vet[right] > vet[largest]) {
    largest = right;
  }

  // Se o maior não é a raiz
  if (largest != root) {
    int temp = vet[root];
    vet[root] = vet[largest];
    vet[largest] = temp;

    // Chama recursivamente a função em subárvore afetada
    maxHeapify(vet, tamanho, largest);
  }
}

// Função principal do Heapsort
void heapSort(int vet[], int tamanho) {
  // Constrói o heap máximo
  for (int i = tamanho / 2 - 1; i >= 0; i--) {
    maxHeapify(vet, tamanho, i);
  }

  // Extrai um elemento por vez do heap
  for (int i = tamanho - 1; i >= 0; i--) {
    // Move a raiz atual para o final
    int temp = vet[0];
    vet[0] = vet[i];
    vet[i] = temp;

    // Chama a função para ajustar o heap reduzido
    maxHeapify(vet, i, 0);
  }
}

// Função para encontrar o próximo número de Fibonacci menor ou igual a 'n'
int proxFibonacci(int n) {
  int a = 0, b = 1, c = a + b;

  while (c <= n) {
    a = b;
    b = c;
    c = a + b;
  }
  return a;
}

// Implementação do algoritmo Shell Sort com a sequência de Fibonacci
void shellSort(int vet[], int n) {
  int i, j, value;
  int h = proxFibonacci(n);

  while (h > 0) {
    for (i = h; i < n; i++) {
      value = vet[i];
      j = i;

      while (j >= h && vet[j - h] > value) {
        vet[j] = vet[j - h];
        j = j - h;
      }

      vet[j] = value;
    }

    h = proxFibonacci(h - 1); // Atualização de 'h' para o próximo número de Fibonacci menor que o valor anterior
  }
}