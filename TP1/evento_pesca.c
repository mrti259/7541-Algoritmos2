#include "evento_pesca.h"
#include <stdlib.h>
#include <string.h>

#define LECTURA "r"
#define ESCRITURA "w"
#define FORMATO_LECTURA_ARRECIFE "%99[^;];%i;%i;%49[^\n]\n"
#define FORMATO_ESCRITURA_ACUARIO "%s;%i;%i;%s\n"
#define CANT_ATRIBUTOS 4
#define ERROR_APERTURA -1
#define ERROR_MODIFICANDO -1
#define ERROR_TRASLADANDO -1
#define ERROR_GUARDANDO -1
#define SIN_ERROR 0
#define SIN_POKEMON 0

/*
 * Modifica el tamaño del vector pokemon. Devuelve SIN_ERROR si se modificó
 * correctamente, o ERROR_MODIFICANDO.
 *
 * Argumentos:
 *      pokemon - puntero al vector de pokemon.
 *      cantidad_pokemon - cantidad de pokemon_t a reservar.
 */
int modificar_pokemon(pokemon_t** pokemon, int cantidad_pokemon) {
    pokemon_t* mis_pokemon = realloc(*pokemon, (size_t) cantidad_pokemon * sizeof(pokemon_t));
    if (mis_pokemon || cantidad_pokemon == SIN_POKEMON) {
        *pokemon = mis_pokemon;
        return SIN_ERROR;
    }
    return ERROR_MODIFICANDO;
}

/*
 * Agrega a mis_pokemon un pokemon. Devuelve SIN_ERROR si se pudo agregar
 * sin inconvenientes, o ERROR_MODIFICANDO.
 *
 * Argumentos:
 *      mis_pokemon - puntero a vector de pokemon.
 *      cantidad_pokemon - cantidad de pokemon en el vector.
 *      pokemon - pokemon que se desea agregar.
 */
int agregar_pokemon(pokemon_t** mis_pokemon, int* cantidad_pokemon, pokemon_t pokemon) {
    bool funciono = modificar_pokemon(mis_pokemon, *cantidad_pokemon + 1) != ERROR_MODIFICANDO;
    if (funciono) {
        *(*mis_pokemon + *cantidad_pokemon) = pokemon;
        (*cantidad_pokemon)++;
        return SIN_ERROR;
    }
    return ERROR_MODIFICANDO;
}

/*
 * Agrega un pokemon al arrecife. Devuelve SIN_ERROR o ERROR_MODIFICANDO.
 *
 * Argumentos:
 *      arrecife - puntero al arrecife.
 *      pokemon - pokemon a agregar.
 */
int agregar_al_arrecife(arrecife_t* arrecife, pokemon_t pokemon) {
    return agregar_pokemon(&(arrecife->pokemon), &(arrecife->cantidad_pokemon), pokemon);
}

/*
 * Agrega un pokemon al acuario. Devuelve SIN_ERROR o ERROR_MODIFICANDO.
 *
 * Argumentos:
 *      acuario - puntero al acuario.
 *      pokemon - pokemon a agregar.
 */
int agregar_al_acuario(acuario_t* acuario, pokemon_t pokemon) {
    return agregar_pokemon(&(acuario->pokemon), &(acuario->cantidad_pokemon), pokemon);
}

/*
 * Elimina físicamente un pokemon reemplazandolo por el último del vector. Devuelvo
 * SIN_ERROR si se corrigió el tamaño, o un error.
 *
 * Argumentos:
 *      mis_pokemon - puntero al vector de pokemon.
 *      posicion_pokemon - posicion del pokemon a eliminar.
 *      cantidad_pokemon - es la direccion de memoria que guarda la cantidad de pokemon.
 */
int eliminar_pokemon(pokemon_t** mis_pokemon, int posicion_pokemon, int* cantidad_pokemon) {
    pokemon_t ultimo_pokemon = (*mis_pokemon)[*cantidad_pokemon - 1];
    (*mis_pokemon)[posicion_pokemon] = ultimo_pokemon;
    (*cantidad_pokemon)--;
    return modificar_pokemon(mis_pokemon, *cantidad_pokemon);
}

