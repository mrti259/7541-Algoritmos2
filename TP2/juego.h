#ifndef __JUEGO_H__
#define __JUEGO_H__

#include <stdbool.h>
#include <stddef.h>

#define MAX_NOMBRE 100

typedef struct pokemon pokemon_t;

typedef struct entrenador entrenador_t;

typedef struct gimnasio gimnasio_t;

typedef struct juego juego_t;

/**
 * Argumentos:
 *  - id_funcion es la función de batalla con la que combateran los Pokémon.
 *               El controlador se responsabiliza de validar la id.
 *  - pokemon_1 apunta al Pokémon que usará el personaje principal para el combate.
 *  - pokemon_2 apunta al otro Pokémon que combatirá.
 * 
 * Devuelve:
 *  - > 0 si gana pokemon_1
 *  - < 0 si gana pokemon_2
 *  - = 0 si no hay combate
 */
extern int funcion_batalla_controller(int id_funcion, pokemon_t* pokemon_1, pokemon_t* pokemon_2);

/**
 * Copia el nombre del Pokemon el vector o lo deja en blanco si no existe.
 */
void pokemon_nombre(pokemon_t*, char[MAX_NOMBRE]);

/**
 * Devuelve el ataque real del Pokémon o -1 si no hay Pokémon.
 */
int pokemon_ataque(pokemon_t*);

/**
 * Devuelve la defensa real del Pokémon o -1 si no hay Pokémon.
 */
int pokemon_defensa(pokemon_t*);

/**
 * Devuelve la velocidad real del Pokémon o -1 si no hay Pokémon.
 */
int pokemon_velocidad(pokemon_t*);

/**
 * Devuelve el tipo principal del Pokémon o '\0' si no hay Pokémon.
 */
char pokemon_tipo_principal(pokemon_t*);

/**
 * Devuelve el tipo secundario del Pokémon o '\0' si no hay Pokémon.
 */
char pokemon_tipo_secundario(pokemon_t*);

/**
 * Devuelve true si le Pokémon está en un party.
 */
bool pokemon_en_party(pokemon_t*);

/**
 * Copia el nombre del entrenador o lo deja en blanco ("") si falla.
 */
void entrenador_nombre(entrenador_t*, char[MAX_NOMBRE]);

/**
 * Devuelve la cantidad de pokemon que tiene el entrenador en su party.
 */
size_t entrenador_party(entrenador_t*);

/**
 * Devuelve la cantidad de Pokémon que le quedan al entrenador para combatir.
 */
size_t entrenador_pokemon_restante(entrenador_t*);

/**
 * Procedimiento que dado un entrenador y una funcion para mostrar
 * información de Pokémon, recorre el party del entrenador y los muestra.
 * Admite un puntero de contexto que puede ser utilizado por la función mostrar.
 */
void entrenador_mostrar_party(entrenador_t*, void (*mostrar)(pokemon_t*, void*), void*);

/**
 * Procedimiento que dado un entrenador y una funcion para mostrar
 * información de Pokémon, recorre el conjunto de Pokémon obtenidos del
 * entrenador y los muestra.
 * Admite un puntero de contexto que puede ser utilizado por la función mostrar.
 */
void entrenador_mostrar_pokemon(entrenador_t*, void (*mostrar)(pokemon_t*, void*), void*);

/**
 * Copia el nombre del gimnasio o lo deja en blanco ("") si falla.
 */
void gimnasio_nombre(gimnasio_t*, char[MAX_NOMBRE]);

/**
 * Devuelve la id de la función de batalla o -1 si falla.
 */
int gimnasio_id_funcion(gimnasio_t*);

/**
 * Devuelve la cantidad de entrenadores que hay quedan en el gimnasio.
 * Devuelve 0 si no hay gimnasio.
 */
size_t gimnasio_entrenadores(gimnasio_t*);

/**
 * Devuelve true si el gimnasio se encuentra derrotado.
 * Devuelve false si no hay gimnasio.
 */
bool gimnasio_derrotado(gimnasio_t*);

/**
 * Devuelve un puntero a una instancia de juego con sus valores inicializados en
 * 0 o NULL si falla.
 */
juego_t* juego_crear();

/**
 * Libera la memoria dedicada al juego y toda sus estructuras. Si el juego es
 * NULL no ocurre nada.
 */
void juego_liberar(juego_t*);

/**
 * Devuelve la cantidad de gimnasios que hay cargados en el juego.
 */
size_t juego_gimnasios(juego_t*);

/**
 * Crea al personaje principal, le asigna el nombre dado y le da un Pokémon.
 */
int juego_nuevo(juego_t*, char[MAX_NOMBRE]);

/**
 * Devuelve un puntero al gimnasio que el jugador debe vencer para avanzar o
 * NULL si no hay gimnasios.
 */
gimnasio_t* gimnasio_actual(juego_t*);

/**
 * Devuelve un puntero al entrenador contra el que se combatirá o NULL.
 */
entrenador_t* rival_actual(juego_t*);

/**
 * Devuelve un puntero al Pokémon contra el que se combatirá o NULL.
 */
pokemon_t* pokemon_enemigo(juego_t*);

/**
 * Devuelve un puntero al jugador o NULL.
 */
entrenador_t* personaje_principal(juego_t*);

/**
 * Devuleve un puntero al Pokemon del jugador o NULL.
 */
pokemon_t* pokemon_jugador(juego_t*);

/**
 * Inicia las batallas contra un gimnasio,
 */
int retar_gimnasio(juego_t*, void (*mostrar)(juego_t*));

/**
 * Quita un Pokémon del party del jugador. Devuelve -1 si falla.
 */
int quitar_del_party(juego_t*, size_t posicion);

/**
 * Agrega un Pokémon de la caja del jugador a su party. Devuelve -1 si falla.
 */
int agregar_a_party(juego_t*, size_t posicion);

/**
 * Toma un Pokémon del líder del gimnasio si este fue vencido. Devuelve -1 si falla.
 */
int tomar_pokemon(juego_t*, size_t posicion);

/**
 * Carga informacion de gimnasios, entrenadores y pokemon de un archivo al
 * juego.
 *
 * Devuelve 0 si la carga resultó exitosa.
 */
int cargar_gimnasios(const char* ruta_archivo, juego_t* juego);

/**
 * Carga la informacion del personaje principal desde un archivo al juego.
 *
 * Devuelve 0 si la carga resultó exitosa.
 */
int cargar_jugador(const char* ruta_archivo, juego_t* juego);

/**
 * Guarda en la ruta indicada la información del jugador.
 *
 * Devuelve 0 si el guardado resultó exitoso.
 */
int guardar_jugador(const char* ruta_archivo, juego_t* juego);

#endif /*__JUEGO_H__*/
