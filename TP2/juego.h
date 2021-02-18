#ifndef __JUEGO_H__
#define __JUEGO_H__

#define MAX_NOMBRE 100

typedef struct pokemon pokemon_t;

/**
 * Devuelve el ataque real del pokemon.
 */
int pokemon_ataque(pokemon_t*);

/**
 * Devuelve la defensa real del pokemon.
 */
int pokemon_defensa(pokemon_t*);

/**
 * Devuelve la velocidad real del pokemon.
 */
int pokemon_velocidad(pokemon_t*);

/**
 * Devuelve el tipo principal del pokemon.
 */
char pokemon_tipo_principal(pokemon_t*);

/**
 * Devuelve el tipo secundario del pokemon.
 */
char pokemon_tipo_secundario(pokemon_t*);

/**
 * Copia el nombre del Pokemon.
 */
void pokemon_nombre(pokemon_t*, char[MAX_NOMBRE]);

/* Caracteres que identifican los tipos de Pokemon */
enum tipos_pokemon
{
    AGUA = 'A' ,
    BICHO = 'B' ,
    DRAGON = 'D' ,
    ELECTRICO = 'E' ,
    FUEGO = 'F' ,
    FANTASMA = 'G' ,
    HOJA = 'H' ,
    LUCHA = 'L' ,
    NORMAL = 'N' ,
    PSIQUICO = 'P' , 
    ROCA = 'R' ,
    TOXICO = 'T' ,
    VUELO = 'V'
};

typedef struct entrenador entrenador_t;

typedef struct gimnasio gimnasio_t;

typedef struct juego juego_t;

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
