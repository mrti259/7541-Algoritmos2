#include "pa2mm_2.h"
#include "../juego.c"
#include "../batallas.h"
#include <stdio.h>
#include <string.h>

const char *ARCHIVO = "datos.tmp", *ESCRIBIR = "w", *LEER = "r";

/**
 * Pruebas de Pokémon.
 * Si se crea correctamente, se setean sus valores y se verifica que sus
 * funciones devuelvan los valores correctos.
 *
 * No deben haber perdidas de memoria.
 */
void pruebas_pokemon()
{
    nuevo_grupo("Pruebas Pokémon");
    pokemon_t* pokemon = pokemon_crear();
    afirmar(pokemon != NULL, "Puedo crear un pokemon");

    if (pokemon)
    {
        pokemon->ataque = 30;
        pokemon->defensa = 20;
        pokemon->velocidad = 40;
        pokemon->adicional = 62;
        pokemon->tipo_1 = 'A';
        pokemon->tipo_2 = 'B';
        strcpy(pokemon->nombre, "Dewpider");
    }
    afirmar(pokemon_ataque(pokemon) == 92, "Tiene 92 de ataque");
    afirmar(pokemon_defensa(pokemon) == 82, "Tiene 82 de defensa");
    afirmar(pokemon_velocidad(pokemon) == 102, "Tiene 102 de velocidad");
    afirmar(pokemon_puede_subir_estadisticas(pokemon), "Puede subir estadisticas");
    afirmar(pokemon_subir_estadisticas(pokemon) == SIN_ERROR, "Sube estadisticas");
    afirmar(!pokemon_puede_subir_estadisticas(pokemon), "No puede subir más");
    afirmar(pokemon_ataque(pokemon) == 93, "Tiene 93 de ataque");
    afirmar(pokemon_defensa(pokemon) == 83, "Tiene 83 de defensa");
    afirmar(pokemon_velocidad(pokemon) == 103, "Tiene 103 de velocidad");
    afirmar(pokemon_tipo_principal(pokemon) == 'A', "El tipo principal es AGUA");
    afirmar(pokemon_tipo_secundario(pokemon) == 'B', "El tipo secundario es BICHO");

    char nombre[MAX_NOMBRE];
    pokemon_nombre(pokemon, nombre);
    afirmar(strcmp("Dewpider", nombre) == 0, "Es un Dewpider");

    pokemon_liberar(pokemon);
}

/**
 * Crea un archivo temporal con un registro de un Pokémon. 
 */
void crear_archivo_pokemon()
{
    FILE* archivo = fopen(ARCHIVO, ESCRIBIR);
    if (archivo)
    {
        fprintf(archivo, ";Goldeen;A;A;40;50;30\n");
        fclose(archivo);
    }
}

/**
 * Crea un archivo temporal con un registro de un Pokémon dañado. 
 */
void crear_archivo_pokemon_daniado()
{
    FILE* archivo = fopen(ARCHIVO, ESCRIBIR);
    if (archivo)
    {
        fprintf(archivo, ";Goldeesdasdasdasdasdasjdhasdhaskjdfhlksahdlkjfsajdkfjakshdkjsahdklashdjkashdlkasjhdkjlshdklahsjdlkahjsdakjsdhalkdhsakjshdaklhsdkajshdkalhsdklahsdklahsdkjahsdkjlhsadlkahsdkajksadhflhasdn;A;A;40;50;30\n");
        fclose(archivo);
    }
}

/**
 * Pruebas de entrenador.
 * Puedo crear un entrenador y cargarle un Pokémon desde un registro.
 *
 * No deben haber perdidas de memoria.
 */
void pruebas_entrenador()
{
    nuevo_grupo("Pruebas Entrenador");
    entrenador_t* entrenador = entrenador_crear();
    afirmar(entrenador != NULL, "Puedo crear un entrenador");

    pokemon_t* pokemon = pokemon_crear();
    afirmar(agregar_pokemon(entrenador, pokemon) == 0,
            "Puedo agregar un pokemon"
           );

    crear_archivo_pokemon();
    FILE* archivo = fopen(ARCHIVO, LEER);
    afirmar(cargar_pokemon(archivo, entrenador) == 0,
            "Cargar un pokemon desde un archivo válido devuelve 0"
           );
    afirmar(cargar_pokemon(archivo, entrenador) == -1,
            "Si no puede cargar un pokemon devuelve -1"
           );
    fclose(archivo);

    crear_archivo_pokemon_daniado();
    archivo = fopen(ARCHIVO, LEER);
    afirmar(cargar_pokemon(archivo, entrenador) == -1,
            "Cargar un pokemon desde un archivo dañado devuelve -1"
           );
    fclose(archivo);
    remove(ARCHIVO);

    entrenador_liberar(entrenador);
}

