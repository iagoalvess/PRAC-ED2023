//---------------------------------------------------------------------
// Arquivo      : analisamem.c
// Conteudo     : analise de localidade de referencia
// Autor        : Wagner Meira Jr. (meira@dcc.ufmg.br)
// Historico    : 2021-10-30 - arquivo criado
//              : 2021-11-08 - comentarios
//              : 2022-04-17 - adicionado distp e png
//---------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <getopt.h>
#include <string.h>
#include <limits.h>
#include "msgassert.h" 
#include "pilhaindexada.h"

// assumimos o que o tamanho da palavra de máquina é 64 bits (8 bytes)
// em uma versao posterior pode ser um parametro
#define TAMPALAVRA 8
#define TAMPALAVRA 1

// variaveis globais para a captura de opcoes de linha de comando
// poderia ser uma estrutura passada como parametro
char lognome[1000];
char prefixo[1000];
char formato[10];
char terminal[1000];

// estrutura do arquivo gnuplot para grafico de acesso
char* gpacesso[]={
  "set term %s",
  "set output \"%s-acesso-%d.%s\"",
  "set title \"Grafico de acesso - ID %d\"",
  "set xlabel \"Acesso\"",
  "set ylabel \"Endereco\"",
  "plot \"%s-acesso-0-%d.gpdat\" u 2:4 w points t \"L\", \"%s-acesso-1-%d.gpdat\" u 2:4 w points t \"E\"", 
  0
};

// estrutura do arquivo gnuplot para histograma de distancia de pilha 
char* gphist[]={
  "set term %s",
  "set output \"%s-hist-%d-%d.%s\"",
  "set style fill solid 1.0",
  "set title \"Distancia de Pilha (Total %ld # %d Media %.2f) - Fase  %d - ID %d\"",
  "set xlabel \"Distancia\"",
  "set ylabel \"Frequencia\"",
  "plot [%d:%d] \"%s-hist-%d-%d.gpdat\" u 3:4 w boxes t \"\"", 
  0
};

char* gpdistp[]={
  "set term %s",
  "set output \"%s-distp-%d.%s\"",
  "set title \"Evolucao Distancia de Pilha - ID %d\"",
  "set xlabel \"Acesso\"",
  "set ylabel \"Distancia de Pilha\"",
  "plot \"%s-acesso-2-%d.gpdat\" u 2:5 w impulses t \"\"", 
  0
};

void uso()
// Descricao: imprime as instrucoes de uso do programa
// Entrada:  N/A
// Saida: instrucoes
{
  fprintf(stderr,"analyzemem\n");
  fprintf(stderr,"\t-i <arq> \t(arquivo de log) \n");
  fprintf(stderr,"\t-p <arq>\t(prefixo de saida)\n");
  fprintf(stderr,"\t-f <fmt>\t(formato graficos: eps/png)\n");
}

void parse_args(int argc,char ** argv)
// Descricao: analisa a linha de comando a inicializa variaveis
// Entrada: argc e argv
// Saida: lognome e prefixo (globais)
{
     extern char * optarg;
     extern int optind;
     int c ;
     lognome[0] = 0;
     prefixo[0] = 0;
     strcpy(formato,"png");
     strcpy(terminal,"png");
     // percorre a linha de comando buscando identificadores
     while ((c = getopt(argc, argv, "i:p:f:h")) != EOF)
       switch(c) {
         case 'i':
	          // log de entrada
	          strcpy(lognome,optarg);
                  break;
         case 'p': 
	          // prefixo dos arquivos de saida
	          strcpy(prefixo,optarg);
		  break;
         case 'f': 
	          // formato de saida dos graficos
	          strcpy(formato,optarg);
		  if (!strcasecmp(formato,"png")){
		    strcpy(terminal,"png");
		  } else if (!strcasecmp(formato,"eps")){
		    strcpy(terminal,"postscript eps color 14");
		  } else{
		    // formato desconhecido, gerar erro 
		    formato[0] = 0;
		  }
		  break;
         case 'h':
         default:
                  uso();
                  exit(1);

       }
       erroAssert(lognome[0],"Arquivo de log nao definido.");
       erroAssert(prefixo[0],"Prefixo de saida nao definido.");
}

