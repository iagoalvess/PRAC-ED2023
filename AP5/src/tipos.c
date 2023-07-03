#include "tipos.h"

void uso() {
// Descricao: imprime as instrucoes de uso do programa
// Entrada:  N/A
// Saida: instrucoes
  fprintf(stderr, "geraexp\n");
  fprintf(stderr, "\t-o <arq>\t(arquivo de saida) \n");
  fprintf(stderr, "\t-s <num>\t(semente)\n");
  fprintf(stderr, "\t-n <num>\t(numero de nos)\n");
  fprintf(stderr, "\t-h\t(opcoes de uso)\n");
}



void parse_args(int argc, char **argv, prm_t *prm) {
// Descricao: analisa a linha de comando a inicializa variaveis
// Entrada: argc e argv
// Saida: prm
  extern char *optarg;
  extern int optind;
  int c;
  // valores padrao
  prm->nomesaida[0] = 0;
  prm->semente = 0;
  prm->numno = 3;
  prm->numlevel = 2;
  // percorre a linha de comando buscando identificadores
  while ((c = getopt(argc, argv, "o:s:n:iph")) != EOF) {
    switch (c) {
    case 'o':
      // arquivo de saida
      strcpy(prm->nomesaida, optarg);
      break;
    case 's':
      // semente aleatoria
      prm->semente = atoi(optarg);
      srand48((long)prm->semente);
      break;
    case 'n':
      // numero de nos
      prm->numno = atoi(optarg);
      prm->numlevel = ((int)log2((double)prm->numno)) + 2;
      break;
    case 'h':
    default:
      uso();
      exit(1);
    }
  }
  // verifica apenas o nome do arquivo de saida
  if (!prm->nomesaida[0]) {
    printf("Arquivo de saida nao definido.");
    exit(1);
  }
}



// Função para imprimir a árvore binária
void dumpTree(TipoApontador *T, int level, prm_t *prm) {
  if ((*T) != NULL) {
    // Imprime espaços para representar o nível do nó na árvore
    for (int i = 0; i < level; i++) {
      fprintf(prm->saida, "    ");
    }
    // Imprime o valor do nó e seu nível
    fprintf(prm->saida, " %3ld (%d)\n", (*T)->Reg.Chave, level);

    // Imprime a subárvore esquerda
    dumpTree(&(*T)->Esq, level + 1, prm);
    // Imprime a subárvore direita
    dumpTree(&(*T)->Dir, level + 1, prm);
  }
}



// Função para criar uma árvore binária aleatória
int createTree(TipoNo **curr, int level, prm_t *prm) {
  // Crie um novo nó e inicializa seus ponteiros para NULL
  (*curr) = (TipoNo *)malloc(sizeof(TipoNo));
  (*curr)->Esq = (*curr)->Dir = NULL;
  // Defina o valor do nó de acordo com uma probabilidade
  if (drand48() > ((8.0 * (1 << level) * prm->treesize)) / (((1 << prm->numlevel) * prm->numno))) {
    (*curr)->Reg.Chave = prm->treesize;
    prm->treesize++;
    // Cria a subárvore esquerda se ainda houver espaço na árvore
    if (prm->treesize < prm->numno) {
      createTree(&((*curr)->Esq), level + 1, prm);
    }
    // Cria a subárvore direita se ainda houver espaço na árvore
    if (prm->treesize < prm->numno) {
      createTree(&((*curr)->Dir), level + 1, prm);
    }
  }
  else {
    (*curr)->Reg.Chave = prm->treesize;
    prm->treesize++;
  }
  return prm->treesize;
}



/* Mudei de ideia! Perceberá que no arquivo texto eu disse que a 
ancestralidade de um nó em relação a outro pudesse ser verificada 
pelas posições desses nós nos vetores resultantes de diferentes 
caminhamentos de uma árvore. Contudo após a tentativa de aplicar 
minha ideia acabei percebendo que existia uma abordagem mais coerente, 
a função proposta abaixo é mais simples e direta, tornando a 
implementação mais fácil e menos propensa a erros.  

Deixo minha primeira ideia de implementação no arquivo ideia.txt,
acredito que tenha ficado funcional mas não tão direto quanto
os métodos abaixo*/



// Função para verificar se um elemento é descendente de outro em uma árvore binária
bool is_descendant(TipoNo *node, int target) {
  // Caso base: se o nó atual for nulo, retorne falso
  if (node == NULL) {
    return false;
  }
  // Caso base: se o nó atual tiver o valor procurado, retorne verdadeiro
  if (node->Reg.Chave == target) {
    return true;
  }
  // Caso recursivo: verifique se o elemento está na subárvore esquerda ou direita
  return is_descendant(node->Esq, target) || is_descendant(node->Dir, target);
}



// Função para verificar se um elemento é ancestral de outro em uma árvore binária
bool is_ancestral(TipoNo *root, int ancestor, int descendant) {
  // Caso base: se a raiz for nula, retorne falso
  if (root == NULL) {
    return false;
  }
   // Caso base: se a raiz tiver o valor do ancestral, verifique se o descendente está na subárvore da raiz
  if (root->Reg.Chave == ancestor) {
    return is_descendant(root, descendant);
  }
  // Caso recursivo: verifique se o ancestral está na subárvore esquerda ou direita
  return is_ancestral(root->Esq, ancestor, descendant) || is_ancestral(root->Dir, ancestor, descendant);
}