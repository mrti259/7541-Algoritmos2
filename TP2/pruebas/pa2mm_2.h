/*
variante de pa2mm.h con nombres mas simples.
corrección de mensaje de salida final.
*/

#ifndef __PA2M_2_H_
#define __PA2M_2_H_

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

#define BLANCO "\x1B[37;1m"
#define VERDE "\x1B[32;1m"
#define ROJO "\x1B[31;1m"
#define AMARILLO "\x1B[33;1m"
#define NORMAL "\x1B[0m"

#define TILDE "✓"
#define CRUZ "✗"

int __pruebas_corridas = 0;
int __pruebas_fallidas = 0;
const char* __prueba_actual = NULL;

void __atajarse(void (*handler)(int)){
    signal(SIGABRT, handler);
    signal(SIGSEGV, handler);
    signal(SIGBUS, handler);
    signal(SIGILL, handler);
    signal(SIGFPE, handler);
}

void __morir(int signum){
    if(__prueba_actual)
        printf(ROJO "\n\nERROR MIENTRAS SE EJECUTABA LA PRUEBA: " AMARILLO "'%s'\n\n" NORMAL, __prueba_actual);
    else printf(ROJO "\n\nFINALIZACION ANORMAL DE LAS PRUEBAS\n\n" NORMAL);
    fflush(stdout);
    __atajarse(SIG_DFL);
}

#define afirmar(afirmacion, descripcion) do {\
        __prueba_actual = descripcion;\
        __atajarse(__morir);\
        if (afirmacion) {\
            printf( VERDE TILDE " ");\
        } else {\
            __pruebas_fallidas++;\
            printf( ROJO CRUZ " ");\
        }\
        printf(BLANCO "%s\n" NORMAL, __prueba_actual);\
        fflush(stdout);\
        __prueba_actual = NULL;\
        __pruebas_corridas++;\
    }while(0);

void nuevo_grupo(const char* descripcion){
    printf(AMARILLO "\n%s\n", descripcion);
    while(*(descripcion++)) printf("=");
    printf(BLANCO "\n" NORMAL);
}

int mostrar_reporte() {
    printf(BLANCO "\n---------------------------------\n"
                 "%i pruebas corridas, %i error%s - %s\n" NORMAL,
                 __pruebas_corridas,
                 __pruebas_fallidas,
                 __pruebas_fallidas == 1 ? "" : "es",
                 __pruebas_fallidas == 0 ? "OK" : "D:");
    return __pruebas_fallidas;
}

#endif // __PA2M_H_
