# Pokémon

Simulador de combate de Pokémon por consola.

## Introducción

## Compilacion

Para jugar es necesario que tengas:

- `gcc`: para compilar los archivos 

- `make`: para automatizar las tareas de compilacion

- *nix: porque no fue testeado en otros sistemas

Ahora en una consola ejecuta el siguiente comando:

> $ make

  Te creará el ejecutable y los directorios necesarios para empezar tu
  aventura.

> $ ./juego.bin

  Para iniciar el juego

## Desarrollo

Este trabajo fue hecho para la asignatura Algoritmos y Programación 2 de la
Facultad de Ingeniería de la Universidad de Buenos Aires. La consigna se
encuentra en la carpeta `docs`.

En `inicio.c` se brindan las funciones que permiten darle una interfaz por
consola al programa para facilitar su jugabilidad. Esta hecho a modo de
ejemplo, ya se que es horrible.

En juego.h se encuentran las funciones esenciales para reproducir la lógica del
juego. Estas estructuras y operaciones se encuentran encapsuladas para que
evitar su incorrecta manipulación y prevenir errores. Cualquier sugerencia para
mejorare el juego siempre será bienvenida (mientras sea con respeto).

### Sobre el juego

#### Pokémon

Son pequeñas bestias hechas para combatir entre ellas. Estas tienen diferentes
habilidades que van por los elementos que manejan (tipos) y sus estadísticas de
ataque, defensa y velocidad. Cuando combaten logran mejorar sus estadísticas.

#### Entrenadores

Son personajes que cuentan con uno o varios Pokémon.

Están limitados a cargar con ellos hasta 6 Pokémon, pero pueden tener más que
quedarán a cargo de un profesor Pokémon que garantizará siempre un gran
cuidado.

Para llevar la cuenta de los Pokemón que poseen en su totalidad o en su party,
se hace uso de listas.

Las listas son la mejor forma de representar estas estructuras porque el
entrenador arma su equipo (party) agregando, consultando y quitando
continuamente de los conjuntos de Pokémon que tiene.

Cuando un entrenador decide enfrentar a otro, podríamos pensar en la
implementación de una cola: el primer Pokémon de su Party será el primero en
combatir y a medida que agoten su energía se va avanzando en la "cola". Pero
por lo mencionado anteriormente en el armado del equipo segun party/caja,
concluimos que usar una lista parece una mejor implementación.

#### Gimnasios

En ellos se encuentra uno o más entrenadores, donde el entrenador principal es
el líder.

El enfrentamiento contra entrenadores tiene un orden y se pelea contra rivales
más débiles hasta llegar al líder que cuenta con estadísticas más altas para
representar un desafío para el jugador.

El líder es la figura central por lo que cuando se carga un gimnasio primero
debe asegurarse que haya un líder (que además cuente con Pokémon) y después se
cargan los entrenadores.

Por esta razón, los gimnasios hacen uso de una pila que organice a los
entrenadores que contiene. El líder es el primer elemento a cargar y el último
a borrar cuando ya se hayan eliminado los entrenadores restantes. Para
desapilar un entrenador, primero debe vencerse por lo que primero se combate y
si el usuario resulta ganador, se borra el entrenador.

Sobre el líder se hace una excepción porque después de vencerlo se tiene la
posibilidad de tomar uno de sus Pokemón. Por este motivo, antes de borrarlo y
borrar el gimnasio, se lo conserva, se marca el gimnasio como derrotado y se lo
deja en ese estado hasta que se decida enfrentar un nuevo gimnasio.

Comentario:

- Queda a cargo del desarrollado elegir cuantos Pokémon pueden tomarse
del líder.

#### Personaje principal

Es el personaje que manejará el jugador, es un entrenador más. Su misión es
combatir a los entrenadores de los Gimnasios y vencer a su lider hasta
convertirse en un Maestro Pokémon. Tiene las características del resto de los
entrenadores y la ventaja de que sus Pokémon subirán sus estadísticas al ganar
batallas.

Para hacer más fácil su aventura, el camino que se hace frente en los gimnasios
va con dificultad creciente. Para esto se emplea un árbol heap.
