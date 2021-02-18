#include "constantes.h"
#include "juego.h"
#include "tda/heap.h"
#include "tda/lista.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*******************************************************************************
 * Pokemon
 ******************************************************************************/
struct pokemon
{
    char nombre[MAX_NOMBRE];
    char tipo_1;
    char tipo_2;
    int ataque;
    int defensa;
    int velocidad;
    int adicional;
};

/* Maximo nivel que aumentan las estadisticas del pokemon */
const int POKEMON_MAX_ADICIONAL = 63;

/**
 * Devuelve un puntero a un pokemon en el heap con sus valores inicializados en
 * 0 o NULL. Si falla devuelve NULL.
 */
pokemon_t* pokemon_crear()
{
    return calloc(1, sizeof(pokemon_t));
}

/**
 * Libera el espacio reservado en heap para el pokemon. Si pokemon es NULL no
 * hace nada.
 */
void pokemon_liberar(pokemon_t* pokemon)
{
    free(pokemon);
}

/**
 * Devuelve true si el pokemon puede aumentar sus estadisticas de combate en 1.
 */
bool pokemon_puede_subir_estadisticas(pokemon_t* pokemon)
{
    return pokemon && pokemon->adicional < POKEMON_MAX_ADICIONAL;
}

/**
 * Aumenta en 1 las estadísticas del pokemon.
 */
int pokemon_subir_estadisticas(pokemon_t* pokemon)
{
    if (!pokemon || !pokemon_puede_subir_estadisticas(pokemon))
    {
        return ERROR;
    }
    (pokemon->adicional)++;

    return SIN_ERROR;
}

/**
 * Definido en juego.h
 */
int pokemon_ataque(pokemon_t* pokemon)
{
    if (!pokemon)
    {
        return 0;
    }
    
    return pokemon->ataque + pokemon->adicional;
}

/**
 * Definido en juego.h
 */
int pokemon_defensa(pokemon_t* pokemon)
{
    if (!pokemon)
    {
        return 0;
    }
    
    return pokemon->defensa + pokemon->adicional;
}

/**
 * Definido en juego.h
 */
int pokemon_velocidad(pokemon_t* pokemon)
{
    if (!pokemon)
    {
        return 0;
    }
    
    return pokemon->velocidad + pokemon->adicional;
}

/**
 * Definido en juego.h
 */
char pokemon_tipo_principal(pokemon_t* pokemon)
{
    if (!pokemon)
    {
        return (char) 0;
    }

    return pokemon->tipo_1;
}

/**
 * Definido en juego.h
 */
char pokemon_tipo_secundario(pokemon_t* pokemon)
{
    if (!pokemon)
    {
        return (char) 0;
    }

    return pokemon->tipo_2;
}

/**
 * Definido en juego.h
 */
void pokemon_nombre(pokemon_t* pokemon, char nombre[MAX_NOMBRE])
{
    if (!pokemon)
    {
        memset(nombre, 0, sizeof(char) * MAX_NOMBRE);
    }
    
    strcpy(nombre, pokemon->nombre);
}

/*******************************************************************************
 * Entrenador
 ******************************************************************************/
struct entrenador
{
    char nombre[MAX_NOMBRE];
    lista_t* pkm_party; // pila de pokemon que lo acompanan
    lista_t* pkm_obtenidos; // lista de todos sus pokemon
};

const int ENTRENADOR_TOPE_PARTY = 6;

/**
 * Devuelve un puntero a un entrenador creado en el heap, sin nombre ni pokemon.
 */
entrenador_t* entrenador_crear()
{
    entrenador_t* entrenador = calloc(1, sizeof(entrenador_t));
    lista_t* pkm_party = lista_crear();
    lista_t* pkm_obtenidos = lista_crear();

    if (!entrenador || !pkm_party || !pkm_obtenidos)
    {
        lista_destruir(pkm_party);
        lista_destruir(pkm_obtenidos);
        free(entrenador);
        return NULL;
    }

    entrenador->pkm_party = pkm_party;
    entrenador->pkm_obtenidos = pkm_obtenidos;

    return entrenador;
}

