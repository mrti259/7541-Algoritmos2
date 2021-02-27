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
    bool en_party;
};

/* Maximo nivel que aumentan las estadisticas del pokemon */
const int POKEMON_MAX_ADICIONAL = 63;

/**
 * Reserva la memoria para un Pokémon y devuelve su puntero. Si falla devuelve NULL.
 */
pokemon_t* pokemon_crear()
{
    return calloc(1, sizeof(pokemon_t));
}

/**
 * Libera el espacio reservado en heap para el Pokémon. Si Pokémon es NULL no
 * hace nada.
 */
void pokemon_liberar(pokemon_t* pokemon)
{
    free(pokemon);
}

/**
 * Devuelve true si el Pokémon puede aumentar sus estadisticas de combate en 1.
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
    return pokemon ? pokemon->ataque + pokemon->adicional : ERROR;
}

/**
 * Definido en juego.h
 */
int pokemon_defensa(pokemon_t* pokemon)
{
    return pokemon ? pokemon->defensa + pokemon->adicional : ERROR;
}

/**
 * Definido en juego.h
 */
int pokemon_velocidad(pokemon_t* pokemon)
{
    return pokemon ? pokemon->velocidad + pokemon->adicional : ERROR;
}

/**
 * Definido en juego.h
 */
char pokemon_tipo_principal(pokemon_t* pokemon)
{
    return pokemon ? pokemon->tipo_1 : (char) 0;
}

/**
 * Definido en juego.h
 */
char pokemon_tipo_secundario(pokemon_t* pokemon)
{
    return pokemon ? pokemon->tipo_2 : (char) 0;
}

/**
 * Definido en juego.h
 */
void pokemon_nombre(pokemon_t* pokemon, char nombre[MAX_NOMBRE])
{
    strcpy(nombre, pokemon ? pokemon->nombre : "");
}

/*******************************************************************************
 * Entrenador
 ******************************************************************************/

struct entrenador
{
    char nombre[MAX_NOMBRE];
    lista_t* pkm_party; // lista de pokémon que lo acompanan
    lista_t* pkm_obtenidos; // lista de todos sus pokemon
    size_t pkm_actual; // posición del pokémon que puede combatir
};

const int ENTRENADOR_TOPE_PARTY = 6;

/**
 * Reserva memoria para un entrenador y devuelve su puntero.  No tiene ni
 * nombre ni Pokémon pero se crean las listas de party y Pokémon
 * obtenidos.
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
 * Definido en juego.h
 */
size_t entrenador_party(entrenador_t* entrenador)
{
    return entrenador ? lista_elementos(entrenador->pkm_party) : 0;
}

/**
 * Devuelve la cantidad de Pokémon que tiene el entrenador.
 */
size_t entrenador_pokemon_obtenidos(entrenador_t* entrenador)
{
    return entrenador ? lista_elementos(entrenador->pkm_obtenidos) : 0;
}

/**
 * Definido en juego.h
 */
size_t entrenador_pokemon_restante(entrenador_t* entrenador)
{
    return entrenador ?
        entrenador_party(entrenador) - entrenador->pkm_actual : 0;
}

/**
 * Devuelve el Pokémon con el que combatirá el entrenador.
 */
pokemon_t* entrenador_pokemon_actual(entrenador_t* entrenador)
{
    return entrenador ?
        lista_elemento_en_posicion(entrenador->pkm_party, entrenador->pkm_actual) : NULL;
}

/**
 * Devuelve true si el entrenador tiene espacio en el party para un Pokémon
 * mas.
 */
bool entrenador_party_con_espacio(entrenador_t* entrenador)
{
    return entrenador && entrenador_party(entrenador) < ENTRENADOR_TOPE_PARTY;
}

/**
 * Devuelve 0 si se agrega el Pokémon al party del entrenador.
 */
int entrenador_agregar_a_party(entrenador_t* entrenador, pokemon_t* pokemon)
{
    if (!entrenador || !pokemon || !entrenador_party_con_espacio(entrenador)
            || (lista_insertar(entrenador->pkm_party, pokemon) == ERROR))
    {
        return ERROR;
    }

    pokemon->en_party = true;

    return SIN_ERROR;
}

/**
 * Devuelve 0 si se puede quitar al Pokémon en la posicion dada del party.
 */
