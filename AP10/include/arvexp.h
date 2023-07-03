#ifndef ARVEXP_H
#define ARVEXP_H

#include <stdlib.h>
#include <stdio.h>

#ifndef CARGA
#define CARGA 100
#endif

#ifndef m
#define m 2
#endif
#define mm (m * 2)
#define FALSE 0
#define TRUE 1

#define MAXCH 100

typedef long TipoChave;

typedef struct Registro
{
  TipoChave Chave;
  char Carga[CARGA];
} Registro;

typedef struct Pagina *Apontador;

typedef struct Pagina
{
  short n;
  Registro r[mm];
  Apontador p[mm + 1];
} Pagina;

typedef struct stat
{
  int X;
  int curr;
  Pagina p[3];
} stat_t;

void Inicializa(Apontador *Dicionario);
void Pesquisa(Registro *x, Apontador Ap);
void Insere(Registro Reg, Apontador *Ap);
void Retira(TipoChave Ch, Apontador *Ap);
void Imprime(Apontador p, FILE *out, stat_t *st, char *pref);
void TestaI(Apontador p, int pai, short direita);

#endif
