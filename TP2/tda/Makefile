CC=gcc
CFLAGS=-g -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O0 -o
VAL=valgrind
VFLAGS=--leak-check=full --track-origins=yes --show-reachable=yes
EXEC=pruebas.exe
CFILES=heap.c pruebas.c
HFILES=heap.h

lint:
	cppcheck --enable=all *.c

test: $(CFILES) $(HFILES)
	$(CC) $(CFLAGS) $(EXEC) $(CFILES)
	$(VAL) $(VFLAGS) ./$(EXEC)

clean:
	rm *.exe