/**
 * Devuelve true si el entrenador tiene espacio en el party para un pokemon mas.
 */
bool entrenador_party_con_espacio(entrenador_t* entrenador)
{
    return entrenador && lista_elementos(entrenador->pkm_party) < ENTRENADOR_TOPE_PARTY;
}

/**
 * Devuelve 0 si se puede agregar el pokemon al party del entrenador.
 */
int entrenador_agregar_pokemon_a_party(entrenador_t* entrenador, pokemon_t* pokemon)
{
    if (!entrenador || !pokemon || !entrenador_party_con_espacio(entrenador))
    {
        return ERROR;
    }

    return lista_apilar(entrenador->pkm_party, pokemon);
}

/**
 * Devuelve 0 si se puede agregar el pokemon a la lista de pokemon obtenidos del
 * entrenador.
 */
int entrenador_agregar_pokemon_a_obtenidos(entrenador_t* entrenador, pokemon_t* pokemon)
{
    if (!entrenador || !pokemon)
    {
        return ERROR;
    }

    return lista_insertar(entrenador->pkm_obtenidos, pokemon);
}

/**
 * Devuelve 0 si se puede agregar el pokemon a la lista de pokemon obtenidos y
 * al party si hay espacio.
 */
int entrenador_agregar_pokemon(entrenador_t* entrenador, pokemon_t* pokemon)
{
    if (!entrenador || !pokemon)
    {
        return ERROR;
    }

    if (entrenador_agregar_pokemon_a_obtenidos(entrenador, pokemon) == ERROR)
    {
        return ERROR;
    }

    if (entrenador_party_con_espacio(entrenador)
        && entrenador_agregar_pokemon_a_party(entrenador, pokemon) == ERROR)
    {
        lista_borrar(entrenador->pkm_obtenidos);
        return ERROR;
    }

    return SIN_ERROR;
}

/**
 * Devuelve la cantidad de pokemon que tiene el entrenador en su party.
 */
size_t entrenador_cantidad_party(entrenador_t* entrenador)
{
    if (!entrenador)
    {
        return 0;
    }

    return lista_elementos(entrenador->pkm_party);
}

/**
 * Devuelve la cantidad de pokemon que tiene el entrenador.
 */
size_t entrenador_cantidad_obtenidos(entrenador_t* entrenador)
{
    if (!entrenador)
    {
        return 0;
    }

    return lista_elementos(entrenador->pkm_obtenidos);
}

/**
 * Libera la memoria reservada para el entrenador, incluyendo sus pokemon.
 */
void entrenador_liberar(entrenador_t* entrenador)
{
    if (!entrenador)
    {
        return;
    }

    pokemon_t* pokemon; // auxiliar

    while (entrenador_cantidad_obtenidos(entrenador) > 0)
    {
        pokemon = lista_primero(entrenador->pkm_obtenidos);
        lista_borrar_de_posicion(entrenador->pkm_obtenidos, 0);
        pokemon_liberar(pokemon);
    }

    lista_destruir(entrenador->pkm_party);
    lista_destruir(entrenador->pkm_obtenidos);
    free(entrenador);
}

/*******************************************************************************
 * Gimnasio
 ******************************************************************************/
struct gimnasio
{
    char nombre[MAX_NOMBRE];
    int dificultad;
    size_t id_funcion;
    lista_t* entrenadores; // pila de entrenadores
};

/**
 * Devuelve un puntero a un gimnasio creado en el heap o NULL.
 */
gimnasio_t* gimnasio_crear()
{
    gimnasio_t* gimnasio = calloc(1, sizeof(gimnasio_t));
    lista_t* entrenadores = lista_crear();

    if (!gimnasio || !entrenadores)
    {
        lista_destruir(entrenadores);
        free(gimnasio);
        return NULL;
    }

    gimnasio->entrenadores = entrenadores;

    return gimnasio;
}

/**
 * Devuelve 0 si se agrega correctamente un entrenador al gimnasio.
 */
int gimnasio_agregar_entrenador(gimnasio_t* gimnasio, entrenador_t* entrenador)
{
    if (!gimnasio || !entrenador)
    {
        return ERROR;
    }

    return lista_apilar(gimnasio->entrenadores, entrenador);
}

