#include "../tda/abb.h"
#include "pa2mm_2.h"

#define ERROR -1
#define SIN_ERROR 0

void ejecutar_pruebas(int argc, char** argv);

int main(int argc, char** argv) {
    ejecutar_pruebas(argc, argv);
    mostrar_reporte();
    return 0;
}

/*
 * Actualiza el valor que se encuentra en una dirección de memoria.
 *
 * Argumentos:
 *  -   numero: dirección de memoria disponible para un entero.
 *  -   valor: valor a inicializar en la memoria.
 */
int* actualizar(int* numero, int valor) {
    *numero = valor;
    return numero;
}

/*
 * Devuelve un puntero a un entero que se encuentra en el heap.
 *
 * Argumentos:
 *  -   entero: valor a inicializar en el heap.
 */
int* crear(int entero) {
    int* mi_entero = malloc(sizeof(int));
    if (mi_entero)
        *mi_entero = entero;
    return mi_entero;
}

/*
 * Recibe dos punteros. Los castea a entero y devuelve la diferencia
 * del primero y el segundo. Si recibe NULL se interpreta por 0.
 *
 * Argumentos:
 *  -   _num1: apunta a un entero.
 *  -   _num2: apunta a un entero.
 */
int mi_comparador(void* _num1, void* _num2) {
    int num1 = _num1 ? *(int*) _num1 : 0,
        num2 = _num2 ? *(int*) _num2 : 0;
    return num1 - num2;
}

/*
 * Recibe dos punteros. Los castea a entero y devuelve la diferencia
 * del primero y el segundo. Si recibe NULL se interpreta por 0.
 * Devuelve true si debe detenerse.
 *
 * Argumentos:
 *  -   _num1: apunta a un entero.
 *  -   _num2: apunta a un entero.
 */
bool sumar(void* _num1, void* _num2) {
    int num1 = _num1 ? *(int*) _num1 : 0;
    *(int*)_num2 += num1;
    return false;
}

/*
 * Recibe un puntero a un elemento y a un contador.
 * El elemento se castea a entero o es 0 si es NULL.
 * Si es negativo se aumenta el contador en 1.
 *
 * Argumentos:
 *  -   _num: puntero a un entero.
 *  -   _total: puntero a un contador.
 */
bool contar_negativos(void* _num, void* _total) {
    bool cuento = ( _num ? *(int*) _num : 0 ) < 0;
    *(int*)_total += cuento;
    return !cuento;
}

/*
 * Prueba que arbol_crear devuelve NULL en las ocasiones que la creación
 * del árbol debe fallar.
 */
void probar_abb_crear() {
    nuevo_grupo("Pruebas de arbol_crear");
    abb_t *arbol = arbol_crear(NULL, NULL);
    afirmar(arbol == NULL, "No se crea un árbol sin comparador y sin destructor.");
    arbol_destruir(arbol);

    arbol = arbol_crear(NULL, free);
    afirmar(arbol == NULL, "No se crea un árbol sin comparador y con destructor.");
    arbol_destruir(arbol);

    arbol = arbol_crear(mi_comparador, NULL);
    afirmar(arbol != NULL, "Se crea un árbol con comparador y sin destructor.");
    arbol_destruir(arbol);

    arbol = arbol_crear(mi_comparador, free);
    afirmar(arbol != NULL, "Se crea un árbol con comparador y con destructor.");
    arbol_destruir(arbol);
}

/*
 * Pruebo que arbol_insertar devuelve ERROR y SIN_ERROR.
 * Se debe poder crear un árbol con arbol_crear.
 */
void probar_abb_insertar() {
    nuevo_grupo("Pruebas de arbol_insertar");
    int dato1, dato2;
    dato1 = dato2 = 5;
    abb_t *arbol = NULL;
    afirmar(arbol_insertar(arbol, &dato1) == ERROR,
		"Si dejo mi árbol NULL, no inserto.");

    arbol = arbol_crear(mi_comparador, NULL);
    afirmar(arbol_insertar(arbol, &dato1) == SIN_ERROR,
		"Si creo mi árbol, puedo insertar un elemento.");

    afirmar(arbol_insertar(arbol, NULL) == SIN_ERROR,
		"Inserto NULL.");

    afirmar(arbol_insertar(arbol, &dato2) == SIN_ERROR,
		"Inserto una clave duplicada.");
	
    arbol_destruir(arbol);
}

