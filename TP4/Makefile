CC = gcc
CFLAGS = -Wall -pedantic-errors -D_GNU_SOURCE -std=c2x
OUTFILE = parser

build:
	flex *.l
	bison *.y
	$(CC) ${CFLAGS} *.c -o $(OUTFILE) -lfl -lm

clean:
	rm scanner.c scanner.h parser.c parser.h parser
