CC = gcc
CFLAGS = -lm
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
INC_DIR = include

all: $(BIN_DIR)/arvexp

$(BIN_DIR)/arvexp: $(OBJ_DIR)/arvexp.o $(OBJ_DIR)/main.o | $(BIN_DIR)
	$(CC) -Dm=$(m) -DCARGA=$(CARGA) $(CFLAGS) -o $@ $^

$(OBJ_DIR)/arvexp.o: $(SRC_DIR)/arvexp.c $(INC_DIR)/arvexp.h | $(OBJ_DIR)
	$(CC) -Dm=$(m) -DCARGA=$(CARGA) $(CFLAGS) -I$(INC_DIR) -c -o $@ $<

$(OBJ_DIR)/main.o: $(SRC_DIR)/main.c $(INC_DIR)/arvexp.h | $(OBJ_DIR)
	$(CC) -Dm=$(m) -DCARGA=$(CARGA) $(CFLAGS) -I$(INC_DIR) -c -o $@ $<

clean:
	rm -rf $(BIN_DIR) $(OBJ_DIR)

$(OBJ_DIR) $(BIN_DIR):
	mkdir -p $@

run: $(BIN_DIR)/arvexp
	$(BIN_DIR)/arvexp
	