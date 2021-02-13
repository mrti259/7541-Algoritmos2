#include "abb.h"

#define ERROR -1
#define SIN_ERROR 0

/*
 * Se inicializa un nodo_abb en el heap con el elemento pedido.
 *
 * Argumentos:
 *  -   elemento: el elemento es válido mientras se encuentre en el stack o en el heap.
 */
nodo_abb_t* nodo_abb_crear(void* elemento) {
    nodo_abb_t* nodo = calloc(1, sizeof(nodo_abb_t));
    if (nodo)
        nodo->elemento = elemento;
    return nodo;
}

/*
 * Se compara un nodo del árbol y un nodo a insertar. Si el nodo a insertar es
 * menor o igual se chequea el nodo de la izquierda, si no, el de la derecha.
 * Cuando no se encuentra un nodo en el árbol, se inserta el nuevo.
 * Devuelve ERROR si no se pudo insertar.
 *
 * Argumentos:
 *  -   nodo_padre: nodo del árbol.
 *  -   nodo: nodo a insertar. contiene al elemento ingresado por el usuario.
 *  -   comparador: comparador del árbol.
 */
int nodo_abb_insertar(nodo_abb_t* nodo_padre, nodo_abb_t* nodo, abb_comparador comparador) {
    /*
    if (nodo_padre->elemento == nodo->elemento)
        return ERROR;
    */
    int insercion = SIN_ERROR;
	
    if (comparador(nodo->elemento, nodo_padre->elemento) <= 0) {
        if (!nodo_padre->izquierda)
            nodo_padre->izquierda = nodo;
        else
            insercion = nodo_abb_insertar(nodo_padre->izquierda, nodo, comparador);
    } else {
        if (!nodo_padre->derecha)
            nodo_padre->derecha = nodo;
        else
            insercion = nodo_abb_insertar(nodo_padre->derecha, nodo, comparador);
    }
    return insercion;
}

/*
 * Devuelve el nodo que contiene al elemento buscado.
 * Si no se encuentra, devuelve NULL.
 *
 * Argumentos:
 *  -   nodo: nodo en comparación.
 *  -   comparador: comparador del árbol.
 *  -   elemento: elemento buscado.
 */
nodo_abb_t* nodo_abb_buscar(nodo_abb_t* nodo, abb_comparador comparador, void* elemento) {
    if (!nodo) return NULL;

    int comparacion = comparador(elemento, nodo->elemento);

    if (comparacion == 0)
        return nodo;

    if (comparacion < 0)
        nodo = nodo->izquierda;
    else
        nodo = nodo->derecha;

    return nodo_abb_buscar(nodo, comparador, elemento);
}

/*
 * Se destruyen el contenido de los nodos, los nodos y sus hijos.
 *
 * Argumentos:
 *  -   nodo: nodo a destruir.
 *  -   destructor: destructor de los elementos del árbol.
 */
void nodo_abb_destruir(nodo_abb_t* nodo, abb_liberar_elemento destructor) {
    if (!nodo) return;

    nodo_abb_destruir(nodo->izquierda, destructor);
    nodo_abb_destruir(nodo->derecha, destructor);
    if (destructor)
        destructor(nodo->elemento);
    free(nodo);
}

/*
 * Se sustituye el nodo por uno de sus hijos manteniendo el orden del ABB.
 * Contempla 4 casos:
 * 1. Si no tiene un hijo a la izquierda, se reemplaza por el nodo de la derecha o NULL.
 * 2. Si tiene un hijo a la izquierda y éste no tiene hijo a la derecha, se
 *    reemplaza por el nodo de la izquierda y mantiene los nodos de la derecha.
 * 3. Si tiene hijo a la izquierda y no tiene a la derecha, se reemplaza por el de la izquierda.
 * 4. Si tiene hijo a la izquierda y éste tiene otro hijo a su derecha,
 *    se busca el precursor inorden (el mayor de sus menores) y se reemplaza por este.
 *
 * Argumentos:
 *  -   nodo: nodo a reemplazar.
 */
void nodo_abb_reemplazar(nodo_abb_t** nodo) {
    nodo_abb_t  *nodo_izquierda = (*nodo)->izquierda,
                *nodo_derecha = (*nodo)->derecha;

    if (!nodo_izquierda) {
        *nodo = nodo_derecha;

    } else if (!nodo_izquierda->derecha) {
        nodo_izquierda->derecha = nodo_derecha;
        *nodo = nodo_izquierda;

    } else if (!nodo_derecha) {
        *nodo = nodo_izquierda;

    } else {
        nodo_abb_t* auxiliar = nodo_izquierda;

        while (auxiliar->derecha->derecha)
            auxiliar = auxiliar->derecha;
        *nodo = auxiliar->derecha;
        (*nodo)->derecha = nodo_derecha;
        auxiliar->derecha = (*nodo)->izquierda;
        (*nodo)->izquierda = nodo_izquierda;
    }
}

