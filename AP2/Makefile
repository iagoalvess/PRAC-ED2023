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
OBJS = $(OBJ)/main.o $(OBJ)/fibonacci.o $(OBJ)/fatorial.o 
HDRS = $(INC)/fibonacci.hpp $(INC)/fatorial.hpp 
CFLAGS = -Wall -c -I$(INC)

EXE = $(BIN)/main

run: $(EXE)
	$(EXE) < $(BIN)/entradas.txt

$(BIN)/main: $(OBJS)
	$(CC) -pg -o $(BIN)/main $(OBJS) $(LIBS)

$(OBJ)/main.o: $(HDRS) $(SRC)/main.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/main.o $(SRC)/main.cpp

$(OBJ)/fatorial.o: $(HDRS) $(SRC)/fatorial.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/fatorial.o $(SRC)/fatorial.cpp
	
$(OBJ)/fibonacci.o: $(HDRS) $(SRC)/fibonacci.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/fibonacci.o $(SRC)/fibonacci.cpp
	
clean:
	rm -f $(EXE) $(OBJS) gmon.out
