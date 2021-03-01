CFLAGS=-Wall -Werror -Wconversion -std=c99 -o
CFILES=*.c
EXEC=evento_pesca
VFLAGS=--leak-check=full --track-origins=yes --show-reachable=yes
EXTRA=README.md 2020_2C_TP1_Algo2.pdf Makefile
TEST=./arrecifes
ENTREGA=20202C-7541-TP1.zip

build:
	gcc $(CFILES) $(CFLAGS) $(EXEC) -g

lint:
	cppcheck --enable=all $(CFILES)

test_0: $(EXEC)
	valgrind $(VFLAGS) ./$(EXEC) $(TEST)/arrecife.txt acuario.txt
	echo 'Finalizacion test archivo inexistente'

test_1: $(EXEC)
	valgrind $(VFLAGS) ./$(EXEC) $(TEST)/vacio.txt acuario_vacio.txt
	echo 'Finalizacion test archivo vacio'

test_2: $(EXEC)
	valgrind $(VFLAGS) ./$(EXEC) $(TEST)/traslado_todos.txt acuario_todos.txt
	echo 'Finalizacion test traslado todos'

test_3: $(EXEC)
	valgrind $(VFLAGS) ./$(EXEC) $(TEST)/traslado_todos_y_sobra.txt acuario_todos.txt
	echo 'Finalizacion test traslado todos y sobran pokemon'

test_4: $(EXEC)
	valgrind $(VFLAGS) ./$(EXEC) $(TEST)/variado.txt acuario_variado.txt
	echo 'Finalizacion test variado'

zip:
	zip $(ENTREGA) $(CFILES) $(EXTRA) $(TEST)/*

.PHONY: clean

clean:
	rm $(EXEC)
