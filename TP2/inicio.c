#include "constantes.h"
#include "juego.h"
#include "batallas.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include "colors.h"
#include "borders.h"

#define MAX_ANCHO 80
#define PEDIR ": "
#define SALIR "Q"
#define MAX_RUTA 100
#define MAX_ARCHIVO 33
#define MAX_CAJA 20
#define ARCHIVO_FORMATO "%32s"
#define NOMBRE_FORMATO "%25s"
#define ORIGEN_JUGADOR "./datos/jugador/"
#define ORIGEN_GIMNASIOS "./datos/gimnasios/"
const char TABLA_CABECERA[] = YELLOW " %50s " B_VERTICAL " %s " B_VERTICAL " %s " B_VERTICAL " %s " B_VERTICAL " %s " B_VERTICAL " %s\n" TEXT_RESET,
           TABLA_POKEMON[] = YELLOW " %50s " B_VERTICAL "  %c " B_VERTICAL "  %c " B_VERTICAL " %3i " B_VERTICAL " %3i " B_VERTICAL " %3i\n" TEXT_RESET;

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

enum menus
{
    I_INICIO,
    I_GIMNASIO,
    I_BATALLA,
    I_VICTORIA,
    I_DERROTA
};

void menu_controller(int, juego_t*);

/*
 * Pausa el programa la cantidad de tiempo indicado.
 * Esta función depende del sistema donde sea ejecutado por lo cual no es portable
 * y no funcionará en sistemas Windows y otros.
 */
void detener_tiempo(float seg)
{
    char comando[100] = "";
    sprintf(comando, "sleep %.2f", seg);
    system(comando);
}

/**
 * Imprime el texto en amarillo.
 */
void texto(const char* texto)
{
    COLORIZE(YELLOW, texto);
}

/**
 * Atajo para imprimir un borde con color.
 */
void borde(const char* color, const char* _borde)
{
    printf(color);
    BORDER(_borde);
    printf(TEXT_RESET);
}

/**
 * Imprime un borde vertical de color amarillo de una línea.
 */
void borde_vertical()
{
    borde(YELLOW, B_VERTICAL);
}

/**
 * Imprime el borde horizontal con extremos indicados ocupando el ancho máximo.
 */
void borde_horizontal(const char* _b_izq, const char* _b_der)
{
    borde(YELLOW, _b_izq);

    for (int i = 0; i < MAX_ANCHO; i++)
        borde(YELLOW, B_HORIZONTAL);

    borde(YELLOW, _b_der);
    printf("\n");
}

/**
 * Imprime el borde superior de ancho máximo.
 */
void borde_superior()
{
    borde_horizontal(B_LEFT_TOP, B_RIGHT_TOP);
}

/**
 * Imprime el borde inferior de ancho máximo.
 */
void borde_inferior()
{
    borde_horizontal(B_LEFT_BOTTOM, B_RIGHT_BOTTOM);
}

/**
 * Imprime el borde medio de ancho máximo.
 */
void borde_medio()
{
    borde(YELLOW, B_LEFT_MIDDLE);

    for (int i = 0; i < MAX_ANCHO; i++)
        borde(YELLOW, B_HORIZONTAL);

    borde(YELLOW, B_RIGHT_MIDDLE);
    printf("\n");
}

/**
 * Imprime un titulo de color amarillo y subrayado.
 */
void titulo_pantalla(const char* titulo)
{
    COLORIZE(YELLOW_UNDERLINE, titulo);
    printf("\n");
}

/**
 * Imprime un carácter de color verde para destacar y una descripción de color amarillo.
 */
void mostrar_opcion(char opcion, const char* descripcion)
{
    borde_vertical();

    char str[] = "  " TEXT_RESET " - ";
    str[1] = opcion;
    COLORIZE(GREEN, str);
    texto(descripcion);
    printf("\n");
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

    borde_superior();
    borde_vertical();
    titulo_pantalla(directorio);

    struct dirent *ent;
    int i = 1;
    while((ent = readdir(dir)))
    {
        if (strcmp(ent->d_name, ".") && strcmp(ent->d_name, ".."))
        {
            borde_vertical();
            printf(ARCHIVO_FORMATO, ent->d_name);
            if (i++ % 2 == 0)
                printf("\n");
        }
    }
    if (i % 2 == 0) borde_vertical();
    closedir(dir);
    printf("\n");
    borde_medio();
}

