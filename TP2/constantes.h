#ifndef __CONST_H__
#define __CONST_H__

// Generales
#define ERROR -1
#define SIN_ERROR 0 
#define LECTURA "r"
#define ESCRITURA "w"

// Estructuras del juego
#define GIMNASIO 'G'
#define GIMNASIO_FORMATO_LECTURA ";%64[^;];%3i;%3lu\n"
#define GIMNASIO_ATTR_LEIDOS 3
#define LIDER 'L'
#define ENTRENADOR 'E'
#define ENTRENADOR_FORMATO_LECTURA ";%64[^\n]\n"
#define ENTRENADOR_ATTR_LEIDOS 1
#define POKEMON 'P'
#define POKEMON_FORMATO_LECTURA ";%64[^;];%c;%c;%3i;%3i;%3i\n"
#define POKEMON_ATTR_LEIDOS 6

#endif /*__CONST_H__*/
