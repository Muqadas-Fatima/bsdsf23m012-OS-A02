# Compiler
CC = gcc

# Directories
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

# Files
SRC = $(SRC_DIR)/lsv1.0.0.c
OBJ = $(OBJ_DIR)/lsv1.0.0.o
TARGET = $(BIN_DIR)/ls

# Rules
all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) -o $@ $^

$(OBJ): $(SRC)
	$(CC) -c -o $@ $<

clean:
	rm -f $(OBJ) $(TARGET)
