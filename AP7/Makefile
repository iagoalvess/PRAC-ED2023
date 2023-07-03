CXX = g++
CXXFLAGS = -Wall -Wextra -Werror -std=c++11 -g
BIN_DIR = bin
INCLUDE_DIR = include
OBJ_DIR = obj
SRC_DIR = src

TARGET = $(BIN_DIR)/programa
SOURCE_FILES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECT_FILES = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SOURCE_FILES))
INCLUDE_FLAGS = -I$(INCLUDE_DIR)

$(TARGET): $(OBJECT_FILES) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(INCLUDE_FLAGS) $^ -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) $(INCLUDE_FLAGS) -c $< -o $@

$(BIN_DIR):
	mkdir -p $@

$(OBJ_DIR):
	mkdir -p $@

.PHONY: clean run

clean:
	rm -rf $(BIN_DIR) $(OBJ_DIR)

run: $(TARGET)
	./$(TARGET) $(ARGS)