/**
 * Pide un carácter por pantalla. Debe recibir una función que valide el dato
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
    scanf("%1s", opcion);

    return es_valido(*opcion) ? *opcion : pedir_tecla(es_valido);
}

/**
 * Valida si el carácter ingresado es SI o NO.
 */
bool confirmacion(char opcion)
{
    return opcion == SI || opcion == NO;
}

/**
 * Le pide al jugador ingresar un nombre. Después de confirmar, se crea su
 * personaje y recibe un Pokémon.
 */
void pantalla_crear_jugador(juego_t* juego)
{
    char nombre[MAX_NOMBRE];

    do
    {
        borde_vertical();
        texto("Cuál es su nombre?\n");
        printf(PEDIR);
        scanf(NOMBRE_FORMATO, nombre);

        borde_vertical();
        texto("Su nombre es: ");
        COLORIZE(WHITE, nombre);
        texto(" ?\n");
        mostrar_opcion(SI, "Para confirmar");
        mostrar_opcion(NO, "Para cambiar");
        printf(PEDIR);
    }
    while (pedir_tecla(confirmacion) == NO);

    juego_nuevo(juego, nombre);
}

/**
 * Muestra cuáles son los archivos de jugadores disponibles en el archivo
 * ORIGEN_JUGADOR y le pide al usuario que ingrese cuál es el que desea cargar.
 * Si no puede abrirlo,
 * puede crear un nuevo personaje.
 */
void pantalla_cargar_jugador(juego_t* juego)
{
    char ruta[MAX_RUTA] = ORIGEN_JUGADOR;
    char archivo[MAX_ARCHIVO];

    mostrar_archivos(ruta);

    borde_vertical();
    texto("Cual es el archivo que desea cargar?:\n");
    printf(PEDIR);
    scanf(ARCHIVO_FORMATO, archivo);

    if (cargar_jugador(strcat(ruta, archivo), juego) == ERROR)
    {
        borde_vertical();
        texto("No se pudo abrir el archivo.\n");
        borde_medio();
        borde_vertical();
        texto("Querés crear una nueva partida?\n");
        mostrar_opcion(SI, "Para confirmar");
        mostrar_opcion(NO, "Para cancelar");
        if (pedir_tecla(confirmacion) == SI)
        {
            pantalla_crear_jugador(juego);
        }
    }
    borde_medio();
    borde_vertical();
    texto("Ok!\n");
}

/**
 * Imprime los archivos del directorio ORIGEN_GIMNASIOS y le da la opción al
 * jugador de cargar los archivos que desee.
 */
void pantalla_agregar_gimnasios(juego_t* juego)
{
    char ruta[MAX_RUTA];
    char archivo[MAX_ARCHIVO];

    mostrar_archivos(ORIGEN_GIMNASIOS);

    borde_vertical();
    texto("Cuales son los gimnasios que quiere cargar?\n");
    printf(PEDIR);
    scanf(ARCHIVO_FORMATO, archivo);

    while (strcmp(archivo, SALIR))
    {
        strcpy(ruta, ORIGEN_GIMNASIOS);
        borde_medio();
        if (cargar_gimnasios(strcat(ruta, archivo), juego) == ERROR)
        {
            borde_vertical();
            texto("Parece que ");
            printf(archivo);
            texto(" no es un archivo válido :(\n");
        }
        else
        {
            borde_vertical();
            texto("Ok!\n");
        }
        borde_medio();
        borde_vertical();
        texto("Querés cargar otro?\n");
        mostrar_opcion(*SALIR, "Para salir");
        printf(PEDIR);
        scanf(ARCHIVO_FORMATO, archivo);
    }
}

/**
 * Enumera e imprime los Pokémon del party.
 */
void mostrar_pokemon_party(pokemon_t* pokemon, void* contexto)
{
    if (!contexto) return;

    borde_vertical();
    char str[MAX_NOMBRE + 10],
    formato[] = "%3i. %s",
    nombre[MAX_NOMBRE];
    pokemon_nombre(pokemon, nombre);
    (*(int*)contexto)++;
    sprintf(str, formato, *(int*)contexto, nombre);
    texto(strcat(str,"\n"));
}

/**
 * Enumera e imprime los Pokémon de la caja.
 */
void mostrar_pokemon_caja(pokemon_t* pokemon, void* contexto)
{
    if (!contexto || pokemon_en_party(pokemon))
        return;

    (*(int*)contexto)++;

    borde_vertical();
    char str[MAX_NOMBRE + 10],
    formato[] = "%3i. %50s",
    nombre[MAX_NOMBRE];
    pokemon_nombre(pokemon, nombre);
    sprintf(str, formato, *(int*)contexto, nombre);
    texto(strcat(str,"\n"));
}

