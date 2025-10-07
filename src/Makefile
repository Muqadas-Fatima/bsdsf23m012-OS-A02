CC = gcc
CFLAGS = -Wall -Wextra -O2

# Change this to your latest source and binary
SRC = src/lsv1.3.0.c
BIN = bin/lsv1.3.0

all: $(BIN)

$(BIN): $(SRC)
	$(CC) $(CFLAGS) -o $(BIN) $(SRC)

clean:
	rm -f bin/lsv1.3.0
