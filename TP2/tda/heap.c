#include "heap.h"
#include <stdlib.h>
#include <stdbool.h>

enum salidas
{
    ERROR = -1,
    SIN_ERROR = 0
};

struct heap
{
    void** elementos;
    size_t tope;
    size_t cantidad;
    heap_comparador comparador;
    heap_destructor destructor;
};

/**
 *
 */
bool heap_hay_lugar(heap_t* heap)
{
    return heap && (heap->cantidad < heap->tope);
}

/**
 *
 */
int heap_agrandar(heap_t* heap)
{
    size_t nuevo_tamanio = (heap->tope ? heap->tope : 1) << 1;
    void** elementos_aux = realloc(heap->elementos, sizeof(void*) * nuevo_tamanio);
    if (!elementos_aux)
    {
        return ERROR;
    }
    heap->elementos = elementos_aux;
    heap->tope = nuevo_tamanio;
    return SIN_ERROR;
}

/**
 * TODO
 * El nodo insertado se compara con su nodo padre hasta recuperar la propiedad
 * de heap. Si el resultado de la comparacion es mayor a 0 se intercambian.
 */
void heap_sift_up(heap_t* heap, size_t posicion)
{
    if (posicion == 0)
    {
        return;
    }
    size_t pos_padre = (posicion - 1) / 2;
    void *nodo = heap->elementos[posicion],
        *padre = heap->elementos[pos_padre];
    if (heap->comparador(nodo, padre) > 0)
    {
        void* aux = nodo;
        heap->elementos[posicion] = padre;
        heap->elementos[pos_padre] = aux;
        heap_sift_up(heap, pos_padre);
    }
}

/**
 * TODO
 * Se desplaza el nodo raiz hacia bajo hasta recuperar la propiedad de heap.
 * Se compara con los subarboles hijos. Si el resultado de la comparacion es
 * .............. se intercambian.
 */
void heap_sift_down(heap_t* heap, size_t posicion)
{
    size_t pos_hijo_izq = 2 * posicion + 1,
           pos_hijo_der = pos_hijo_izq + 1,
           pos_cambio = pos_hijo_izq;
    if (pos_hijo_izq >= heap->cantidad)
    {
        return;
    }
    if (pos_hijo_der < heap->cantidad)
    {
        pos_cambio = heap->comparador(
            heap->elementos[pos_hijo_der],
            heap->elementos[pos_hijo_izq]
        ) > 0 ? pos_hijo_der : pos_hijo_izq;  
    }
    void *nodo = heap->elementos[posicion],
         *hijo = heap->elementos[pos_cambio];
    if (heap->comparador(hijo, nodo) > 0)
    {
        void* aux = nodo;
        heap->elementos[posicion] = hijo;
        heap->elementos[pos_cambio] = aux;
        heap_sift_down(heap, pos_cambio);
    }
}

/**
 * Definidos en heap.h.
 */
heap_t* heap_crear(heap_comparador comparador, heap_destructor destructor)
{
    if (!comparador)
    {
        return NULL;
    }        
    heap_t* heap = calloc(1, sizeof(heap_t));
    if (heap)
    {        
        heap->comparador = comparador;
        heap->destructor = destructor;
    }
    return heap;
}

int heap_insertar(heap_t* heap, void* elemento)
{
    if (!heap || (!heap_hay_lugar(heap) && (heap_agrandar(heap) == ERROR)))
    {
        return ERROR;
    }
    heap->elementos[heap->cantidad] = elemento;
    (heap->cantidad)++;
    // Se recupera la propiedad del heap con heap_sift_up
    heap_sift_up(heap, heap->cantidad - 1);
    return SIN_ERROR;
}

int heap_eliminar_raiz(heap_t* heap)
{
    if (!heap_cantidad(heap))
    {
        return ERROR;
    }
    // Se libera de la memoria si es necesario.
    if (heap->destructor)
    {
        heap->destructor(heap_raiz(heap));
    }
    // Se elimina el elemento.
    (heap->cantidad)--;
    heap->elementos[0] = heap->elementos[heap->cantidad];
    // Se recupera la propiedad del heap con sift-down
    heap_sift_down(heap, 0);
    return SIN_ERROR;
}

size_t heap_cantidad(heap_t* heap)
{
    if (!heap || !heap->elementos)
    {
        return 0;
    }
    return heap->cantidad;
}

void* heap_raiz(heap_t* heap)
{
    if (!heap_cantidad(heap))
    {
        return NULL;
    }
    return heap->elementos[0];
}

void heap_destruir(heap_t* heap)
{
    if (!heap) return;

    if (heap->elementos)
    {
        for (size_t i = 0; heap->destructor && i < heap->cantidad; i++)
        {
            heap->destructor(heap->elementos[i]);
        }
        free(heap->elementos);
    }
    free(heap);
}
