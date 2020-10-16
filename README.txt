Autor: Martina Garibotti
Fecha: 16/10/2020
Facultad de Ingeniería, Universidad de Buenos Aires
7541 - Algoritmos y Programación II
Curso 3 - Méndez


¡Gran pesca Pokémon!
====================

Introducción:
-------------

El siguiente trabajo consiste en el desarrollo de las implementaciones
de una biblioteca dada cumpliendo con las firmas solicitadas. Las
firmas pedidas se pueden encontrar en el archivo `evento_pesca.h`,
mientras su implementación se encuentra en `evento_pesca.c`. Para que
el código pueda ser compilado y ejecutado, se proveen archivos extras
como `misty.c' que permite un flujo simple del programa.

Sin embargo se debe contar con archivos de texto que contenga registros
de Pokemón en formato `especie;velocidad;peso;color` para simular el
traslado de Pokemón del arrecife al acuario.

El programa cargará en la memoria los registros de Pokemón y hará una
selección de algunos Pokemón especiales para llevar al evento.

Se utilizaran las siguientes funciones:

bool seleccionar_chico(pokemon_t* pokemon) -> Para seleccionar Pokemón
chicos.

bool seleccionar_lento(pokemon_t* pokemon) -> Para seleccionar Pokemón
lentos.

bool seleccionar_magikarp_dorado(pokemon_t* pokemon) -> Buscará el
premio mayor del evento.

bool seleccionar_sublegendario(pokemon_t* pokemon) -> Podrían
encontrarse Pokemón de rareza.

bool seleccionar_legendario(pokemon_t* pokemon) -> ¿Quién no quiere
tener un Mewtwo en su equipo?

La selección y traslado se hará gradual, por lo que si no se cumple con
la cantidad solicitada, se interrumpirá el traslado de más Pokemón y se
guardarán los que se encuentren en el acuario.


Compilación:
------------

Para compilar el código fuente se recomienda ubicarse en el directorio
e ingresar el siguiente comando en la consola.

> gcc *.c -Wall -Werror -Wconversion -std=c99 -o evento_pesca


Ejecución:
----------

Una vez que se ha compilado con éxito, se podrá ejecutar haciendo el
siguiente llamado.

> ./evento_pesca

Pero es importante mencionar que el programa buscará en el directorio
el archivo `arrecife.txt` que contará con la información de los Pokemón
a cargar. En caso de que este no pueda ser leído, el programa
finalizará con la salida -1. Pero si el flujo del programa no se vea
interrumpido, puede esperarse la escritura del archivo `acuario.txt` en
el mismo directorio con información de los Pokemón que se podrían
trasladar al acuario. En caso de que no se pudo cumplir con unas de las
traslaciones solicitadas, el programa interrumpirá su flujo, guardará
la información en el archivo antes mencionado y devolverá la salida -1.

También puede pasar el nombre de los archivo a abrir por parámetro de
la siguiente manera:

> ./evento_pesca [mi_arrecife.txt] [mi_acuario.txt]

Siendo:
    mi_arrecife.txt -> el archivo de entrada
    mi_acuario.txt -> el archivo de salida


Marco Teórico:
---------------

Una vez que el código fuente es compilado, toma forma como un archivo
en formato objeto el cual es posible ejecutar en una computadora. Al
ser sus instrucciones ejecutadas por el procesador de la computadora,
pueden distinguirse tres secciones en el funcionamiento del programa:

Código (.code): donde se almacena el código del mismo, traducido por el
compilador.

Datos (.data): donde se almacenan los datos de las constantes, las
variables externas y los valores literales del programa.

Pila de ejecución (.stack): existente sólo durante la ejecución del programa.

Montículo (.heap): existente sólo durante la ejecución del programa.

Normalmente, las tres secciones .code, .data y .stack son controladas
exclusivamente por el compilador y el programador no tiene forma de
alterar estas secciones. La última sección, .heap, está reservada a la
memoria dinámica. Esta no es reservada por el compilador, sino que es
manejada por el programador, en tiempo de ejecución del programa.

El sistema operativo es el encargado de leer la estructura del programa
compilado, y teniendo en cuenta la memoria RAM, reserva espacio para
las cuatro secciones.

- Punteros.

La memoria de la computadora puede verse como un arreglo de celdas con
un nombre asociado. Este nombre es un número, cuya longitud depende de
la arquitectura de la computadora. Cada una de las celdas posee un
número consecutivo a su vecina, iniciando de 0 hasta la cantidad que la
computadora posea.

Los punteros variables tipo (void*), un tipo de dato cuyo rango son
todos los valores que puede tomar una dirección de memoria.


- Aritmética de punteros.

Los punteros son variables, al igual que otros tipos de variables,
tienen definidos operadores sobre ellas y sus valores. Los más
utilizados son:

Operador de dirección (&): permite acceder a la dirección de memoria de
una variable.

Operador de Indirección(*): permite declarar un tipo de dato puntero, ó
permite ver el valor que está en la dirección asignada.

Incrementos(++) y decrementos(--): se puede usar un puntero como se de
un array se tratase.

La ventaja de esta nomenclatura para las direcciones de memoria, es que
nos permite acceder a una celda conociendo la cantidad de bytes que se
desee desplazar a partir de otra celda, por medio de un puntero.

Así mismo, la notación para acceder a un elemento de un arreglo y la
aritmética de punteros son similares.

Algunas equivalencias serian:

┌──────────────────┬────────────────────┐
│ Notación Arreglo │  Notación Puntero  │
├──────────────────┼────────────────────┤
│     array[0]     │       *array       │
│     array[i]     │    *(array + i)    │
│    array[2 * i]  |  *(array + 2 * 1)  │
│ array[tope - i]  │*(array + tope - i) │
│   matriz[0][0]   │     **matriz       │
│   matriz[i][j]   │*((matriz + i) + j) │
│ matriz[i][j][k]  │*(((matriz+i)+j)+k) │
└──────────────────┴────────────────────┘


- Punteros a funciones.

Las funciones en C se guardan en la sección .text y un puntero a una
función no es más que la dirección de memoria donde reside una
determinada función.

Los punteros a funciones pueden: ser elementos de un vector, ser pasados
como parámetros a una función o ser devueltos por una función.

Un ejemplo de declaración y asignación puede ser:

```c
tipo_de_retorno (* mi_funcion) (tipo_1, ...); // Declaración de mi_funcion()
mi_funcion = otra_funcion;  // mi_funcion apunta a la misma dirección que otra_funcion()
                            // por lo cual tienen el mismo funcionamiento.