int entrenador_quitar_del_party(entrenador_t* entrenador, size_t posicion)
{
    pokemon_t* pokemon;
    if (!entrenador
            || !(pokemon = lista_elemento_en_posicion(entrenador->pkm_party, posicion))
            || (lista_borrar_de_posicion(entrenador->pkm_party, posicion) == ERROR))
    {
        return ERROR;
    }

    if ((lista_borrar_de_posicion(entrenador->pkm_obtenidos, posicion) == ERROR)
            || (lista_insertar(entrenador->pkm_obtenidos, pokemon) == ERROR))
    {
        lista_insertar_en_posicion(entrenador->pkm_party, pokemon, posicion);
        return ERROR;
    }

    pokemon->en_party = false;

    return SIN_ERROR;
}

/**
 * Devuelve 0 si se puede agregar el pokemon a la lista de pokemon obtenidos del
 * entrenador.
 */
int entrenador_agregar_a_obtenidos(entrenador_t* entrenador, pokemon_t* pokemon)
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

    if (entrenador_party_con_espacio(entrenador))
    {
        // Posicion del party donde se va a intentar insertar el Pokémon
        size_t pos = entrenador_party(entrenador);

        if (entrenador_agregar_a_party(entrenador, pokemon) == ERROR)
        {
            return ERROR;
        }

        if (lista_insertar_en_posicion(entrenador->pkm_obtenidos, pokemon, pos) == ERROR)
        {
            entrenador_quitar_del_party(entrenador, pos);
            return ERROR;
        }

        return SIN_ERROR;
    }

    return entrenador_agregar_a_obtenidos(entrenador, pokemon);
}

/**
 * Recorre una lista de Pokémon y las muestra. Los parámetros no pueden ser
 * NULL.
 */
void entrenador_recorrer_pokemon(lista_t* pkm, void (*mostrar)(pokemon_t*))
{
    lista_iterador_t* iterador = lista_iterador_crear(pkm);
    while (lista_iterador_tiene_siguiente(iterador))
    {
        mostrar(lista_iterador_elemento_actual(iterador));
        lista_iterador_avanzar(iterador);
    }
    lista_iterador_destruir(iterador);
}

/**
 * Definido en juego.h
 */
void entrenador_mostrar_party(entrenador_t* entrenador, void (*mostrar)(pokemon_t*))
{
    if (!entrenador || !entrenador->pkm_party || !mostrar)
    {
        return;
    }

    entrenador_recorrer_pokemon(entrenador->pkm_party, mostrar);
}

/**
 * Definido en juego.h
 */
void entrenador_mostrar_pokemon(entrenador_t* entrenador, void (*mostrar)(pokemon_t*))
{
    if (!entrenador || !mostrar || !entrenador->pkm_obtenidos)
    {
        return;
    }

    entrenador_recorrer_pokemon(entrenador->pkm_obtenidos, mostrar);
}

/**
 * Definido en juego.h
 */
void entrenador_nombre(entrenador_t* entrenador, char nombre[MAX_NOMBRE])
{
    strcpy(nombre, entrenador ? entrenador->nombre : "");
}

/**
 * Libera la memoria reservada para el entrenador y los Pokémon que le
 * pertenezcan.
 */
void entrenador_liberar(entrenador_t* entrenador)
{
    if (!entrenador)
    {
        return;
    }

    lista_iterador_t* iterador = lista_iterador_crear(entrenador->pkm_obtenidos);
    while (lista_iterador_tiene_siguiente(iterador))
    {
        pokemon_liberar(lista_iterador_elemento_actual(iterador));
        lista_iterador_avanzar(iterador);
    }

    lista_iterador_destruir(iterador);
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
    int id_funcion;
    lista_t* entrenadores; // pila de entrenadores
    bool derrotado;
};

/**
 * Reserva la memoria para un gimnasio y su pila de entenadores vacía.
 * Devuelve su puntero. Si falla devuelve NULL.
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
 * Devuelve 0 si se borra correctamente un entrenador.
 */
int gimnasio_borrar_entrenador(gimnasio_t* gimnasio)
{
    if (!gimnasio)
    {
        return ERROR;
    }

    entrenador_liberar(lista_tope(gimnasio->entrenadores));

    return lista_desapilar(gimnasio->entrenadores);
}

/**
 * Definido en juego.h
 */
size_t gimnasio_entrenadores(gimnasio_t* gimnasio)
{
    return gimnasio ? lista_elementos(gimnasio->entrenadores) : 0;
}

/**
 * Definido en juego.h
 */
bool gimnasio_derrotado(gimnasio_t* gimnasio)
{
    return gimnasio ? gimnasio->derrotado : false;
}

/**
 * Definido en juego.h
 */
