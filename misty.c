#include "evento_pesca.h"
#include <string.h>

const char
    *RUTA_ARRECIFE = "arrecife.txt",
    *RUTA_ACUARIO = "acuario.txt",
    *ESPECIE = "ESPECIE",
    *VELOCIDAD = "VELOCIDAD",
    *PESO = "PESO",
    *COLOR = "COLOR",
    *MAGIKARP = "Magikarp",
    *DORADO = "dorado",
    *AZUL = "azul";

#define MAX_CELDA 16

const int
    CANT_ATRIBUTOS = 4,
    LENTO = 30,
    CHICO = 30;

const char* (SUBLEGENDARIOS[MAX_CELDA]) = {
    "Articuno", "Zapdos", "Moltres",
    "Raikou", "Entei", "Suicune",
    "Regirock", "Regice", "Registeel",
    };
const int CANT_SUBLEGENDARIOS = 9;

const char* (LEGENDARIOS[MAX_CELDA]) = {
    "Mewtwo",
    "Lugia", "Ho-Oh",
    "Kyogre", "Groudon", "Rayquaza",
    };
const int CANT_LEGENDARIOS = 6;

/*
 * Devuelve true si es legendario.
 */
bool seleccionar_legendario(pokemon_t* pokemon);

/*
 * Devuelve true si es sublegendario.
 */
bool seleccionar_sublegendario(pokemon_t* pokemon);

/*
 * Devuelve true si su velocidad no supera LENTO
 */
bool seleccionar_lento(pokemon_t* pokemon);

/*
 * Devuelve true si su peso no supera el valor CHICO
 */
bool seleccionar_chico(pokemon_t* pokemon);

/*
 * Devuelve true si es un MAGIKARP de color DORADO.
 */
bool seleccionar_magikarp_dorado(pokemon_t* pokemon);

/*
 * Inicializa las estructuras principales en el heap.
 * Devuelve 0 si *arrecife y *acuario no son NULL.
 */
int crear_estructuras(arrecife_t** arrecife, acuario_t** acuario, const char* ruta_arrecife);

/*
 * Traslada los pokemones de arrecife a acuario y muestra los restantes
 * en el arrecife. Devuelve 0 si se trasladaron correctamente, o devuelve
 * un error.
 *
 * Argumentos:
 *      arrecife - puntero al heap.
 *      acuario - puntero al heap.
 *      selecciona - devuelve true ante una caracteristica deseada.
 *      cant_seleccion - cantidad de pokemon a trasladar.
 */
int trasladar_y_censar(arrecife_t* arrecife, acuario_t* acuario, bool (*selecciona)(pokemon_t*), int cant_seleccion);

/*
 * Libera la memoria destintada a las estructuras.
 *
 * Argumentos:
 *      arrecife - *arrecife apunta al heap.
 *      acuario - *acuario apunta al heap.
*/
void liberar_memoria(arrecife_t** arrecife, acuario_t** acuario);

int main (int argc, char **argv){
    arrecife_t* arrecife = NULL;
    acuario_t* acuario = NULL;
    int error_ejecucion = (
        crear_estructuras(&arrecife, &acuario, argc > 1 ? argv[1] : RUTA_ARRECIFE)
        || trasladar_y_censar(arrecife, acuario, seleccionar_chico, 4)
        || trasladar_y_censar(arrecife, acuario, seleccionar_lento, 4)
        || trasladar_y_censar(arrecife, acuario, seleccionar_magikarp_dorado, 1)
        || trasladar_y_censar(arrecife, acuario, seleccionar_sublegendario, 1)
        || trasladar_y_censar(arrecife, acuario, seleccionar_legendario, 1)
    );

    int error_guardado = guardar_datos_acuario(acuario, argc > 2 ? argv[2] : RUTA_ACUARIO);

    liberar_memoria(&arrecife, &acuario);
    return error_ejecucion || error_guardado;
}

/*
 * Devuelve true si el pokemon es de la especie solicitada.
 */
bool es_especie(pokemon_t* pokemon, const char* especie) {
    return !strcmp(pokemon->especie, especie);
}

/*
 * Devuelve true si el pokmeon es del color solicitado.
 */
bool es_color(pokemon_t* pokemon, const char* color) {
    return !strcmp(pokemon->color, color);
}

/*
 * Devuelve true si el pokemon es más veloz que el valor solicitado.
 */
bool supera_velocidad(pokemon_t* pokemon, const int velocidad) {
    return pokemon->velocidad > velocidad;
}

/*
 * Devuelve true si el pokemon es más pesado que el valor solicitado.
 */
bool supera_peso(pokemon_t* pokemon, const int peso) {
    return pokemon->peso > peso;
}

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
void crear_nueva_celda(const char* string) {
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

int crear_estructuras(arrecife_t** arrecife, acuario_t** acuario, const char* ruta_arrecife) {
    *arrecife = crear_arrecife(ruta_arrecife);
    *acuario = crear_acuario();
    return !(*arrecife) || !(*acuario);
}

int trasladar_y_censar(arrecife_t* arrecife, acuario_t* acuario, bool (*selecciona)(pokemon_t*), int cant_seleccion) {
    int error = trasladar_pokemon(arrecife, acuario, selecciona, cant_seleccion);
    mostrar_encabezado_tabla();
    censar_arrecife(arrecife, mostrar_fila_tabla);
    crear_linea_horizontal();
    printf("Cantidad restante: %i\n", arrecife->cantidad_pokemon);
    return error;
}

void liberar_memoria(arrecife_t** arrecife, acuario_t** acuario){
    liberar_arrecife(*arrecife);
    liberar_acuario(*acuario);
}

bool seleccionar_legendario(pokemon_t* pokemon) {
    bool encontrado = false;
    int i = 0;
    while (i < CANT_LEGENDARIOS) {
        if (es_especie(pokemon, LEGENDARIOS[i]))
            encontrado = true;
        i++;
    }
    return encontrado;
}

bool seleccionar_sublegendario(pokemon_t* pokemon) {
    bool encontrado = false;
    int i = 0;
    while (i < CANT_SUBLEGENDARIOS) {
        if (es_especie(pokemon, SUBLEGENDARIOS[i]))
            encontrado = true;
        i++;
    }
    return encontrado;
}

bool seleccionar_magikarp_dorado(pokemon_t* pokemon) {
    return es_especie(pokemon, MAGIKARP) && es_color(pokemon, DORADO);
}

bool seleccionar_chico(pokemon_t* pokemon) {
    return !supera_peso(pokemon, CHICO);
}

bool seleccionar_lento(pokemon_t* pokemon) {
    return !supera_velocidad(pokemon, LENTO);
}
