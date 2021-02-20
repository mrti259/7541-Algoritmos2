#ifndef __HEAP_H__
#define __HEAP_H__

#include <stddef.h>

/**
 * Es la estructura que almacenará los datos. Para su manejo se debe hacer
 * uso de las siguientes funciones primitivas. Necesita una funcion
 * comparador para el ordenamiento interno de los elementos. Es opcional
 * el uso de un destructor que actuará sobre los elementos cuando se
 * extraigan del heap.
 */
typedef struct heap heap_t;

/**
 * Compara dos elementos.
 * Debe devolver:
 *   > 0  -> cuando el primer elemento es mayor que el segundo.
 *  == 0  -> cuando los elementos son iguales
 *   < 0  -> cuando el primero elementos es menor que el segundo.
 *
 * Esto determinara si el heap es minimal o maximal.
 */
typedef int (*heap_comparador) (void*, void*);

/**
 * Cada vez que un elemento deja el heap, se invoca al
 * destructor para que actue sobre él.
 */
typedef void (*heap_destructor) (void*);

/**
 * Recibe un comparador para definir el comportamiento del heap.
 * El destructor puede ser NULL. Devuelve un puntero al heap creado,
 * o NULL si falló. El heap creado se encuentra vacío. Para destruirlo se debe
 * invocar a heap_destruir.
 */
heap_t* heap_crear(heap_comparador, heap_destructor);

/**
 * Inserta un elemento en el heap. Devuelve -1 si falló, o 0.
 */
int heap_insertar(heap_t*, void*);

/**
 * Extrae la raíz. Devuelve -1 si falló, o 0.
 */
int heap_extraer_raiz(heap_t*);

/**
 * Devuelve la cantidad de elementos que hay guardados en el heap.
 */
size_t heap_cantidad(heap_t*);

/**
 * Devuelve el elemento de la raíz, o NULL si está vacío.
 */
void* heap_raiz(heap_t*);

/**
 * Libera la memoria. Si tiene destructor se invoca sobre cada elemento.
 */
void heap_destruir(heap_t*);

#endif /*__HEAP_H__*/