void gimnasio_nombre(gimnasio_t* gimnasio, char nombre[MAX_NOMBRE])
{
    strcpy(nombre, gimnasio ? gimnasio->nombre : "");
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

    while (gimnasio_entrenadores(gimnasio) > 0)
    {
        entrenador_liberar(lista_tope(gimnasio->entrenadores));
        lista_desapilar(gimnasio->entrenadores);
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
 * Definido en juego.h
 */
juego_t* juego_crear()
{
    juego_t* juego = calloc(1, sizeof(juego_t));
    heap_t* gimnasios = heap_crear(gimnasio_comparador, gimnasio_destruir);

    if (!juego || !gimnasios)
    {
        heap_destruir(gimnasios);
        free(juego);
        return NULL;
    }

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
 * Borra un gimnasio. El heap se encarga de liberar la memoria.
 */
int juego_borrar_gimnasio(juego_t* juego)
{
    return juego ? heap_extraer_raiz(juego->gimnasios) : ERROR;
}

/**
 * Devuelve la cantidad de gimnasios restantes en el juego.
 */
size_t juego_gimnasios(juego_t* juego)
{
    return juego ? heap_cantidad(juego->gimnasios) : 0;
}

/**
 * Definido en juego.h
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

/**
 * Crea un Pokémon inicial para el entrenador que inicie su aventura o NULL si falla.
 */
pokemon_t* pokemon_inicial()
{
    pokemon_t* pokemon = pokemon_crear();
    if (pokemon)
    {
        strcpy(pokemon->nombre, "Pikachu");
        pokemon->ataque = 5;
        pokemon->defensa = 5;
        pokemon->velocidad = 5;
        pokemon->tipo_1 = pokemon->tipo_2 = 'E';
    }

    return pokemon;
}

/**
 * Definido en juego.h
 */
int juego_nuevo(juego_t* juego, char nombre[MAX_NOMBRE])
{
    entrenador_t* jugador;

    if (!juego || !strcmp(nombre, "") || !(jugador = entrenador_crear()))
    {
        return ERROR;
    }

    pokemon_t* pokemon = pokemon_inicial();

    if (entrenador_agregar_pokemon(jugador, pokemon) == ERROR)
    {
        pokemon_liberar(pokemon);
        entrenador_liberar(jugador);
        return ERROR;
    }

    strcpy(jugador->nombre, nombre);
    juego->jugador = jugador;

    return SIN_ERROR;
}

/**
 * Definido en juego.h
 */
gimnasio_t* gimnasio_actual(juego_t* juego)
{
    return juego ? heap_raiz(juego->gimnasios) : NULL;
}

/**
 * Definido en juego.h
 */
entrenador_t* rival_actual(juego_t* juego)
{
    gimnasio_t* gimnasio = gimnasio_actual(juego);

    return gimnasio ? lista_tope(gimnasio->entrenadores) : NULL;
}

/**
 * Definido en juego.h
 */
pokemon_t* pokemon_enemigo(juego_t* juego)
{
    return entrenador_pokemon_actual(rival_actual(juego));
}

/**
 * Definido en juego.h
 */
entrenador_t* personaje_principal(juego_t* juego)
{
    return juego ? juego->jugador : NULL;
}

/**
 * Definido en juego.h
 */
pokemon_t* pokemon_jugador(juego_t* juego)
{
    return entrenador_pokemon_actual(personaje_principal(juego));
}

/**
 * Devuelve true si el pokemon_1 ganó el combate.
 */
bool gana_pokemon_1(int resultado)
{
    return resultado > 0;
}

/**
 * Recibe la instancia de juego y puede recibir una funcion para mostrar.
 * La id_funcion se pasa al controlador de funciones de batalla para determinar
 * el resultado del combate.
 * Si el Pokémon del jugador gana el combate y puede subir sus estadísticas, estas
 * se aumentan.
 */
int combate_pokemon(juego_t* juego,
                    void (*mostrar)(juego_t*))
{
    pokemon_t *pokemon_1 = pokemon_jugador(juego),
              *pokemon_2 = pokemon_enemigo(juego);
    gimnasio_t *gimnasio = gimnasio_actual(juego);

    if (!pokemon_1 || !pokemon_2 || !gimnasio)
    {
        return 0;
    }

    if (mostrar) mostrar(juego);

    int resultado = funcion_batalla_controller(gimnasio->id_funcion, pokemon_1, pokemon_2);

    if (gana_pokemon_1(resultado) && pokemon_puede_subir_estadisticas(pokemon_1))
    {
        pokemon_subir_estadisticas(pokemon_1);
    }

    return resultado;
}

/**
 * Combate a los Pokémon de los entrenadores hasta que uno de ellos se quede sin Pokémon
 * para combatir.
 *
 * Devuelve:
 *  = 0 si no se pudo combatir.
 *  > 0 si gana el personaje_principal.
 *  < 0 si gana el rival_actual.
 */
int combate_entrenadores(juego_t* juego,
                        void (*mostrar)(juego_t*))
{
    entrenador_t *entrenador_1 = personaje_principal(juego),
                 *entrenador_2 = rival_actual(juego);

    if (!entrenador_1 || !entrenador_2)
    {
        return 0;
    }

    int resultado = combate_pokemon(juego, mostrar);

    if (!resultado)
    {
        // El combate terminó. Los Pokémon vencidos se recuperan.
        entrenador_1->pkm_actual = 0;
        entrenador_2->pkm_actual = 0;
        return 0;
    }

    if (gana_pokemon_1(resultado))
    {
        entrenador_2->pkm_actual++;
    }
    else
    {
        entrenador_1->pkm_actual++;
    }

    int ganador = combate_entrenadores(juego, mostrar);

    return ganador ? ganador : resultado;
}

/**
 * Definido en juego.h
 */
int retar_gimnasio(juego_t* juego, void (*mostrar)(juego_t*))
{
    if (gimnasio_derrotado(gimnasio_actual(juego)))
    {
        juego_borrar_gimnasio(juego);
    }

    gimnasio_t* gimnasio;

    if (!(gimnasio = gimnasio_actual(juego)))
    {
        return 0;
    }

    int resultado = combate_entrenadores(juego, mostrar);

    while (gana_pokemon_1(resultado) && gimnasio_entrenadores(gimnasio) > 1)
    {
        gimnasio_borrar_entrenador(gimnasio);
        resultado = combate_entrenadores(juego, mostrar);
    }

    if (gana_pokemon_1(resultado))
    {
        gimnasio->derrotado = true;
    }

    return resultado;
}

/**
 * Definido en juego.h
 */
int quitar_del_party(juego_t* juego, size_t posicion)
{
    if (!juego || !(posicion < ENTRENADOR_TOPE_PARTY))
    {
        return ERROR;
    }

    return entrenador_quitar_del_party(juego->jugador, posicion);
}

/**
 * Definido en juego.h
 */
int agregar_a_party(juego_t* juego, size_t posicion)
{
    pokemon_t* pokemon;

    if (!juego
            || !(pokemon = lista_elemento_en_posicion(
                    juego->jugador->pkm_obtenidos, posicion))
            || pokemon->en_party)
    {
        return ERROR;
    }

    return entrenador_agregar_a_party(juego->jugador, pokemon);
}

/**
 * Definido en juego.h
 */
int tomar_pokemon(juego_t* juego, size_t posicion)
{
    gimnasio_t* gimnasio = gimnasio_actual(juego);
    entrenador_t* lider = rival_actual(juego);
    pokemon_t* pokemon;

    if (!juego || !gimnasio || !gimnasio->derrotado || !lider)
    {
        return ERROR;
    }

    pokemon = lista_elemento_en_posicion(lider->pkm_obtenidos, posicion);
    lista_borrar_de_posicion(lider->pkm_obtenidos, posicion);

    if (entrenador_agregar_a_obtenidos(juego->jugador, pokemon) == ERROR)
    {
        return ERROR;
    }

    return juego_borrar_gimnasio(juego);
}

/*******************************************************************************
 * Manejo de archivos
 ******************************************************************************/

/**
 * Devuelve el primer caracter no blanco leído.
 */
char caracter_leido(FILE* stream)
{
    char caracter[] = " ";
    fscanf(stream, "%1s", caracter);
    return *caracter;
}

/**
 * Devuelve 0 si se lee correctamente un pokemon desde un archivo y se carga al
 * entrenador.
 */
int cargar_pokemon(FILE* archivo, entrenador_t* entrenador)
{
    pokemon_t* pokemon = pokemon_crear();

    int leidos = fscanf(archivo, POKEMON_FORMATO_LECTURA
            , pokemon->nombre
            , &(pokemon->tipo_1)
            , &(pokemon->tipo_2)
            , &(pokemon->ataque)
            , &(pokemon->defensa)
            , &(pokemon->velocidad)
            );

    if ((leidos != POKEMON_ATTR_LEIDOS)
            || (entrenador_agregar_pokemon(entrenador, pokemon) == ERROR))
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

    while (leidos == ENTRENADOR_ATTR_LEIDOS && caracter_leido(archivo) == POKEMON)
    {
        cargar_pokemon(archivo, entrenador);
    }

    if ((entrenador_pokemon_obtenidos(entrenador) == 0)
            || (gimnasio_agregar_entrenador(gimnasio, entrenador) == ERROR))
    {
        entrenador_liberar(entrenador);
        return ERROR;
    }

    // Me vuelvo para volver a leer después
    fseek(archivo, -(long)sizeof(char), SEEK_CUR);

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

    if (leidos == GIMNASIO_ATTR_LEIDOS && caracter_leido(archivo) == LIDER)
    {
        cargar_entrenador(archivo, gimnasio);
    }

    if (!(gimnasio_entrenadores(gimnasio))
            || (juego_agregar_gimnasio(juego, gimnasio) == ERROR))
    {
        gimnasio_liberar(gimnasio);
        return ERROR;
    }

    while (caracter_leido(archivo) == ENTRENADOR)
    {
        cargar_entrenador(archivo, gimnasio);
    }

    // Me vuelvo para volver a leer después
    fseek(archivo, -(long)sizeof(char), SEEK_CUR);

    return SIN_ERROR;
}

/**
 * Definido en juego.h
 */
int cargar_gimnasios(const char* ruta_archivo, juego_t* juego)
{
    FILE* archivo;

    if (!ruta_archivo || !juego
        || !(archivo = fopen(ruta_archivo, LECTURA))) // ~> no hay resource leak
    {
        return ERROR;
    }

    int cargo = 0;

    while (caracter_leido(archivo) == GIMNASIO)
    {
        if (cargar_gimnasio(archivo, juego) == SIN_ERROR)
        {
            cargo++;
        }
    }

    fclose(archivo);

    return cargo > 0 ? SIN_ERROR : ERROR;
}

/**
 * Definido en juego.h
 */
int cargar_jugador(const char* ruta_archivo, juego_t* juego)
{
    FILE* archivo;
    entrenador_t* jugador;

    if (!ruta_archivo || !juego
        || !(archivo = fopen(ruta_archivo, LECTURA))) // ~> No hay resource leak
    {
        return ERROR;
    }

    if (!(caracter_leido(archivo) == ENTRENADOR) || !(jugador = entrenador_crear()))
    {
        fclose(archivo);
        return ERROR;
    }

    int leidos = fscanf(archivo, ENTRENADOR_FORMATO_LECTURA, jugador->nombre);

    while (leidos == ENTRENADOR_ATTR_LEIDOS && caracter_leido(archivo) == POKEMON)
    {
        cargar_pokemon(archivo, jugador);
    }

    fclose(archivo);

    if (!entrenador_pokemon_obtenidos(jugador))
    {
        entrenador_liberar(jugador);
        return ERROR;
    }

    entrenador_liberar(juego->jugador);
    juego->jugador = jugador;

    return SIN_ERROR;
}

/**
 * Función para ser utilizada en lista_con_cada_elemento.
 * Guarda el Pokémon en el stream abierto. Devuelve false para dejar de iterar.
 */
bool guardar_pokemon(void* pkm, void* stream)
{
    if (!pkm || !stream)
    {
        return false;
    }

    pokemon_t* pokemon = pkm;
    FILE* archivo = stream;
    fprintf(archivo, POKEMON_FORMATO_ESCRITURA
            , pokemon->nombre
            , pokemon->tipo_1
            , pokemon->tipo_2
            , pokemon->ataque // pokemon_ataque(pokemon),
            , pokemon->defensa // pokemon_defensa(pokemon),
            , pokemon->velocidad // pokemon_velocidad(pokemon)
           );

    return true;
}

/**
 * Definido en juego.h
 */
int guardar_jugador(const char* ruta_archivo, juego_t* juego)
{
    FILE* archivo;

    if (!ruta_archivo || !juego || !juego->jugador
        || !(archivo = fopen(ruta_archivo, ESCRITURA))) // ~> No hay resource leak
    {
        return ERROR;
    }

    fprintf(archivo, ENTRENADOR_FORMATO_ESCRITURA, juego->jugador->nombre);

    size_t guardados = lista_con_cada_elemento(
            juego->jugador->pkm_obtenidos,
            guardar_pokemon,
            archivo
            );

    fclose(archivo);

    return guardados > 0 ? SIN_ERROR : ERROR;
}
