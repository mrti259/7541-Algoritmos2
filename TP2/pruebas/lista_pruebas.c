#include "../tda/lista.h"
#include "pa2mm_2.h"
#include <string.h>

#define COMANDO_VER_PRUEBAS "mostrar_pruebas"
#define MAX_TOPE 50000

void ejecutar_pruebas(int argc, char** argv);

int main(int argc, char** argv) {
    ejecutar_pruebas(argc, argv);
    mostrar_reporte();
    return 0;
}

/*
 * Devuelve true si al ejecutarse el programa, se ingresó por parámetro
 * el comando COMANDO_VER_PRUEBAS.
 *
 * Este comando imprime información sobre resultados de las algunas pruebas.
 */
bool mostrar_pruebas(int argc, char** argv) {
    int i = 1, ingreso = false;

    while (i < argc && !ingreso) {
        if (!strcmp(argv[i], COMANDO_VER_PRUEBAS))
            ingreso = true;
        i++;
    }
    return ingreso;
}

/*
 * Inserta una cadena en la lista usando su función
 * lista_insertar(lista*, void*). Devuelve la cantidad de insertados.
 *
 * Argumentos:
 *  -   lista: apunta al heap.
 *  -   mensaje: vector de char a insertar en la lista desde 0 a tope.
 *  -   tope: cantidad de char que puede contener mensaje. Incluye '\0'.
 */
size_t insertar_mensaje(lista_t* lista, char mensaje[], size_t tope) {
    size_t insertados = 0;

    for (size_t i = 0; i < tope; i++)
        insertados += lista_insertar(lista, mensaje + i) == 0 ? 1 : 0;

    return insertados;
}

/*
 * Elimina los elementos de la lista con lista_borrar(lista_t*).
 * Devuelve la cantidad de elementos eliminados.
 *
 * Argumentos:
 *  -   lista: apunta al heap.
 */
size_t borrar_mensaje(lista_t* lista) {
    size_t eliminados = 0;
    size_t cantidad = lista_elementos(lista);

    while (cantidad > 0) {
        eliminados += lista_borrar(lista) == 0 ? 1 : 0;
        cantidad--;
    }
    return eliminados;
}

/*
 * Inserta una cadena en la lista usando su función
 * lista_insertar_en_posicion(lista_t*, void*, size_t) para agregarlos
 * desde la posición 0. Devuelve la cantidad de elementos insertados.
 *
 * Argumentos:
 *  -   lista: puntero de lista_t que apunta al heap.
 *  -   mensaje: vector de char a insertar en la lista desde 0 a tope.
 *  -   tope: cantidad de char que puede contener mensaje. Incluye '\0'.
 */
size_t insertar_mensaje_al_principio(lista_t* lista, char* mensaje, size_t tope) {
    size_t insertados = 0;

    for (size_t i = 0; i < tope; i++)
        insertados += lista_insertar_en_posicion(lista, mensaje + i, i) == 0 ? 1 : 0;

    return insertados;
}

/*
 * Castea el contenido de una lista a tipo char y lo imprime en pantalla.
 *
 * Argumentos:
 *  -   lista: apunta al heap.
 */
void mostrar_letras_de_lista(lista_t* lista) {
    lista_iterador_t *iterador = lista_iterador_crear(lista);
    printf(NORMAL "\n");

    while (lista_iterador_tiene_siguiente(iterador)) {
        char* letra = lista_iterador_elemento_actual(iterador);
        printf("%c", *letra);
        lista_iterador_avanzar(iterador);
    }

    lista_iterador_destruir(iterador);
    printf("\n\n");
}

/*
 * Se verifica que la creación de la lista sea correcta. Y si no se crea
 * una lista, las funciones devuelven error sin producir resultados
 * inesperadores.
 */
