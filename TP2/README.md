# Pokémon

Simulador de combate de Pokémon por consola.

## Introducción

Este trabajo fue hecho para la asignatura Algoritmos y Programación 2 de la
Facultad de Ingeniería de la Universidad de Buenos Aires. La consigna se
encuentra en la carpeta `docs`.

## Compilacion

Para jugar es necesario que tengas:

- `gcc`: para compilar los archivos 

- `make`: para automatizar las tareas de compilacion

- *unix: porque no fue testeado en otros sistemas

Ahora en una consola ejecuta el siguiente comando:

> $ make

  Te creará el ejecutable y los directorios necesarios para empezar tu
  aventura.

> $ ./juego.bin

  Para iniciar el juego

## Desarrollo

En `menu.c` se brindan las funciones que permiten darle una interfaz por
consola al programa para facilitar su jugabilidad. Está hecho a modo de
ejemplo, ya sé que es horrible en tanto apariencia y en código.

En `juego.h` se encuentran las funciones esenciales para reproducir la lógica
del juego. Estas estructuras y operaciones se encuentran encapsuladas para
evitar su incorrecta manipulación y prevenir errores. Cualquier sugerencia para
mejorar el juego siempre será bienvenida (mientras sea con respeto).

En `batallas.h` se encuentran las funciones de batalla a utilizar. Estas son
utilizadas por `juego.h` mediante un controlador, es decir, `juego.h` hace uso
de un controlador externo que determinará cuáles son las funciones a utilizar.
Este controlador se encuentra declarado en `juego.h` de la siguiente manera:

```c
extern int funcion_batalla_controller(int, void*, void*);
```

Y su implementación se encuentra en `main.c`.

La razón por la cuál se realizó esto, es porque permite extender el juego sin
modificar `juego.c` o `juego.h` o romper con su encapsulación. Se pueden usar
la cantidad de bibliotecas de batallas que se deseen, mientras haya un
controlador que se encargue de articularlas adecuadamente.

En `tda/` se encuentran otras bibliotecas creadas para la asignatura, que
permiten la utilización de listas, árboles binarios y árboles heap.

`colors.h` fue extraído de https://gist.github.com/guiben/abb55f8a3eb1650d1d57
para agregar colores a la interfaz.

`borders.h`, de mi autoría, permite el agregado de bordes en la interfaz.

### Sobre el juego

#### Pokémon

Son criaturas privadas de su libertad y entrenadas para combatir entre ellas.
Estas tienen diferentes habilidades que van por los elementos que manejan
(tipos) y sus estadísticas de ataque, defensa y velocidad. Cuando combaten
pueden mejorar sus estadísticas y ser explotados en mayor medida por sus
captores.

#### Entrenadores

Son personajes que cuentan con uno o varios Pokémon.

Están limitados a cargar con ellos hasta 6 Pokémon que serán almacenados en sus
Pokébolas, pero pueden tener más que quedarán a cargo de un profesor Pokémon
que les garantizará cuidado y al menos 20 minutos al sol por día.

Para llevar la cuenta de los Pokémon que poseen en su totalidad o en su party,
se hace uso de listas.

Las listas son la mejor forma de representar estas estructuras porque el
entrenador arma su equipo (party) agregando, consultando y quitando
continuamente de los conjuntos de Pokémon que tiene.

Cuando un entrenador decide enfrentar a otro, podríamos pensar en la
implementación de una cola: el primer Pokémon de su party será el primero en
combatir y a medida que agotan su energía se va avanzando en la cola. Pero por
lo mencionado anteriormente en el armado del equipo segun party/caja,
concluimos que usar una lista es más conveniente y, durante los combates, se
conservan las listas y se utiliza un iterador para avanzar sobre ellas a medida
que cambian los Pokémon

#### Gimnasios

En ellos se encuentra uno o más entrenadores, cuyo entrenador principal es el
líder.

El enfrentamiento contra entrenadores tiene orden y se pelea contra rivales más
débiles hasta llegar al líder que cuenta con estadísticas más altas para
presentar un desafío para el jugador.

El líder es la figura central por lo que, cuando se carga un gimnasio, primero
debe asegurarse que haya un líder (que además cuente con Pokémon) y después se
cargan los entrenadores.

Por esta razón, los gimnasios hacen uso de una pila que organice a los
entrenadores que contiene. El líder es el primer elemento a cargar y el último
a borrar cuando ya se hayan eliminado los otros entrenadores. Para desapilar un
entrenador, primero hay que vencerlo. Por lo tanto, primero se combate y si el
usuario resulta ganador, se borra lo borra.

Sobre el líder se hace una excepción porque después de vencerlo se tiene la
posibilidad de tomar uno de sus Pokémon. Por este motivo, antes de borrarlo y
borrar el gimnasio, se lo conserva, se marca el gimnasio como derrotado y se lo
deja en ese estado hasta que se decida enfrentar un nuevo gimnasio o se tome un
Pokémon.

#### Personaje principal

Es el personaje que manejará el jugador, es un entrenador que reta gimnasios
para convertirse en un Maestro Pokémon. Tiene las características del resto de
los entrenadores y la ventaja de que sus Pokémon subirán sus estadísticas al
ganar batallas.

Para hacer más fácil su aventura, el camino que hace frente en los gimnasios va
con dificultad creciente. Para esto se emplea un árbol heap que siempre
devolverá cuál es el gimnasio con el que debe combatir.

#### Juego

Es la estructura principal para el desarrollo del juego. Se crea un personaje,
que será el jugador y se cargan los gimnasios contra los que se peleará.

El personaje principal siempre debe contar con al menos un Pokémon. Por eso,
cuando no se pueda cargar ninguno, se dará la posibilidad de iniciar una nueva
partida y, en su nueva aventura, se le entregará un Pokémon inicial.

Luego se deberán cargar los gimnasios con los cuales comenzar la aventura. Cada
gimnasio debe tener un líder y el líder debe tener al menos un Pokémon. Los
entrenadores restantes que pertenezcan al gimnasio, también deben tener al
menos un Pokémon y prepararán al jugador para el combate final.

El juego siempre conoce quién es el personaje principal, cuál es el Pokémon con
el que combatirá, quién es su próximo contricante y qué Pokémon utilizará.
Obviamente, también conoce cuál es el gimnasio en el que se encuentra y si este
fue derrotado o aún no.

## Pruebas

El archivo `make` incluye otras reglas que permiten realizar pruebas.

- `make test` ejecuta el juego bajo la herramienta valgrind que permite detectar
accesos incorrectos a la memoria y/o pérdidas.

- `make test_juego` ejecuta pruebas unitarias de la mayoría de las funciones de
juego.c. Estas pruebas son de caja blanca y también hace uso de valgrind.

- `make test_heap` ejecuta pruebas unitarias de las funciones de heap.

- `make test_abb` ejecuta pruebas unitarias de las funciones de abb.

- `make test_lista` ejecuta pruebas unitarias de las funciones de lista.

- `make lint` hace uso de `cppcheck` para analizar el código.
