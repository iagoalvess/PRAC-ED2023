//---------------------------------------------------------------------
// Arquivo      : pilhaindexada.h
// Conteudo     : definicoes da biblioteca de pilha indexada 
// Autor        : Wagner Meira Jr. (meira@dcc.ufmg.br)
// Historico    : 2021-10-30 - arquivo criado
//              : 2021-11-08 - comentarios
//---------------------------------------------------------------------

#ifndef PILHAINDEXADAH

#define PILHAINDEXADAH
#define ELEMATIVO 1
#define ELEMINATIVO 0

#define PILHAIDXNULO -1

// tipo de endereco do indice
typedef long endidx_t;

// informacoes a serem colocadas na pilha
// nesse caso esta atrelado à biblioteca memlog
// ultimo momento que o registro foi empilhado e qual fase
typedef struct endinfoidx{
  long tsec, tnsec;
  int fase;
} endinfoidx_t;

// item da pilha
typedef struct elemidx{
  // ponteiros para elemento acima e abaixo na pilha
  long ant, prox;
  // informação empilhada
  endinfoidx_t info;
} elemidx_t;

// pilha
typedef struct pilhaidx{
  // endereco do topo
  long topo;
  // espaço de enderecos da pilha
  endidx_t maxend; 
  // vetor de enderecos
  elemidx_t * pilha;
} pilhaidx_t;

int elemidxempty(elemidx_t * el);

int endinfoidxcopia(endinfoidx_t * src, endinfoidx_t * dst);

void criapilhaidx(pilhaidx_t *p, endidx_t maxend);

int pilhaidxvazia(pilhaidx_t * p);

int empilhaidx(pilhaidx_t *p, endidx_t e,  endinfoidx_t * in);

int desempilhaidx(pilhaidx_t *p, endidx_t *e, endinfoidx_t * o);

void destroipilhaidx(pilhaidx_t *p);

void imprimepilhaidx(pilhaidx_t *p, FILE * out);

void imprimeidx(pilhaidx_t *p, FILE * out);

#endif