/*
 * Se recorre el árbol en búsqueda del elemento. Cuando lo encuentra,
 * se reemplaza por NULL o uno de sus hijos, y el nodo que contiene al
 * elemento se destruye. Si el elemento no se encuentra se devuelve ERROR.
 *
 * Argumentos:
 *  - nodo: nodo a chequear. Si es el nodo a eliminar es reemplazado en el árbol.
 *  - elemento: es el elemento buscado para borrar.
 *  - comparador: comparador del árbol.
 *  - destructor: destructor del árbol.
 */
int nodo_abb_borrar(nodo_abb_t** nodo, void* elemento, abb_comparador comparador, abb_liberar_elemento destructor) {
    if (!*nodo) return ERROR;

    nodo_abb_t** auxiliar = NULL;
    int comparacion = comparador(elemento, (*nodo)->elemento);

    if (comparacion == 0) {
        nodo_abb_t* encontrado = *nodo;
        nodo_abb_reemplazar(nodo);
        encontrado->izquierda = encontrado->derecha = NULL;
        nodo_abb_destruir(encontrado, destructor);
        return SIN_ERROR;
    }

    if (comparacion < 0)
        auxiliar = &((*nodo)->izquierda);
    else
        auxiliar = &((*nodo)->derecha);

    return nodo_abb_borrar(auxiliar, elemento, comparador, destructor);
}

/*
 * Agrega el elemento al vector en la posición indicada y aumenta la posición en 1.
 */
void agregar_al_vector(void* elemento, void** vector, size_t* posicion) {
    *(vector + (*posicion)++) = elemento;
}

/*
 * Ubica en un vector los elementos de los nodos en el orden pedido.
 *
 * Argumentos:
 *  -   recorrido: ABB_RECORRER_PRORDEN, ABB_RECORRER_INORDEN, ABB_RECORRER_POSTORDEN
 *  -   nodo: nodo recorrido.
 *  -   vector: vector donde se insertan los elementos.
 *  -   tamanio_vector: tope del vector.
 *  -   posicion: posición que tomará el elemento a agregar.
 */
void nodo_abb_recorrer(int recorrido, nodo_abb_t* nodo, void** vector, size_t tamanio_vector, size_t* posicion) {
    if (!nodo || !vector || *posicion >= tamanio_vector) return;

    if (recorrido == ABB_RECORRER_PREORDEN && *posicion < tamanio_vector)
        agregar_al_vector(nodo->elemento, vector, posicion);

    nodo_abb_recorrer(recorrido, nodo->izquierda, vector, tamanio_vector, posicion);

    if (recorrido == ABB_RECORRER_INORDEN && *posicion < tamanio_vector)
        agregar_al_vector(nodo->elemento, vector, posicion);

    nodo_abb_recorrer(recorrido, nodo->derecha, vector, tamanio_vector, posicion);

    if (recorrido == ABB_RECORRER_POSTORDEN && *posicion < tamanio_vector)
        agregar_al_vector(nodo->elemento, vector, posicion);
}

/*
 * Aumenta el contador de elementos recorridos y devuelve true si tiene que seguir
 * iterando.
 *
 *  -   elemento: elemento del árbol.
 *  .   funcion: realiza una operación sobre el elemento. Es definida por el usuario.
 *               Devuelve true para detener la iteración.
 *  -   extra: puntero pasarse a la función. Puede ser NULL.
 *  -   cantidad: cantidad de elementos recorridos.
 */
bool nodo_abb_seguir(void* elemento, bool (*funcion)(void*, void*), void* extra, size_t* cantidad) {
    (*cantidad)++;
    return !funcion(elemento, extra);
}

/*
 * Itera sobre los elementos del árbol con una función hasta que la función de la
 * señal de detener o no haya más elementos por recorrer.
 * Devuelve la cantidad de nodos recorridos.
 *
 * Argumentos:
 *  -   seguir: indica si debe iterarse. Es false cuando la función da la señal de detener.
 *  -   nodo: nodo recorrido.
 *  -   funcion: realiza una operación sobre el elemento. Es definida por el usuario.
 *  -   extra: puntero para pasarse a la función. Puede ser NULL.
 */