/*
 * Elimina un pokemon del arrecife. Devuelve SIN_ERROR ó ERROR_MODIFICANDO.
 *
 * Argumentos:
 *      arrecife - arrecife cuenta con pokemon en la posicion posicion_pokemon.
 *      posicion_pokemon - posicion del pokemon a eliminar.
 */
int eliminar_del_arrecife(arrecife_t* arrecife, int posicion_pokemon) {
    return eliminar_pokemon(&(arrecife->pokemon), posicion_pokemon, &(arrecife->cantidad_pokemon));
}

/*
 * Lee los registros de pokemon de un archivo y los carga en un vector.
 *
 * Argumentos:
 *      archivo - archivo de texto con los registros de pokemon y
 *                permisos de lectura. Debe cumplir con el formato:
 *                'especie;velocidad;peso;color'
 *      arrecife - puntero a arrecife.
 */
void leer_registros_arrecife(FILE* archivo, arrecife_t* arrecife) {
    pokemon_t pokemon;
    arrecife->pokemon = NULL;
    arrecife->cantidad_pokemon = SIN_POKEMON;
    int agregado = SIN_ERROR;
    int leidos = fscanf(archivo,
        FORMATO_LECTURA_ARRECIFE,
        pokemon.especie,
        &(pokemon.velocidad),
        &(pokemon.peso),
        pokemon.color
        );
    while (leidos == CANT_ATRIBUTOS && agregado == SIN_ERROR) {
        agregado = agregar_al_arrecife(arrecife, pokemon);
        leidos = fscanf(archivo,
            FORMATO_LECTURA_ARRECIFE,
            pokemon.especie,
            &(pokemon.velocidad),
            &(pokemon.peso),
            pokemon.color
            );
    }
}

/*
 * Escribe en un archivo de texto los registros de pokemon. Se guardará
 * con el formato 'especie;velocidad;peso;color'.
 *
 * Argumentos:
 *      pokemon - vector de pokemon_t.
 *      cantidad_pokemon - cantidad de pokemon en el vector.
 *      archivo - archivo de texto con permisos de escritura.
 */
void escribir_pokemon(pokemon_t* pokemon, int cantidad_pokemon, FILE* archivo) {
    pokemon_t pokemon_actual;
    for (int i = 0; i < cantidad_pokemon; i++) {
        pokemon_actual = *(pokemon + i);
        fprintf(
            archivo,
            FORMATO_ESCRITURA_ACUARIO,
            pokemon_actual.especie,
            pokemon_actual.velocidad,
            pokemon_actual.peso,
            pokemon_actual.color
            );
    }
}

/*
 * Busca los pokemon en arrecife con determinada caracteristica y carga
 * los punteros a mis_pokemon. Devuelve la cantidad encontrada.
 *
 * Argumentos:
 *      arrecife - puntero a arrecife.
 *      selecciona_pokemon - devuelve true si se pasa un pokemon con la
 *                            caracteristica deseada.
 *      cant_seleccion - cantidad máxima de pokemon a buscar.
 *      v_pokemon - vector para las posiciones de los pokemon encontrados.
 */
int buscar_pokemon(arrecife_t* arrecife, bool (*selecciona_pokemon)(pokemon_t*), int cant_seleccion, int* v_pokemon) {
    int i = 0, encontrados = SIN_POKEMON;
    while ((encontrados < cant_seleccion) && (i < arrecife->cantidad_pokemon)) {
        if (selecciona_pokemon(arrecife->pokemon + i)) {
            v_pokemon[encontrados] = i;
            encontrados++;
        }
        i++;
    }
    return encontrados;
}