/*
 * Pruebo que arbol_borrar devuelve ERROR y SIN_ERROR.
 * Se debe poder crear un árbol con arbol_crear e insertar con arbol_insertar.
 */
void probar_abb_borrar() {
    nuevo_grupo("Pruebas de arbol_borrar");
    int dato1, dato2;
    dato1 = dato2 = 5;
    abb_t *arbol = NULL;
    afirmar(arbol_borrar(arbol, &dato1) == ERROR,
		"Si dejo mi árbol NULL y borro da error.");

    arbol = arbol_crear(mi_comparador, NULL);
    afirmar(arbol_borrar(arbol, &dato1) == ERROR,
		"Si creo mi árbol y borro un elemento que no ingresé da error.");

    arbol_insertar(arbol, &dato1);
    afirmar(arbol_borrar(arbol, &dato1) == SIN_ERROR,
		"Puedo borrar un elemento.");

    arbol_insertar(arbol, &dato2);
    arbol_insertar(arbol, NULL);
    arbol_borrar(arbol, &dato1); // Borro por su clave.
    afirmar(arbol_borrar(arbol, &dato2) == ERROR,
		"No puedo borrar un elemento que ya eliminé.");

    afirmar(arbol_borrar(arbol, NULL) == SIN_ERROR,
		"Puedo borrar NULL.");

    arbol_destruir(arbol);
}

/*
 * Pruebo que la función arbol_buscar devuelva el elemento del árbol buscado o NULL.
 * Se debe poder crear un árbol con arbol_crear e insertar con arbol_insertar.
 */
void probar_abb_buscar() {
    nuevo_grupo("Pruebas de arbol_buscar");
    abb_t* arbol = NULL;
    int buscado;
    afirmar(arbol_buscar(arbol, actualizar(&buscado, 2)) == NULL,
		"Devuelve NULL si no tengo un árbol.");

    arbol = arbol_crear(mi_comparador, free);
    afirmar(arbol_buscar(arbol, &buscado) == NULL,
		"Devuelve NULL si no está el elemento buscado.");

    arbol_insertar(arbol, crear(2));
    afirmar(arbol_buscar(arbol, &buscado) != NULL,
		"No devuelve NULL si encuentra un elemento.");
    
    afirmar(arbol_buscar(arbol, &buscado) != &buscado,
		"No me devuelve un elemento que no está en el árbol.");
    
    afirmar(*(int*) arbol_buscar(arbol, &buscado) == 2,
		"El elemento que encuentra es el que esperaba.");
		
    arbol_destruir(arbol);
}

/*
 * Pruebo que arbol_raiz devuelve el elemento adecuado.
 * Se debe poder crear un árbol con arbol_crear, insertar con arbol_insertar y
 * borrar con arbol_borrar.
 */
void probar_abb_raiz() {
    nuevo_grupo("Pruebas de arbol_raíz");
    abb_t *arbol = NULL;
    afirmar(arbol_raiz(arbol) == NULL, "Si dejo mi árbol en NULL, su raíz es NULL.");

    arbol = arbol_crear(mi_comparador, free);
    afirmar(arbol_raiz(arbol) == NULL, "Después de crear el árbol, su raíz es NULL.");

    arbol_insertar(arbol, crear(2));
    afirmar(*(int*) arbol_raiz(arbol) == 2,
        "Si inserto un elemento, se vuelve raíz.");

    arbol_insertar(arbol, crear(0));
    afirmar(*(int*) arbol_raiz(arbol) == 2,
        "Si inserto un elemento menor, la raíz sigue siendo la misma.");

    arbol_insertar(arbol, crear(4));
    afirmar(*(int*) arbol_raiz(arbol) == 2,
        "Si inserto un elmento mayor, la raíz sigue siendo la misma.");

    arbol_borrar(arbol, arbol_raiz(arbol));
    afirmar(*(int*) arbol_raiz(arbol) == 0,
        "Si elimino la raíz, el elemento menor pasa a ser la raíz.");

    arbol_borrar(arbol, arbol_raiz(arbol));
    afirmar(*(int*) arbol_raiz(arbol) == 4,
        "Si elimino la raíz, el elemento mayor pasa a ser la raíz");

    arbol_destruir(arbol);
}

/*
 * Pruebo que arbol_vacio devuelva el valor bool adecuado.
 * Se debe poder crear un árbol con arbol_crear, insertar arbol_insertar y
 * borrar con arbol_borrar.
 */
