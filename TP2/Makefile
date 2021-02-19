CC=gcc
CFLAGS=-g -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O0 -o
VAL=valgrind
VFLAGS=--leak-check=full --track-origins=yes --show-reachable=yes
EXEC=juego.bin

lint:
	cppcheck --enable=all ../*.c

build:
	$(CC) $(CFLAGS) $(EXEC) tda/*.c juego.c inicio.c

play: build
	./$(EXEC)

test: build
	$(VAL) $(VFLAGS) ./$(EXEC)

clean:
	rm *.bin
