#ifndef __JUEGO_H__
#define __JUEGO_H__

#define MAX_NOMBRE 100

typedef struct pokemon pokemon_t;

typedef struct entrenador entrenador_t;

typedef struct gimnasio gimnasio_t;

typedef struct juego juego_t;

/**
 * Copia el nombre del Pokemon o lo deja en blanco ("") si falla.
 */
void pokemon_nombre(pokemon_t*, char[MAX_NOMBRE]);

/**
 * Devuelve el ataque real del Pokémon o 0 si no hay Pokémon.
 */
int pokemon_ataque(pokemon_t*);

/**
 * Devuelve la defensa real del Pokémon o si no hay Pokémon.
 */
int pokemon_defensa(pokemon_t*);

/**
 * Devuelve la velocidad real del Pokémon o si no hay Pokémon.
 */
int pokemon_velocidad(pokemon_t*);

/**
 * Devuelve el tipo principal del Pokémon o si no hay Pokémon.
 */
char pokemon_tipo_principal(pokemon_t*);

/**
 * Devuelve el tipo secundario del Pokémon o si no hay Pokémon.
 */
char pokemon_tipo_secundario(pokemon_t*);

/**
 * Copia el nombre del entrenador o lo deja en blanco ("") si falla.
 */
void entrenador_nombre(entrenador_t*, char[MAX_NOMBRE]);

/**
 * Copia el nombre del gimnasio o lo deja en blanco ("") si falla.
 */
void gimnasio_nombre(gimnasio_t*, char[MAX_NOMBRE]);

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

#endif /*__JUEGO_H__*/