void probar_abb_vacio() {
    nuevo_grupo("Pruebas de arbol_vacio");
    abb_t *arbol = NULL;
    afirmar(arbol_vacio(arbol) == true, "Si dejo mi árbol NULL, está vacío.");

    arbol = arbol_crear(mi_comparador, free);
    afirmar(arbol_vacio(arbol) == true, "Si creo mi árbol, este está vacío.");

    arbol_insertar(arbol, crear(2));
    afirmar(arbol_vacio(arbol) == false, "Si inserto un elemento, el árbol no está vacío.");

    arbol_insertar(arbol, crear(3));
    afirmar(arbol_vacio(arbol) == false, "Cargo más elementos, el árbol no está vacío.");

    arbol_borrar(arbol, arbol_raiz(arbol));
    afirmar(arbol_vacio(arbol) == false, "Elimino un elemento, el árbol no está vacío.");

    arbol_borrar(arbol, arbol_raiz(arbol));
    afirmar(arbol_vacio(arbol) == true, "Borro elementos; árbol vuelve a estar vacío.");

    arbol_destruir(arbol);
}

/*
 * Pruebo que arbol_recorrido_inorden devuelva el valor adecuado y que en el array guarde
 * los elementos que corresponden.
 */
void probar_abb_recorrido_inorden(abb_t* arbol, int** elementos) {
    nuevo_grupo("Pruebas con arbol_recorrido_inorden");
    afirmar(arbol_recorrido_inorden(NULL, (void**)elementos, 10) == 0,
		"No puedo recorrer sin un árbol.");

    afirmar(arbol_recorrido_inorden(arbol, NULL, 10) == 0,
		"No puedo recorrer sin un vector.");

    afirmar(arbol_recorrido_inorden(arbol, (void**)elementos, 3) == 3,
        "Se recorrieron 3 elementos inorden.");
    afirmar(**(elementos + 0) == -3 && **(elementos + 1) == -2 && **(elementos + 2) == -1,
        "Se obtieron los elementos esperados.");

    afirmar(arbol_recorrido_inorden(arbol, (void**)elementos, 10) == 7,
        "Se recorrieron todos los elementos inorden.");
    afirmar(**(elementos + 4) == 1 && **(elementos + 5) == 2 && **(elementos + 6) == 3,
        "Se obtieron los elementos esperados.");
}

/*
 * Pruebo que arbol_recorrido_preorden devuelva el valor adecuado y que en el array guarde
 * los elementos que corresponden.
 */
void probar_abb_recorrido_preorden(abb_t* arbol, int** elementos) {
    nuevo_grupo("Pruebas con arbol_recorrido_preorden");
    afirmar(arbol_recorrido_preorden(NULL, (void**)elementos, 10) == 0,
		"No puedo recorrer sin un árbol.");

    afirmar(arbol_recorrido_preorden(arbol, NULL, 10) == 0,
		"No puedo recorrer sin un vector.");

    afirmar(arbol_recorrido_preorden(arbol, (void**)elementos, 3) == 3,
        "Se recorrieron 3 elementos preorden.");
    afirmar(**(elementos + 0) == 0 && **(elementos + 1) == -2 && **(elementos + 2) == -3,
        "Se obtieron los elementos esperados.");

    afirmar(arbol_recorrido_preorden(arbol, (void**)elementos, 10) == 7,
        "Se recorrieron todos los elementos preorden.");
    afirmar(**(elementos + 4) == 2 && **(elementos + 5) == 1 && **(elementos + 6) == 3,
        "Se obtieron los elementos esperados.");
}

/*
 * Pruebo que arbol_recorrido_postorden devuelva el valor adecuado y que en el array guarde
 * los elementos que corresponden.
 */
void probar_abb_recorrido_postorden(abb_t* arbol, int** elementos) {
    nuevo_grupo("Pruebas con arbol_recorrido_postorden");
    afirmar(arbol_recorrido_postorden(NULL, (void**)elementos, 10) == 0,
		"No puedo recorrer sin un árbol.");

    afirmar(arbol_recorrido_postorden(arbol, NULL, 10) == 0,
		"No puedo recorrer sin un vector.");

    afirmar(arbol_recorrido_postorden(arbol, (void**)elementos, 3) == 3,
        "Se recorrieron 3 elementos postorden.");
    afirmar(**(elementos + 0) == -3 && **(elementos + 1) == -1 && **(elementos + 2) == -2,
        "Se obtieron los elementos esperados.");

    afirmar(arbol_recorrido_postorden(arbol, (void**)elementos, 10) == 7,
        "Se recorrieron todos los elementos postorden.");
    afirmar(**(elementos + 4) == 3 && **(elementos + 5) == 2 && **(elementos + 6) == 0,
        "Se obtieron los elementos esperados.");
}

