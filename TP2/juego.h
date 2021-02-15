#ifndef __JUEGO_H__
#define __JUEGO_H_

typedef struct pokemon pokemon_t;

typedef struct entrenador entrenador_t;

typedef struct gimnasio gimnasio_t;

typedef struct juego juego_t;

/**
 * Carga la informacion del archivo en el juego
 *
 * Devuelve 0 si se cargo informacion en el juego
 */
int cargar_gimnasios(const char* ruta_archivo, juego_t* juego);

#endif /*__JUEGO_H_*/
