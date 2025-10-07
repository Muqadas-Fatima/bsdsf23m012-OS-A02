# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -O2

# Source files
SRC_V1_0 = src/lsv1.0.0.c
SRC_V1_1 = src/lsv1.1.0.c
SRC_V1_2 = src/lsv1.2.0.c
SRC_V1_3 = src/lsv1.3.0.c

# Binaries
BIN_V1_0 = bin/lsv1.0.0
BIN_V1_1 = bin/lsv1.1.0
BIN_V1_2 = bin/lsv1.2.0
BIN_V1_3 = bin/lsv1.3.0

# Default target: build all versions
all: $(BIN_V1_0) $(BIN_V1_1) $(BIN_V1_2) $(BIN_V1_3)

# Build rules
$(BIN_V1_0): $(SRC_V1_0)
	$(CC) $(CFLAGS) -o $(BIN_V1_0) $(SRC_V1_0)

$(BIN_V1_1): $(SRC_V1_1)
	$(CC) $(CFLAGS) -o $(BIN_V1_1) $(SRC_V1_1)

$(BIN_V1_2): $(SRC_V1_2)
	$(CC) $(CFLAGS) -o $(BIN_V1_2) $(SRC_V1_2)

$(BIN_V1_3): $(SRC_V1_3)
	$(CC) $(CFLAGS) -o $(BIN_V1_3) $(SRC_V1_3)

# Clean all binaries
clean:
	rm -f bin/lsv1.0.0 bin/lsv1.1.0 bin/lsv1.2.0 bin/lsv1.3.0