/*
 * Setéa las condiciones para probar las funciones de recorridos inorden, preorden y postorden.
 */
void probar_abb_recorridos() {
    abb_t* arbol = arbol_crear(mi_comparador, free);
    arbol_insertar(arbol, crear(0));
    arbol_insertar(arbol, crear(-2));
    arbol_insertar(arbol, crear(2));
    arbol_insertar(arbol, crear(-3));
    arbol_insertar(arbol, crear(3));
    arbol_insertar(arbol, crear(-1));
    arbol_insertar(arbol, crear(1));

    int **elementos = calloc(10, sizeof(int*));
    probar_abb_recorrido_inorden(arbol, elementos);
    probar_abb_recorrido_preorden(arbol, elementos);
    probar_abb_recorrido_postorden(arbol, elementos);
    arbol_destruir(arbol);
    free(elementos);
}

/*
 * Prueba que la funcion abb_con_cada_elemento itere bien en ABB_RECORRER_INORDEN
 */
void probar_abb_itera_inorder(abb_t* arbol) {
    nuevo_grupo("Pruebas abb_con_cada_elemento inorden");
    size_t total;
    afirmar(abb_con_cada_elemento(NULL, ABB_RECORRER_INORDEN, NULL, &total) == 0,
        "Iterar inorden sin un árbol devuelve 0.");

    afirmar(abb_con_cada_elemento(arbol, ABB_RECORRER_INORDEN, NULL, &total) == 0,
        "Iterar inorden sin una función devuelve 0.");

    total = 0;
    afirmar(abb_con_cada_elemento(arbol, ABB_RECORRER_INORDEN, sumar, &total) == 10,
        "Iterar inorden en un árbol devuelve la cantidad de elementos recorridos.");
    afirmar(total == 13, "Se operó correctamente.");

    total = 0;
    afirmar(abb_con_cada_elemento(arbol, ABB_RECORRER_INORDEN, contar_negativos, &total) == 4,
        "Se cuentan los negativos inorden, devuelve la cantidad de elementos recorridos.");
    afirmar(total == 3, "Se operó correctamente.");
}

/*
 * Prueba que la funcion abb_con_cada_elemento itere bien en ABB_RECORRER_PREORDEN
 */
void probar_abb_itera_preorder(abb_t* arbol) {
    nuevo_grupo("Pruebas abb_con_cada_elemento preorden");
    size_t total;
    afirmar(abb_con_cada_elemento(NULL, ABB_RECORRER_PREORDEN, sumar, &total) == 0,
        "Iterar preorden sin un árbol devuelve 0.");

    afirmar(abb_con_cada_elemento(arbol, ABB_RECORRER_PREORDEN, NULL, &total) == 0,
        "Iterar preorden sin una función devuelve 0.");

    total = 0;
    afirmar(abb_con_cada_elemento(arbol, ABB_RECORRER_PREORDEN, sumar, &total) == 10,
        "Iterar preorden en un árbol devuelve la cantidad de elementos recorridos.");
    afirmar(total == 13, "Se operó correctamente.");

    total = 0;
    afirmar(abb_con_cada_elemento(arbol, ABB_RECORRER_PREORDEN, contar_negativos, &total) == 1,
        "Se cuentan los negativos preorden, devuelve la cantidad de elementos recorridos.");
    afirmar(total == 0, "Se operó correctamente.");
}

/*
 * Prueba que la funcion abb_con_cada_elemento itere bien en ABB_RECORRER_PREORDEN
 */
void probar_abb_itera_postorder(abb_t* arbol) {
    nuevo_grupo("Pruebas abb_con_cada_elemento postorden");
    size_t total;

    afirmar(abb_con_cada_elemento(NULL, ABB_RECORRER_POSTORDEN, sumar, &total) == 0,
        "Iterar postorden sin un árbol devuelve 0.");

    afirmar(abb_con_cada_elemento(arbol, ABB_RECORRER_POSTORDEN, NULL, &total) == 0,
        "Iterar postorden sin una función devuelve 0.");

    total = 0;
    afirmar(abb_con_cada_elemento(arbol, ABB_RECORRER_POSTORDEN, sumar, &total) == 10,
        "Iterar postorden en unárbol devuelve la cantidad de elementos recorridos.");
    afirmar(total == 13, "Se operó correctamente.");

    total = 0;
    afirmar(abb_con_cada_elemento(arbol, ABB_RECORRER_POSTORDEN, contar_negativos, &total) == 2,
        "Se cuentan los negativos postorden, devuelve la cantidad de elementos recorridos.");
    afirmar(total == 1, "Se operó correctamente.");
}

