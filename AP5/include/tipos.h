#ifndef TIPOS_H
#define TIPOS_H

#include <sys/time.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <getopt.h>
#include <string.h>
#include <math.h>

// Syntax tree structure
typedef long TipoChave;

typedef struct TipoRegistro {
  TipoChave Chave;
} TipoRegistro;

typedef struct TipoNo *TipoApontador;

typedef struct TipoNo {
  TipoRegistro Reg;
  TipoApontador Esq, Dir;
} TipoNo;

typedef struct TipoArvore {
  TipoApontador Raiz;
} TipoArvore;

typedef struct prm {
  char nomesaida[200];
  int semente;
  int numno;
  FILE *saida;
  int treesize;
  int numlevel;
} prm_t;

void uso();

void parse_args(int argc, char **argv, prm_t *prm);

void dumpTree(TipoApontador *T, int level, prm_t *prm);

int createTree(TipoNo **curr, int level, prm_t *prm);

bool is_ancestral(TipoNo *root, int ancestor, int descendant);
bool is_descendant(TipoNo *node, int target);

#endif

