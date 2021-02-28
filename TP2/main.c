#include "juego.h"
#include "menu.h"
#include "batallas.h"

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