/*
 * Pruebas con iterador. Se verifica que las funciones de arbol_recorrido_inorder,
 * arbol_recorrido_preorden, y arbol_recorrido_postorden funcionen correctamente con el
 * mismo set de datos.
 */
void probar_abb_iterador() {
    nuevo_grupo("Pruebas con abb_con_cada_elemento");
    abb_t* arbol = arbol_crear(mi_comparador, free);
    arbol_insertar(arbol, crear(10));
    arbol_insertar(arbol, crear(-2));
    arbol_insertar(arbol, crear(12));
    arbol_insertar(arbol, crear(-30));
    arbol_insertar(arbol, crear(3));
    arbol_insertar(arbol, crear(-1));
    arbol_insertar(arbol, crear(21));
    arbol_insertar(arbol, crear(0));
    arbol_insertar(arbol, crear(0));
    arbol_insertar(arbol, crear(0));

    size_t total;
    afirmar(abb_con_cada_elemento(arbol, 3, sumar, &total) == 0,
        "No se puede iterar de otra manera que no sea inorden, preorden o postorden.");
    probar_abb_itera_inorder(arbol);
    probar_abb_itera_preorder(arbol);
    probar_abb_itera_postorder(arbol);
    arbol_destruir(arbol);
}

/*
 * Pruebas con varias inserciones. Los elementos que son insertados
 * se pueden buscar.
 */
void probar_abb_inserto_y_busco(abb_t** _arbol) {
    nuevo_grupo("Pruebas inserto y busco");
    abb_t *arbol = arbol_crear(mi_comparador, free);
    size_t insertados = 0;
    int i, datos[] = { 50, 60, 30, 40, 20, 55, 70, 35, 66, 45, 10, 80},
        *buscado = malloc (sizeof(int));
    for (i = 0; i < sizeof(datos) / sizeof(int); i++)
        insertados += arbol_insertar(arbol, crear(datos[i])) == 0 ? 1 : 0;

    afirmar(insertados == i,
        "Se insertaron todos los elementos.");

    afirmar(arbol_insertar(arbol, NULL) == SIN_ERROR, "Inserto NULL.")

    afirmar(arbol_insertar(arbol, NULL) == SIN_ERROR, "Vuelvo a insertar NULL.")

    afirmar(*(int*)arbol_buscar(arbol, actualizar(buscado, 80)) == 80,
        "Puedo encontrar el 80.");

    afirmar(*(int*)arbol_buscar(arbol, actualizar(buscado, 10)) == 10,
        "Puedo encontrar el 10.");

    afirmar(*(int*)arbol_buscar(arbol, actualizar(buscado, 45)) == 45,
        "Puedo encontrar el 45.");

    afirmar(*(int*)arbol_buscar(arbol, actualizar(buscado, 66)) == 66,
        "Puedo encontrar el 66.");

    afirmar(*(int*)arbol_buscar(arbol, actualizar(buscado, 35)) == 35,
        "Puedo encontrar el 35.");

    afirmar(*(int*)arbol_buscar(arbol, actualizar(buscado, 70)) == 70,
        "Puedo encontrar el 70.");

    afirmar(*(int*)arbol_buscar(arbol, actualizar(buscado, 55)) == 55,
        "Puedo encontrar el 55.");

    afirmar(*(int*)arbol_buscar(arbol, actualizar(buscado, 20)) == 20,
        "Puedo encontrar el 20.");

    afirmar(*(int*)arbol_buscar(arbol, actualizar(buscado, 40)) == 40,
        "Puedo encontrar el 40.");

    afirmar(*(int*)arbol_buscar(arbol, actualizar(buscado, 30)) == 30,
        "Puedo encontrar el 30.");

    afirmar(*(int*)arbol_buscar(arbol, actualizar(buscado, 60)) == 60,
        "Puedo encontrar el 60.");

    afirmar(*(int*)arbol_buscar(arbol, actualizar(buscado, 50)) == 50,
        "Puedo encontrar el 50.");

    afirmar(*(int*)arbol_raiz(arbol) == 50,
        "El 50 es raíz.");

    afirmar(arbol_buscar(arbol, actualizar(buscado, 1)) == NULL,
        "No encuentro un 1.");

    afirmar(arbol_buscar(arbol, actualizar(buscado, 54)) == NULL,
        "No encuentro un 54.");

    afirmar(arbol_buscar(arbol, actualizar(buscado, 99)) == NULL,
        "No encuentro un 99.");

    free(buscado);
    *_arbol = arbol;
}