/**
 * Imprime una fila de la tabla con información del Pokémon.
 */
void mostrar_pokemon_tabla(pokemon_t* pokemon, void* contexto)
{
    char nombre[MAX_NOMBRE];
    pokemon_nombre(pokemon, nombre);
    borde_vertical();
    printf(TABLA_POKEMON, nombre, pokemon_tipo_principal(pokemon),
            pokemon_tipo_secundario(pokemon), pokemon_ataque(pokemon),
            pokemon_defensa(pokemon), pokemon_velocidad(pokemon));
}

/**
 * Crea el encabezado para la tabla de Pokémon
 */
void tabla_pokemon(juego_t* juego, const char* titulo, entrenador_t* entrenador)
{
    borde_vertical();
    titulo_pantalla(titulo);
    borde_vertical();
    printf(TABLA_CABECERA, "Nombre", "T1", "T2", "Att", "Def", "Vel");
}

/**
 * Imprime los Pokémon del equipo del jugador.
 */
void pantalla_ver_equipo(juego_t* juego)
{
    tabla_pokemon(juego, "Mi equipo", personaje_principal(juego));
    entrenador_mostrar_party(personaje_principal(juego), mostrar_pokemon_tabla, NULL);
}

/**
 * Muestra los Pokémon del party y permite al usuario sacar uno.
 * Muestra los Pokémon de la caja y permite al usuario agregar uno al party.
 */
void pantalla_cambiar_equipo(juego_t* juego)
{
    size_t contexto = 0, posicion;
    borde_superior();
    borde_vertical();
    titulo_pantalla("Cambiar equipo");
    entrenador_mostrar_party(personaje_principal(juego), mostrar_pokemon_party, &contexto);

    borde_vertical();
    texto("Qué Pokémon quiere sacar? (Ingrese nº)\n");
    do
    {
        char str[10] = "";
        printf(PEDIR);
        scanf("%3s", str); // para prevenir overflow
        posicion = (size_t) atoi(str);
    }
    while (quitar_del_party(juego, posicion - 1) == ERROR);

    contexto--;
    entrenador_mostrar_pokemon(personaje_principal(juego), mostrar_pokemon_caja, &contexto);
    borde_vertical();
    texto("Qué Pokémon quiere ingresar? (Ingrese nº)\n");
    do
    {
        char str[4];
        printf(PEDIR);
        scanf("%3s", str); // para prevenir overflow
        posicion = (size_t) atoi(str);
    }
    while (agregar_al_party(juego, posicion - 1));
}

/**
 * Muestra información del gimnasio.
 */
void pantalla_gimnasio(juego_t* juego)
{
    char nombre[MAX_NOMBRE];
    gimnasio_t *gimnasio = gimnasio_actual(juego);
    gimnasio_nombre(gimnasio, nombre);

    borde_vertical();
    texto("Estas en ");
    printf("%s\n", nombre);
    borde_vertical();
    texto("Quedan ");
    printf("%i", (int) gimnasio_entrenadores(gimnasio));
    texto(" entrenadores\n");
    borde_vertical();
    texto("La función de batalla tiene id: ");
    printf("%i\n", gimnasio_id_funcion(gimnasio));
}

/**
 * Muestra información del rival.
 */
void pantalla_rival(juego_t* juego)
{
    char nombre[MAX_NOMBRE];
    entrenador_t* rival = rival_actual(juego);

    entrenador_nombre(rival, nombre);
    borde_vertical();
    texto("El próximo rival es ");
    printf("%s\n", nombre);
    borde_vertical();
    texto("Cuenta con ");
    printf("%i", (int) entrenador_pokemon_party(rival));
    texto(" Pokémon\n");

    borde_medio();
    tabla_pokemon(juego, "Su equipo", rival);
    entrenador_mostrar_party(rival, mostrar_pokemon_tabla, NULL);
}

/**
 * Muestra información de la batalla actual.
 */
