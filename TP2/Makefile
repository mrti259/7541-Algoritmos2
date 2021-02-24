CC = gcc
CFLAGS = -g -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O0 -o
VAL = valgrind
VFLAGS = --leak-check=full --track-origins=yes --show-reachable=yes
EXEC = juego.bin
CFILES = tda/*.c juego.c inicio.c
DIRS = datos/jugador datos/gimnasios

all: build dirs play

build:
	$(CC) $(CFLAGS) $(EXEC) tda/*.c juego.c inicio.c

dirs:
	mkdir -p $(DIRS)

play:
	./$(EXEC)

test: build
	$(VAL) $(VFLAGS) ./$(EXEC)

lint:
	cppcheck --enable=all *.c

clean:
	rm *.bin */*.bin *.tmp */*.tmp
