#include <chrono>
#include <iostream>
#include <iomanip>

#include "aulapratica7.hpp"

int main() {
  const int num_vetores = 1000;
  const int tamanho_vetor = 100;
  const int num_iteracoes = 100;

  double media_total = 0.0;

  for (int k = 0; k < num_iteracoes; ++k) {
    int media = 0;

    for (int i = 0; i < num_vetores; ++i) {
      int* vetor = gerarVetorAleatorio(tamanho_vetor);

      auto inicio = std::chrono::high_resolution_clock::now();

      shellSort(vetor, tamanho_vetor);

      auto fim = std::chrono::high_resolution_clock::now();

      auto duracao = std::chrono::duration_cast<std::chrono::microseconds>(fim - inicio);

      media += duracao.count();

      delete[] vetor;
    }

    double media_iteracao = static_cast<double>(media) / num_vetores;
    media_total += media_iteracao;

  }

  double media_final = media_total / num_iteracoes;
  std::cout << "Média final shellsort: " << std::fixed << std::setprecision(2) << media_final << std::endl;

  double media_totalH = 0.0;

  for (int k = 0; k < num_iteracoes; ++k) {
    int media = 0;

    for (int i = 0; i < num_vetores; ++i) {
      int* vetor = gerarVetorAleatorio(tamanho_vetor);

      auto inicio = std::chrono::high_resolution_clock::now();

      heapSort(vetor, tamanho_vetor);

      auto fim = std::chrono::high_resolution_clock::now();

      auto duracao = std::chrono::duration_cast<std::chrono::microseconds>(fim - inicio);

      media += duracao.count();

      delete[] vetor;
    }

    double media_iteracaoH = static_cast<double>(media) / num_vetores;
    media_totalH += media_iteracaoH;

  }

  double media_finalH = media_totalH / num_iteracoes;
  std::cout << "Média final heapsort: " << std::fixed << std::setprecision(2) << media_finalH << std::endl;

  return 0;
}
