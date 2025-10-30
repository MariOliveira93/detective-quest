# Compilador e flags
CC = gcc
CFLAGS = -Wall -Wextra -g -I./include
LDFLAGS =

# Diretórios
SRC_DIR = src
INC_DIR = include
OBJ_DIR = obj
BIN_DIR = build

# Arquivos
SOURCES = $(wildcard $(SRC_DIR)/*.c)
OBJECTS = $(SOURCES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
TARGET = $(BIN_DIR)/detective-quest

# Regra padrão
all: directories $(TARGET)

# Criar diretórios necessários
directories:
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(BIN_DIR)

# Compilar o executável
$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)
	@echo "✅ Compilação concluída: $(TARGET)"

# Compilar arquivos objeto
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Executar o programa
run: all
	@echo "========================================="
	@echo "Iniciando Detective Quest..."
	@echo "========================================="
	@./$(TARGET)

# Limpar arquivos compilados
clean:
	@rm -rf $(OBJ_DIR) $(BIN_DIR)
	@echo "✅ Arquivos limpos"

# Recompilar tudo
rebuild: clean all

# Debug
debug: CFLAGS += -DDEBUG
debug: rebuild

.PHONY: all clean run rebuild debug directories