void pantalla_batalla(juego_t* juego)
{
    char str[MAX_NOMBRE];
    gimnasio_t *gimnasio = gimnasio_actual(juego);
    entrenador_t *rival = rival_actual(juego);
    pokemon_t *pkm_rival = pokemon_enemigo(juego),
              *pkm_jugador = pokemon_jugador(juego);

    gimnasio_nombre(gimnasio, str);
    borde_vertical();
    texto("Estas en el Gimnasio ");
    printf("%s\n", str);

    entrenador_nombre(rival, str);
    borde_vertical();
    texto("Combates contra ");
    printf("%s\n", str);

    pokemon_nombre(pkm_rival, str);
    borde_vertical();
    texto("Pokémon enemigo: ");
    printf("%s\n", str);

    pokemon_nombre(pkm_jugador, str);
    borde_vertical();
    texto("Pokémon actual: ");
    printf("%s\n", str);
    borde_medio();
    detener_tiempo(1);
}

/**
 * Muestra los Pokémon del líder en pantalla y le da la opción al jugador
 * de elegir cuál prefiere tomar prestado.
 */
void pantalla_pedir_pokemon(juego_t* juego)
{
    if (!gimnasio_derrotado(gimnasio_actual(juego)))
    {
        return;
    }
    char nombre[MAX_NOMBRE];
    entrenador_nombre(rival_actual(juego), nombre);

    size_t n = 0;
    borde_superior();
    borde_vertical();
    texto("Toma un Pokémon de ");
    printf("%s\n", nombre);
    entrenador_mostrar_party(rival_actual(juego), mostrar_pokemon_party, &n);
    do
    {
        printf(PEDIR);
        scanf("%lu", &n); // ~> no es portable
    }
    while (tomar_pokemon(juego, n));
}

/**
 * Mensaje a mostrar cuando se vencen todos los gimnasios.
 */
void pantalla_victoria(juego_t* juego)
{
    borde_vertical();
    texto("FELICIDADES! Has derrotado todos los gimnasios!\n");
    borde_vertical();
    texto("Recuerda combatir a la Elite Four para\n");
    borde_vertical();
    texto("convertirte en Maestro Pokémon!\n");
}

/**
 * Mensaje a mostrar cuando se abandona.
 */
void pantalla_derrota(juego_t* juego)
{
    borde_vertical();
    texto("Perdiste...\n");
    borde_vertical();
    texto("Todavía te falta madera para convertirte en Maestro Pokémon!\n");
}

/**
 * Muestra como el personaje principal avanza en su aventura con su equipo
 * si darle la opción al usuario de intervenir. Si pierde un enfrentamiento
 * termina la Simulación, si no continúa hasta convertise en campeón.
 */
void pantalla_simulacion(juego_t* juego)
{
    if (!gimnasio_actual(juego))
    {
        COLORIZE(RED_BOLD, " No hay gimnasios cargados!\n");
        menu_controller(I_INICIO, juego);
        return;
    }
    if (!personaje_principal(juego))
    {
        COLORIZE(RED_BOLD, " No hay cargaste tu personaje!\n");
        menu_controller(I_INICIO, juego);
        return;
    }

    borde_superior();
    borde_vertical();
    titulo_pantalla("Simulación");
    int resultado = retar_gimnasio(juego, pantalla_batalla);

    while (resultado > 0)
    {
        borde_vertical();
        COLORIZE(GREEN, "Has vencido el gimnasio!\n");
        borde_medio();
        resultado = retar_gimnasio(juego, pantalla_batalla);
    }

    if (!juego_gimnasios(juego))
    {
        pantalla_victoria();
    }
    else
    {
        pantalla_derrota();
    }
    borde_inferior();
}

/**
 *
 */
void pantalla_final(juego_t* juego)
{
    borde_superior();
    borde_vertical();
    texto("Es triste dejarte ir, pero espero que hayas disfrutado tu aventura\n");
    borde_vertical();
    texto("Querés guardar su partida?\n");
    mostrar_opcion(SI, "Para confirmar");
    mostrar_opcion(NO, "Para cancelar");
    if (pedir_tecla(confirmacion) == SI)
    {
        borde_vertical();
        texto("Ingrese un nombre para el archivo que desea guardar:\n");
        char nombre[MAX_ARCHIVO], ruta[MAX_RUTA] = ORIGEN_JUGADOR;
        printf(PEDIR);
        scanf(ARCHIVO_FORMATO, nombre);
        if (guardar_jugador(strcat(ruta, nombre), juego))
        {
            borde(RED, B_VERTICAL);
            COLORIZE(RED_BOLD, "Ocurrió un error al guardar la partida\n");
        }
        else
        {
            borde_vertical();
            texto("Espero que nos volvamos a ver pronto\n");
        }
    }
    borde_inferior();
}

