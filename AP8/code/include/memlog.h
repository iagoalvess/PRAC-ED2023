#ifndef MEMLOGH
#define MEMLOGH

#include <stdio.h>
#include <time.h>

typedef struct memlog{
	FILE * log;
	clockid_t clk_id;
	struct timespec inittime;	
	long count;
	int fase;
	int ativo;
} memlog_tipo;
extern memlog_tipo ml;

// constantes definindo os estados de registro
#define MLATIVO 1
#define MLINATIVO 0

// macros para maior eficiencia
#define LEMEMLOG(pos,tam,id) ((void) ((ml.ativo==MLATIVO)?leMemLog(pos,tam,id):0))
#define ESCREVEMEMLOG(pos,tam,id) ((void) ((ml.ativo==MLATIVO)?escreveMemLog(pos,tam,id):0))

// prototipos das funcoes

int iniciaMemLog(char * nome);
int ativaMemLog();
int desativaMemLog();
int defineFaseMemLog(int f);
int leMemLog(long int pos, long int tam, int id);
int escreveMemLog(long int pos, long int tam, int id);
int finalizaMemLog();

#endif
