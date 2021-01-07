#include <stdio.h>
#include <string.h>
#include "heap.h"
#include "pa2mm_2.h"

enum salidas
{
    ERROR = -1,
    SIN_ERROR = 0
};

void ejecutar_pruebas();

int main()
{
    ejecutar_pruebas();
    mostrar_reporte();
    return 0;
}

/*
 * Reserva memoria dinámica para un caracter.
 */
void* creador(char caracter)
{
    return memset(malloc(sizeof(char)), caracter, sizeof(char));
}

/*
 * Compara dos caracteres.
 * Devuelve:
 *   > 0 -> si el primer caracter es mayor que el segundo
 *  == 0 -> si son iguales
 *   < 0 -> si el primer caracter es menor que el segundo
 */
int comparador_maximal(void* elemento1, void* elemento2)
{
    char char1 = elemento1 ? *(char*) elemento1 : '\0';
    char char2 = elemento2 ? *(char*) elemento2 : '\0';
    return char1 - char2;
}

/*
 * Compara dos caracteres.
 * Devuelve:
 *   > 0 -> si el primer caracter es menor que el segundo
 *  == 0 -> si son iguales
 *   < 0 -> si el primer caracter es mayor que el segundo
 */
int comparador_minimal(void* elemento1, void* elemento2)
{
    char char1 = elemento1 ? *(char*) elemento1 : '\0';
    char char2 = elemento2 ? *(char*) elemento2 : '\0';
    return char2 - char1;
}

void probar_crear()
{
    nuevo_grupo("Pruebas heap_crear / heap_cantidad");
    
    heap_t* heap = heap_crear(NULL, NULL);
    afirmar(!heap, "No se crea un heap sin comparador y sin destructor.");
    afirmar(heap_cantidad(heap) == 0, "Si el heap es NULL contiene 0 elementos.");
    heap_destruir(heap);

    heap = heap_crear(NULL, free);
    afirmar(!heap, "No se crea un heap sin comparador y con destructor.");
    heap_destruir(heap);

    heap = heap_crear(comparador_minimal, NULL);
    afirmar(heap, "Se crea un heap con comparador y sin destructor.");
    heap_destruir(heap);

    heap = heap_crear(comparador_maximal, free);
    afirmar(heap, "Se crea un heap con comparador y con destructor");
    afirmar(heap_cantidad(heap) == 0, "El heap contiene 0 elementos.");
    heap_destruir(heap);
}

void probar_insertar()
{
    nuevo_grupo("Pruebas heap_insertar / heap_cantidad");
    heap_t* heap = NULL;
    char caracteres[] = {'a', 'l', 'g', 'a', '\n'};

    afirmar(
        heap_insertar(heap, caracteres + 0) == -1,
        "Insertar un elemento sin heap devuelve -1."
    );

    heap = heap_crear(comparador_maximal, NULL);
    afirmar(
        heap_insertar(heap, caracteres + 0) == 0,
        "Insertar un elemento en el heap devuelve 0."
    );
    afirmar(
        heap_cantidad(heap) == 1,
        "El heap tiene 1 elemento."
    );
    
    afirmar(
        heap_insertar(heap, caracteres + 1) == 0,
        "Insertar otro elemento en el heap devuelve 0."
    );
    afirmar(
        heap_cantidad(heap) == 2,
        "El heap tiene 2 elemento."
    );
    
    afirmar(
        heap_insertar(heap, caracteres + 2) == 0,
        "Insertar otro elemento en el heap devuelve 0."
    );
    afirmar(
        heap_cantidad(heap) == 3,
        "El heap tiene 3 elemento."
    );
    
    afirmar(
        heap_insertar(heap, caracteres + 3) == 0,
        "Insertar una clave repetida devuelve 0."
    );
    afirmar(
        heap_cantidad(heap) == 4,
        "El heap tiene 4 elemento."
    );
    
    afirmar(
        heap_insertar(heap, caracteres + 1) == 0,
        "Insertar un elemento repetido devuelve 0."
    );
    afirmar(
        heap_cantidad(heap) == 5,
        "El heap tiene 5 elemento."
    );
    
    afirmar(
        heap_insertar(heap, NULL) == 0,
        "Insertar NULL devuelve 0."
    );
    afirmar(
        heap_cantidad(heap) == 6,
        "El heap tiene 6 elemento."
    );
    
    heap_destruir(heap);
}

