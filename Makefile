# Compiler and flags
CC = gcc
CFLAGS = -Wall

# Directories
SRC_DIR = src
BIN_DIR = bin

# Files
V1_0 = $(SRC_DIR)/lsv1.0.0.c
V1_1 = $(SRC_DIR)/lsv1.1.0.c
V1_2 = $(SRC_DIR)/lsv1.2.0.c

# Targets
all: v1.2.0

v1.0.0: $(V1_0)
	$(CC) $(CFLAGS) $(V1_0) -o $(BIN_DIR)/lsv1.0.0

v1.1.0: $(V1_1)
	$(CC) $(CFLAGS) $(V1_1) -o $(BIN_DIR)/lsv1.1.0

v1.2.0: $(V1_2)
	$(CC) $(CFLAGS) $(V1_2) -o $(BIN_DIR)/lsv1.2.0

# Clean compiled binaries
clean:
	rm -f $(BIN_DIR)/lsv1.0.0 $(BIN_DIR)/lsv1.1.0 $(BIN_DIR)/lsv1.2.0