/*
 * Mueve la cantidad seleccionada de pokemon de arrecife a acuario,
 * desde el último seleccionado, al primero. Devuelve la cantidad de
 * pokemon movidos.
 *
 * Argumentos:
 *      arrecife - puntero a arrecife.
 *      acuario - puntero a acuario.
 *      cant_seleccion - cantidad a mover.
 *      v_pokemon - vector con las posiciones de los pokemon a mover.
 */
int mover_pokemon(arrecife_t* arrecife, acuario_t* acuario, int cant_seleccion, int* v_pokemon) {
    int i = cant_seleccion - 1, movidos = SIN_POKEMON;
    bool funciono = true;
    while (i >= SIN_POKEMON && funciono) {
        funciono = agregar_al_acuario(acuario, arrecife->pokemon[v_pokemon[i]]) != ERROR_MODIFICANDO;
        if (funciono) {
            funciono = eliminar_del_arrecife(arrecife, v_pokemon[i]) != ERROR_MODIFICANDO;
            movidos++;
        }
        i--;
    }
    return movidos;
}

/*
 * Libera el espacio de memoria dedicado a pokemon.
 */
void liberar_pokemon(pokemon_t* pokemon) {
    if (!pokemon) return;
    free(pokemon);
}

/*
 * Definidos en evento_pesca.h
 */

arrecife_t* crear_arrecife(const char* ruta_archivo) {
    arrecife_t* arrecife = NULL;
    FILE *info_arrecife = fopen(ruta_archivo, LECTURA);
    if (!info_arrecife) {
        printf("No se pudo abrir %s\n", ruta_archivo);
    } else {
        arrecife = (arrecife_t*) malloc(sizeof(arrecife_t));
        if (arrecife) {
            leer_registros_arrecife(info_arrecife, arrecife);
        }
        if (arrecife->cantidad_pokemon == SIN_POKEMON) {
            liberar_arrecife(arrecife);
            arrecife = NULL;
        }
        fclose(info_arrecife);
    }
    return arrecife;
}

acuario_t* crear_acuario() {
    acuario_t* nuevo_acuario = malloc(sizeof(acuario_t));
    if (nuevo_acuario) {
        nuevo_acuario->pokemon = NULL;
        nuevo_acuario->cantidad_pokemon = SIN_POKEMON;
    }
    return nuevo_acuario;
}

int trasladar_pokemon(arrecife_t* arrecife, acuario_t* acuario, bool (*seleccionar_pokemon) (pokemon_t*), int cant_seleccion) {
    int movidos = SIN_POKEMON;
    int* v_pokemon = calloc((size_t) cant_seleccion, sizeof(int));
    if (v_pokemon) {
        int encontrados = buscar_pokemon(arrecife, seleccionar_pokemon, cant_seleccion, v_pokemon);
        if (encontrados == cant_seleccion) {
            movidos = mover_pokemon(arrecife, acuario, cant_seleccion, v_pokemon);
         }
        free(v_pokemon);
    }
    return movidos == cant_seleccion ? SIN_ERROR : ERROR_TRASLADANDO;
}

void censar_arrecife(arrecife_t* arrecife, void (*mostrar_pokemon)(pokemon_t*)) {
    for (int i = 0; i < arrecife->cantidad_pokemon; i++) {
        mostrar_pokemon(arrecife->pokemon + i);
    }
}

int guardar_datos_acuario(acuario_t* acuario, const char* nombre_archivo) {
    FILE *info_acuario = fopen(nombre_archivo, ESCRITURA);
    if (info_acuario) {
        escribir_pokemon(acuario->pokemon, acuario->cantidad_pokemon, info_acuario);
        fclose(info_acuario);
        return SIN_ERROR;
    }
    printf("No se pudo abrir %s\n", nombre_archivo);
    return ERROR_APERTURA;
}

void liberar_acuario(acuario_t* acuario) {
    if (!acuario) return;
    liberar_pokemon(acuario->pokemon);
    free(acuario);
}

void liberar_arrecife(arrecife_t* arrecife) {
    if (!arrecife) return;
    liberar_pokemon(arrecife->pokemon);
    free(arrecife);
}