void probar_eliminar_sin_destructor()
{
    nuevo_grupo("Pruebas heap_eliminar (sin destructor) / heap_cantidad");
    heap_t* heap = NULL;
    char caracteres[] = {'a', 'l', 'g', 'a', '\n'};

    afirmar(
        heap_eliminar_raiz(heap) == -1,
        "Eliminar un elemento cuando el heap es NULL devuelve -1."
    );

    heap = heap_crear(comparador_maximal, NULL);
    afirmar(
        heap_eliminar_raiz(heap) == -1,
        "Eliminar un elemento cuando el heap no contiene elementos -1."
    );
    
    for (size_t i = 0; i < sizeof(caracteres) / sizeof(char); i++)
    {
        heap_insertar(heap, caracteres + i);
    }
    afirmar(
        heap_cantidad(heap) == 5,
        "Ahora el heap contiene 5 elementos (\"alga\")"
    );

    afirmar(heap_eliminar_raiz(heap) == 0, "Eliminar la raiz devuelve 0.");
    afirmar(heap_cantidad(heap) == 4, "Ahora el heap contiene 4 elementos.");

    afirmar(heap_eliminar_raiz(heap) == 0, "Eliminar la raiz devuelve 0.");
    afirmar(heap_cantidad(heap) == 3, "Ahora el heap contiene 3 elementos.");

    afirmar(heap_eliminar_raiz(heap) == 0, "Eliminar la raiz devuelve 0.");
    afirmar(heap_cantidad(heap) == 2, "Ahora el heap contiene 2 elementos.");

    afirmar(heap_eliminar_raiz(heap) == 0, "Eliminar la raiz devuelve 0.");
    afirmar(heap_cantidad(heap) == 1, "Ahora el heap contiene 1 elementos.");

    afirmar(heap_eliminar_raiz(heap) == 0, "Eliminar la raiz devuelve 0.");
    afirmar(heap_cantidad(heap) == 0, "Ahora el heap contiene 0 elementos.");

    afirmar(heap_eliminar_raiz(heap) == -1, "Eliminar la raiz devuelve -1.");
    afirmar(heap_cantidad(heap) == 0, "Ahora el heap contiene 0 elementos.");

    heap_destruir(heap);
}

