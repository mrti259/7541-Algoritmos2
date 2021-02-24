#include "constantes.h"
#include "juego.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>

#define MAX_ANCHO 80
#define PEDIR ": "
#define SALIR "Q"
#define MAX_RUTA 100
#define MAX_ARCHIVO 21
#define ARCHIVO_FORMATO "%30s"
#define NOMBRE_FORMATO "%20s"
#define ORIGEN_JUGADOR "./datos/jugador/"
#define ORIGEN_GIMNASIOS "./datos/gimnasios"

enum teclas
{
    SI = 'S',
    NO = 'N',
    CARGAR_JUGADOR='E', 
    AGREGAR_GIMNASIOS='A', 
    COMENZAR_PARTIDA='I', 
    SIMULAR_PARTIDA='S',
    VER_EQUIPO = 'E', 
    VER_GIMNASIO = 'G', 
    CAMBIAR_EQUIPO = 'C', 
    PELEAR = 'B', 
    SIGUIENTE = 'N',
    VER_VICTORIAS = 'V', 
    VER_DERROTAS = 'F',
    PEDIR_POKEMON = 'T', 
    PROXIMO_GIMNASIO = 'N',
    REINTENTAR_GIMNASIO = 'R', 
    FINALIZAR_PARTIDA = 'F'
};

void menu_inicio(juego_t*);

int main(int argc,char** argv)
{
    juego_t* juego = juego_crear();

    if (!juego)
        return -1;

    menu_inicio(juego);

    juego_liberar(juego);

    return 0;
}

/**
 * Pide un caracter por pantalla. Debe recibir una función que valide el dato
 * ingresado. Retorna una de las opciones válidas.
 */
char pedir_tecla(bool es_valido(char))
{
    if (!es_valido)
    {
        return (char) 0;
    }

    char opcion[] = " ";

    printf(PEDIR);
    scanf(" %c", opcion);

    return es_valido(*opcion) ? *opcion : pedir_tecla(es_valido);
}

/**
 * Valida si el caracter ingresado es SI o NO.
 */
bool confirmacion(char opcion)
{
    return opcion == SI || opcion == NO;
}

/**
 * Muestra en pantalla los archivos del directorio.
 */
void mostrar_archivos(char directorio[MAX_NOMBRE])
{
    DIR* dir = opendir(directorio);
    if (!dir)
    {
        return;
    }

    struct dirent *ent;
    int i = 0;
    while((ent = readdir(dir)))
    {
        if (strcmp(ent->d_name, ".") && strcmp(ent->d_name, ".."))
        {
            i++;
            printf(ARCHIVO_FORMATO, ent->d_name);
            if (i % 3 == 0) printf("\n");
        }
    }
    closedir(dir);
    printf("\n");
}

/**
 *
 */
void pantalla_crear_jugador(juego_t* juego)
{
    char nombre[MAX_NOMBRE];

    do
    {
        printf("| Cuál es su nombre?%s", PEDIR);
        scanf(NOMBRE_FORMATO, nombre);

        printf("| Su nombre es: %s ? (%c para confirmar / %c para cambiar)%s",
                nombre, SI, NO, PEDIR
                );
    }
    while (pedir_tecla(confirmacion) == NO);

    juego_nuevo(juego, nombre);
}

/**
 *
 */
void pantalla_cargar_jugador(juego_t* juego)
{
    char ruta[MAX_RUTA] = ORIGEN_JUGADOR;
    char archivo[MAX_ARCHIVO];

    mostrar_archivos(ruta);

    printf("| Cual es el archivo que desea cargar?: ");
    scanf(ARCHIVO_FORMATO, archivo);

    if (cargar_jugador(strcat(ruta, archivo), juego) == ERROR)
    {
        printf("| No se pudo abrir el archivo.\n");

        printf("| Quiere crear una nueva partida?\n");
        
        if (pedir_tecla(confirmacion) == SI)
        {
            pantalla_crear_jugador(juego);
        }
    }
    printf("| Ok!\n");
}

/**
 *
 */
void pantalla_agregar_gimnasios(juego_t* juego)
{
    char ruta[MAX_RUTA];
    char archivo[MAX_ARCHIVO];

    mostrar_archivos(ruta);

    printf("| Cuales son los gimnasios que quiere cargar?: ");
    scanf(ARCHIVO_FORMATO, archivo);

    while (strcmp(archivo, SALIR))
    {
        strcpy(ruta, ORIGEN_GIMNASIOS);
        if (cargar_gimnasios(strcat(ruta, archivo), juego) == ERROR)
        {
            printf("| Parece que %s no es un archivo válido :(\n", archivo);
        }
        else
        {
            printf("| Ok!\n");
        }
        printf("| Quiere cargar otro? (%s para salir): ", SALIR);
        scanf(ARCHIVO_FORMATO, archivo);
    }
}

