#define OPSOMAR 1
#define OPMULTIPLICAR 2
#define OPTRANSPOR 3
#define OPCRIAR 4

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <getopt.h>
#include "mat.h"
#include "msgassert.h"

// variaveis globais para opcoes
static int opescolhida;
char outnome[100];
int optx, opty;

void uso()
// Descricao: imprime as opcoes de uso
// Entrada: nao tem
// Saida: impressao das opcoes de linha de comando
{
  fprintf(stderr,"matop\n");
  fprintf(stderr,"\t-s \t(somar matrizes) \n");
  fprintf(stderr,"\t-m \t(multiplicar matrizes) \n");
  fprintf(stderr,"\t-t \t(transpor matriz)\n");
  fprintf(stderr,"\t-c <arq> \t(cria matriz e salva em arq)\n");
  fprintf(stderr,"\t-x <int>\t(primeira dimensao)\n");
  fprintf(stderr,"\t-y <int>\t(segunda dimensao)\n");
}


void parse_args(int argc,char ** argv)
// Descricao: le as opcoes da linha de comando e inicializa variaveis
// Entrada: argc e argv
// Saida: optescolhida, optx, opty
{
     // variaveis externas do getopt
     extern char * optarg;
     extern int optind;

     // variavel auxiliar
     int c;

     // inicializacao variaveis globais para opcoes
     opescolhida = -1;
     optx = -1;
     opty = -1;
     outnome[0] = 0;

     // getopt - letra indica a opcao, : junto a letra indica parametro
     // no caso de escolher mais de uma operacao, vale a ultima
     while ((c = getopt(argc, argv, "smtc:p:x:y:lh")) != EOF){
       switch(c) {
         case 'm':
		  avisoAssert(opescolhida==-1,"Mais de uma operacao escolhida");
	          opescolhida = OPMULTIPLICAR;
                  break;
         case 's':
		  avisoAssert(opescolhida==-1,"Mais de uma operacao escolhida");
	          opescolhida = OPSOMAR;
                  break;
         case 't':
		  avisoAssert(opescolhida==-1,"Mais de uma operacao escolhida");
	          opescolhida = OPTRANSPOR;
                  break;
         case 'c':
		  avisoAssert(opescolhida==-1,"Mais de uma operacao escolhida");
	          opescolhida = OPCRIAR;
	          strcpy(outnome,optarg);
                  break;
         case 'x': 
	          optx = atoi(optarg);
		  break;
         case 'y': 
	          opty = atoi(optarg);
		  break;
         case 'h':
         default:
                  uso();
                  exit(1);

       }
     }
     // verificacao da consistencia das opcoes
     erroAssert(opescolhida>0,"matop - necessario escolher operacao");
     erroAssert(optx>0,"matop - dimensao X da matriz tem que ser positiva");
     erroAssert(opty>0,"matop - dimensao Y da matriz tem que ser positiva");
     if (opescolhida==OPCRIAR){
       erroAssert(strlen(outnome)>0, "matop - nome de arquivo de saida tem que ser definido");
     }
}


int main(int argc, char ** argv)
// Descricao: programa principal para execucao de operacoes de matrizes 
// Entrada: argc e argv
// Saida: depende da operacao escolhida
{
  // ate 3 matrizes sao utilizadas, dependendo da operacao
  mat_tipo a, b, c;
  FILE * outfile;

  // avaliar linha de comando
  parse_args(argc,argv);

  // execucao dependente da operacao escolhida
  switch (opescolhida){
    case OPSOMAR:
         // cria matrizes a e b aleatorias, que sao somadas para a matriz c
	 // matriz c é impressa e todas as matrizes sao destruidas
         criaMatriz(&a,optx,opty,0);
         inicializaMatrizAleatoria(&a);
         criaMatriz(&b,optx,opty,1);
         inicializaMatrizAleatoria(&b);
         criaMatriz(&c,optx,opty,2);
         inicializaMatrizNula(&c);
         somaMatrizes(&a,&b,&c);
	 imprimeMatriz(&c);
         destroiMatriz(&a);
         destroiMatriz(&b);
         destroiMatriz(&c);
	 break;
    case OPMULTIPLICAR:
         // cria matrizes a e b aleatorias, que sao multiplicadas para matriz c
	 // matriz c é impressa e todas as matrizes sao destruidas
         criaMatriz(&a,optx,opty,0);
         inicializaMatrizAleatoria(&a);
         criaMatriz(&b,opty,optx,1);
         inicializaMatrizAleatoria(&b);
         criaMatriz(&c,optx,optx,2);
         inicializaMatrizNula(&c);
         multiplicaMatrizes(&a,&b,&c);
	 imprimeMatriz(&c);
         destroiMatriz(&a);
         destroiMatriz(&b);
         destroiMatriz(&c);
	 break;
    case OPTRANSPOR:
         // cria matriz a aleatoria, que e transposta, impressa e destruida
         criaMatriz(&a,optx,opty,0);
         inicializaMatrizAleatoria(&a);
	 transpoeMatriz(&a);
	 imprimeMatriz(&a);
         destroiMatriz(&a);
	 break;
    case OPCRIAR:
         // cria matriz a aleatoria, que e salva
	 outfile = fopen(outnome,"wt");
         erroAssert(outfile != NULL,"Erro na criacao do arquivo de saida");
         criaMatriz(&a,optx,opty,0);
         inicializaMatrizAleatoria(&a);
	 salvaMatriz(&a,outfile);
         destroiMatriz(&a);
	 fclose(outfile);
	 break;
   default:
         // nao deve ser executado, pois ha um erroAssert em parse_args
         uso();
	 exit(1);
  }

  // conclui registro de acesso
  return 0;
}