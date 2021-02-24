#include "batallas.h"
#include "juego.h"
#include "constantes.h"
#include <stdlib.h>
#include <string.h>

/* Caracteres que identifican los tipos de Pokemon */
enum tipos_pokemon
{
    AGUA = 'A' ,
    BICHO = 'B' ,
    ACERO = 'C' ,
    DRAGON = 'D' ,
    ELECTRICO = 'E' ,
    FUEGO = 'F' ,
    FANTASMA = 'G' ,
    HOJA = 'H' ,
    HIELO = 'I',
    LUCHA = 'L' ,
    MAGICO = 'M' ,
    NORMAL = 'N' ,
    SINIESTRO = 'O' ,
    PSIQUICO = 'P' , 
    ROCA = 'R' ,
    TIERRA = 'S' ,
    TOXICO = 'T' ,
    VUELO = 'V'
};

/**
 * Gana el más fuerte.
 */
int funcion_batalla_1(void* pkm_1, void* pkm_2)
{
    pokemon_t *p_1 = pkm_1, *p_2 = pkm_2;

    int ataque_1 = pokemon_ataque(p_1) ,
        defensa_1 = pokemon_defensa(p_1) ,
        velocidad_1 = pokemon_velocidad(p_1) ,
        ataque_2 = pokemon_ataque(p_2) ,
        defensa_2 = pokemon_defensa(p_2) ,
        velocidad_2 = pokemon_velocidad(p_2) ;

    int dmg_1 = ataque_1 - defensa_2 , // daño causado por pkm_1
        dmg_2 = ataque_2 - defensa_1 ; // daño causado por pkm_2

    if (dmg_1 == dmg_2 && (velocidad_1 > velocidad_2))
    {
        return GANO_PRIMERO;
    }

    return  dmg_1 > dmg_2 ? GANO_PRIMERO : GANO_SEGUNDO;
}

/**
 * Gana el más rápido.
 */
int funcion_batalla_2(void* pkm_1, void* pkm_2)
{
    pokemon_t *p_1 = pkm_1, *p_2 = pkm_2;

    int velocidad_1 = pokemon_velocidad(p_1), velocidad_2 = pokemon_velocidad(p_2);

    return velocidad_1 > velocidad_2 ? GANO_PRIMERO : GANO_SEGUNDO;
}

/**
 * Gana el más lindo según el estandar de belleza 60-90-60.
 */
int funcion_batalla_3(void* pkm_1, void* pkm_2)
{
    pokemon_t *p_1 = pkm_1, *p_2 = pkm_2;

    int ataque_1 = pokemon_ataque(p_1) ,
        defensa_1 = pokemon_defensa(p_1) ,
        velocidad_1 = pokemon_velocidad(p_1) ,
        ataque_2 = pokemon_ataque(p_2) ,
        defensa_2 = pokemon_defensa(p_2) ,
        velocidad_2 = pokemon_velocidad(p_2) ;

    int pts_1 = 0;

    int dif_1 = ataque_1 - velocidad_1 ,
        dif_2 = ataque_2 - velocidad_2 ;

    // Gana menor dif entre ataque y velocidad
    if (-dif_2 < dif_1 && dif_1 < dif_2)
    {
        pts_1++;
    }
    // Gana el más gordito -> mayor defensa
    defensa_1 > defensa_2 ? pts_1++ : 0;

    return pts_1 > 0 ? GANO_PRIMERO : GANO_SEGUNDO;
}

/**
 * Devuelve el nivel de rareza de un tipo Pokémon
 */
int rareza(char tipo)
{
    switch (tipo)
    {
        case ELECTRICO:
        case SINIESTRO:
            return 12;
        case FANTASMA:
        case PSIQUICO:
            return 10;
        case DRAGON:
        case MAGICO:
        case TOXICO:
            return 8;
        case ACERO:
        case BICHO:
        case FUEGO:
        case LUCHA:
        case VUELO:
            return 6;
        case AGUA:
        case HOJA:
        case ROCA:
            return 4;
        default:
            return 2;
    }
}

/**
 * Gana el que tenga mayor rareza.
 */
int funcion_batalla_4(void* pkm_1, void* pkm_2)
{
    pokemon_t *p_1 = pkm_1, *p_2 = pkm_2;

    char tipo_1_a = pokemon_tipo_principal(p_1) ,
         tipo_1_b = pokemon_tipo_secundario(p_1) ,
         tipo_2_a = pokemon_tipo_principal(p_2) ,
         tipo_2_b = pokemon_tipo_secundario(p_2) ;

    int rareza_1 = rareza(tipo_1_a) + rareza(tipo_1_b) / 2 ,
        rareza_2 = rareza(tipo_2_a) + rareza(tipo_2_b) / 2 ;

    return rareza_1 > rareza_2 ? GANO_PRIMERO : GANO_SEGUNDO;
}

/**
 * Gana el mejor rapeando.
 */
int funcion_batalla_5(void* pkm_1, void* pkm_2)
{
    pokemon_t *p_1 = pkm_1, *p_2 = pkm_2;

    int pts_1 = 0;

    char nombre_1[MAX_NOMBRE] = "", nombre_2[MAX_NOMBRE] = "";
    pokemon_nombre(p_1, nombre_1);
    pokemon_nombre(p_2, nombre_2);

    // Gana si tiene nombre más corto
    if (strlen(nombre_1) < strlen(nombre_2))
    {
        pts_1++;
    }

    // Gana si tiene buen flow
    if (pokemon_velocidad(p_1) > pokemon_velocidad(p_2))
    {
        pts_1++;
    }

    // Gana si resiste los beef de su oponente
    if (pokemon_defensa(p_1) > pokemon_ataque(p_2))
    {
        pts_1++;
    }

    // Gana si humilla a su oponente
    if (pokemon_ataque(p_1) > pokemon_defensa(p_2))
    {
        pts_1++;
    }

    return pts_1 > 2 ? GANO_PRIMERO : GANO_SEGUNDO;
}