/**
 * Devuelve la cantidad de entrenadores que hay en el gimnasio.
 */
size_t gimnasio_entrenadores(gimnasio_t* gimnasio)
{
    if (!gimnasio) 
    {
        return 0;
    }

    return lista_elementos(gimnasio->entrenadores);
}

/**
 * Libera la memoria dedicada al gimnasio y sus entrenadores.
 */
void gimnasio_liberar(gimnasio_t* gimnasio)
{
    if (!gimnasio)
    {
        return;
    }

    entrenador_t* entrenador; // auxiliar
    while (gimnasio_entrenadores(gimnasio) > 0)
    {
        entrenador = lista_tope(gimnasio->entrenadores);
        lista_desapilar(gimnasio->entrenadores);
        entrenador_liberar(entrenador);
    }

    lista_destruir(gimnasio->entrenadores);
    free(gimnasio);
}

/*******************************************************************************
 * Juego
 ******************************************************************************/
struct juego
{
    entrenador_t* jugador;
    heap_t* gimnasios;
};

/**
 * Devuelve 0 si la dificultad del gimnasio 1 (gym1) y del gimnasio 2 (gym2) es
 * igual.
 * Devuelve < 0  si la dificultad del gimnasio 1 es menor que la del gimnasio 2
 * Devuelve > 0 en caso contrario.
 */
int gimnasio_comparador(void* gimnasio_1, void* gimnasio_2)
{
    int dificultad_1 = gimnasio_1 ? ((gimnasio_t*)gimnasio_1)->dificultad : 0 ,
        dificultad_2 = gimnasio_2 ? ((gimnasio_t*)gimnasio_2)->dificultad : 0 ;

    return dificultad_2 - dificultad_1;
}

/**
 * Destructor para el heap de gimnasios.
 */
void gimnasio_destruir(void* gimnasio)
{
    gimnasio_liberar((gimnasio_t*) gimnasio);
}

/**
 * Devuelve un puntero a un juego creado en el heap o NULL si falló.
 */
juego_t* juego_crear()
{
    juego_t* juego = calloc(1, sizeof(juego_t));
    entrenador_t* jugador = entrenador_crear();
    heap_t* gimnasios = heap_crear(gimnasio_comparador, gimnasio_destruir);

    if (!juego || !jugador || !gimnasios)
    {
        heap_destruir(gimnasios);
        entrenador_liberar(jugador);
        free(juego);
        return NULL;
    }

    juego->jugador = jugador;
    juego->gimnasios = gimnasios;

    return juego;
}

/**
 * Devuelve 0 si se agrega exitosamente un gimnasio al juego.
 */
int juego_agregar_gimnasio(juego_t* juego, gimnasio_t* gimnasio)
{
    if (!juego || !gimnasio)
    {
        return ERROR;
    }

    return heap_insertar(juego->gimnasios, gimnasio);
}

/**
 * Devuelve la cantidad de gimnasios restantes en el juego.
 */
size_t juego_gimnasios(juego_t* juego)
{
    if (!juego)
    {
        return 0;
    }

    return heap_cantidad(juego->gimnasios);
}

/**
 * Libera la memoria dedicada a la instancia de juego y a todas sus estructuras.
 */
void juego_liberar(juego_t* juego)
{
    if (!juego)
    {
        return;
    }

    if (juego->jugador)
    {
        entrenador_liberar(juego->jugador);
    }

    while (juego_gimnasios(juego) > 0)
    {
        heap_extraer_raiz(juego->gimnasios);
    }

    heap_destruir(juego->gimnasios);
    free(juego);
}

/*******************************************************************************
 *
 ******************************************************************************/

/**
 * Devuelve 0 si se lee correctamente un pokemon desde un archivo y se carga al
 * entrenador.
 */
