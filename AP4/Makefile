#---------------------------------------------------------------------
# Arquivo	: Makefile
# Conteúdo	: compilar o programa 
#---------------------------------------------------------------------
# Opções	: make all - compila tudo
#		: make clean - remove objetos e executável
#---------------------------------------------------------------------

CC = g++
LIBS = -lm
SRC = src
OBJ = obj
INC = include
BIN = bin
OBJS = $(OBJ)/main.o $(OBJ)/pilha.o $(OBJ)/filacircular.o 
HDRS = $(INC)/pilha.hpp $(INC)/filacircular.hpp 
CFLAGS = -Wall -c -I$(INC)

EXE = $(BIN)/main

run: $(EXE)
	$(EXE)

$(BIN)/main: $(OBJS)
	$(CC) -o $(BIN)/main $(OBJS) $(LIBS)

$(OBJ)/main.o: $(HDRS) $(SRC)/main.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/main.o $(SRC)/main.cpp

$(OBJ)/filacircular.o: $(HDRS) $(SRC)/filacircular.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/filacircular.o $(SRC)/filacircular.cpp
	
$(OBJ)/pilha.o: $(HDRS) $(SRC)/pilha.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/pilha.o $(SRC)/pilha.cpp
	
clean:
	rm -f $(EXE) $(OBJS)