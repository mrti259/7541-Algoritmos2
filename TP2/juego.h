#ifndef __JUEGO_H__
#define __JUEGO_H__

typedef struct pokemon pokemon_t;

typedef struct entrenador entrenador_t;

typedef struct gimnasio gimnasio_t;

typedef struct juego juego_t;

/**
 * Carga la informacion de los gimnasios desde un archivo al juego
 *
 * Devuelve 0 si se cargo informacion en el juego
 */
int cargar_gimnasios(const char* ruta_archivo, juego_t* juego);

/**
 * Carga la informacion del jugador desde un archivo al juego
 *
 * Devuelve 0 si se cargo informacion en el juego
 */
int cargar_jugador(const char* ruta_archivo, juego_t* juego);

#endif /*__JUEGO_H__*/
