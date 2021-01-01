#ifndef __HEAP_H__
#define __HEAP_H__

#include <stddef.h>

/**
 * TODO: poner definicion de heap
 */
typedef struct heap heap_t;

/**
 * Compara dos elementos.
 * Devuelve:
 *   > 0  -> cuando el primer elemento es mayor que el segundo.
 *  == 0  -> cuando los elementos son iguales
 *   < 0  -> cuando el primero elementos es menor que el segundo.
 */
typedef int (*heap_comparador) (void*, void*);

/**
 * Cada vez que un elemento deja el heap, se invoca al
 * destructor.
 */
typedef void (*heap_destructor) (void*);

/**
 *
 */
heap_t* heap_crear(heap_comparador, heap_destructor);

/**
 *
 */
int heap_insertar(heap_t*, void*);

/**
 *
 */
int heap_eliminar_raiz(heap_t*);

/**
 * Devuelve la cantidad de elementos que hay guardados en el heap.
 */
size_t heap_cantidad(heap_t*);

/**
 * Devuelve el elemento de la raíz.
 */
void* heap_raiz(heap_t*);

/**
 *
 */
void heap_destruir(heap_t*);

#endif /*__HEAP_H__*/