/*
 * Pruebas borrando diferentes casos. Se verifica que la estructura del
 * árbol sea la esperada.
 */
void probar_abb_borro_y_busco(abb_t* arbol) {
    nuevo_grupo("Pruebas borro y busco");
    int *buscado = malloc(sizeof(int));

    afirmar(arbol_borrar(arbol, actualizar(buscado, 55)) == SIN_ERROR,
        "Borro el 55 - Es hoja.");
    afirmar(arbol_buscar(arbol, actualizar(buscado, 55)) == NULL,
        "No puedo encontrar el 55.");

    afirmar(arbol_borrar(arbol, actualizar(buscado, 70)) == SIN_ERROR,
        "Borro el 70 - Tiene 2 hojas.");
    afirmar(arbol_buscar(arbol, actualizar(buscado, 70)) == NULL,
        "No puedo encontrar el 70.");

    afirmar(arbol_borrar(arbol, actualizar(buscado, 60)) == SIN_ERROR,
        "Borro el 60 - Tiene una rama.");
    afirmar(arbol_buscar(arbol, actualizar(buscado, 60)) == NULL,
        "No puedo encontrar el 60.");

    afirmar(arbol_borrar(arbol, actualizar(buscado, 30)) == SIN_ERROR,
        "Borro el 30 - Tiene dos ramas.");
    afirmar(arbol_buscar(arbol, actualizar(buscado, 30)) == NULL,
        "No puedo encontrar el 30.");

    afirmar(arbol_borrar(arbol, actualizar(buscado, 50)) == SIN_ERROR,
        "Borro el 50 - Es raíz.");
    afirmar(arbol_buscar(arbol, actualizar(buscado, 50)) == NULL,
        "No puedo encontrar el 50.");

    afirmar(arbol_borrar(arbol, actualizar(buscado, 66)) == SIN_ERROR,
        "Borro el 66.");
    afirmar(arbol_buscar(arbol, actualizar(buscado, 66)) == NULL,
        "No puedo encontrar el 66.");

    afirmar(arbol_borrar(arbol, actualizar(buscado, 80)) == SIN_ERROR,
        "Borro el 80.");
    afirmar(arbol_buscar(arbol, actualizar(buscado, 80)) == NULL,
        "No puedo encontrar el 80.");

    afirmar(arbol_borrar(arbol, actualizar(buscado, 45)) == SIN_ERROR,
        "Borro el 45.");
    afirmar(arbol_borrar(arbol, buscado) != SIN_ERROR,
        "No puedo borra el 45 de nuevo.");

    afirmar(arbol_borrar(arbol, NULL) == SIN_ERROR,
        "Borro el NULL.");
    afirmar(arbol_borrar(arbol, NULL) == SIN_ERROR,
        "Vuelvo a borrar el NULL de nuevo.");

    afirmar(*(int*)arbol_buscar(arbol, actualizar(buscado, 10)) == 10,
        "Puedo encontrar el 10.");

    afirmar(*(int*)arbol_buscar(arbol, actualizar(buscado, 35)) == 35,
        "Puedo encontrar el 35.");

    afirmar(*(int*)arbol_buscar(arbol, actualizar(buscado, 40)) == 40,
        "Puedo encontrar el 40.");

    afirmar(*(int*)arbol_raiz(arbol) == 20, "El 20 quedó como raíz");

    free(buscado);
}

/*
 * Se aumenta el grado de casos y complejidad de las operaciones. El correcto
 * funcionamiento de estas funcionen son necesarias para mantener las condiciones
 * del ABB.
 */
void pruebas_complicadas() {
    abb_t* arbol;
    probar_abb_inserto_y_busco(&arbol);
    probar_abb_borro_y_busco(arbol);
    arbol_destruir(arbol);
}

/*
 * Se ejecutan todas las pruebas.
 */
void ejecutar_pruebas(int argc, char** argv) {
    probar_abb_crear();
    probar_abb_insertar();
    probar_abb_borrar();
    probar_abb_buscar();
    probar_abb_raiz();
    probar_abb_vacio();
    pruebas_complicadas();
    probar_abb_recorridos();
    probar_abb_iterador();
}
