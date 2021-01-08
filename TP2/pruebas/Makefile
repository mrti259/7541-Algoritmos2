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

clean:
	rm *.exe
