CC=gcc
CFLAGS=-g -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O0 -o
VAL=valgrind
VFLAGS=--leak-check=full --track-origins=yes --show-reachable=yes
EXEC=pruebas.exe

lint:
	cppcheck --enable=all ../*.c

heap:
	$(CC) $(CFLAGS) $(EXEC) heap_pruebas.c ../tda/heap.c
	$(VAL) $(VFLAGS) ./$(EXEC)

abb:
	$(CC) $(CFLAGS) $(EXEC) abb_pruebas.c ../tda/abb.c
	$(VAL) $(VFLAGS) ./$(EXEC)

lista:
	$(CC) $(CFLAGS) $(EXEC) lista_pruebas.c ../tda/lista.c
	$(VAL) $(VFLAGS) ./$(EXEC)

juego:
	$(CC) $(CFLAGS) $(EXEC) juego_pruebas.c ../tda/heap.c ../tda/lista.c ../batallas.c
	$(VAL) $(VFLAGS) ./$(EXEC)

clean:
	rm *.exe
