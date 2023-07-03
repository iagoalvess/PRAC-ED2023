#include "tipos.h"

int main(int argc, char *argv[]) {
  TipoNo *root;
  prm_t prm;
  int i, j;

  parse_args(argc, argv, &prm);
  prm.saida = fopen(prm.nomesaida, "wt");
  prm.treesize = 0;

  createTree(&root, 0, &prm);
  dumpTree(&root, 0, &prm);

  for (int k = 0; k < prm.treesize; k++) {
    i = j = 0;
    while (i == j) {
      i = (int)(drand48() * prm.treesize);
      j = (int)(drand48() * prm.treesize);
    }
    fprintf(prm.saida, "%d testando ancestral(%d,%d)\n", k, i, j);
    int isAncestor = is_ancestral(root, i, j);
    fprintf(prm.saida, "O valor retornado por ancestral é: %d\n", isAncestor);
  }

  fclose(prm.saida);
  return 0;
}