```

Es importante tener en cuenta estas diferencias con los punteros
_normales_:

1. Los punteros a funciones apuntan a código y no a datos,
normalmente a la primera instrucción ejecutable de una función.

2. No se debe reservar-liberar espacio de memoria.

3. No es necesario utilizar los operadores (&) y (*). El nombre de la
función puede ser utilizado para obtener la dirección de la misma. A su
vez también puede ser desreferenciada sin la utilización del *.


- Memoria Dinámica

La memoria dinámica es aquella que será reservada y utilizada
únicamente en tiempo de ejecución. Esta es reservada en el .heap del
programa. Para ser utilizada, debe ser solicitada al sistema operativo
por el programa y dependerá del programador su correcta administración.

La biblioteca estándar `stdlib.h` proporciona las funciones útiles para
hacer uso de la memoria dinámica. Entre ellas, se han encuentran malloc(),
calloc(), realloc() y free().

void* malloc(size_t size) -> reserva tantos bytes sean pasados por
parámetros en el heap. Devuelve un puntero al inicio de aquella memoria
o NULL.

void* calloc(size_t n, size_t size) -> reserva n bloques de tamaño size
en el heap, la memoria se setea con 0 y devuelve un puntero al inicio
de aquella memoria.

void* realloc(void* ptr, size_t size) -> modifica el tamaño de un
bloque de memoria apuntado por ptr en size bytes y devuelve un puntero
al inicio de aquel bloque o NULL. Si ptr era NULL y size es distinto a
0, equivale a hacer malloc(size). Si ptr no era NULL y size es 0
equivale a hacer free(ptr). Si el tamaño es mayor al que tenia antes
del llamado, la memoria añadida no se encuentra inicializada en ningún
valor.

void* free(void* ptr) -> libera el espacio de memoria apuntado por ptr
que debe haber sido devuelto previamente por una llamada malloc(),
calloc() o realloc().
