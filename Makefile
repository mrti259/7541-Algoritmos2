CFLAGS=-Wall -Werror -Wconversion -std=c99 -o
CFILES=*.c
EXEC=evento_pesca
VFLAGS=--leak-check=full --track-origins=yes --show-reachable=yes
EXTRA=README.txt 2020_2C_TP1_Algo2.pdf
ENTREGA=20202C-7541-TP1.zip

build:
	gcc $(CFILES) $(CFLAGS) $(EXEC) -g

lint:
	cppcheck --enable=all $(CFILES)

test: $(EXEC)
	valgrind $(VFLAGS) ./$(EXEC)

debug: $(EXEC)
	valgrind $(VFLAGS) -v ./$(EXEC)

zip:
	zip $(ENTREGA) $(CFILES) $(EXTRA)

.PHONY: clean

clean:
	rm $(EXEC)
