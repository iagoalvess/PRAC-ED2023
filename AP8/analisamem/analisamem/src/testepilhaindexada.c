//---------------------------------------------------------------------
// Arquivo      : testepilhaindexada.c
// Conteudo     : programa para testar a biblioteca de pilhaindexada
// Autor        : Wagner Meira Jr. (meira@dcc.ufmg.br)
// Historico    : 2021-10-30 - arquivo criado
//              : 2021-11-08 - comentarios
//---------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "pilhaindexada.h"

// enderecos de 1 a 5
#define MAXEND 5

// vetor de acessos para teste
// -1 sinaliza o fim da sequencia
int acessos[]={
1,1,2,1,3,4,1,2,5,1,2,3,4,5,-1};

// como é apenas um teste, nao tem argc e argv
int main(){
  pilhaidx_t p;
  endinfoidx_t ei;
  endidx_t ea;
  int i,distpilha;

  // cria a pilha
  criapilhaidx(&p,MAXEND);

  // percorre o vetor de acesso empilhando
  i = 0;
  while (acessos[i] != -1){
    ei.tsec = i;
    ei.tnsec = 0;
    ei.fase = 0;
    distpilha = empilhaidx(&p,acessos[i],&ei);
    printf("empilha %d à %d = %d\n",i,acessos[i],distpilha);
    // imprime a pilha apos cada acesso para verificacao
    imprimepilhaidx(&p,stdout);
    i++;
  }

  // esvazia a pilha, aproveitando para verificar outras operacoes
  while(!pilhaidxvazia(&p)){
    desempilhaidx(&p,&ea,&ei);
    printf("desempilha %ld \n",ea);
    imprimepilhaidx(&p,stdout);
  }

  // impressao final
  imprimepilhaidx(&p,stdout);
  
  // desaloca a pilha
  destroipilhaidx(&p);

  return 0;
}
