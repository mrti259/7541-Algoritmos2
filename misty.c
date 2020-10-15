#include "evento_pesca.h"
#include <string.h>

#define RUTA_ARRECIFE "arrecife.txt"
#define RUTA_ACUARIO "acuario.txt"
#define MAX_CELDA 16
#define ESPECIE "ESPECIE"
#define VELOCIDAD "VELOCIDAD"
#define PESO "PESO"
#define COLOR "COLOR"
#define CANT_ATRIBUTOS 4
#define MAGIKARP "Magikarp"
#define ROJO "rojo"
#define LENTO 30
#define GRANDE 80
#define RAPIDO 90
#define CHICO 10

/*
 * Devuelve true si el pokemon es de la especie solicitada.
 */
bool es_especie(pokemon_t* pokemon, char* especie) {
    return !strcmp(pokemon->especie, especie);
}

/*
 * Devuelve true si el pokmeon es del color solicitado.
 */
bool es_color(pokemon_t* pokemon, char* color) {
    return !strcmp(pokemon->color, color);
}

/*
 * Devuelve true si el pokemon es más veloz que el valor solicitado.
 */
bool supera_velocidad(pokemon_t* pokemon, int velocidad) {
    return pokemon->velocidad > velocidad;
}

/*
 * Devuelve true si el pokemon es más pesado que el valor solicitado.
 */
bool supera_peso(pokemon_t* pokemon, int peso) {
    return pokemon->peso > peso;
}

/* Funciones para seleccionar */

/*
 * Devuelve true si es un MAGIKARP.
 */
bool seleccionar_magikarp(pokemon_t* pokemon) {
    return es_especie(pokemon, MAGIKARP);
}

/*
 * Devuelve true si su color es ROJO y su velocidad no supera LENTO
 */
bool seleccionar_rojo_lento(pokemon_t* pokemon) {
    return es_color(pokemon, ROJO) && !supera_velocidad(pokemon, LENTO);
}

/*
 * Devuelve true si su peso supera el valor GRANDE
 */
bool seleccionar_grande(pokemon_t* pokemon) {
    return supera_peso(pokemon, GRANDE);
}

/*
 * Devuelve true si su velocidad supera RAPIDO
 */
bool seleccionar_veloz(pokemon_t* pokemon) {
    return supera_velocidad(pokemon, RAPIDO);
}

/*
 * Devuelve true si su especie empieza con M.
 */
bool seleccionar_con_m(pokemon_t* pokemon) {
    pokemon_t copia = *pokemon;
    copia.especie[1] = '\0';
    return es_especie(&copia, "M");
}

/* Funciones para mostrar */

/*
 * Muestra información completa del pokemón.
 */
void mostrar_ficha_pokemon(pokemon_t* pokemon) {
    printf("---------------------------\n");
    printf("Pokemon: %s\n", pokemon->especie);
    printf("Velocidad: %i\n", pokemon->velocidad);
    printf("Peso: %i\n", pokemon->peso);
    printf("Color: %s\n", pokemon->color);
}

/*
 * Imprime un bloque de largo MAX_CELDA con la cadena dada.
 *
 * Precondición: string no puede superar el largo MAX_CELDA.
 */
void crear_nueva_celda(char* string) {
    char celda[MAX_CELDA];
    memset(celda, ' ', MAX_CELDA * sizeof(char));
    size_t len = strlen(string);
    strcpy(celda + MAX_CELDA - len, string);
    printf("|%s", celda);
}

/*
 * Imprime una linea horizontal para la tabla.
 */
void crear_linea_horizontal() {
    char linea[MAX_CELDA];
    memset(linea, '=', MAX_CELDA * sizeof(char));
    linea[MAX_CELDA - 1] = '\0';
    for (int i = 0; i < CANT_ATRIBUTOS; i++)
        crear_nueva_celda(linea);
    printf("|\n");
}

/*
 * Imprime el encabezado de la tabla.
 */
void mostrar_encabezado_tabla() {
    printf("\n");
    crear_linea_horizontal();
    crear_nueva_celda(ESPECIE);
    crear_nueva_celda(VELOCIDAD);
    crear_nueva_celda(PESO);
    crear_nueva_celda(COLOR);
    printf("|\n");
    crear_linea_horizontal();
}

/*
 * Imprime una fila de la tabla con los datos de un pokemon.
 */
void mostrar_fila_tabla(pokemon_t* pokemon) {
    char velocidad[MAX_CELDA], peso[MAX_CELDA];
    sprintf(velocidad, "%i", pokemon->velocidad);
    sprintf(peso, "%i", pokemon->peso);
    crear_nueva_celda(pokemon->especie);
    crear_nueva_celda(velocidad);
    crear_nueva_celda(peso);
    crear_nueva_celda(pokemon->color);
    printf("|\n");
}

/* Funciones del flujo principal */

/*
 * Inicializa las estructuras principales en el heap.
 * Devuelve 0 si *arrecife y *acuario no son NULL.
 */
int crear_estructuras(arrecife_t** arrecife, acuario_t** acuario, const char* ruta_arrecife) {
    *arrecife = crear_arrecife(ruta_arrecife);
    *acuario = crear_acuario();
    return !(*arrecife) || !(*acuario);
}

/*
 * Traslada los pokemones de arrecife a acuario y muestra los restantes
 * en el arrecife.
 *
 * Argumentos:
 *      arrecife - puntero al heap.
 *      acuario - puntero al heap.
 *      selecciona - devuelve true ante una caracteristica deseada.
 *      cant_seleccion - cantidad de pokemon a trasladar.
 */
int trasladar_y_censar(arrecife_t* arrecife, acuario_t* acuario, bool (*selecciona)(pokemon_t*), int cant_seleccion) {
    int error = trasladar_pokemon(arrecife, acuario, selecciona, cant_seleccion);
    mostrar_encabezado_tabla();
    censar_arrecife(arrecife, mostrar_fila_tabla);
    crear_linea_horizontal();
    printf("Cantidad restante: %i\n", arrecife->cantidad_pokemon);
    return error;
}

/*
 * Libera la memoria destintada a las estructuras.
 *
 * Argumentos:
 *      arrecife - *arrecife apunta al heap.
 *      acuario - *acuario apunta al heap.
*/
void liberar_memoria(arrecife_t** arrecife, acuario_t** acuario){
    liberar_arrecife(*arrecife);
    liberar_acuario(*acuario);
}

int main (int argc, char **argv){
    arrecife_t* arrecife = NULL;
    acuario_t* acuario = NULL;
    int error = (
        /* Se crean las estructuras a utilizar */
        crear_estructuras(&arrecife, &acuario, argc > 1 ? argv[1] : RUTA_ARRECIFE)

        /* Se tralasda y censa */
        || trasladar_y_censar(arrecife, acuario, seleccionar_rojo_lento, 1)
        || trasladar_y_censar(arrecife, acuario, seleccionar_con_m, 4)
        || trasladar_y_censar(arrecife, acuario, seleccionar_veloz, 2)
        || trasladar_y_censar(arrecife, acuario, seleccionar_grande, 2)
        || trasladar_y_censar(arrecife, acuario, seleccionar_magikarp, 2)
    );

    /* Se guardan los pokémon del acuario */
    if (acuario && acuario->pokemon)
        guardar_datos_acuario(acuario, argc > 2 ? argv[2] : RUTA_ACUARIO);

    /* Se liberara la memoria utilizada */
    liberar_memoria(&arrecife, &acuario);
    return error;
}
