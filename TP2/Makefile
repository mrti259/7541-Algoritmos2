CC = gcc
CFLAGS = -g -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O0 -o
VAL = valgrind
VFLAGS = --leak-check=full --track-origins=yes --show-reachable=yes 
EXEC = juego.bin
EXEC_TEST = pruebas.bin
CFILES = tda/*.c juego.c batallas.c menu.c main.c
DIR_TESTS = pruebas

all: build files play

build:
	@echo "Compilando..."
	@$(CC) $(CFLAGS) $(EXEC) $(CFILES)

files:
	@echo "Generando algunos archivos de ejemplo..."
	@mkdir -p datos/jugador datos/gimnasios
	@cp docs/jugador/* datos/jugador/
	@cp docs/gimnasios/* datos/gimnasios/
	@sleep 1

play:
	@./$(EXEC)

test: build files
	$(VAL) $(VFLAGS) ./$(EXEC)

test_juego:
	$(CC) $(CFLAGS) $(EXEC_TEST) $(DIR_TESTS)/juego_pruebas.c batallas.c tda/*.c
	$(VAL) $(VFLAGS) ./$(EXEC_TEST)

test_heap:
	$(CC) $(CFLAGS) $(EXEC_TEST) $(DIR_TESTS)/heap_pruebas.c tda/heap.c
	$(VAL) $(VFLAGS) ./$(EXEC_TEST)

test_abb:
	$(CC) $(CFLAGS) $(EXEC_TEST) $(DIR_TESTS)/abb_pruebas.c tda/abb.c
	$(VAL) $(VFLAGS) ./$(EXEC_TEST)

test_lista:
	$(CC) $(CFLAGS) $(EXEC_TEST) $(DIR_TESTS)/lista_pruebas.c tda/lista.c
	$(VAL) $(VFLAGS) ./$(EXEC_TEST)


lint:
	cppcheck --enable=all *.c */*.c

clean:
	rm *.bin */*.bin *.tmp */*.tmp