void pruebas_lista_crear() {
    lista_t* lista = lista_crear();
    afirmar(lista != NULL, "Puedo crear una lista.");
    afirmar(lista_vacia(lista), "La lista esta vacía.");
    lista_destruir(lista); // No se debe perder memoria.

    lista_t* lista_nula = NULL;
    void* elemento = lista;
    size_t posicion = 0;

    afirmar(lista_insertar(lista_nula, elemento) != 0,
        "No puedo insertar en una lista nula");

    afirmar(lista_borrar(lista_nula) != 0,
        "No puedo borrar en una lista nula");

    afirmar(lista_insertar_en_posicion(lista_nula, elemento, posicion) != 0,
        "No puedo insertar en una posición de una lista nula");

    afirmar(lista_elemento_en_posicion(lista_nula, posicion) == NULL,
        "No encuentro elementos en una lista nula");

    afirmar(lista_borrar_de_posicion(lista_nula, posicion) != 0,
        "No puedo borrar elementos desde una posición de una lista nula");
}

/*
 * Se verifica que la inserción de un elemento cuando la lista está vacia sea correcta.
 * Se comprueban los estados de las funciones de lista luego de insertar un elemento.
 */
void pruebas_lista_insertar_primero(lista_t* lista, void* elemento) {
    afirmar(lista_insertar(lista, elemento) == 0,
        "La lista está vacía, e inserto el primer elemento.");

    afirmar(!lista_vacia(lista),
        "La lista ya no esta vacía.");

    afirmar(lista_elementos(lista) == 1,
        "La lista tiene 1 elemento.");

    afirmar(lista_elemento_en_posicion(lista, 0) == elemento,
        "La lista empieza por el elemento añadido.");

    afirmar(lista_ultimo(lista) == elemento,
        "El último elemento es el añadido.");
}

/*
 * Se verifica que la eliminación de un elemento cuando es el único de la lista
 * es correcta. Se comprueban los estados de las funciones de listas después de
 * eliminar el último elemento.
 */
void pruebas_lista_borrar_primero(lista_t* lista) {
    afirmar(lista_borrar(lista) == 0,
        "La lista tiene un elemento, puedo eliminarlo.");

    afirmar(lista_vacia(lista),
        "La lista ahora esta vacía.");

    afirmar(lista_elementos(lista) == 0,
        "La lista tiene 0 elementos.");

    afirmar(!lista_elemento_en_posicion(lista, 0),
        "La lista no empieza por un elemento.");

    afirmar(!lista_ultimo(lista),
        "La lista no termina con un elemento.");
}

/*
 * Se realizan las pruebas con un elemento.
 */
void pruebas_lista_primer_elemento() {
    nuevo_grupo("Pruebas lista con primer elemento");
    lista_t* lista = lista_crear();
    void* elemento = lista;
    pruebas_lista_insertar_primero(lista, elemento);
    pruebas_lista_borrar_primero(lista);
    lista_destruir(lista);
}

/*
 * Se verifica el agregado de varios elementos en la lista. Se comrpueban los
 * estados de las funciones de listas después de insertar varios elementos.
 * Se comprueban que varios elementos estén en la ubicacion esperada.
 */
void pruebas_lista_insertar_mensaje(lista_t* lista, char* mensaje, size_t tope) {
    size_t posicion_1 = 10;
    size_t posicion_2 = 20;
    size_t posicion_3 = 30;
    size_t posicion_4 = 40;
    size_t posicion_5 = 50;

    afirmar(insertar_mensaje(lista, mensaje, tope) == tope,
        "Se insertaron varios elementos.");

    afirmar(!lista_vacia(lista),
        "La lista no está vacía");

    afirmar(lista_elementos(lista) == tope,
        "La lista tiene la cantidad de elementos esperados.");

    afirmar(lista_elemento_en_posicion(lista, 0) == mensaje,
        "El primer elemento de la lista es el primer elemento insertado.");

    afirmar(
        (
            lista_elemento_en_posicion(lista, posicion_1) == mensaje + posicion_1
            && lista_elemento_en_posicion(lista, posicion_2) == mensaje + posicion_2
            && lista_elemento_en_posicion(lista, posicion_3) == mensaje + posicion_3
            && lista_elemento_en_posicion(lista, posicion_4) == mensaje + posicion_4
            && lista_elemento_en_posicion(lista, posicion_5) == mensaje + posicion_5
        ), "Se busca un elemento arbitrario y coincide con el esperado.");

    afirmar(lista_ultimo(lista) == (mensaje + tope - 1),
        "El último elemento de la lista es el último elemento insertado.");
}

/*
 * Verifica que se pueden borrar todos los elementos de la lista. Se comprueba el
 * estado de las funciones de lista después de borrar varios elementos.
 */