/**
 * Crea un archivo temporal con un registro de un entrenador y sus Pokémon.
 */
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
/**
 * Crea un archivo temporal con un registro de un entrenador dañado.
 */
void crear_archivo_entrenador_daniado()
{
    FILE* archivo = fopen(ARCHIVO, ESCRIBIR);
    if (archivo)
    {
        fprintf(archivo, ";Dominguera Dianasdkjashdajksdhjakshdjkashdjlkahsdkjlahsdkljahsdjkhasdkjhaskdlhakljsdhakjsdhalkhdsaklsjhdakjshdlkhsdkalhjsdkajshdlkahdjsajkhdskjashdkajshdlkahsdkalhdsaklhdjakjhdsakjshdakhjsdakjshdakjshdakjhsdaklhsdakhsdkjas\n");
        fprintf(archivo, "P;Goldeen;A;A;40;50;30\n");
        fclose(archivo);
    }
}

/**
 * Pruebas de gimnasio.
 * Puedo crear un gimnasio y cargarle entrenadores y Pokémon desde un archivo.
 *
 * No deben haber perdidas de memoria.
 */
void pruebas_gimnasio()
{
    nuevo_grupo("Pruebas Gimnasio");
    gimnasio_t* gimnasio = gimnasio_crear();
    afirmar(gimnasio != NULL, "Puedo crear un gimnasio");

    entrenador_t* entrenador = entrenador_crear();
    afirmar(agregar_entrenador(gimnasio, entrenador) == 0,
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

    crear_archivo_entrenador_daniado();
    archivo = fopen(ARCHIVO, LEER);
    afirmar(cargar_entrenador(archivo, gimnasio) == -1,
            "Cargar un entrenador desde un archivo dañado devuelve -1"
           );
    fclose(archivo);
    remove(ARCHIVO);

    afirmar(lista_elementos(gimnasio->entrenadores) == 2,
            "Hay 2 entrenadores"
           );

    gimnasio_liberar(gimnasio);
}

/**
 * Crea un archivo temporal con un registro de un gimnasio y sus entrenadores.
 */
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

/**
 * Crea un archivo temporal con un registro de un gimnasio dañado.
 */
void crear_archivo_gimnasio_daniado()
{
    FILE* archivo = fopen(ARCHIVO, ESCRIBIR);
    if (archivo)
    {
        fprintf(archivo, ";Gimnasio de Ciudad Celsdjkahsdjkashdjkashdkjlshadjklashdjkahsdkjlahsdkljashdjkashdkjashdkjladkjashdkahsdklhsadjahsdkjahsdklahsdlkjhasdkhaskdhakdslhaksdjhaksjdhakjsdhakjshdkahsdkahdalkjshdaklhdsakjshdkalhdsakeste;15;3\n");
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

/**
 * Crea un archivo temporal con más de un registro de gimnasios
 */
void crear_archivo_gimnasios()
{
    FILE* archivo = fopen(ARCHIVO, ESCRIBIR);
    if (archivo)
    {
        fprintf(archivo, "G;Gimnasio de Ciudad Carmín;9;1\n");
        fprintf(archivo, "L;Lt. Surge\n");
        fprintf(archivo, "P;Voltorb;E;E;50;40;50\n");
        fprintf(archivo, "P;Pikachu;E;E;90;50;60\n");
        fprintf(archivo, "P;Raichu;E;E;90;50;60\n");
        fprintf(archivo, "E;Marinero Dimas\n");
        fprintf(archivo, "P;Pikachu;E;E;40;50;30\n");
        fprintf(archivo, "P;Pikachu;E;E;40;50;30\n");
        fprintf(archivo, "E;Mecanico Manolo\n");
        fprintf(archivo, "P;Voltorb;E;E;45;30;20\n");
        fprintf(archivo, "P;Magnamite;E;I;30;20;45\n");
        fprintf(archivo, "E;Caballero Tito\n");
        fprintf(archivo, "P;Pikachu;E;E;45;30;20\n");

        fprintf(archivo, "G;Gimnasio de Ciudad Verde;45;3\n");
        fprintf(archivo, "L;Giovanni\n");
        fprintf(archivo, "P;Rhyhorn;S;R;50;40;50\n");
        fprintf(archivo, "P;Dugtrio;T;S;90;50;60\n");
        fprintf(archivo, "P;Nidoking;T;S;90;50;60\n");
        fprintf(archivo, "P;Nidoqueen;T;S;90;50;60\n");
        fprintf(archivo, "P;Rhyhorn;S;R;90;50;60\n");
        fprintf(archivo, "E;Entrenador Guay Yuji\n"); 
        fprintf(archivo, "P;Sandlash;S;S;40;50;30\n");
        fprintf(archivo, "P;Graveler;S;S;40;50;30\n");
        fprintf(archivo, "P;Onix;S;S;40;50;30\n");
        fprintf(archivo, "P;Graveler;S;S;40;50;30\n");
        fprintf(archivo, "P;Marowak;S;S;40;50;30\n");

        fprintf(archivo, "G;Gimnasio de Ciudad Plateada;4;2\n");
        fprintf(archivo, "L;Brock\n");
        fprintf(archivo, "P;Geodude;R;S;50;40;50\n");
        fprintf(archivo, "P;Onix;R;S;50;50;60\n");
        fprintf(archivo, "E;Campista Angelito\n");
        fprintf(archivo, "P;Godude;R;S;40;50;30\n");
        fprintf(archivo, "P;Sandshrew;R;S;45;30;20\n");

        fprintf(archivo, "G;Gimnasio de Ciudad Celeste;15;4\n");
        fprintf(archivo, "P;Shellder;A;A;30;20;45\n");
        fclose(archivo);
    }
}

/**
 * Crea un archivo temporal con datos de un jugador.
 */ 
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

/**
 * Crea un archivo temporal con datos de un jugador dañado.
 */ 
void crear_archivo_jugador_daniado()
{
    FILE* archivo = fopen(ARCHIVO, ESCRIBIR);
    if (archivo)
    {
        fprintf(archivo, "E;Ash\n");
        fprintf(archivo, "P;Pikachu;E;E;12312370;31231231230;312312310\n");
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

/**
 * Pruebas de juego.
 * Crea un juego, carga los archivos de gimnasios y personaje que un jugador
 * pueda ingresar.
 */
void pruebas_juego()
{
    nuevo_grupo("Pruebas Juego");
    juego_t* juego = juego_crear();
    afirmar(juego != NULL, "Puedo crear un juego");

    gimnasio_t* gimnasio = gimnasio_crear();
    afirmar(agregar_gimnasio(juego, gimnasio) == 0,
            "Puedo agregar un gimnasio"
           );
    afirmar(juego_gimnasios(juego) == 1,
            "Tengo un gimnasio cargado"
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
    afirmar(juego_gimnasios(juego) == 2,
            "Cargué 2 gimnasios"
           );

    crear_archivo_gimnasio_daniado();
    archivo = fopen(ARCHIVO, LEER);
    afirmar(cargar_gimnasio(archivo, juego) == -1,
            "Cargar un gimnasio desde un archivo dañado devuelve -1"
           );
    fclose(archivo);

    crear_archivo_gimnasios();
    afirmar(cargar_gimnasios(ARCHIVO, juego) == 0,
            "Cargar gimnasios desde un archivo valido aunque dañado devuelve 0"
           );
    afirmar(juego_gimnasios(juego) == 5,
            "Se cuenta con 5 Gimnasios"
           );

    remove(ARCHIVO);
    afirmar(cargar_gimnasios(ARCHIVO, juego) == -1,
            "Cargar gimnasios con un archivo inexistente devuelve -1"
           );
    afirmar(cargar_gimnasios("", juego) == -1,
            "Cargar gimnasios sin un archivo devuelve -1"
           );

    crear_archivo_jugador();
    afirmar(cargar_gimnasios(ARCHIVO, juego) == -1,
            "Cargar gimnasios de un archivo no valido devuelve -1"
           );

    afirmar(cargar_jugador(ARCHIVO, juego) == 0,
            "Cargar un jugador principal desde un archivo valido devuelve 0"
           );

    crear_archivo_gimnasio();
    afirmar(cargar_jugador(ARCHIVO, juego) == -1,
            "Cargar un jugador principal desde un archivo no valido devuelve -1"
           );

    crear_archivo_jugador_daniado();
    afirmar(cargar_jugador(ARCHIVO, juego) == -1,
            "Cargar un jugador principal desde un archivo dañado devuelve -1"
           );

    remove(ARCHIVO);
    afirmar(cargar_jugador(ARCHIVO, juego) == -1,
            "Cargar un jugador principal con un archivo inexistente devuelve -1"
           );
    afirmar(cargar_jugador("", juego) == -1,
            "Cargar un jugador principal sin un archivo devuelve -1"
           );

    afirmar(descartar_gimnasio(juego) == 0,
            "Puedo eliminar un gimnasio"
           );
    afirmar(juego_gimnasios(juego) == 4,
            "Ahora hay 4 gimnasios"
           );

    char str[MAX_NOMBRE];
    gimnasio = gimnasio_actual(juego);
    entrenador_t* entrenador = rival_actual(juego);
    pokemon_t* pokemon = pokemon_enemigo(juego);

    gimnasio_nombre(gimnasio, str);
    afirmar(strcmp(str, "Gimnasio de Ciudad Plateada") == 0,
            "El gimnasio actual es el Gimnasio de Ciudad Plateada"
           );
    afirmar(gimnasio_entrenadores(gimnasio) == 2,
            "El gimnasio tiene 2 rivales"
           );

    entrenador_nombre(entrenador, str);
    afirmar(strcmp(str, "Campista Angelito") == 0,
            "El primer rival es el Campista Angelito"
           );
    afirmar(entrenador_pokemon(entrenador) == 2,
            "Tiene 2 Pokémon"
           );

    pokemon_nombre(pokemon, str);
    afirmar(strcmp(str, "Sandshrew") == 0,
            "El primer Pokémon rival es Sandshrew"
           );

    juego_liberar(juego);
}

/**
 * Prueba las funciones de batalla.
 * Se tiene que mantener la constancia del ganador
 */
void pruebas_batallas()
{
    nuevo_grupo("Pruebas batallas");

    pokemon_t *pkm_1 = pokemon_crear(), *pkm_2 = pokemon_crear();
    if (pkm_1 && pkm_2)
    {
        pkm_1->ataque = 20;
        pkm_1->defensa = 26;
        pkm_1->velocidad = 23;
        pkm_1->adicional = 9;
        pkm_1->tipo_1 = 'F';
        pkm_1->tipo_2 = 'V';
        strcpy(pkm_1->nombre, "Charizard");

        pkm_2->ataque = 26;
        pkm_2->defensa = 22;
        pkm_2->velocidad = 20;
        pkm_2->adicional = 0;
        pkm_2->tipo_1 = 'N';
        pkm_2->tipo_2 = 'V';
        strcpy(pkm_2->nombre, "Pidgeotto");
    }

    afirmar(funcion_batalla_1(pkm_1, pkm_2) == GANO_PRIMERO,
            "Funcion batalla 1: Gana primero"
           );
    afirmar(funcion_batalla_1(pkm_2, pkm_1) == GANO_SEGUNDO,
            "Funcion batalla 1: Gana segundo"
           );
    afirmar(funcion_batalla_2(pkm_1, pkm_2) == GANO_PRIMERO,
            "Funcion batalla 2: Gana primero"
           );
    afirmar(funcion_batalla_2(pkm_2, pkm_1) == GANO_SEGUNDO,
            "Funcion batalla 2: Gana segundo"
           );
    afirmar(funcion_batalla_3(pkm_1, pkm_2) == GANO_PRIMERO,
            "Funcion batalla 3: Gana primero"
           );
    afirmar(funcion_batalla_3(pkm_2, pkm_1) == GANO_SEGUNDO,
            "Funcion batalla 3: Gana segundo"
           );
    afirmar(funcion_batalla_4(pkm_1, pkm_2) == GANO_PRIMERO,
            "Funcion batalla 4: Gana primero"
           );
    afirmar(funcion_batalla_4(pkm_2, pkm_1) == GANO_SEGUNDO,
            "Funcion batalla 4: Gana segundo"
           );
    afirmar(funcion_batalla_5(pkm_1, pkm_2) == GANO_PRIMERO,
            "Funcion batalla 5: Gana primero"
           );
    afirmar(funcion_batalla_5(pkm_2, pkm_1) == GANO_SEGUNDO,
            "Funcion batalla 5: Gana segundo"
           );

    pokemon_liberar(pkm_1);
    pokemon_liberar(pkm_2);
}

/**
 * Pruebas de Jugabilidad.
 * Verifica que las funciones que permiten la jugabilidad funcionan correctamente.
 */
void pruebas_jugabilidad()
{
    juego_t* juego = juego_crear();
    crear_archivo_jugador();
    cargar_jugador(ARCHIVO, juego);
    crear_archivo_gimnasios();
    cargar_gimnasios(ARCHIVO, juego);
    remove(ARCHIVO);

    
    
    juego_liberar(juego);
}

void ejecutar_pruebas()
{
    pruebas_pokemon();
    pruebas_entrenador();
    pruebas_gimnasio();
    pruebas_juego();
    pruebas_batallas();
    pruebas_jugabilidad();
}

int main()
{
    ejecutar_pruebas();
    mostrar_reporte();
    return 0;
}
