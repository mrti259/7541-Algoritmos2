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
    afirmar(!pokemon->en_party, "Tengo un Pokémon libre");
    afirmar(entrenador_agregar_pokemon(entrenador, pokemon) == 0,
            "Puedo agregar un pokemon"
           );
    afirmar(pokemon->en_party, "El Pokémon está en el Party");

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

    afirmar(entrenador_pokemon(entrenador) == 2,
            "El entrenador tiene 2 Pokémon en total"
           );
    afirmar(entrenador_party(entrenador) == 2,
            "Tiene 2 Pokémon en el party"
           );

    for (int i = 0; i < 10; i++)
        entrenador_agregar_pokemon(entrenador, pokemon_crear());

    afirmar(entrenador_pokemon(entrenador) == 12,
            "Ahora tiene 12 Pokémon en total");
    afirmar(entrenador_party(entrenador) == 6,
            "Tiene 6 Pokémon en el party"
           );

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

    crear_archivo_entrenador_daniado();
    archivo = fopen(ARCHIVO, LEER);
    afirmar(cargar_entrenador(archivo, gimnasio) == -1,
            "Cargar un entrenador desde un archivo dañado devuelve -1"
           );
    fclose(archivo);

    afirmar(gimnasio_entrenadores(gimnasio) == 2,
            "Hay 2 entrenadores"
           );

    afirmar(gimnasio_agregar_entrenador(gimnasio, NULL) == -1,
            "No puedo agregar un entrenador NULL"
           );
    afirmar(gimnasio_entrenadores(gimnasio) == 2,
            "Hay 2 entrenadores"
           );
    afirmar(gimnasio_agregar_entrenador(NULL, entrenador) == -1,
            "No puedo agregar un entrenador a un gimnasio NULL"
           );

    crear_archivo_entrenador();
    archivo = fopen(ARCHIVO, LEER);
    afirmar(cargar_entrenador(archivo, NULL) == -1,
            "Cargar un entrenador a un gimnasio NULL devuelve -1"
           );
    fclose(archivo);
    remove(ARCHIVO);
    afirmar(gimnasio_entrenadores(NULL) == 0,
            "No hay entrenadores en un gimnasio NULL"
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
        fprintf(archivo, "P;Geodude;R;S;40;50;30\n");
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
        fprintf(archivo, "P;Squirtle;A;A;30;20;40\n");
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
    afirmar(juego_agregar_gimnasio(juego, gimnasio) == 0,
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

    afirmar(juego_descartar_gimnasio(juego) == 0,
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
    afirmar(strcmp(str, "Geodude") == 0,
            "El primer Pokémon rival es Geodude"
           );

    juego_liberar(juego);
}

/**
 *
 */
void pruebas_guardado()
{
    nuevo_grupo("Pruebas guardado");
    juego_t* juego = juego_crear();

    afirmar(juego_nuevo(NULL, "Bor") == -1,
            "No puedo crear mi personaje sin juego"
           );
    afirmar(juego_nuevo(juego, "") == -1,
            "No puedo crear mi personaje sin nombre"
           );
    afirmar(juego_nuevo(juego, "Bor") == 0,
            "Puedo crear mi personaje"
           );

    afirmar(guardar_jugador("", juego) == -1,
            "No puedo guardar mi personaje sin indicar archivo"
           );
    afirmar(guardar_jugador(ARCHIVO, NULL) == -1,
            "No puedo guardar mi personaje sin un juego"
           );
    afirmar(guardar_jugador(ARCHIVO, juego) == 0,
            "Puedo guardar mi personaje"
           );

    afirmar(cargar_jugador(ARCHIVO, juego) == 0,
            "Mi formato es válido para volver a cargarlo luego"
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
        pkm_1->ataque = 100;
        pkm_1->defensa = 80;
        pkm_1->velocidad = 100;
        pkm_1->adicional = 20;
        pkm_1->tipo_1 = 'F';
        pkm_1->tipo_2 = 'V';
        strcpy(pkm_1->nombre, "Charizard");

        pkm_2->ataque = 70;
        pkm_2->defensa = 56;
        pkm_2->velocidad = 88;
        pkm_2->adicional = 0;
        pkm_2->tipo_1 = 'V';
        pkm_2->tipo_2 = 'N';
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

    afirmar(funcion_batalla_1(pkm_2, NULL) == GANO_PRIMERO,
            "Funcion batalla 1: Gana primero"
           );
    afirmar(funcion_batalla_1(NULL, pkm_2) == GANO_SEGUNDO,
            "Funcion batalla 1: Gana segundo"
           );
    afirmar(funcion_batalla_2(pkm_2, NULL) == GANO_PRIMERO,
            "Funcion batalla 2: Gana primero"
           );
    afirmar(funcion_batalla_2(NULL, pkm_2) == GANO_SEGUNDO,
            "Funcion batalla 2: Gana segundo"
           );
    afirmar(funcion_batalla_3(pkm_2, NULL) == GANO_PRIMERO,
            "Funcion batalla 3: Gana primero"
           );
    afirmar(funcion_batalla_3(NULL, pkm_2) == GANO_SEGUNDO,
            "Funcion batalla 3: Gana segundo"
           );
    afirmar(funcion_batalla_4(pkm_2, NULL) == GANO_PRIMERO,
            "Funcion batalla 4: Gana primero"
           );
    afirmar(funcion_batalla_4(NULL, pkm_2) == GANO_SEGUNDO,
            "Funcion batalla 4: Gana segundo"
           );
    afirmar(funcion_batalla_5(pkm_2, NULL) == GANO_PRIMERO,
            "Funcion batalla 1: Gana primero"
           );
    afirmar(funcion_batalla_5(NULL, pkm_2) == GANO_SEGUNDO,
            "Funcion batalla 1: Gana segundo"
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
    nuevo_grupo("Pruebas jugabilidad");

    char str[MAX_NOMBRE] = "";
    juego_t* juego = juego_crear();
    crear_archivo_jugador();
    cargar_jugador(ARCHIVO, juego);
    crear_archivo_gimnasios();
    cargar_gimnasios(ARCHIVO, juego);
    remove(ARCHIVO);

    afirmar(tomar_pokemon(juego, 0) == -1,
            "No puedo tomar un Pokémon sin vencer un gimnasio"
            );
    /*
     * retar pokemon -> gana -> aumentan stats
     *
     * retar entrenador -> flujo
     *
     * retar gimnasio -> flujo
     */

    pokemon_t* pokemon = pokemon_jugador(juego);
    int ataque = pokemon_ataque(pokemon);
    pokemon_nombre(pokemon, str);
    afirmar(strcmp(str, "Pikachu") == 0,
            "El Pokemon actual es Pikachu"
           );
    afirmar(retar_pokemon(juego) == 1,
            "Gano la primera pelea"
            );
    afirmar(pokemon_ataque(pokemon) == ataque + 1,
            "El ataque de mi Pokémon aumentó en 1"
            );

    afirmar(retar_entrenador(juego) == 1,
            "Le gano al primer entrenador"
            );

    afirmar(retar_pokemon(juego) == -1,
            "Pierdo la primera pelea"
            );
    pokemon_nombre(pokemon_jugador(juego), str);
    afirmar(strcmp(str, "Butterfree") == 0,
            "El Pokemon actual es Butterfree"
           );
    afirmar(retar_pokemon(juego) == 1,
            "Gano la segunda pelea"
            );
    pokemon_nombre(pokemon_jugador(juego), str);
    afirmar(strcmp(str, "Pikachu") == 0,
            "El Pokemon actual es Pikachu"
           );
    afirmar(pokemon_ataque(pokemon_jugador(juego)) == ataque + 1,
            "Conservó sus stats"
            );

    afirmar(entrenador_party(personaje_principal(juego)) == 6,
            "Mi personaje tiene 6 Pokémon"
           );
    pokemon_nombre(pokemon_jugador(juego), str);
    afirmar(strcmp(str, "Pikachu") == 0,
            "El Pokemon actual es Pikachu"
           );
    afirmar(quitar_del_party(juego, 0) == 0,
            "Quite del party Pikachu");
    pokemon_nombre(pokemon_jugador(juego), str);
    afirmar(strcmp(str, "Butterfree") == 0,
            "El Pokemon actual es Butterfree"
           );
    afirmar(quitar_del_party(juego, 0) == 0,
            "Quite al 1 Pokemón");
    afirmar(entrenador_party(personaje_principal(juego)) == 4,
            "Mi personaje tiene 4 Pokémon"
           );

    afirmar(agregar_a_party(juego, 3) == -1,
            "El Pokémon que se intenta agregar ya esta en el Party"
            );
    afirmar(agregar_a_party(juego, 4) == 0,
            "Se agrega un Pokémon de la caja al party"
            );
    afirmar(entrenador_party(personaje_principal(juego)) == 5,
            "Mi personaje ahora tiene 5 Pokemón"
           );
    afirmar(agregar_a_party(juego, 4) == -1,
            "El Pokemón ya está en el Party"
            );

    afirmar(tomar_pokemon(juego, 0) == 0,
            "Puedo tomar un Pokemón después de vencer un gimnasio"
            );
    afirmar(tomar_pokemon(juego, 0 ) == -1,
            "No puedo tomar otro Pokemón"
            );

    juego_liberar(juego);
}

void ejecutar_pruebas()
{
    pruebas_pokemon();
    pruebas_entrenador();
    pruebas_gimnasio();
    pruebas_juego();
    pruebas_batallas();
    pruebas_guardado();
    pruebas_jugabilidad();
}

int main()
{
    ejecutar_pruebas();
    mostrar_reporte();

    return 0;
}