int cargar_pokemon(FILE* archivo, entrenador_t* entrenador)
{
    pokemon_t* pokemon = pokemon_crear();
    if (!pokemon)
    {
        return ERROR;
    }
    
    int leidos = fscanf(archivo, POKEMON_FORMATO_LECTURA
            , pokemon->nombre
            , &(pokemon->tipo_1)
            , &(pokemon->tipo_2)
            , &(pokemon->ataque)
            , &(pokemon->defensa)
            , &(pokemon->velocidad)
            );
    if (leidos != POKEMON_ATTR_LEIDOS
        || entrenador_agregar_pokemon(entrenador, pokemon) == ERROR)
    {
        pokemon_liberar(pokemon);
        return ERROR;
    }

    return SIN_ERROR;
}

/**
 * Devuelve 0 si se lee correctamente el entenador, sus pokemon y se carga al
 * gimnasio.
 */
int cargar_entrenador(FILE* archivo, gimnasio_t* gimnasio)
{
    entrenador_t *entrenador = entrenador_crear();
    if (!entrenador)
    {
        return ERROR;
    }
    
    int leidos = fscanf(archivo, ENTRENADOR_FORMATO_LECTURA, entrenador->nombre);

    int cargados = 0;
    while (leidos == ENTRENADOR_ATTR_LEIDOS && fgetc(archivo) == POKEMON)
    {
        cargados += cargar_pokemon(archivo, entrenador) == SIN_ERROR ? 1 : 0;
    }

    if (cargados == 0
        || gimnasio_agregar_entrenador(gimnasio, entrenador) == ERROR)
    {
        entrenador_liberar(entrenador);
        return ERROR;
    }
   
    return SIN_ERROR;
}

/**
 * Devuelve 0 si se lee correctamente un gimnasio, junto a sus entrenadores y
 * pokemon, y se carga exitosamente al juego.
 */
int cargar_gimnasio(FILE* archivo, juego_t* juego)
{
    gimnasio_t* gimnasio = gimnasio_crear();
    if (!gimnasio)
    {
        return ERROR;
    }
    
    int leidos = fscanf(archivo, GIMNASIO_FORMATO_LECTURA
            , gimnasio->nombre
            , &(gimnasio->dificultad)
            , &(gimnasio->id_funcion)
            );

    int cargados = 0;
    if (leidos == GIMNASIO_ATTR_LEIDOS && fgetc(archivo) == LIDER)
    {
        cargados += cargar_entrenador(archivo, gimnasio) == SIN_ERROR ? 1 : 0;
    }

    if (cargados == 0
        || juego_agregar_gimnasio(juego, gimnasio) == ERROR)
    {
        gimnasio_liberar(gimnasio);
        return ERROR;
    }

    while (fgetc(archivo) == ENTRENADOR)
    {
        cargar_entrenador(archivo, gimnasio);
    }
    
    return SIN_ERROR;
}

/**
 * Definido en juego.h
 */
int cargar_gimnasios(const char* ruta_archivo, juego_t* juego)
{
    if (!ruta_archivo || !juego)
    {
        return ERROR;
    }

    FILE* archivo = fopen(ruta_archivo, LECTURA);
    if (!archivo)
    {
        return ERROR;
    }

    int cargados = 0;
    
    while (fgetc(archivo) == GIMNASIO)
    {
        cargados += cargar_gimnasio(archivo, juego) == SIN_ERROR ? 1 : 0;
    }
    
    fclose(archivo);
    return cargados > 0 ? SIN_ERROR : ERROR;
}

/**
 * Definido en juego.h
 */
int cargar_jugador(const char* ruta_archivo, juego_t* juego)
{
    if (!ruta_archivo || !juego)
    {
        return ERROR;
    }

    FILE* archivo = fopen(ruta_archivo, LECTURA);
    if (!archivo)
    {
        return ERROR;
    }

    int cargados = 0;
    int leido = fscanf(archivo, "E" ENTRENADOR_FORMATO_LECTURA, juego->jugador->nombre);
    while (leido == ENTRENADOR_ATTR_LEIDOS && fgetc(archivo) == POKEMON)
    {
        cargados += cargar_pokemon(archivo, juego->jugador) == SIN_ERROR ? 1 : 0;
    }

    fclose(archivo);
    return cargados > 0 ? SIN_ERROR : ERROR;
}