void pruebas_lista_borrar_mensaje(lista_t* lista, size_t cantidad) {
    afirmar(borrar_mensaje(lista) == cantidad,
        "Se eliminaron todos los elementos");

    afirmar(lista_vacia(lista), "La lista ahora esta vacía.");

    afirmar(lista_elementos(lista) == 0, "La lista tiene 0 elementos.");

    afirmar(!lista_elemento_en_posicion(lista, 0),
        "La lista no empieza por un elemento.");

    afirmar(!lista_ultimo(lista), "La lista no termina en un elemento.");
}

/*
 * Se realizan las pruebas con varios elementos en la lista.
 * Se pueden ver resultados si el programa se llama con
 * COMANDO_VER_PRUEBAS.
 */
void pruebas_lista_varios_elementos(bool mostrar) {
    nuevo_grupo("Pruebas lista con varios elementos");
    lista_t* lista = lista_crear();
    char mensaje[] = "Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed doeiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enimad minim veniam, quis nostrud exercitation ullamco laboris nisi utaliquip ex ea commodo consequat. Duis aute irure dolor inreprehenderit in voluptate velit esse cillum dolore eu fugiat nullapariatur. Excepteur sint occaecat cupidatat non proident, sunt inculpa qui officia deserunt mollit anim id est laborum. Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed doeiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enimad minim veniam, quis nostrud exercitation ullamco laboris nisi utaliquip ex ea commodo consequat. Duis aute irure dolor inreprehenderit in voluptate velit esse cillum dolore eu fugiat nullapariatur. Excepteur sint occaecat cupidatat non proident, sunt inculpa qui officia deserunt mollit anim id est laborum. Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed doeiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enimad minim veniam, quis nostrud exercitation ullamco laboris nisi utaliquip ex ea commodo consequat. Duis aute irure dolor inreprehenderit in voluptate velit esse cillum dolore eu fugiat nullapariatur. Excepteur sint occaecat cupidatat non proident, sunt inculpa qui officia deserunt mollit anim id est laborum. Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed doeiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enimad minim veniam, quis nostrud exercitation ull";
    size_t tope = sizeof(mensaje) / sizeof(char);

    pruebas_lista_insertar_mensaje(lista, mensaje, tope);
    if (mostrar)
        mostrar_letras_de_lista(lista);

    pruebas_lista_borrar_mensaje(lista, tope);
    if (mostrar)
        mostrar_letras_de_lista(lista);

    lista_destruir(lista);
}

/*
 * Se insertan los caracteres de manera ordenada desde la posicion 0 a tope usando
 * lista_insertar_en_posicion(). Se comprueba que se inserten todos los elementos.
 */
void pruebas_lista_insertar_al_principio(lista_t* lista, char* mensaje, size_t tope) {
    afirmar(insertar_mensaje_al_principio(lista, mensaje, tope) == tope,
        "Se insertaron elementos al principio." );

    afirmar(!lista_vacia(lista), "La lista no está vacía.");

    afirmar(lista_elementos(lista) == tope,
        "La lista vuelve a tener la cantidad de elementos esperados.");

    afirmar(lista_elemento_en_posicion(lista, 0) == mensaje,
        "El primer elemento de la lista es el primer elemento insertado.");

    afirmar(
        (
            lista_elemento_en_posicion(lista, 1) == mensaje + 1
            && lista_elemento_en_posicion(lista, 3) == mensaje + 3
            && lista_elemento_en_posicion(lista, 5) == mensaje + 5
            && lista_elemento_en_posicion(lista, 7) == mensaje + 7
            && lista_elemento_en_posicion(lista, 9) == mensaje + 9
        ), "Se busca un elemento arbitrario y coincide con el esperado. (5)");

    afirmar(lista_ultimo(lista) == (mensaje + tope - 1) ,
        "El último elemento de la lista es el último elemento insertado.");

    afirmar(lista_insertar_en_posicion(lista, mensaje + tope + 1, 2) == 0,
        "(1) Se insertó un elemento en una posición arbitraria.");

    afirmar(lista_elemento_en_posicion(lista, 2) == mensaje + tope + 1,
            "(1) El elemento insertado en la posición arbitraria es el esperado");

    afirmar(lista_insertar_en_posicion(lista, mensaje + tope + 2, 4) == 0,
            "(2) Se insertó un elemento en una posición arbitraria.");

    afirmar(lista_elemento_en_posicion(lista, 4) == mensaje + tope + 2,
            "(2) El elemento insertado en la posición arbitraria es el esperado");

    afirmar(lista_insertar_en_posicion(lista, mensaje + tope + 3, 6) == 0,
            "(2) Se insertó un elemento en una posición arbitraria.");

    afirmar(lista_elemento_en_posicion(lista, 6) == mensaje + tope + 3,
        "(2) El elemento insertado en la posición arbitraria es el esperado");
}