size_t nodo_abb_iterar(bool* seguir, nodo_abb_t* nodo, int recorrido, bool (*funcion)(void *, void *), void *extra) {
    size_t cantidad = 0;
    if (nodo && *seguir) {

        if (recorrido == ABB_RECORRER_PREORDEN && *seguir)
            *seguir = nodo_abb_seguir(nodo->elemento, funcion, extra, &cantidad);

        cantidad += nodo_abb_iterar(seguir, nodo->izquierda, recorrido, funcion, extra);

        if (recorrido == ABB_RECORRER_INORDEN && *seguir)
            *seguir = nodo_abb_seguir(nodo->elemento, funcion, extra, &cantidad);

        cantidad += nodo_abb_iterar(seguir, nodo->derecha, recorrido, funcion, extra);

        if (recorrido == ABB_RECORRER_POSTORDEN && *seguir)
            *seguir = nodo_abb_seguir(nodo->elemento, funcion, extra, &cantidad);
    }
    return cantidad;
}

/*
 *
 * Definidos en abb.h
 *
 */

abb_t *arbol_crear(abb_comparador comparador, abb_liberar_elemento destructor) {
    if (!comparador) return NULL;

    abb_t* arbol = calloc(1, sizeof(abb_t));
    if (arbol) {
        arbol->comparador = comparador;
        arbol->destructor = destructor;
    }
    return arbol;
}

int arbol_insertar(abb_t *arbol, void *elemento) {
    if (!arbol)
        return ERROR;

    nodo_abb_t *nodo_nuevo = nodo_abb_crear(elemento);

    if (!nodo_nuevo)
        return ERROR;

    if (!arbol_vacio(arbol)) {
        int insercion = nodo_abb_insertar(arbol->nodo_raiz, nodo_nuevo, arbol->comparador);
        if (insercion == ERROR)
            free(nodo_nuevo);
        return insercion;
    }
    arbol->nodo_raiz = nodo_nuevo;
    return SIN_ERROR;
}

int arbol_borrar(abb_t *arbol, void *elemento) {
    if (arbol_vacio(arbol)) return ERROR;
    return nodo_abb_borrar(&(arbol->nodo_raiz), elemento, arbol->comparador, arbol->destructor);
}

void *arbol_buscar(abb_t *arbol, void *elemento) {
    if (arbol_vacio(arbol)) return NULL;

    nodo_abb_t *nodo = nodo_abb_buscar(arbol->nodo_raiz, arbol->comparador, elemento);
    return nodo ? nodo->elemento : NULL;
}

void *arbol_raiz(abb_t *arbol) {
    if (arbol_vacio(arbol)) return NULL;
    return arbol->nodo_raiz->elemento;
}

bool arbol_vacio(abb_t *arbol) {
    return !arbol || !arbol->nodo_raiz;
}

size_t arbol_recorrido_inorden(abb_t *arbol, void** vector, size_t tamanio_vector) {
    size_t puestos = 0;
    if (!arbol_vacio(arbol))
        nodo_abb_recorrer(ABB_RECORRER_INORDEN, arbol->nodo_raiz, vector, tamanio_vector, &puestos);
    return puestos;
}

size_t arbol_recorrido_preorden(abb_t *arbol, void** vector, size_t tamanio_vector) {
    size_t puestos = 0;
    if (!arbol_vacio(arbol))
        nodo_abb_recorrer(ABB_RECORRER_PREORDEN, arbol->nodo_raiz, vector, tamanio_vector, &puestos);
    return puestos;
}

size_t arbol_recorrido_postorden(abb_t *arbol, void** vector, size_t tamanio_vector) {
    size_t puestos = 0;
    if (!arbol_vacio(arbol))
        nodo_abb_recorrer(ABB_RECORRER_POSTORDEN, arbol->nodo_raiz, vector, tamanio_vector, &puestos);
    return puestos;
}

void arbol_destruir(abb_t *arbol) {
    if (!arbol_vacio(arbol))
        nodo_abb_destruir(arbol->nodo_raiz, arbol->destructor);
    free(arbol);
}

size_t abb_con_cada_elemento(abb_t *arbol, int recorrido, bool (*funcion)(void *, void *), void *extra) {
    bool seguir = true;
    return !arbol || !funcion ? 0
        : nodo_abb_iterar(&seguir, arbol->nodo_raiz, recorrido, funcion, extra);
}
