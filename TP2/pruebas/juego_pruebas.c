#include <stdio.h>
#include "pa2mm_2.h"
#include "../juego.h"

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

void pruebas_entrenador()
{
    nuevo_grupo("Pruebas Entrenador");
    entrenador_t* entrenador = entrenador_crear();
    afirmar(entrenador != NULL, "Puedo crear un entrenador");

    pokemon_t* pokemon = pokemon_crear();
    afirmar(entrenador_agregar_pokemon(entrenador, pokemon) == 0,
            "Puedo agregar un pokemon"
            );

    entrenador_liberar(entrenador);
}

void pruebas_gimnasio();
extern gimnasio_t* gimnasio_crear();
extern void gimnasio_liberar(gimnasio_t*);
extern int gimnasio_agregar_entrenador(gimnasio_t*, entrenador_t*);

void pruebas_gimnasio()
{
    nuevo_grupo("Pruebas Gimnasio");
    gimnasio_t* gimnasio = gimnasio_crear();
    afirmar(gimnasio != NULL, "Puedo crear un gimnasio");

    entrenador_t* entrenador = entrenador_crear();
    afirmar(gimnasio_agregar_entrenador(gimnasio, entrenador) == 0,
            "Puedo agregar un entrenador"
            );

    gimnasio_liberar(gimnasio);
}

void pruebas_juego();
extern juego_t* juego_crear();
extern void juego_liberar(juego_t*);
extern int juego_agregar_gimnasio(juego_t*, gimnasio_t*);

void pruebas_juego()
{
    nuevo_grupo("Pruebas Juego");
    juego_t* juego = juego_crear();
    afirmar(juego != NULL, "Puedo crear un juego");

    gimnasio_t* gimnasio = gimnasio_crear();
    afirmar(juego_agregar_gimnasio(juego, gimnasio) == 0,
            "Puedo agregar un gimnasio"
            );

    juego_liberar(juego);
}

void pruebas_cargas();
extern int cargar_pokemon(FILE*, entrenador_t*);
extern int cargar_entrenador(FILE*, gimnasio_t*);
extern int cargar_gimnasio(FILE*, juego_t*);

const char *ARCHIVO = "datos.tmp",
    *ESCRIBIR = "w",
    *LEER = "r";

void crear_archivo_pokemon()
{
    FILE* archivo = fopen(ARCHIVO, ESCRIBIR);
    if (archivo)
    {
        fprintf(archivo, ";Pikachu;E;E;50;40;60\n");
        fclose(archivo);
    }
}
void crear_archivo_entrenador()
{
    FILE* archivo = fopen(ARCHIVO, ESCRIBIR);
    if (archivo)
    {
        fprintf(archivo, ";Dominguera Diana\n");
        fprintf(archivo, "P;Pikachu;E;E;50;40;60\n");
        fprintf(archivo, "P;Pikachu;E;E;50;40;60\n");
        fclose(archivo);
    }
}
void crear_archivo_gimnasio()
{
    FILE* archivo = fopen(ARCHIVO, ESCRIBIR);
    if (archivo)
    {
        fprintf(archivo, ";Gimnasio Azul;1;1\n");
        fprintf(archivo, "L;Dominguera Diana\n");
        fprintf(archivo, "P;Pikachu;E;E;50;40;60\n");
        fprintf(archivo, "P;Pikachu;E;E;50;40;60\n");
        fclose(archivo);
    }
}
void crear_archivo_gimnasios()
{
    FILE* archivo = fopen(ARCHIVO, ESCRIBIR);
    if (archivo)
    {
        fprintf(archivo, "G;Gimnasio Azul;1;1\n");
        fprintf(archivo, "L;Dominguera Diana\n");
        fprintf(archivo, "P;Pikachu;E;E;50;40;60\n");
        fprintf(archivo, "P;Pikachu;E;E;50;40;60\n");
        fprintf(archivo, "E;Dominguera Diana\n");
        fprintf(archivo, "P;Pikachu;E;E;50;40;60\n");
        fprintf(archivo, "P;Pikachu;E;E;50;40;60\n");
        fclose(archivo);
    }
}

void pruebas_cargas()
{
    nuevo_grupo("Cargas");
    juego_t* juego = juego_crear();
    FILE* archivo = NULL;
    
    afirmar(cargar_gimnasios("", juego) == -1,
            "Cargar gimnasios sin un archivo devuelve -1"
            );
    afirmar(cargar_gimnasios("datos_jugador.txt", juego) == -1,
            "Cargar gimnasios de un archivo no valido devuelve -1"
            );

    crear_archivo_pokemon();
    entrenador_t* entrenador = entrenador_crear();
    archivo = fopen(ARCHIVO, LEER);
    afirmar(cargar_pokemon(archivo, entrenador) == 0,
            "Puedo cargar un pokemon desde un archivo"
            );
    fclose(archivo);
    entrenador_liberar(entrenador);

    crear_archivo_entrenador();
    gimnasio_t* gimnasio = gimnasio_crear();
    archivo = fopen(ARCHIVO, LEER);
    afirmar(cargar_entrenador(archivo, gimnasio) == 0,
            "Puedo cargar un entrenador desde un archivo"
            );
    fclose(archivo);
    gimnasio_liberar(gimnasio);

    crear_archivo_gimnasio();
    archivo = fopen(ARCHIVO, LEER);
    afirmar(cargar_gimnasio(archivo, juego) == 0,
            "Puedo cargar un gimnasio desde un archivo"
            );
    fclose(archivo);

    crear_archivo_gimnasios();
    afirmar(cargar_gimnasios(ARCHIVO, juego) == 0,
            "Cargar gimnasios desde un archivo valido devuelve 0"
            );

    remove(ARCHIVO);
    juego_liberar(juego);
}

void ejecutar_pruebas()
{
    pruebas_pokemon();
    pruebas_entrenador();
    pruebas_gimnasio();
    pruebas_juego();
    pruebas_cargas();
}

int main()
{
    ejecutar_pruebas();
    mostrar_reporte();
    return 0;
}