/*
 * Se borran elementos aleatorios. Se comprueban que los elementos no estén en la
 * posicion donde se encontraban.
 */
void pruebas_lista_borrar_posiciones(lista_t* lista) {
    size_t posicion = 8;
    void* elemento_borrado = lista_elemento_en_posicion(lista, posicion);
    void* elemento_anterior = lista_elemento_en_posicion(lista, posicion - 1);
    afirmar(lista_borrar_de_posicion(lista, posicion) == 0,
        "(1) Puedo eliminar un elemento en una posición arbitraria.");
    afirmar(elemento_borrado != lista_elemento_en_posicion(lista, posicion),
        "(1) El elemento eliminado ya no se encuentra en esa posición.");
    afirmar(elemento_anterior == lista_elemento_en_posicion(lista, posicion - 1),
        "(1) El elemento anterior no se vio afectado.");

    posicion = 6;
    elemento_borrado = lista_elemento_en_posicion(lista, posicion);
    elemento_anterior = lista_elemento_en_posicion(lista, posicion - 1);
    afirmar(lista_borrar_de_posicion(lista, posicion) == 0,
        "(2) Puedo eliminar un elemento en una posición arbitraria.");
    afirmar(elemento_borrado != lista_elemento_en_posicion(lista, posicion),
        "(2) El elemento eliminado ya no se encuentra en esa posición.");
    afirmar(elemento_anterior == lista_elemento_en_posicion(lista, posicion - 1),
        "(2) El elemento anterior no se vio afectado.");

    posicion = 4;
    elemento_borrado = lista_elemento_en_posicion(lista, posicion);
    elemento_anterior = lista_elemento_en_posicion(lista, posicion - 1);
    afirmar(lista_borrar_de_posicion(lista, posicion) == 0,
        "(3) Puedo eliminar un elemento en una posición arbitraria.");
    afirmar(elemento_borrado != lista_elemento_en_posicion(lista, posicion),
        "(3) El elemento eliminado ya no se encuentra en esa posición.");
    afirmar(elemento_anterior == lista_elemento_en_posicion(lista, posicion - 1),
        "(3) El elemento anterior no se vio afectado.");

    posicion = lista_elementos(lista);
    elemento_borrado = lista_ultimo(lista);
    elemento_anterior = lista_elemento_en_posicion(lista, lista_elementos(lista) - 2);
    afirmar(lista_borrar_de_posicion(lista, posicion) == 0,
        "(4) Puedo eliminar un elemento con una posición no válida.");
    afirmar(elemento_borrado != lista_ultimo(lista),
        "(4) El elemento eliminado era el último de la lista.");
    afirmar(elemento_anterior == lista_elemento_en_posicion(lista, lista_elementos(lista) - 1),
        "(4) El elemento anterior no se vio afectado.");

    posicion = lista_elementos(lista) + 1000;
    elemento_borrado = lista_ultimo(lista);
    elemento_anterior = lista_elemento_en_posicion(lista, lista_elementos(lista)- 2);
    afirmar(lista_borrar_de_posicion(lista, posicion) == 0,
        "(5) Puedo eliminar un elemento con una posición no válida.");
    afirmar(elemento_borrado != lista_ultimo(lista),
        "(5) El elemento eliminado era el último de la lista.");
    afirmar(elemento_anterior == lista_elemento_en_posicion(lista, lista_elementos(lista) - 1),
        "(5) El elemento anterior no se vio afectado.");
}

/*
 * Ejecuta las pruebas con funciones de lista que hacen uso de las posiciones.
 */