/**
 * Valida si la opcion elegida por el usuario está contemplada en el menu de
 * inicio.
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
 * Controlador de las acciones del menu de inicio.
 */
void menu_inicio_controller(char opcion, juego_t* juego)
{
    switch (opcion)
    {
        case CARGAR_JUGADOR:
            pantalla_cargar_jugador(juego);
            menu_controller(I_INICIO, juego);
            return;
        case AGREGAR_GIMNASIOS:
            pantalla_agregar_gimnasios(juego);
            menu_controller(I_INICIO, juego);
            return;
        case COMENZAR_PARTIDA:
            menu_controller(I_GIMNASIO, juego);
            return;
        case SIMULAR_PARTIDA:
            pantalla_simulacion(juego);
            return;
    }
}

/**
 * Menú inicial. Da las opciones para que el jugador pueda crear su partida a
 * su gusto.
 */
void menu_inicio(juego_t* juego)
{
    char nombre[MAX_NOMBRE];
    entrenador_nombre(personaje_principal(juego), nombre);
    int cargados = (int) juego_gimnasios(juego);

    borde_superior();
    borde_vertical();
    texto("Hola");
    texto(strcmp(nombre, "") ? ", " : "");
    printf("%s", nombre);
    texto("!\n");

    borde_vertical();
    texto("Hay ");
    printf("%i", (int) cargados);
    texto(" gimnasios cargado");
    texto(cargados == 1 ? "\n" : "s\n");

    borde_medio();
    borde_vertical();
    texto("¿Que desea hacer?\n");
    borde_medio();
    mostrar_opcion(CARGAR_JUGADOR, "Cargar mi personaje");
    mostrar_opcion(AGREGAR_GIMNASIOS, "Agregar gimnasios");
    mostrar_opcion(COMENZAR_PARTIDA, "Comenzar la partida");
    mostrar_opcion(SIMULAR_PARTIDA, "Simular la partida");
    menu_inicio_controller(pedir_tecla(menu_inicio_opcion_valido), juego);
}

/**
 * Valida si la opcion ingresada por el usuario está contemplada en el menu de
 * batalla.
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
 * Menú de batalla a mostrar durante un enfrentamiento.
 */
void menu_batalla(juego_t* juego)
{
    borde_superior();
    pantalla_batalla(juego);
    borde_vertical();
    texto("¿Qué desea hacer?\n");
    borde_medio();
    mostrar_opcion(SIGUIENTE, "Pelear!");
    pedir_tecla(menu_batalla_opcion_valido);
    borde_inferior();
}

/**
 * Valida si la opcion ingresada por el usuario está contemplada en el menu de
 * gimnasio.
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
 * Controlador de acciones del menu de gimnasio.
 */
void menu_gimnasio_controller(char opcion, juego_t* juego)
{
    switch(opcion)
    {
        case VER_EQUIPO:
            borde_superior();
            pantalla_ver_equipo(juego);
            menu_controller(I_GIMNASIO, juego);
            return;
        case VER_GIMNASIO:
            borde_superior();
            pantalla_gimnasio(juego);
            pantalla_rival(juego);
            menu_controller(I_GIMNASIO, juego);
            return;
        case CAMBIAR_EQUIPO:
            pantalla_cambiar_equipo(juego);
            menu_controller(I_GIMNASIO, juego);
            return;
        case PELEAR:
            if (retar_gimnasio(juego, menu_batalla) > 0)
                menu_controller(I_VICTORIA, juego);
            else
                menu_controller(I_DERROTA, juego);
            return;
    }
}

/**
 * Menú de gimnasio.
 */
void menu_gimnasio(juego_t* juego)
{
    if (!gimnasio_actual(juego))
    {
        COLORIZE(RED_BOLD, " No hay gimnasios cargados!\n");
        menu_controller(I_INICIO, juego);
        return;
    }
    if (!personaje_principal(juego))
    {
        COLORIZE(RED_BOLD, " No hay cargaste tu personaje!\n");
        menu_controller(I_INICIO, juego);
        return;
    }

    borde_superior();
    pantalla_gimnasio(juego);

    borde_medio();
    borde_vertical();
    texto("¿Que desea hacer?\n");
    borde_medio();
    mostrar_opcion(VER_EQUIPO, "Ver mi equipo");
    mostrar_opcion(VER_GIMNASIO, "Ver información del gimnasio actual");
    mostrar_opcion(CAMBIAR_EQUIPO, "Cambiar equipo");
    mostrar_opcion(PELEAR, "Pelear!");
    menu_gimnasio_controller(pedir_tecla(menu_gimnasio_opcion_valido), juego);
}