/**
 *
 */
void pantalla_partida(juego_t* juego)
{
    printf("| Partida\n|\n|\n|\n");
}

/**
 *
 */
void pantalla_equipo(juego_t* juego)
{
    printf("| Ver Equipo\n|\n|\n|\n");
}

/**
 *
 */
void pantalla_cambiar_equipo(juego_t* juego)
{
    printf("| Cambiar equipo\n|\n|\n|\n");
}

/**
 *
 */
void pantalla_gimnasio(juego_t* juego)
{
    char str[MAX_NOMBRE];
    gimnasio_t *gimnasio = gimnasio_actual(juego);

    gimnasio_nombre(gimnasio, str);
    printf("| Estas en el Gimnasio %s\n|\n|\n|\n", str); 
}

/**
 *
 */
void pantalla_batalla(juego_t* juego)
{
    char str[MAX_NOMBRE];
    gimnasio_t *gimnasio = gimnasio_actual(juego);
    entrenador_t *rival = rival_actual(juego);
    pokemon_t *pkm_rival = pokemon_enemigo(juego),
              *pkm_jugador = pokemon_jugador(juego);

    gimnasio_nombre(gimnasio, str);
    printf("| Estas en el Gimnasio %s\n|\n|\n", str); 

    entrenador_nombre(rival, str);
    printf("| Combates contra %s\n", str);
    printf("| \n");

    printf("| \n");
    pokemon_nombre(pkm_rival, str);
    printf("| Oponente: %s\n", str);

    pokemon_nombre(pkm_jugador, str);
    printf("| Mi pkm: %s\n", str);
}

/**
 *
 */
void pantalla_victorias(juego_t* juego)
{
    printf("| Victoria\n|\n|\n|\n");
}

/**
 *
 */
void pantalla_derrotas(juego_t* juego)
{
    printf("| Derrotas\n|\n|\n|\n");
}

void pantalla_pedir_pokemon(juego_t* juego)
{
    printf("| Pedir pokemon\n|\n|\n|\n");
}

/**
 *
 */
void pantalla_final(juego_t* juego)
{
    printf("| Fin\n|\n|\n|\n");
}

/**
 * Devuelve true a las opciones validas del menu_inicio
 */
bool menu_inicio_opcion_valido(char opcion)
{
    switch (opcion)
    {
        case CARGAR_JUGADOR:
        case AGREGAR_GIMNASIOS:
        case COMENZAR_PARTIDA:
        case SIMULAR_PARTIDA:
            return true;
        default:
            return false;
    }
}

/**
 * Realiza una de las acciones del menu inicio.
 */
void menu_inicio_accionar(char opcion, juego_t* juego)
{
    switch (opcion)
    {
        case CARGAR_JUGADOR:
            pantalla_cargar_jugador(juego);
            menu_inicio(juego);
            return;
        case AGREGAR_GIMNASIOS:
            pantalla_agregar_gimnasios(juego);
            menu_inicio(juego);
            return;
        case COMENZAR_PARTIDA:
            pantalla_partida(juego);//, AVENTURA);
            return;
        case SIMULAR_PARTIDA:
            pantalla_partida(juego);//, SIMULACION);
            return;
    }
}

/**
 *
 */
void menu_inicio(juego_t* juego)
{
    char nombre[MAX_NOMBRE], str[MAX_NOMBRE + 4] = ", ";
    entrenador_nombre(personaje_principal(juego), nombre);
    int cargados = (int) juego_gimnasios(juego);

    printf("|\n| Hola%s!\n", strcmp(nombre, "") ? strcat(str, nombre) : "" );
    printf("| Hay %u gimnasio%s cargados\n", cargados, cargados == 1 ? "" : "s");

    printf("|\n| ¿Que desea hacer?\n");
    printf("| %c - Cargar mi personaje\n", CARGAR_JUGADOR);
    printf("| %c - Agregar gimnasios\n", AGREGAR_GIMNASIOS);
    printf("| %c - Comenzar la partida\n", COMENZAR_PARTIDA);
    printf("| %c - Simular la partida\n", SIMULAR_PARTIDA);

    menu_inicio_accionar(pedir_tecla(menu_inicio_opcion_valido), juego);
}

/**
 *
 */
bool menu_gimnasio_opcion_valido(char opcion)
{
    switch (opcion)
    {
        case VER_EQUIPO:
        case VER_GIMNASIO:
        case CAMBIAR_EQUIPO:
        case PELEAR:
            return true;
        default:
            return false;
    }
}

/**
 *
 */