void probar_raiz_maximal()
{
    nuevo_grupo("Pruebas heap_raiz (maximal)");
    heap_t* heap = NULL;
    char caracteres[] = {'a', 'l', 'g', 'a', ' ', 'm', 'a', 'r', 'i', 'n', 'a', '\n'};

    afirmar(
        heap_raiz(heap) == NULL,
        "Si el heap es NULL, la raíz es NULL."
    );
    heap = heap_crear(comparador_maximal, NULL);
    afirmar(
        heap_raiz(heap) == NULL,
        "Cuando creo el heap, la raíz es NULL."
    );

    for (size_t i = 0; i < sizeof(caracteres) / sizeof(char); i++)
    {
        heap_insertar(heap, &(caracteres[i]));
    }
    afirmar(heap_cantidad(heap) == 12, "Ahora el heap contiene 12 elementos (\"alga marina\")");

    afirmar(
        *(char*) heap_raiz(heap) == 'r',
        "El heap es maximal, por lo cual en la raíz se encuentra 'r'."
    );
    
    heap_eliminar_raiz(heap);
    afirmar(
        *(char*) heap_raiz(heap) == 'n',
        "Elimino un elemento y en la raíz queda 'n'."
    );
    
    heap_eliminar_raiz(heap);
    afirmar(
        *(char*) heap_raiz(heap) == 'm',
        "Elimino un elemento y en la raíz queda 'm'."
    );
    
    heap_eliminar_raiz(heap);
    afirmar(
        *(char*) heap_raiz(heap) == 'l',
        "Elimino un elemento y en la raíz queda 'l'."
    );
    
    heap_eliminar_raiz(heap);
    afirmar(
        *(char*) heap_raiz(heap) == 'i',
        "Elimino un elemento y en la raíz queda 'i'."
    );
    
    heap_eliminar_raiz(heap);
    afirmar(
        *(char*) heap_raiz(heap) == 'g',
        "Elimino un elemento y en la raíz queda 'g'."
    );
    
    heap_eliminar_raiz(heap);
    afirmar(
        *(char*) heap_raiz(heap) == 'a',
        "Elimino un elemento y en la raíz queda 'a'."
    );
    
    heap_eliminar_raiz(heap);
    afirmar(
        *(char*) heap_raiz(heap) == 'a',
        "Elimino un elemento y en la raíz queda 'a'."
    );
    
    heap_eliminar_raiz(heap);
    afirmar(
        *(char*) heap_raiz(heap) == 'a',
        "Elimino un elemento y en la raíz queda 'a'."
    );
    
    heap_eliminar_raiz(heap);
    afirmar(
        *(char*) heap_raiz(heap) == 'a',
        "Elimino un elemento y en la raíz queda 'a'."
    );
    
    heap_eliminar_raiz(heap);
    afirmar(
        *(char*) heap_raiz(heap) == ' ',
        "Elimino un elemento y en la raíz queda ' '."
    );
    
    heap_eliminar_raiz(heap);
    afirmar(
        *(char*) heap_raiz(heap) == '\n',
        "Elimino un elemento y en la raíz queda '\\n'."
    );
    
    heap_destruir(heap);
}

void probar_eliminar_con_destructor()
{
    nuevo_grupo("Pruebas heap_eliminar (con destructor) / heap_cantidad");
    heap_t* heap = NULL;
    char caracteres[] = {'a', 'l', 'g', 'a', '\n'};

    afirmar(
        heap_eliminar_raiz(heap) == -1,
        "Eliminar un elemento cuando el heap es NULL devuelve -1."
    );

    heap = heap_crear(comparador_minimal, free);
    afirmar(
        heap_eliminar_raiz(heap) == -1,
        "Eliminar un elemento cuando el heap no contiene elementos -1."
    );
    
    for (size_t i = 0; i < sizeof(caracteres) / sizeof(char); i++)
    {
        heap_insertar(heap, creador(caracteres[i]));
    }
    afirmar(
        heap_cantidad(heap) == 5,
        "Ahora el heap contiene 5 elementos (\"alga\")"
    );

    afirmar(
        heap_eliminar_raiz(heap) == 0, "Eliminar la raiz devuelve 0.");
    afirmar(heap_cantidad(heap) == 4, "Ahora el heap contiene 4 elementos.");

    afirmar(heap_eliminar_raiz(heap) == 0, "Eliminar la raiz devuelve 0.");
    afirmar(heap_cantidad(heap) == 3, "Ahora el heap contiene 3 elementos.");

    afirmar(heap_eliminar_raiz(heap) == 0, "Eliminar la raiz devuelve 0.");
    afirmar(heap_cantidad(heap) == 2, "Ahora el heap contiene 2 elementos.");

    afirmar(heap_eliminar_raiz(heap) == 0, "Eliminar la raiz devuelve 0.");
    afirmar(heap_cantidad(heap) == 1, "Ahora el heap contiene 1 elementos.");

    afirmar(heap_eliminar_raiz(heap) == 0, "Eliminar la raiz devuelve 0.");
    afirmar(heap_cantidad(heap) == 0, "Ahora el heap contiene 0 elementos.");

    afirmar(heap_eliminar_raiz(heap) == -1, "Eliminar la raiz devuelve -1.");
    afirmar(heap_cantidad(heap) == 0, "Ahora el heap contiene 0 elementos.");

    heap_destruir(heap);
}

