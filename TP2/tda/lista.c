#include "lista.h"
#include <stdlib.h>
#include <stdio.h>

#define ERROR_NO_VALIDO -1
#define SIN_ERROR 0
#define AUMENTAR 'A'
#define DISMINUIR 'D'
#define INICIO 'I'
#define FINAL 'F'

/*
 * Inicializa un nodo en el heap y devuelve si dirección de memoria.
 */
nodo_t* lista_nodo_crear(void* elemento) {
    nodo_t* nodo_nuevo = calloc(1,sizeof(nodo_t));
    if (nodo_nuevo) {
        nodo_nuevo->elemento = elemento;
    }
    return nodo_nuevo;
}

/*
 * Establece la relación entre dos nodos. El nodo_anterior apuntará al
 * nodo_siguiente.
 *
 * Argumentos:
 *  -   nodo_anterior: va antes que nodo siguiente.
 *  -   nodo_siguiente: es el nodo que va despues en la lista. Puede ser NULL.
 */
void lista_nodo_vincular(nodo_t* nodo_anterior, nodo_t* nodo_siguiente) {
    if (nodo_anterior)
        nodo_anterior->siguiente = nodo_siguiente;
}

/*
 * Devuelve true si la posición existe.
 *
 * Argumentos:
 *  -   cantidad: cantidad de elementos de la lista
 *  -   posicion: posicion que se desea acceder, siendo 0 el nodo
 *                de inicio.
 */
bool lista_nodo_acceder_a_la_posicion(size_t cantidad, size_t posicion) {
    return posicion < cantidad;
}

/*
 * Busca el nodo en la posicion indicada, Devuelve el nodo anterior.
 * Si *nodo llega a NULL, nodo_anterior es el último de la lista.
 *
 * Argumentos:
 *  -   lista: apunta al heap.
 *  -   posicion: es la posicion del nodo a buscar, inicia en 0.
 *  -   nodo: es el nodo a inicializar con el valor de la posicion buscada.
 */
nodo_t* lista_nodo_en_posicion(lista_t* lista, size_t posicion, nodo_t** nodo) {
    nodo_t* nodo_aux = NULL;
    *nodo = lista->nodo_inicio;
    for (size_t posicion_actual = 0; posicion_actual < posicion; posicion_actual++) {
        nodo_aux = *nodo;
        *nodo = (*nodo)->siguiente;
    }
    return nodo_aux;
}

/*
 * Recibe un nodo. Si el nodo en NULL no hace nada. Si es válido,
 * toma el nodo siguiente, libera el nodo actual y avanza al siguiente
 * para liberarlos en cadena.
 */
void lista_nodo_destruir(nodo_t* nodo) {
    if (!nodo) return;
    nodo_t *nodo_siguiente = nodo->siguiente;
    free(nodo);
    lista_nodo_destruir(nodo_siguiente);
}

/*
 * Coloca el nodo en el extremo indicado.
 *
 * Argumentos:
 *  -   lista: apunta al la lista a modificar.
 *  -   nodo: apunta al nodo a agregar.
 *  -   extremo: es el extremo de la lista donde agregar el nodo.
 *               Puede ser INICIO o FINAL.
 */
void lista_poner(lista_t* lista, nodo_t* nodo, char extremo) {
    if (extremo == INICIO)
        lista->nodo_inicio = nodo;
    else
        lista->nodo_fin = nodo;
}

/*
 * Actualiza la cantidad de elementos que se encuentran en la lista.
 * Si la lista llega a 0, actualiza el nodo icial a NULL.
 *
 * Argumentos:
 *  -   lista: apunta a una lista en el heap.
 *  -   variar: modifica en uno la cantidad de la lista. Puede ser
 *              AUMENTAR o DISMINUIR
 */
void lista_modificar_cantidad(lista_t* lista, char variar) {
    if (variar == AUMENTAR) {
        (lista->cantidad)++;
        return;
    }

    (lista->cantidad)--;
    if (lista->cantidad == 0)
        lista_poner(lista, NULL, INICIO);
}

/*
 * Funciones públicas definidas en lista.h
 */

lista_t* lista_crear() {
    lista_t* lista_nueva = calloc(1, sizeof(lista_t));
    return lista_nueva;
}


int lista_insertar(lista_t* lista, void* elemento) {
    if (!lista)
        return ERROR_NO_VALIDO;

    nodo_t* nodo_nuevo = lista_nodo_crear(elemento);
    if (!nodo_nuevo)
        return ERROR_NO_VALIDO;

    if (lista_vacia(lista))
        lista_poner(lista, nodo_nuevo, INICIO);
    else
        lista_nodo_vincular(lista->nodo_fin, nodo_nuevo);

    lista_poner(lista, nodo_nuevo, FINAL);
    lista_modificar_cantidad(lista, AUMENTAR);
    return SIN_ERROR;
}