bool menu_gimnasio_opcion_valido_extras(char opcion)
{
    switch(opcion)
    {
        case VER_VICTORIAS:
        case VER_DERROTAS:
            return true;
        default:
            return menu_gimnasio_opcion_valido(opcion);
    }
}

/**
 *
 */
void menu_gimnasio_accionar(char opcion, juego_t* juego)
{
    switch(opcion)
    {
        case VER_EQUIPO:
            pantalla_equipo(juego);
            return;
        case VER_GIMNASIO:
            pantalla_gimnasio(juego);
            return;
        case CAMBIAR_EQUIPO:
            pantalla_cambiar_equipo(juego);
            return;
        case PELEAR:
            pantalla_batalla(juego);
            return;
        case VER_VICTORIAS:
            pantalla_victorias(juego);
            return;
        case VER_DERROTAS:
            pantalla_derrotas(juego);
            return;
    }
}

/**
 *
 */
void menu_gimnasio(juego_t* juego)
{
    printf("|\n| ¿Que desea hacer?\n");
    printf("| %c - Ver mi equipo\n", VER_EQUIPO);
    printf("| %c - Ver información del gimnasio actual\n", VER_GIMNASIO);
    printf("| %c - Cambiar equipo\n", CAMBIAR_EQUIPO);
    printf("| %c - Pelear!\n", PELEAR);

    // if hay victorias, mostrar
    printf("| %c - Mis victorias :D \n", VER_VICTORIAS);

    // if hay derrotas, mostrar
    printf("| %c - Mis derrotas :( \n", VER_DERROTAS);

    menu_gimnasio_accionar(pedir_tecla(menu_gimnasio_opcion_valido), juego);
}

/**
 *
 */
bool menu_batalla_opcion_valido(char opcion)
{
    switch (opcion)
    {
        case SIGUIENTE:
            return true;
        default:
            return false;
    }
}

/**
 *
 */
void menu_batalla_accionar(char opcion, juego_t* juego)
{
    switch (opcion)
    {
        case SIGUIENTE:
            pantalla_batalla(juego);
            return;
    }
}

/**
 *
 */
void menu_batalla(juego_t* juego)
{
    pokemon_t* mi_pkm = 

    printf("|\n| ¿Que desea hacer?\n");
    printf("| %c - Pelear!\n", SIGUIENTE);

    menu_batalla_accionar(pedir_tecla(menu_batalla_opcion_valido), juego);
}

/**
 *
 */
bool menu_victoria_opcion_valido(char opcion)
{
    switch (opcion)
    {
        case PEDIR_POKEMON:
        case CAMBIAR_EQUIPO:
        case PROXIMO_GIMNASIO:
            return true;
        default:
            return false;
    }
}

/**
 *
 */
void menu_victoria_accionar(char opcion, juego_t* juego)
{
    switch (opcion)
    {
        case PEDIR_POKEMON:
            pantalla_pedir_pokemon(juego);
            return;
        case CAMBIAR_EQUIPO:
            pantalla_cambiar_equipo(juego);
            return;
        case PROXIMO_GIMNASIO:
            pantalla_gimnasio(juego);
            return;
    }
}

/**
 *
 */
void menu_victoria(juego_t* juego)
{
    printf("|\n| ¿Que desea hacer?\n");
    printf("| %c - Pedir Pokemon\n", PEDIR_POKEMON);
    printf("| %c - Cambiar equipo\n", CAMBIAR_EQUIPO);
    printf("| %c - Ir al próximo gimnasio\n", PROXIMO_GIMNASIO);

    menu_victoria_accionar(pedir_tecla(menu_victoria_opcion_valido), juego);
}

/**
 *
 */
bool menu_derrota_opcion_valido(char opcion)
{
    switch (opcion)
    {
        case CAMBIAR_EQUIPO:
        case REINTENTAR_GIMNASIO:
        case FINALIZAR_PARTIDA:
            return true;
        default:
            return false;
    }
}

/**
 *
 */
void menu_derrota_accionar(char opcion, juego_t* juego)
{
    switch (opcion)
    {
        case CAMBIAR_EQUIPO:
            pantalla_cambiar_equipo(juego);
            return;
        case REINTENTAR_GIMNASIO:
            pantalla_gimnasio(juego);
            return;
        case FINALIZAR_PARTIDA:
            pantalla_final(juego);
            return;
    }
}

/**
 *
 */
void menu_derrota(juego_t* juego)
{
    printf("|\n| ¿Que desea hacer?\n");
    printf("| %c - Cambiar mi equipo\n", CAMBIAR_EQUIPO);
    printf("| %c - Reintentar gimnasio\n", REINTENTAR_GIMNASIO);
    printf("| %c - Finalizar partida\n", FINALIZAR_PARTIDA);

    menu_derrota_accionar(pedir_tecla(menu_derrota_opcion_valido), juego);
}