void probar_raiz_minimal()
{
    nuevo_grupo("Pruebas heap_raiz (minimal)");
    heap_t* heap = NULL;
    char caracteres[] = {'a', 'l', 'g', 'a', ' ', 'm', 'a', 'r', 'i', 'n', 'a', '\n'};

    afirmar(
        heap_raiz(heap) == NULL,
        "Si el heap es NULL, la raíz es NULL."
    );
    heap = heap_crear(comparador_minimal, free);
    afirmar(
        heap_raiz(heap) == NULL,
        "Cuando creo el heap, la raíz es NULL."
    );

    for (size_t i = 0; i < sizeof(caracteres) / sizeof(char); i++)
    {
        heap_insertar(heap, creador(caracteres[i]));
    }
    afirmar(heap_cantidad(heap) == 12, "Ahora el heap contiene 12 elementos (\"alga marina\")");

    afirmar(
        *(char*) heap_raiz(heap) == '\n',
        "El heap es minimal, por lo cual en la raíz se encuentra '\\n'."
    );
    
    heap_eliminar_raiz(heap);
    afirmar(
        *(char*) heap_raiz(heap) == ' ',
        "Elimino un elemento y en la raíz queda ' '."
    );
    
    heap_eliminar_raiz(heap);
    afirmar(
        *(char*) heap_raiz(heap) == 'a',
        "Elimino un elemento y en la raíz queda 'a'."
    );
    
    heap_eliminar_raiz(heap);
    afirmar(
        *(char*) heap_raiz(heap) == 'a',
        "Elimino un elemento y en la raíz queda 'a'."
    );
    
    heap_eliminar_raiz(heap);
    afirmar(
        *(char*) heap_raiz(heap) == 'a',
        "Elimino un elemento y en la raíz queda 'a'."
    );
    
    heap_eliminar_raiz(heap);
    afirmar(
        *(char*) heap_raiz(heap) == 'a',
        "Elimino un elemento y en la raíz queda 'a'."
    );
    
    heap_eliminar_raiz(heap);
    afirmar(
        *(char*) heap_raiz(heap) == 'g',
        "Elimino un elemento y en la raíz queda 'g'."
    );
    
    heap_eliminar_raiz(heap);
    afirmar(
        *(char*) heap_raiz(heap) == 'i',
        "Elimino un elemento y en la raíz queda 'i'."
    );
    
    heap_eliminar_raiz(heap);
    afirmar(
        *(char*) heap_raiz(heap) == 'l',
        "Elimino un elemento y en la raíz queda 'l'."
    );
    
    heap_eliminar_raiz(heap);
    afirmar(
        *(char*) heap_raiz(heap) == 'm',
        "Elimino un elemento y en la raíz queda 'm'."
    );
    
    heap_eliminar_raiz(heap);
    afirmar(
        *(char*) heap_raiz(heap) == 'n',
        "Elimino un elemento y en la raíz queda 'n'."
    );
    
    heap_eliminar_raiz(heap);
    afirmar(
        *(char*) heap_raiz(heap) == 'r',
        "Elimino un elemento y en la raíz queda 'r'."
    );
    
    heap_destruir(heap);
}

void pruebas_heap_maximal_sin_destructor()
{
    probar_eliminar_sin_destructor();
    probar_raiz_maximal();
}

void pruebas_heap_minimal_con_destructor()
{
    probar_eliminar_con_destructor();
    probar_raiz_minimal();
}

void prueba_de_carga()
{
    nuevo_grupo("Prueba de carga");
    heap_t* heap = heap_crear(comparador_minimal, free);
    size_t cant_a_insertar = 100000, i = 0;
    for(size_t j = 0; j < cant_a_insertar; j++)
    {
        i += heap_insertar(heap, creador((char)j)) == 0? 1 : 0;
    }
    afirmar(
        i == cant_a_insertar,
        "Se insertaron 100000 elementos sin errores."
    );
    afirmar(
        heap_cantidad(heap) == cant_a_insertar,
        "Hay 100000 elementos."
    );
    heap_destruir(heap);
}

void ejecutar_pruebas() {
    probar_crear();
    probar_insertar();
    pruebas_heap_maximal_sin_destructor();
    pruebas_heap_minimal_con_destructor();
    prueba_de_carga();
}
