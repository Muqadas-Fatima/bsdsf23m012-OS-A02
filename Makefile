# Makefile for ls-v1.1.0
CC = gcc
SRC = src/lsv1.1.0.c
BIN = bin/lsv1.1.0

all: $(BIN)

$(BIN): $(SRC)
	mkdir -p bin
	$(CC) $(SRC) -o $(BIN)

clean:
	rm -rf bin/*
