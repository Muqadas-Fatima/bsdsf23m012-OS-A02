CC = gcc
CFLAGS = -Wall

SRC_DIR = src
BIN_DIR = bin

v1.0.0: $(SRC_DIR)/lsv1.0.0.c
	mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $(SRC_DIR)/lsv1.0.0.c -o $(BIN_DIR)/lsv1.0.0

v1.1.0: $(SRC_DIR)/lsv1.1.0.c
	mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $(SRC_DIR)/lsv1.1.0.c -o $(BIN_DIR)/lsv1.1.0

v1.2.0: $(SRC_DIR)/lsv1.2.0.c
	mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $(SRC_DIR)/lsv1.2.0.c -o $(BIN_DIR)/lsv1.2.0

all: v1.2.0

clean:
	rm -f $(BIN_DIR)/lsv1.0.0 $(BIN_DIR)/lsv1.1.0 $(BIN_DIR)/lsv1.2.0
