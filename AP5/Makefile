#---------------------------------------------------------------------
# Arquivo	: Makefile
#---------------------------------------------------------------------
# Opções	: make all - compila tudo e executa exemplo
#		: make clean - remove objetos e executável
#---------------------------------------------------------------------

CC = gcc
LIBS = -lm -ldl
SRC = src
OBJ = obj
INC = include
BIN = bin
OBJS = $(OBJ)/main.o $(OBJ)/tipos.o 
HDRS = $(INC)/tipos.h 
CFLAGS = -Wall -c -I$(INC) -I$(SRC)
LDFLAGS = -L$(SRC)

EXE = $(BIN)/main

run:  $(EXE)
	$(EXE) -o saida.txt -s 400 -n 10

$(BIN)/main: $(OBJS)
	$(CC) -g -o $(BIN)/main $(OBJS) $(LIBS) $(LDFLAGS)

$(OBJ)/main.o: $(HDRS) $(SRC)/main.c
	$(CC) $(CFLAGS) -o $(OBJ)/main.o $(SRC)/main.c 

$(OBJ)/tipos.o: $(HDRS) $(SRC)/tipos.c
	$(CC) $(CFLAGS) -o $(OBJ)/tipos.o $(SRC)/tipos.c 
	
clean:
	rm -f $(EXE) $(OBJS) gmon.out