void pruebas_lista_posiciones(bool mostrar) {
    nuevo_grupo("Pruebas lista con posiciones");
    lista_t* lista = lista_crear();
    char mensaje[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    size_t tope = 10;

    pruebas_lista_insertar_al_principio(lista, mensaje, tope);
    if (mostrar)
        mostrar_letras_de_lista(lista);

    pruebas_lista_borrar_posiciones(lista);
    if (mostrar)
        mostrar_letras_de_lista(lista);

    lista_destruir(lista);
}

/*
 * Ejecuta todas las pruebas de las funciones de lista.
 */
void pruebas_listas(bool mostrar) {
    nuevo_grupo("Pruebas de listas");
    pruebas_lista_crear();
    pruebas_lista_primer_elemento();
    pruebas_lista_varios_elementos(mostrar);
    pruebas_lista_posiciones(mostrar);
}

/*
 * Se prueban las funciones de pila.
 * Se apilan 50000 elementos y se comprueba que el elemento apilado sea
 * el tope. Se desapilan los elementos y se comprueba que el elemento
 * tope sea el siguiente.
 */
void pruebas_pilas(bool mostrar) {
    nuevo_grupo("Pruebas de pilas");
    lista_t* pila = lista_crear();
    size_t tope = MAX_TOPE, i, elementos[tope];
    size_t apilados_ok = 0, topes_ok = 0, desapilados_ok = 0;

    for (i = 0; i < tope; i++) {
        apilados_ok += lista_apilar(pila, elementos + i) == 0 ? 1 : 0;
        topes_ok += lista_tope(pila) == (elementos + i) ? 1 : 0;
    }

    afirmar(apilados_ok == tope,
        "Se apilaron 50000 elementos los elementos.");

    afirmar(topes_ok == tope,
        "El tope es el último elemento apilado.");

    topes_ok = 0;
    while (!lista_vacia(pila)) {
        size_t* elemento = i - 1 > tope ? NULL : elementos + i - 1;
        topes_ok += lista_tope(pila) == elemento ? 1 : 0;
        desapilados_ok += lista_desapilar(pila) == 0 ? 1 : 0;
        i--;
    }

    afirmar(desapilados_ok == tope,
        "Se desapilaron 50000 los elementos.");
    afirmar(topes_ok == tope,
        "Se desapilan desde el último al primero.");

    if (mostrar) {
        printf("\nApilados: %zu", apilados_ok);
        printf("\nDesapilados: %zu", desapilados_ok);
        printf("\nTopes: %zu\n", topes_ok);
    }

    lista_destruir(pila);

    afirmar(lista_apilar(NULL, elementos) != 0,
        "No puedo apilar sin una pila.");

    afirmar(lista_desapilar(NULL) != 0,
        "No puedo desapilar sin una pila.");

    afirmar(!lista_tope(NULL),
        "No puedo ver el tope sin una pila.");
}

/*
 * Se prueban las funciones de cola.
 * Se encolan los elementos y se comprueba que el elemento encolado
 * sea el último. Se desencolan los elementos y se comprueba que el
 * elemento desencolado sea el primero.
*/
void pruebas_colas(bool mostrar) {
    nuevo_grupo("Pruebas de colas");
    lista_t* cola = lista_crear();
    size_t  tope = MAX_TOPE, i, elementos[tope];
    size_t  encolados_ok = 0, primeros_ok = 0,
            ultimos_ok = 0, desencolados_ok = 0;

    for (i = 0; i < tope; i++) {
        encolados_ok += lista_encolar(cola, elementos + i) == 0 ? 1 : 0;
        ultimos_ok += lista_ultimo(cola) == elementos + i ? 1 : 0;
    }

    afirmar(encolados_ok == tope,
        "Se encolaron 50000 los elementos.")

    afirmar(ultimos_ok == tope,
        "El último elemento es siempre el último encolado.")

    for (i = 0; !lista_vacia(cola); i++) {
        size_t* elemento = i + 1 < tope ? elementos + i + 1 : NULL;
        desencolados_ok += lista_desencolar(cola) == 0 ? 1 : 0;
        primeros_ok += lista_primero(cola) == elemento ? 1 : 0;
    }

    afirmar(desencolados_ok == tope,
            "Se desencolaron 50000 los elementos.")

    afirmar(primeros_ok == tope,
            "Se desencolan desde el primero al último.")

    if (mostrar) {
        printf("\nEncolados: %zu", encolados_ok);
        printf("\nUltimos: %zu", ultimos_ok);
        printf("\nDesencolados: %zu", desencolados_ok);
        printf("\nPrimeros: %zu\n", primeros_ok);
    }

    lista_destruir(cola);

    afirmar(lista_encolar(NULL, elementos) != 0,
        "No puedo encolar sin una cola.");

    afirmar(lista_desencolar(NULL) != 0,
        "No puedo desencolar sin una cola.");

    afirmar(!lista_primero(NULL),
        "No puedo ver el primero sin una cola.");
}

/*
 * Se prueba que la creación de un iterador sin lista fallé
 * y no produzca resultados inesperados.
 */
void pruebas_iteradores_sin_lista() {
    lista_iterador_t* iterador = lista_iterador_crear(NULL);
    afirmar(iterador == NULL,
        "No puedo crear un iterador sin una lista válida.");

    afirmar(!lista_iterador_tiene_siguiente(iterador),
        "No puedo ver siguientes sin una lista.");

    afirmar(!lista_iterador_avanzar(iterador),
        "No puedo avanzar sin una lista.");

    afirmar(!lista_iterador_elemento_actual(iterador),
        "No tengo elementos sin una lista");

    lista_iterador_destruir(iterador); // No debo tener error de memoria.
}

/*
 * Se prueba la creación de un iterador con una lista vacía.
 * Al no tener elementos para iterar no es válido. Se comprueba
 * que no se produzcan resultados inesperados.
 */
void pruebas_iteradores_con_lista_vacia(lista_t* lista) {
    lista_iterador_t* iterador = lista_iterador_crear(lista);
    afirmar(iterador != NULL,
        "Puedo crear un interador con una lista válida y vacía.");

    afirmar(!lista_iterador_tiene_siguiente(iterador),
        "Si mi lista esta vacia, mi iterador no indica un siguiente.");

    afirmar(!lista_iterador_avanzar(iterador),
        "No puedo avanzar en una lista vacía.");

    afirmar(!lista_iterador_elemento_actual(iterador),
        "No tengo elementos en una lista vacía.");

    lista_iterador_destruir(iterador); // No debo perder memoria.
}

/*
 * Se prueba la creación de un iterador con una lista con 5 elementos,
 * y se prueban las funciones de estado del iterador y su correcto
 * funcionamiento al avanzar a lo largo de la lista.
 */
void pruebas_iteradores_con_lista_con_cosas(lista_t* lista) {
    char elemento[] = "abcde";
    lista_insertar(lista, elemento);
    lista_insertar(lista, elemento + 1);
    lista_insertar(lista, elemento + 2);
    lista_insertar(lista, elemento + 3);
    lista_insertar(lista, elemento + 4);
    lista_iterador_t* iterador = lista_iterador_crear(lista);

    afirmar(iterador != NULL,
        "Puedo crear un interador con una lista válida con cosas.");

    afirmar(lista_iterador_elemento_actual(iterador) == elemento,
        "Mi iterador devuelve el primer elemento de la lista.");

    afirmar(lista_iterador_tiene_siguiente(iterador),
        "Mi iterador tiene siguiente.");

    afirmar(lista_iterador_avanzar(iterador),
        "El iterador avanza por la lista y quedan elementos.");

    afirmar(lista_iterador_elemento_actual(iterador) == elemento + 1,
        "Mi iterador devuelve al segundo elemento de la lista.")

    afirmar(lista_iterador_tiene_siguiente(iterador),
        "Mi iterador puede avanzar.")

    afirmar(lista_iterador_avanzar(iterador),
        "El iterador avanza por la lista y quedan elementos.");

    afirmar(lista_iterador_elemento_actual(iterador) == elemento + 2,
        "Mi iterador devuelve al tercer elemento de la lista.")

    afirmar(lista_iterador_tiene_siguiente(iterador),
        "Mi iterador puede avanzar.")

    afirmar(lista_iterador_avanzar(iterador),
        "El iterador avanza por la lista y quedan elementos.");

    afirmar(lista_iterador_elemento_actual(iterador) == elemento + 3,
        "Mi iterador devuelve al cuarto elemento de la lista.")

    afirmar(lista_iterador_tiene_siguiente(iterador),
        "Mi iterador puede avanzar.")

    afirmar(lista_iterador_avanzar(iterador),
        "El iterador avanza por la lista y quedan elementos.");

    afirmar(lista_iterador_elemento_actual(iterador) == elemento + 4,
        "Mi iterador devuelve al quinto elemento de la lista.")

    afirmar(lista_iterador_tiene_siguiente(iterador),
        "Mi iterador puede avanzar.")

    afirmar(!lista_iterador_avanzar(iterador),
        "Avanzo al final y no me quedan elementos para recorrer.");

    afirmar(!lista_iterador_elemento_actual(iterador),
        "El iterador no devuelve ningun elemento.")

    afirmar(!lista_iterador_tiene_siguiente(iterador),
        "Mi iterador ya no puede avanzar.")

    lista_iterador_destruir(iterador); // No debo perder memoria.
}

/*
 * Esta función puede pasarse a un iterador interno. Recibe un elemento
 * de una lista, lo castea a entero y lo suma al total.
 *
 * Argumentos:
 *  -   _numero: elemento de una lista.
 *  -   _total: puntero donde almacenar el total.
 */
bool suma_total(void* _numero, void* _total) {
    int *numero = _numero, *total = _total;
    if (numero)
        *total += *numero;
    return true;
}

/*
 * Esta función puede pasarse a un iterador interno. Recibe un elemento
 * de una lista, lo castea a enteor y si es múltiplo de 3 aumenta el contador.
 *
 * Argumentos:
 *  -   _numero: elemento de una lista.
 *  -   _total: puntero donde almacenar el contador.
 */
bool multiplos_de_3(void* _numero, void* _total) {
    int *numero = _numero, *total = _total;
    if (numero && *numero % 3 == 0)
        *total += 1;
    return true;
}

/*
 * Ejecuta pruebas con el iterador interno
 */
void pruebas_iterador_interno(lista_t* lista) {
    int numeros[] = {23,54,65,23,76,98,4,324,32,545,11,43,23}, i,
        total = 0, total_contexto = 0,
        multiplos = 0, multiplos_contexto = 0;

    for (i = 0; i < sizeof(numeros)/sizeof(int); i++) {
        lista_insertar(lista, numeros + i);
        total += numeros[i];
        if (numeros[i] % 3 == 0) multiplos++;
    }
    afirmar(lista_con_cada_elemento(lista, suma_total, &total_contexto) == i,
        "El iterador iteró toda la lista.");
    afirmar(total_contexto == total, "La suma es la correcta");

    afirmar(lista_con_cada_elemento(lista, multiplos_de_3, &multiplos_contexto) == i,
        "El iterador vuelve a iterar todos mis elementos.");

    afirmar(multiplos_contexto == multiplos,
        "La cantidad de múltiplos encontrados es la correcta");

    afirmar(!lista_con_cada_elemento(lista, NULL, &total_contexto),
        "No itero sin una función.");

    afirmar (!lista_con_cada_elemento(NULL, suma_total, &total_contexto),
        "No itero sin una lista");
}

/*
 * Ejecuta todas las pruebas de las funciones de iteradores.
 */
void pruebas_iteradores(bool mostrar) {
    nuevo_grupo("Pruebas de iterador externo");
    lista_t* lista = lista_crear();

    pruebas_iteradores_sin_lista();
    pruebas_iteradores_con_lista_vacia(lista);
    pruebas_iteradores_con_lista_con_cosas(lista);
    lista_destruir(lista);

    lista = lista_crear();
    nuevo_grupo("Pruebas de iterador interno");
    pruebas_iterador_interno(lista);
    lista_destruir(lista);
}

/*
 * Ejecuta todas las pruebas.
 * Chequea si se llamo a COMANDO_VER_PRUEBAS al ejecutar el programa.
 */
void ejecutar_pruebas(int argc, char** argv) {
    bool mostrar = mostrar_pruebas(argc, argv);
    pruebas_listas(mostrar);
    pruebas_pilas(mostrar);
    pruebas_colas(mostrar);
    pruebas_iteradores(mostrar);
}
