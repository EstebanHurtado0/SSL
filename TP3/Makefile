CC = gcc
OUTFILE = parser

run: build
	./$(OUTFILE) < entrada.txt

build:
	flex *.l
	bison *.y
	$(CC) -Wall *.c -o $(OUTFILE) -lfl

