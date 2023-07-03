//---------------------------------------------------------------------
// Arquivo      : pilhaindexada.c
// Conteudo     : implementacao da biblioteca de pilha indexada
// Autor        : Wagner Meira Jr. (meira@dcc.ufmg.br)
// Historico    : 2021-10-30 - arquivo criado
//              : 2021-11-08 - comentarios
//---------------------------------------------------------------------

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "pilhaindexada.h"
#include "msgassert.h"

int elemidxempty(elemidx_t * el)
// Descricao: verifica se o elemento da pilha esta vazio
// Entrada: elemento el
// Saida: 1, se vazio, 0, se nao vazio
{
  erroAssert(el != NULL,"Elemento nulo");
  return ((el->ant == PILHAIDXNULO) && (el->prox == PILHAIDXNULO));
}

int endinfoidxcopia(endinfoidx_t * src, endinfoidx_t * dst)
// Descricao: copia informacao de um endereco src para dst
// Entrada: src
// Saida: dst
{
  erroAssert(src != NULL,"src nulo");
  erroAssert(dst != NULL,"dst nulo");
  dst->tsec = src->tsec;
  dst->tnsec = src->tnsec;
  dst->fase = src->fase;
  return 1;
}

void criapilhaidx(pilhaidx_t *p, endidx_t maxend)
// Descricao: inicializa a estrutura de dados pilha para um espaco de 
//            enderecamento entre 0 e maxend
// Entrada: p e maxend
// Saida: p
{
  long i;
  erroAssert(p != NULL,"p nulo");
  p->topo = PILHAIDXNULO;
  p->maxend = maxend;
  p->pilha = (elemidx_t*) malloc((maxend+1)*sizeof(elemidx_t));
  erroAssert(p->pilha != NULL,"nao foi possivel alocar p->pilha");
  for (i=0; i<=maxend; i++){
    p->pilha[i].ant = PILHAIDXNULO;
    p->pilha[i].prox = PILHAIDXNULO;
    p->pilha[i].info.fase = -1;
    p->pilha[i].info.tsec = -1;
    p->pilha[i].info.tnsec = 0;
  }
}

int pilhaidxvazia(pilhaidx_t * p)
// Descricao: verifica se a pilha p esta vazia
// Entrada: p 
// Saida: 1 - pilha vazia ou 0 - caso contrario
{
  erroAssert(p != NULL,"p nulo");
  return (p->topo == PILHAIDXNULO);
}

int empilhaidx(pilhaidx_t *p, endidx_t e,  endinfoidx_t * in)
// Descricao: empilha o endereço e com informacao in
// Entrada: p, e e in
// Saida: p
{
  int distpilha = 1;
  erroAssert(p != NULL,"p nulo");
  erroAssert(p->pilha != NULL,"p->pilha nulo");
  erroAssert(((e<=p->maxend) || (e>=0)),"e fora de faixa");
  if (elemidxempty(&(p->pilha[e]))){
    // primeiro acesso
    // coloca no topo da pilha
    p->pilha[e].prox = p->topo;
    // elemento do topo aponta para ele mesmo
    // serve para identificar os casos onde só tem o topo na pilha
    p->pilha[e].ant = e;
    // atualiza info
    endinfoidxcopia(in,&(p->pilha[e].info));
    // verifica se é a primeira insercao
    if (p->topo != PILHAIDXNULO){
      p->pilha[p->topo].ant = e;
    }
    // atualiza p->topo
    p->topo = e;
    // sinaliza primeiro acesso
    distpilha = 0;
  } else {
    long aux,ant,prox;
    // não é o primeiro acesso
    // calcula a distância de pilha.
    // conta quantos elementos ate o topo
    aux = e; 
    while(aux!=p->topo){
      distpilha++;
      aux = p->pilha[aux].ant;
    }
    // move para o topo da pilha
    // antes verifica se ja nao esta no topo
    if (p->topo != e){
      // reencadeia a pilha
      ant = p->pilha[e].ant;
      prox = p->pilha[e].prox;
      // caso estiver nos extremos
      if (ant != PILHAIDXNULO){
        p->pilha[ant].prox = prox;
      }
      if (prox != PILHAIDXNULO){
        p->pilha[prox].ant = ant;
      }
      // sinaliza que e o elemento topo da pilha
      p->pilha[p->topo].ant = e;
      // coloca no topo da pilha
      p->pilha[e].prox = p->topo;
      p->pilha[e].ant = e;
      p->pilha[p->topo].ant = e;
      // atualiza o topo
      p->topo = e;
    }
    // atualiza as informacoes
    endinfoidxcopia(in,&(p->pilha[e].info));
  }
  // usado para contabilizar a distancia de pilha
  return distpilha;
}

