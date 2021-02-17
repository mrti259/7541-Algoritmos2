#include <stdio.h>
#include "pa2mm_2.h"
#include "../juego.h"

const char *ARCHIVO = "datos.tmp",
    *ESCRIBIR = "w",
    *LEER = "r";

void pruebas_pokemon();
extern pokemon_t* pokemon_crear();
extern void pokemon_liberar(pokemon_t*);

void pruebas_pokemon()
{
    nuevo_grupo("Pruebas Pokemon");
    pokemon_t* pokemon = pokemon_crear();
    afirmar(pokemon != NULL, "Puedo crear un pokemon");
    
    pokemon_liberar(pokemon);
}

void pruebas_entrenador();
extern entrenador_t* entrenador_crear();
extern void entrenador_liberar(entrenador_t*);
extern int entrenador_agregar_pokemon(entrenador_t*, pokemon_t*);
extern int cargar_pokemon(FILE*, entrenador_t*);

void crear_archivo_pokemon()
{
    FILE* archivo = fopen(ARCHIVO, ESCRIBIR);
    if (archivo)
    {
        fprintf(archivo, ";Goldeen;A;A;40;50;30\n");
        fclose(archivo);
    }
}

void pruebas_entrenador()
{
    nuevo_grupo("Pruebas Entrenador");
    entrenador_t* entrenador = entrenador_crear();
    afirmar(entrenador != NULL, "Puedo crear un entrenador");

    pokemon_t* pokemon = pokemon_crear();
    afirmar(entrenador_agregar_pokemon(entrenador, pokemon) == 0,
            "Puedo agregar un pokemon"
            );

    crear_archivo_pokemon();
    FILE* archivo = fopen(ARCHIVO, LEER);
    afirmar(cargar_pokemon(archivo, entrenador) == 0,
            "Cargar un pokemon desde un archivo valido devuelve 0"
            );
    afirmar(cargar_pokemon(archivo, entrenador) == -1,
            "Si no puede cargar un pokemon devuelve -1"
            );
    fclose(archivo);
    remove(ARCHIVO);

    entrenador_liberar(entrenador);
}

void pruebas_gimnasio();
extern gimnasio_t* gimnasio_crear();
extern void gimnasio_liberar(gimnasio_t*);
extern int gimnasio_agregar_entrenador(gimnasio_t*, entrenador_t*);
extern int cargar_entrenador(FILE*, gimnasio_t*);

void crear_archivo_entrenador()
{
    FILE* archivo = fopen(ARCHIVO, ESCRIBIR);
    if (archivo)
    {
        fprintf(archivo, ";Dominguera Diana\n");
        fprintf(archivo, "P;Goldeen;A;A;40;50;30\n");
        fclose(archivo);
    }
}

void pruebas_gimnasio()
{
    nuevo_grupo("Pruebas Gimnasio");
    gimnasio_t* gimnasio = gimnasio_crear();
    afirmar(gimnasio != NULL, "Puedo crear un gimnasio");

    entrenador_t* entrenador = entrenador_crear();
    afirmar(gimnasio_agregar_entrenador(gimnasio, entrenador) == 0,
            "Puedo agregar un entrenador"
            );

    crear_archivo_entrenador();
    FILE* archivo = fopen(ARCHIVO, LEER);
    afirmar(cargar_entrenador(archivo, gimnasio) == 0,
            "Cargar un entrenador desde un archivo valido devuelve 0"
            );
    afirmar(cargar_entrenador(archivo, gimnasio) == -1,
            "Si no puede cargar un entrenador devuelve -1"
            );
    fclose(archivo);
    remove(ARCHIVO);

    gimnasio_liberar(gimnasio);
}

void pruebas_juego();
extern juego_t* juego_crear();
extern void juego_liberar(juego_t*);
extern int juego_agregar_gimnasio(juego_t*, gimnasio_t*);
extern int cargar_gimnasio(FILE*, juego_t*);

void crear_archivo_gimnasio()
{
    FILE* archivo = fopen(ARCHIVO, ESCRIBIR);
    if (archivo)
    {
        fprintf(archivo, ";Gimnasio de Ciudad Celeste;15;3\n");
        fprintf(archivo, "L;Misty\n");
        fprintf(archivo, "P;Staryu;A;A;50;40;50\n");
        fprintf(archivo, "P;Starmie;A;A;90;50;60\n");
        fprintf(archivo, "E;Dominguera Diana\n");
        fprintf(archivo, "P;Goldeen;A;A;40;50;30\n");
        fprintf(archivo, "E;Nadador Luis\n");
        fprintf(archivo, "P;Horsea;A;A;45;30;20\n");
        fprintf(archivo, "P;Shellder;A;A;30;20;45\n");
        fclose(archivo);
    }
}