/**
 * Valida si la opcion elegida por el jugador esta contemplada en el menu de victoria
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
 * Controlador de acciones del menu de victoria.
 */
void menu_victoria_controller(char opcion, juego_t* juego)
{
    switch (opcion)
    {
        case PEDIR_POKEMON:
            pantalla_pedir_pokemon(juego);
            menu_controller(I_GIMNASIO, juego);
            return;
        case CAMBIAR_EQUIPO:
            pantalla_cambiar_equipo(juego);
            menu_controller(I_GIMNASIO, juego);
            return;
        case PROXIMO_GIMNASIO:
            retar_gimnasio(juego, menu_gimnasio);
            return;
    }
}

/**
 * Menú a mostrar cuando el jugador gana un gimnasio.
 */
void menu_victoria(juego_t* juego)
{
    borde_superior();
    borde_vertical();
    texto("Pudiste superar al líder :D\n");
    borde_vertical();
    texto("Podés pedirle prestado un Pokémon y prepararte para tu próxima aventura\n");
    borde_medio();
    borde_vertical();
    texto("¿Qué desea hacer?\n");
    borde_medio();
    mostrar_opcion(PEDIR_POKEMON, "Pedir Pokémon");
    mostrar_opcion(CAMBIAR_EQUIPO, "Cambiar equipo");
    mostrar_opcion(PROXIMO_GIMNASIO, "Próximo gimnasio");
    menu_victoria_controller(pedir_tecla(menu_victoria_opcion_valido), juego);
}

/**
 * Valida que la opción elegida este contemplada en el menu derrota.
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
 * Controlador de acciones del menu derrota.
 */
void menu_derrota_controller(char opcion, juego_t* juego)
{
    switch (opcion)
    {
        case CAMBIAR_EQUIPO:
            pantalla_cambiar_equipo(juego);
            menu_controller(I_GIMNASIO, juego);
            return;
        case REINTENTAR_GIMNASIO:
            pantalla_gimnasio(juego);
            menu_controller(I_GIMNASIO, juego);
            return;
        case FINALIZAR_PARTIDA:
            pantalla_final(juego);
            return;
    }
}

/**
 * Menú a mostrar cuando el jugador pierde un enfrentamiento.
 */
void menu_derrota(juego_t* juego)
{
    borde_superior();
    borde_vertical();
    texto("Tu equipo no tiene más energía...\n");
    borde_vertical();
    texto("Parece que subestimaste la fuerza de este rival\n");
    borde_medio();
    borde_vertical();
    texto("¿Qué desea hacer?\n");
    borde_medio();
    mostrar_opcion(CAMBIAR_EQUIPO, "Cambiar Pokémon");
    mostrar_opcion(REINTENTAR_GIMNASIO, "Reintentar gimnasio");
    mostrar_opcion(FINALIZAR_PARTIDA, "Finalizar partida");
    menu_derrota_controller(pedir_tecla(menu_derrota_opcion_valido), juego);
}

/**
 * Recibe una instancia de juego creada y un numero i_menu que representa
 * el indice del menu que se desea mostrar.
 */
void menu_controller(int i_menu, juego_t* juego)
{
    void (*menus[])(juego_t*) = {
        menu_inicio,
        menu_gimnasio,
        menu_batalla,
        menu_victoria,
        menu_derrota
    };

    borde_inferior();
    detener_tiempo(1);
    menus[i_menu](juego);
}

/**
 * Controller requerido por juego.h
 */
int funcion_batalla_controller(int id_funcion, pokemon_t* pokemon_1, pokemon_t* pokemon_2)
{
    if (id_funcion < 1 || id_funcion > 5)
    {
        return 0;
    }

    int (*funcion_batalla[])(void*, void*) = {
        funcion_batalla_1,
        funcion_batalla_2,
        funcion_batalla_3,
        funcion_batalla_4,
        funcion_batalla_5
    };

    return funcion_batalla[id_funcion - 1](pokemon_1, pokemon_2);
}

int main(int argc,char** argv)
{
    juego_t* juego = juego_crear();

    if (!juego)
        return -1;

    menu_inicio(juego);

    juego_liberar(juego);

    return 0;
}
