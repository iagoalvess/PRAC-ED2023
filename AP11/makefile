# Diretórios
SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := bin
INC_DIR := include

# Compilador
CC := g++

# Opções de compilação
CFLAGS := -c -I$(INC_DIR)

# Arquivos fonte
SOURCES := $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SOURCES))

# Nome do executável
EXECUTABLE := $(BIN_DIR)/main

# Regras
.PHONY: all clean run

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	@mkdir -p $(BIN_DIR)
	$(CC) $^ -o $@
	@echo "Compilação concluída. O executável está em $(EXECUTABLE)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $< -o $@

clean: clean_files
	rm -rf $(OBJ_DIR) $(BIN_DIR)

clean_files:
	rm -f data.dat grafico.pdf

run: $(EXECUTABLE)
	@echo "Executando o programa..."
	./$(EXECUTABLE)
	gnuplot plot.plt