int lista_insertar_en_posicion(lista_t* lista, void* elemento, size_t posicion) {
    if (!lista)
        return ERROR_NO_VALIDO;

    if (lista_vacia(lista)
        || !lista_nodo_acceder_a_la_posicion(lista_elementos(lista), posicion))
        return lista_insertar(lista, elemento);

    nodo_t *nodo_posicion, *nodo_anterior, *nodo_nuevo = lista_nodo_crear(elemento);
    if (!nodo_nuevo)
        return ERROR_NO_VALIDO;

    nodo_anterior = lista_nodo_en_posicion(lista, posicion, &nodo_posicion);

    if (!nodo_anterior)
        lista_poner(lista, nodo_nuevo, INICIO);
    else
        lista_nodo_vincular(nodo_anterior, nodo_nuevo);

    lista_nodo_vincular(nodo_nuevo, nodo_posicion);
    lista_modificar_cantidad(lista, AUMENTAR);
    return SIN_ERROR;
}


int lista_borrar(lista_t* lista) {
    if (lista_vacia(lista))
        return ERROR_NO_VALIDO;

    nodo_t  *nodo_fin,
            *nodo_anterior = lista_nodo_en_posicion(lista, lista_elementos(lista) - 1, &nodo_fin);

    if (nodo_anterior)
        lista_nodo_vincular(nodo_anterior, NULL);

    lista_poner(lista, nodo_anterior, FINAL);
    lista_nodo_destruir(nodo_fin);
    lista_modificar_cantidad(lista, DISMINUIR);
    return SIN_ERROR;
}


int lista_borrar_de_posicion(lista_t* lista, size_t posicion) {
    if (lista_vacia(lista))
        return ERROR_NO_VALIDO;

    if (!lista_nodo_acceder_a_la_posicion(lista_elementos(lista) - 1, posicion))
        return lista_borrar(lista);

    nodo_t  *nodo_posicion,
            *nodo_anterior = lista_nodo_en_posicion(lista, posicion, &nodo_posicion);

    if (!nodo_anterior)
        lista_poner(lista, nodo_posicion->siguiente, INICIO);
    else
        lista_nodo_vincular(nodo_anterior, nodo_posicion->siguiente);

    lista_nodo_vincular(nodo_posicion, NULL);
    lista_nodo_destruir(nodo_posicion);
    lista_modificar_cantidad(lista, DISMINUIR);
    return SIN_ERROR;
}


void* lista_elemento_en_posicion(lista_t* lista, size_t posicion) {
    if (!lista || !lista_nodo_acceder_a_la_posicion(lista_elementos(lista), posicion))
        return NULL;

    if (posicion == lista_elementos(lista) - 1)
        return lista_ultimo(lista);

    nodo_t* nodo;
    lista_nodo_en_posicion(lista, posicion, &nodo);
    return nodo->elemento;
}


void* lista_ultimo(lista_t* lista) {
    if (lista_vacia(lista))
        return NULL;

    return lista->nodo_fin->elemento;
}


bool lista_vacia(lista_t* lista) {
    return !lista_elementos(lista);
}

size_t lista_elementos(lista_t* lista) {
    if (!lista)
        return 0;
    return lista->cantidad;
}


int lista_apilar(lista_t* lista, void* elemento) {
    return lista_insertar_en_posicion(lista, elemento, 0);
}


int lista_desapilar(lista_t* lista) {
    return lista_borrar_de_posicion(lista, 0);
}


void* lista_tope(lista_t* lista) {
    return lista_primero(lista);
}


int lista_encolar(lista_t* lista, void* elemento) {
    return lista_insertar(lista, elemento);
}


int lista_desencolar(lista_t* lista) {
    return lista_borrar_de_posicion(lista, 0);
}


void* lista_primero(lista_t* lista) {
    return lista_elemento_en_posicion(lista, 0);
}


void lista_destruir(lista_t* lista) {
    if (!lista_vacia(lista))
        lista_nodo_destruir(lista->nodo_inicio);
    free(lista);
}


lista_iterador_t* lista_iterador_crear(lista_t* lista) {
    if (!lista)
        return NULL;

    lista_iterador_t* nuevo_iterador = calloc(1, sizeof(lista_iterador_t));
    if (nuevo_iterador) {
        nuevo_iterador->lista = lista;
        nuevo_iterador->corriente = lista->nodo_inicio;
    }
    return nuevo_iterador;
}


bool lista_iterador_tiene_siguiente(lista_iterador_t* iterador) {
    return iterador && iterador->corriente;
}


bool lista_iterador_avanzar(lista_iterador_t* iterador) {
    if (!lista_iterador_tiene_siguiente(iterador))
        return false;

    iterador->corriente = iterador->corriente->siguiente;
    return lista_iterador_tiene_siguiente(iterador);
}


void* lista_iterador_elemento_actual(lista_iterador_t* iterador) {
    if (!iterador || !iterador->corriente)
        return NULL;

    return iterador->corriente->elemento;
}


void lista_iterador_destruir(lista_iterador_t* iterador) {
    free(iterador);
}


size_t lista_con_cada_elemento(lista_t* lista, bool (*funcion)(void*, void*), void *contexto) {
    size_t cantidad = 0;
    if (!lista_vacia(lista) && funcion) {
        nodo_t *nodo = lista->nodo_inicio;
        while (nodo && funcion(nodo->elemento, contexto)) {
            nodo = nodo->siguiente;
            cantidad++;
        }
    }
    return cantidad;
}