int lelinha(FILE * in,char * line)
// Descricao: le uma linha do arquivo in
// Entrada: in
// Saida: line
{
  int pos = 0,ch;
  // le a linha ate a quebra de linha ou fim de arquivo
  while (((ch=getc(in)) != '\n') && !feof(in)){
    // coloca o caracter lido no vetor
    line[pos] = ch;
    pos++;
  }
  // limitando a string
  line[pos] = 0;
  return pos;
}

int quebralinha(char * line, char tkvet[1000][20])
// Descricao: divide a linha em tokens separados por espaço
// Entrada: line
// Saida: tkvet
{
  char *token;
  char *saveptr1;
  // tokens delimitados por espaços em branco
  char delim[2] = " ";
  int j;

  j=0;
  // quebra a linha em tokens
  token = strtok_r(line, delim, &saveptr1);
  // se a linha for vazia
  if (token == NULL) return 0;
  // copia o primeiro token
  strcpy(tkvet[j],token);
  j++;
  // enquanto houver token
  while ((token=strtok_r((char *) 0,delim, &saveptr1))) {
    strcpy(tkvet[j],token);
    j++;
  }
  return j;
}

int main(int argc, char ** argv)
// Descricao: 
// Entrada: 
// Saida: 
{

  FILE * log;
  char linha[1000];
  char tkvet[1000][20];
  char tipo;
  FILE *** out; 
  char outnome[2000];
  int auxtipo;
  int auxcont;
  int ** controle;
  int ** liminf;
  int ** limsup;

  pilhaidx_t **p; // e um vetor de pilhas
  endinfoidx_t ei;

  // declara e inicializa as variaveis de controle 
  long int minend = LONG_MAX;
  long int maxend = -1;
  long int auxend;
  long int numend;

  int minfase = INT_MAX;
  int maxfase = -1;
  int auxfase;
  int numfase;

  int minid = INT_MAX;
  int maxid = -1;
  int auxid;
  int numid;

  int auxdp,i,j,k,numcampos;
  long *** dpvet;
  int retclose, retprint;

  // analisa a linha de comando
  parse_args(argc,argv);

  // le arquivo de log, determinando o limite superior e inferior de end
  // determina o número de fases e de identificadores de variaveis
  log = fopen(lognome,"rt");
  erroAssert(log!=NULL,"Erro no fopen");
  while (lelinha(log,linha)){
    numcampos = quebralinha(linha,tkvet);
    // I, L , E ou F
    tipo = tkvet[0][0];
    switch (tipo){
      case 'I': 
                erroAssert(numcampos == 3, "Numero de campos errado");
                // nao usamos essa informacao no momento
                break;
      case 'L':
      case 'E':
                // caso seja L ou E, verifica e atualiza os limites
                erroAssert(numcampos == 7, "Numero de campos errado");
                auxend = atol(tkvet[5]);
		if (auxend > maxend) maxend = auxend;
		if (auxend < minend) minend = auxend;
		auxfase = atoi(tkvet[1]);
		if (auxfase > maxfase) maxfase = auxfase;
		if (auxfase < minfase) minfase = auxfase;
		auxid = atoi(tkvet[3]);
		if (auxid > maxid) maxid = auxid;
		if (auxid < minid) minid = auxid;
                break;
      case 'F':
                erroAssert(numcampos == 4, "Numero de campos errado");
                // nao usamos essa informacao no momento
                break;
    }
  }
  retclose = fclose(log);
  erroAssert(retclose==0,"Erro no fclose");

  // verifica se minfase e minid sao 0
  erroAssert(minid == 0, "Id minimo nao e zero");
  erroAssert(minfase == 0, "Fase minima nao e zero");

  // calcula as dimensoes a serem utilizadas na analise
  numend = ((maxend-minend)/TAMPALAVRA)+2;
  numfase = (maxfase-minfase)+1;
  numid = (maxid-minid)+1;

  // apenas para conferencia
  fprintf(stderr,"Enderecos:  [%ld-%ld] (%ld) #end %ld\n",
          minend,maxend,maxend-minend, numend);
  fprintf(stderr,"Fases: [%d-%d] (%d) #fase %d\n",
          minfase,maxfase,maxfase-minfase,numfase);
  fprintf(stderr,"Ids: [%d-%d] #id %d\n",
          minid,maxid,numid);

  // cria pilha e vetor de contagem de distância de pilha, um por fase.
  // primeira dimensao: numfase
  // segunda dimensao: numid
  // terceira dimensao: numend (apenas para pilha)

  p = malloc(numfase*sizeof(pilhaidx_t*));
  erroAssert(p!=NULL,"Malloc falhou");
  dpvet = malloc(numfase*sizeof(long**));
  erroAssert(dpvet!=NULL,"Malloc falhou");
  for (i=0; i<numfase;i++){
    p[i] = malloc(numid*sizeof(pilhaidx_t));
    erroAssert(p[i]!=NULL,"Malloc falhou");
    dpvet[i] = malloc((numid)*sizeof(long*));
    erroAssert(dpvet[i]!=NULL,"Malloc falhou");
    for (j=0;j<numid; j++){
      criapilhaidx(&(p[i][j]),numend);
      dpvet[i][j] = malloc((numend)*sizeof(long));
      erroAssert(dpvet[i][j]!=NULL,"Malloc falhou");
      for(k=0;k<numend;k++){
        dpvet[i][j][k] = 0;
      }
    }
  }

  // le arquivo de log
  // ajusta enderecos
  // imprime arquivos para mapa de acessos



  // cria arquivos de saida
  // 3(escrita, leitura, historico)*numid arquivos
  // leitura = 0 e escrita = 1 
  out = malloc(3*sizeof(FILE**));
  erroAssert(out!=NULL,"Malloc falhou");
  for (i=0; i<3;i++){
    out[i] = malloc(numid*sizeof(FILE*));
    erroAssert(out[i]!=NULL,"Malloc falhou");
    for (j=0; j<numid; j++){
      retprint = sprintf((char*) outnome,"%s-acesso-%d-%d.gpdat",prefixo,i,j);
      erroAssert(retprint>=0,"Erro no sprintf");
      out[i][j] = fopen(outnome,"wt");
      erroAssert(out[i][j]!=NULL,"Erro no fopen");
    }
  }

  // le novamente o arquivo de log e analisa e registra os acessos
  log = fopen(lognome,"rt");
  erroAssert(log!=NULL,"Erro no fopen");
  while (lelinha(log,linha)){
    quebralinha(linha,tkvet);
    tipo = tkvet[0][0];
    switch (tipo){
      case 'I': 
                break;
      case 'L':
      case 'E':
                // qual a fase?
		auxfase = atoi(tkvet[1]);
		// qual o contador de evento?
		auxcont = atoi(tkvet[2]);
		// qual o identificador de variavel?
		auxid = atoi(tkvet[3]);
		// qual o endereco?
		// escalar para a faixa 0-maxend, considerando TAMPALAVRA
                auxend = (atol(tkvet[5])-minend)/TAMPALAVRA;
                // informacoes do evento 
		ei.fase = auxfase;
		// por hora nao usamos o momento do acesso
		ei.tsec = 0;
		ei.tnsec = 0;
		// empilha o acesso
                auxdp = empilhaidx(&(p[auxfase][auxid]),auxend,&ei);
		// registro de distancia de pilha
		if (auxdp>=0) dpvet[auxfase][auxid][auxdp]++;
		// L - auxtipo=0 / E - auxtipo=1
		auxtipo = (tipo == 'E');
		// escreve no arquivo acessos por tipo e id
		retprint = fprintf(out[auxtipo][auxid],"%d %d %d %ld\n",
		        auxfase, auxcont, auxid, auxend);
                erroAssert(retprint>=0,"Erro no fprintf");
		retprint = fprintf(out[2][auxid],"%d %d %d %ld %d\n",
		        auxfase, auxcont, auxid, auxend, auxdp);
                erroAssert(retprint>=0,"Erro no fprintf");
                break;
      case 'F':
                break;
    }
  }
  // fecha o arquivo de leitura e todos de escrita
  retclose = fclose(log);
  erroAssert(retclose==0,"Erro no fclose");
  for (i=0; i<3;i++){
    for (j=0; j<numid; j++){
      retclose = fclose(out[i][j]);
      erroAssert(retclose==0,"Erro no fclose");
    }
    free(out[i]);
  }
  free(out);

  // geracao de arquivos gnuplot para acessos
  // na verdade nao e necessario usar a matriz de arquivos de saida
  // feito assim por comodidade
  out = malloc(1*sizeof(FILE**));
  erroAssert(out!=NULL,"Malloc falhou");
  for (i=0; i<1;i++){
    out[i] = malloc(numid*sizeof(FILE*));
    erroAssert(out[i]!=NULL,"Malloc falhou");
    for (j=0; j<numid; j++){
      retprint = sprintf((char*) outnome,"%s-acesso-%d.gp",prefixo,j);
      erroAssert(retprint>=0,"Erro no sprintf");
      out[i][j] = fopen(outnome,"wt");
      erroAssert(out[i][j]!=NULL,"Erro no fopen");
      k=0;
      while(gpacesso[k]){
	switch (k){
	  case 0:
      	    retprint = fprintf(out[i][j],gpacesso[k],terminal);
            erroAssert(retprint>=0,"Erro no fprintf");
	    break;
	  case 3:
	  case 4: 
	    // linhas que nao tem parametro
	    retprint = fprintf(out[i][j], gpacesso[k],"\n");
            erroAssert(retprint>=0,"Erro no fprintf");
	    break;
	  case 1:
	    // nome do arquivo de saida
	    retprint = fprintf(out[i][j],gpacesso[k],prefixo,j,formato);
            erroAssert(retprint>=0,"Erro no fprintf");
	    break;
	  case 5:
	    // geracao do grafico
	    retprint = fprintf(out[i][j],gpacesso[k],prefixo,j,prefixo,j);
            erroAssert(retprint>=0,"Erro no fprintf");
	    break;
	  case 2:
	    // titulo do grafico
	    retprint = fprintf(out[i][j],gpacesso[k],j);
            erroAssert(retprint>=0,"Erro no fprintf");
	    break;
	}
	retprint = fprintf(out[i][j],"\n");
        erroAssert(retprint>=0,"Erro no fprintf");
	k++;
      }
      retclose = fclose(out[i][j]);
      erroAssert(retclose==0,"Erro no fclose");
    }
  }

  // desalocacao dos arquivos
  for (i=0; i<1;i++){
    free(out[i]);
  }
  free(out);

  // geracao de arquivos gnuplot para distancias de pilha
  // na verdade nao e necessario usar a matriz de arquivos de saida
  // feito assim por comodidade
  out = malloc(1*sizeof(FILE**));
  erroAssert(out!=NULL,"Malloc falhou");
  for (i=0; i<1;i++){
    out[i] = malloc(numid*sizeof(FILE*));
    erroAssert(out[i]!=NULL,"Malloc falhou");
    for (j=0; j<numid; j++){
      retprint = sprintf((char*) outnome,"%s-distp-%d.gp",prefixo,j);
      erroAssert(retprint>=0,"Erro no sprintf");
      out[i][j] = fopen(outnome,"wt");
      erroAssert(out[i][j]!=NULL,"Erro no fopen");
      k=0;
      while(gpacesso[k]){
	switch (k){
	  case 0:
      	    retprint = fprintf(out[i][j],gpdistp[k],terminal);
            erroAssert(retprint>=0,"Erro no fprintf");
	    break;
	  case 3:
	  case 4: 
	    // linhas que nao tem parametro
	    retprint = fprintf(out[i][j], gpdistp[k],"\n");
            erroAssert(retprint>=0,"Erro no fprintf");
	    break;
	  case 1:
	    // nome do arquivo de saida
	    retprint = fprintf(out[i][j],gpdistp[k],prefixo,j,formato);
            erroAssert(retprint>=0,"Erro no fprintf");
	    break;
	  case 5:
	    // geracao do grafico
	    retprint = fprintf(out[i][j],gpdistp[k],prefixo,j);
            erroAssert(retprint>=0,"Erro no fprintf");
	    break;
	  case 2:
	    // titulo do grafico
	    retprint = fprintf(out[i][j],gpdistp[k],j);
            erroAssert(retprint>=0,"Erro no fprintf");
	    break;
	}
	retprint = fprintf(out[i][j],"\n");
        erroAssert(retprint>=0,"Erro no fprintf");
	k++;
      }
      retclose = fclose(out[i][j]);
      erroAssert(retclose==0,"Erro no fclose");
    }
  }

  // desalocacao dos arquivos
  for (i=0; i<1;i++){
    free(out[i]);
  }
  free(out);

  // impressao dos contadores de distancia de pilha para depuracao 
  for (i=0; i<numfase;i++){
    for(j=0;j<numid;j++){
      for(k=0;k<numend;k++){
        if (dpvet[i][j][k]){
	  retprint = fprintf(stderr,"%d %d %d %ld\n",i,j,k,dpvet[i][j][k]);
          erroAssert(retprint>=0,"Erro no fprintf");
        }
      }
    }
  }


  // criacao dos arquivos e estruturas de controle para histogramas
  controle = malloc(numfase*sizeof(int*));
  erroAssert(controle!=NULL,"Malloc falhou");
  liminf = malloc(numfase*sizeof(int*));
  erroAssert(liminf!=NULL,"Malloc falhou");
  limsup = malloc(numfase*sizeof(int*));
  erroAssert(limsup!=NULL,"Malloc falhou");
  out = malloc(numfase*sizeof(FILE**));
  erroAssert(out!=NULL,"Malloc falhou");
  for (i=0; i<numfase;i++){
    out[i] = malloc(numid*sizeof(FILE*));
    erroAssert(out[i]!=NULL,"Malloc falhou");
    controle[i] = malloc(numid*sizeof(int));
    erroAssert(controle[i]!=NULL,"Malloc falhou");
    liminf[i] = malloc(numid*sizeof(int));
    erroAssert(liminf[i]!=NULL,"Malloc falhou");
    limsup[i] = malloc(numid*sizeof(int));
    erroAssert(limsup[i]!=NULL,"Malloc falhou");
    for (j=0; j<numid; j++){
      retprint = sprintf((char*) outnome,"%s-hist-%d-%d.gpdat",prefixo,i,j);
      erroAssert(retprint>=0,"Erro no sprintf");
      out[i][j] = fopen(outnome,"wt");
      erroAssert(out[i][j]!=NULL,"Erro no fopen");
      controle[i][j] = 0;
      limsup[i][j] = -1;
      liminf[i][j] = INT_MAX;
    }
  }
  
  // identificacao de limites do histograma e geracao de arquivos de dados
  for (i=0; i<numfase;i++){
    for(j=0;j<numid;j++){
      // delimitar limite inferior e superior de cada histograma
      for(k=0;k<numend;k++){
	if (dpvet[i][j][k]){
	  if (liminf[i][j]>k) liminf[i][j] = k;
	  if (limsup[i][j]<k) limsup[i][j] = k;
	}
      }
      for(k=liminf[i][j];k<=limsup[i][j];k++){
        retprint = fprintf(out[i][j],"%d %d %d %ld\n",i,j,k,dpvet[i][j][k]);
        erroAssert(retprint>=0,"Erro no fprintf");
        controle[i][j]++;
      }
    }
  }

  // fechar os arquivos
  for (i=0; i<numfase;i++){
    for (j=0; j<numid; j++){
      retclose=fclose(out[i][j]);
      erroAssert(retclose==0,"Erro no fclose");
    }
    free(out[i]);
  }
  free(out);

  // geracao de arquivos gnuplot dos histogramas
  out = malloc(numfase*sizeof(FILE**));
  erroAssert(out!=NULL,"Malloc falhou");
  for (i=0; i<numfase;i++){
    out[i] = malloc(numid*sizeof(FILE*));
    erroAssert(out[i]!=NULL,"Malloc falhou");
    for (j=0; j<numid; j++){
      // verifica se ha dados para gerar os histogramas
      if (controle[i][j]){
        long somadp=0;
	int countnonzero=0;
        for (k=0;k<numend;k++){
	  somadp += dpvet[i][j][k]*k;
	  if (dpvet[i][j][k]) countnonzero+=dpvet[i][j][k];
	}
        retprint = sprintf((char*) outnome,"%s-hist-%d-%d.gp",prefixo,i,j);
        erroAssert(retprint>=0,"Erro no sprintf");
        out[i][j] = fopen(outnome,"wt");
        erroAssert(out[i][j]!=NULL,"Erro no fopen");
        k=0;
        while(gphist[k]){
      	switch (k){
      	  case 0:
      	    retprint = fprintf(out[i][j],gphist[k],terminal);
            erroAssert(retprint>=0,"Erro no fprintf");
	    break;
      	  case 2:
      	  case 4:
      	  case 5: 
    	    // imprimir as linhas
      	    retprint = fprintf(out[i][j],gphist[k],"\n");
            erroAssert(retprint>=0,"Erro no fprintf");
      	    break;
      	  case 1:
    	    // arquivo de saida
      	    retprint = fprintf(out[i][j],gphist[k],prefixo,i,j,formato);
            erroAssert(retprint>=0,"Erro no fprintf");
      	    break;
      	  case 6:
    	    // gera grafico
      	    retprint = fprintf(out[i][j],gphist[k],liminf[i][j]-1,
    	            limsup[i][j]+1,prefixo,i,j);
            erroAssert(retprint>=0,"Erro no fprintf");
      	    break;
      	  case 3:
    	    // titulo
      	    retprint = fprintf(out[i][j],gphist[k],somadp,countnonzero,
	                       (somadp*1.0)/countnonzero,i,j);
            erroAssert(retprint>=0,"Erro no fprintf");
      	    break;
      	}
  	retprint = fprintf(out[i][j],"\n");
        erroAssert(retprint>=0,"Erro no fprintf");
  	k++;
        }
        retclose=fclose(out[i][j]);
        erroAssert(retclose==0,"Erro no fclose");
      }
    }
  }

  // desaloca as estruturas de controle

  for (i=0; i<numfase;i++){
    free(out[i]);
    free(controle[i]);
    free(liminf[i]);
    free(limsup[i]);
  }
  free(out);
  free(controle);
  free(liminf);
  free(limsup);

  // desaloca as varias estruturas de dados auxiliares

  for (i=0; i<numfase;i++){
    for (j=0; j<numid; j++){
      destroipilhaidx(&(p[i][j]));
      free(dpvet[i][j]);
    }
    free(p[i]);
    free(dpvet[i]);
  }
  free(p);
  free(dpvet);

  return 0;
}

