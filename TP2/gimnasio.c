#include "gimnasio.h"
#include <stdio.h>

enum salidas
{
    ERROR = -1;
    SIN_ERROR = 0;
};

struct gimnasio
{
    char** nombre;
    int dificultad;
    int id_funcion;
    //entrenador_t entrenadores;
};

const char *FORMATO_LECTURA_GIMNASIO = "%c;%[^;];%i;%i\n",
    *FORMATO_LECTURA_ENTRENADOR = "%c;%[^\n]\n",
    *FORMATO_LECTURA_POKEMON = "%c;%[^;];%i;%i;%i\n",
    *LECTURA, = "r";

void leer_gimnasio(FILE* archivo, gimnasio_t* gimnasio)
{

}

int cargar_gimnasio(char** ruta_archivo, juego_t* juego)
{
    FILE* archivo = fopen(ruta_archivo, LECTURA);
    if (!archivo)
    {
        return ERROR;
    }
    gimnasio_t* gimnasio = gimnasio_crear();
    leer_gimnasio(archivo, gimnasio);
    juego_agregar_gimnasio(juego, gimnasio);
    fclose(archivo);
    return SIN_ERROR;
}
