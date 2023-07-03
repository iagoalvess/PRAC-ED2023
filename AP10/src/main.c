#define PESQUISA 0
#define INSERE 1
#define RETIRA 2

#include "arvexp.h"

typedef struct exp
{
  int numops;
  float op[3];
  int maxch;
  int seed;
  int print;
} exp_t;


int main(int argc, char *argv[])
{
  Registro x;
  Pagina *D;
  stat_t st;
  exp_t exp;

  int i, j, op;

  exp.print = 0;
  exp.seed = 1;
  exp.numops = 10000;
  exp.maxch = 100;
  exp.op[PESQUISA] = 0.4;
  exp.op[INSERE] = 0.7;
  exp.op[RETIRA] = 1.0;

  srand48((unsigned int)exp.seed);

  Inicializa(&D);

  for (i = 0; i < exp.numops; i++)
  {
    // define op
    double opaux = drand48();
    for (op = 0; op < 3; op++)
    {
      if (opaux < exp.op[op])
      {
        break;
      }
    }

    // define chave
    x.Chave = (long)(exp.maxch * drand48());

    if (exp.print)
    {
      printf("i %d opaux %f op %d x %ld\n", i, opaux, op, x.Chave);
    }

    switch (op)
    {
    case PESQUISA:
      Pesquisa(&x, D);
      break;
    case INSERE:
      Insere(x, &D);
      break;
    case RETIRA:
      Retira(x.Chave, &D);
      break;
    }
    if (exp.print)
      Imprime(D, stdout, &st, "");
  }

  return 0;
}