void crear_archivo_gimnasios()
{
    FILE* archivo = fopen(ARCHIVO, ESCRIBIR);
    if (archivo)
    {
        fprintf(archivo, "G;Gimnasio de Ciudad Celeste;15;3\n");
        fprintf(archivo, "L;Misty\n");
        fprintf(archivo, "P;Staryu;A;A;50;40;50\n");
        fprintf(archivo, "P;Starmie;A;A;90;50;60\n");
        fprintf(archivo, "E;Dominguera Diana\n");
        fprintf(archivo, "P;Goldeen;A;A;40;50;30\n");
        fprintf(archivo, "E;Nadador Luis\n");
        fprintf(archivo, "P;Horsea;A;A;45;30;20\n");
        fprintf(archivo, "P;Shellder;A;A;30;20;45\n");

        fprintf(archivo, "G;Gimnasio de Ciudad Celeste;15;3\n");
        fprintf(archivo, "L;Misty\n");
        fprintf(archivo, "P;Staryu;A;A;50;40;50\n");
        fprintf(archivo, "P;Starmie;A;A;90;50;60\n");
        fprintf(archivo, "E;Dominguera Diana\n");
        fprintf(archivo, "P;Goldeen;A;A;40;50;30\n");
        fprintf(archivo, "E;Nadador Luis\n");
        fprintf(archivo, "P;Horsea;A;A;45;30;20\n");
        fprintf(archivo, "P;Shellder;A;A;30;20;45\n");
        fclose(archivo);
    }
}

void crear_archivo_jugador()
{
    FILE* archivo = fopen(ARCHIVO, ESCRIBIR);
    if (archivo)
    {
        fprintf(archivo, "E;Ash\n");
        fprintf(archivo, "P;Pikachu;E;E;70;30;30\n");
        fprintf(archivo, "P;Butterfree;B;V;50;40;50\n");
        fprintf(archivo, "P;Pidgeotto;V;N;65;40;30\n");
        fprintf(archivo, "P;Bulbasaur;P;P;20;40;30\n");
        fprintf(archivo, "P;Charmander;F;F;40;30;20\n");
        fprintf(archivo, "P;SquirtleA;A;30;20;40\n");
        fprintf(archivo, "P;Krabby;A;A;20;30;20\n");
        fprintf(archivo, "P;Raticate;N;N;30;50;20\n");
        fprintf(archivo, "P;Haunter;G;G;40;60;20\n");
        fprintf(archivo, "P;Primeape;L;N;50;60;30\n");
        fprintf(archivo, "P;Muk;T;T;20;40;60\n");
        fclose(archivo);
    }
}

void pruebas_juego()
{
    nuevo_grupo("Pruebas Juego");
    juego_t* juego = juego_crear();
    afirmar(juego != NULL, "Puedo crear un juego");

    gimnasio_t* gimnasio = gimnasio_crear();
    afirmar(juego_agregar_gimnasio(juego, gimnasio) == 0,
            "Puedo agregar un gimnasio"
            );

    crear_archivo_gimnasio();
    FILE* archivo = fopen(ARCHIVO, LEER);
    afirmar(cargar_gimnasio(archivo, juego) == 0,
            "Cargar un gimnasio desde un archivo valido devuelve 0"
            );
    afirmar(cargar_gimnasio(archivo, juego) == -1,
            "Si no puedo cargar un gimnasio devuelve -1"
            );
    fclose(archivo);

    crear_archivo_gimnasios();
    afirmar(cargar_gimnasios(ARCHIVO, juego) == 0,
            "Cargar gimnasios desde un archivo valido devuelve 0"
            );

    remove(ARCHIVO);
    afirmar(cargar_gimnasios(ARCHIVO, juego) == -1,
            "Cargar gimnasios sin un archivo devuelve -1"
            );

    crear_archivo_jugador();
    afirmar(cargar_gimnasios(ARCHIVO, juego) == -1,
            "Cargar gimnasios de un archivo no valido devuelve -1"
            );

    afirmar(cargar_jugador(ARCHIVO, juego) == 0,
            "Cargar un jugador principal desde un archivo valido devuelve 0"
           );

    remove(ARCHIVO);
    afirmar(cargar_jugador(ARCHIVO, juego) == -1,
            "Cargar un jugador principal desde un archivo no valido devuelve -1"
           );

    juego_liberar(juego);
}

void pruebas_batallas()
{
    nuevo_grupo("Pruebas batallas");

    afirmar(0,
            ""
           );
    afirmar(0,
            ""
            );
    afirmar(0,
            ""
           );
    afirmar(0,
            ""
           );
    afirmar(0,
            ""
            );
    afirmar(0,
            ""
           );
}

void ejecutar_pruebas()
{
    pruebas_pokemon();
    pruebas_entrenador();
    pruebas_gimnasio();
    pruebas_juego();
    pruebas_batallas();
}

int main()
{
    ejecutar_pruebas();
    mostrar_reporte();
    return 0;
}
