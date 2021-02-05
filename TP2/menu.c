#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define INPUT "-> "

void correr_menu(int n);

int main(int argc,char** argv) {
    if (argc != 2)
    {
        printf("Ingresa un numero la proxima que llames!!");
        return 0;
    }
    correr_menu(atoi(argv[1]));
    return 0;
}

/**
 * Pide un caracter por pantalla. Debe recibir una función que valide el dato
 * ingresado. Retorna una de las opciones válidas.
 *
 */
char ingresar_caracter(bool es_valido(char))
{
    // Se ingresa un caracter por pantalla.
    printf(INPUT);
    char opcion = (char) getchar();

    // Repite hasta tener un caracter válido.
    while (!es_valido(opcion))
    {
        // Se descartan los caracteres que hayan quedado en el buffer.
        while(getchar() != 10);
        printf(INPUT);
        opcion = (char) getchar(); 
    }
    
    return opcion;
}

enum menu_inicio_opciones {MIO1='E', MIO2='A', MIO3='I', MIO4='S'};

bool menu_inicio_opcion_valido(char opcion)
{
    switch (opcion)
    {
        case MIO1:
        case MIO2:
        case MIO3:
        case MIO4:
            return true;
        default:
            return false;
    }
}

void menu_inicio_accionar(char opcion)
{
    switch (opcion)
    {
        case MIO1:
	    //ver_personaje
            return;
        case MIO2:
	    //agergar_gimnasio
            return;
        case MIO3:
	    //comenzar_partida
            return;
        case MIO4:
	    //simular_partida
            return;
        default:
	    //repetir_accion
            return;
    }
}

void menu_inicio()
{
    printf("¿Que desea hacer?\n");
    printf("%c - Ver mi personaje\n", MIO1);
    printf("%c - Agregar gimnasios\n", MIO2);
    printf("%c - Comenzar la partida\n", MIO3);
    printf("%c - Simular la partida\n", MIO4);
    char opcion = ingresar_caracter(menu_inicio_opcion_valido);
    menu_inicio_accionar(opcion);
}

enum menu_gimnasio_opciones {MGO1='E', MGO2='G', MGO3='C', MGO4='B', MGOE1 = 'V', MGOE2 = 'F'};

bool menu_gimnasio_opcion_valido(char opcion)
{
    switch (opcion)
    {
        case MGO1:
        case MGO2:
        case MGO3:
        case MGO4:
            return true;
        default:
            return false;
    }
}

bool menu_gimnasio_opcion_valido_extras(char opcion)
{
    switch(opcion)
    {
        case MGOE1:
        case MGOE2:
            return true;
        default:
            return menu_gimnasio_opcion_valido;
    }
}

void menu_gimnasio_accionar(char opcion)
{
    switch(opcion)
    {
        case MGO1:
            return;
        case MGO2:
            return;
        case MGO3:
            return;
        case MGO4:
            return;
        case MGOE1:
            return;
        case MGOE2:
            return;
        default:
            return;
    }
}

void menu_gimnasio()
{
    printf("¿Que desea hacer?\n");
    printf("%c - Ver mi equipo\n", MGO1);
    printf("%c - Ver información del gimnasio actual\n", MGO2);
    printf("%c - Cambiar equipo\n", MGO3);
    printf("%c - Pelear!\n", MGO4);

    // if hay medallas, mostrar
    printf("%c - Mis victorias :D \n", MGOE1);

    // if hay derrotas, mostrar
    printf("%c - Mis derrotas :( \n", MGOE2);

    char opcion = ingresar_caracter(menu_gimnasio_opcion_valido);
    menu_gimnasio_accionar(opcion);
}

enum menu_batalla_opciones { MBO1='N' };

bool menu_batalla_opcion_valido(char opcion)
{
    switch (opcion)
    {
        case MBO1:
            return true;
        default:
            return false;
    }
}

void menu_batalla_accionar(char opcion)
{
    switch (opcion)
    {
        case MBO1:
            return;
        default:
            return;
    }
}

void menu_batalla()
{
    // TODO: mostrar informacion de batalla
    printf("¿Que desea hacer?\n");
    printf("%c - Pelear!\n", MBO1);
    char opcion = ingresar_caracter(menu_batalla_opcion_valido);
    menu_batalla_accionar(opcion);
}

enum menu_victoria_opciones {MVO1='T', MVO2='C', MVO3='N'};

bool menu_victoria_opcion_valido(char opcion)
{
    switch (opcion)
    {
        case MVO1:
        case MVO2:
        case MVO3:
            return true;
        default:
            return false;
    }
}

void menu_victoria_accionar(char opcion)
{
    switch (opcion)
    {
        case MVO1:
	    //pedir pokemon
            return;
        case MVO2:
	    //cambiar pokemon
            return;
        case MVO3:
	    //proximo gimnasio
            return;
        default:
            return;
    }
}

void menu_victoria()
{
    printf("¿Que desea hacer?\n");
    printf("%c - Pedir Pokemon\n", MVO1);
    printf("%c - Cambiar Pokemon\n", MVO2);
    printf("%c - Ir al próximo gimnasio\n", MVO3);
    char opcion = ingresar_caracter(menu_victoria_opcion_valido);
    menu_victoria_accionar(opcion);
}

enum menu_derrota_opciones {MDO1='C', MDO2='R', MDO3='F'};

bool menu_derrota_opcion_valido(char opcion)
{
    switch (opcion)
    {
        case MDO1:
        case MDO2:
        case MDO3:
            return true;
        default:
            return false;
    }
}

void menu_derrota_accionar(char opcion)
{
    switch (opcion)
    {
        case MDO1:
		//cabmiar equipo
            return;
        case MDO2:
	    //reintentargimnasio
            return;
        case MDO3:
	    //finalizar partida
            return;
        default:
            return;
    }
}

void menu_derrota()
{
    printf("¿Que desea hacer?\n");
    printf("%c - Cambiar mi equipo\n", MDO1);
    printf("%c - Reintentar gimnasio\n", MDO2);
    printf("%c - Finalizar partida\n", MDO3);
    char opcion = ingresar_caracter(menu_derrota_opcion_valido);
    menu_derrota_accionar(opcion);
}

void correr_menu(int n)
{
    void (*menus[])() = {
        menu_inicio,
        menu_gimnasio,
        menu_batalla,
        menu_victoria,
        menu_derrota
    };
    menus[n]();
}