int desempilhaidx(pilhaidx_t *p, endidx_t * e, endinfoidx_t * o)
// Descricao: desempilha o topo da pilha, que é colocado em "e" e "o"
// Entrada: p
// Saida: "e" e "o"
{
  // verifica se a pilha nao esta vazia
  if (!pilhaidxvazia(p)){
    long aux;
    // informacoes a serem retornadas
    (*e) = p->topo;
    endinfoidxcopia(&(p->pilha[p->topo].info),o);
    // atualiza o topo
    aux = p->topo; 
    p->topo = p->pilha[aux].prox;
    // atualiza o novo topo
    if (p->topo != PILHAIDXNULO){
      p->pilha[p->topo].ant = p->topo;
    }
    // remove elemento da pilha
    p->pilha[aux].prox = PILHAIDXNULO;
    p->pilha[aux].ant = PILHAIDXNULO;
    return (*e);
  }
  else{
    return PILHAIDXNULO;
  }
}

void destroipilhaidx(pilhaidx_t *p)
// Descricao: destroi a estrutura pilha indexada, anulando as variaveis
// Entrada: p
// Saida: p
{
  // atualiza topo e maxend
  if (p){
    p->topo = PILHAIDXNULO;
    p->maxend = PILHAIDXNULO;
    // libera a pilha
    if (p->pilha) {
      free(p->pilha);
    } else {
      avisoAssert(p->pilha!=NULL,"Pilha inexistente");
    }
    p->pilha = NULL;
  } else {
    avisoAssert(p!=NULL,"Pilha inexistente");
  }
}

void imprimepilhaidx(pilhaidx_t *p, FILE * out)
// Descricao: imprime a pilha a partir do topo
// Entrada: p e out
// Saida: pilha impressa em out
{
  int retprint;
  elemidx_t * paux;
  long aux;
  // preambulo da impressao
  retprint = fprintf(out,"---------------------------------------\n");
  erroAssert(retprint>=0,"Nao foi possivel imprimir");
  retprint = fprintf(out,"Topo %ld Max %ld\n",p->topo,p->maxend);
  erroAssert(retprint>=0,"Nao foi possivel imprimir");
  // inicializa com o topo
  aux = p->topo;
  // enquanto houver elementos da pilha
  while (aux != PILHAIDXNULO){
    // imprime e avanca na pilha
    paux = &(p->pilha[aux]);
    retprint = fprintf(out,"%10ld|%ld.%.9ld %d| Ant %ld Prox %ld\n",
            aux,paux->info.tsec, paux->info.tnsec, paux->info.fase, 
            paux->ant, paux->prox);
    erroAssert(retprint>=0,"Nao foi possivel imprimir");
    aux = p->pilha[aux].prox;
  }
  // separacao final
  retprint = fprintf(out,"---------------------------------------\n");
  erroAssert(retprint>=0,"Nao foi possivel imprimir");
}

void imprimeidx(pilhaidx_t *p, FILE * out)
// Descricao: imprime a pilha toda, ordenada por endereco
// Entrada: p e out
// Saida: impressao em out
{
  long i;
  int retprint;
  elemidx_t * paux;
  // preambulo da impressao
  retprint = fprintf(out,"---------------------------------------\n");
  erroAssert(retprint>=0,"Nao foi possivel imprimir");
  retprint = fprintf(out,"Topo %ld Max %ld\n",p->topo,p->maxend);
  erroAssert(retprint>=0,"Nao foi possivel imprimir");
  // percorre a pilha na ordem dos elementos
  for (i=0; i<=p->maxend;i++){
    paux = &(p->pilha[i]);
    retprint = fprintf(out,"%10ld|%ld.%.9ld %d| Ant %ld Prox %ld\n",
            i,paux->info.tsec, paux->info.tnsec, paux->info.fase, 
            paux->ant, paux->prox);
    erroAssert(retprint>=0,"Nao foi possivel imprimir");
  }
  // separacao final
  retprint = fprintf(out,"---------------------------------------\n");
  erroAssert(retprint>=0,"Nao foi possivel imprimir");
}

