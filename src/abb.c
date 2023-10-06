#include "abb.h"
#include "abb_estructura_privada.h"
#include <stddef.h>
#include <stdlib.h>

/*
 * Crea un nodo con el elemento pasado por parametro.
 */
nodo_abb_t *crear_nodo(void *elemento)
{
	nodo_abb_t *nodo = calloc(1, sizeof(nodo_abb_t));
	if (nodo == NULL)
		return NULL;
	nodo->elemento = elemento;
	return nodo;
}

/*
 * Inserta un nuevo elemento en el arbol de modo que se siga cumpliendo que es un ABB.
 */
void insertar_nodo(nodo_abb_t *nuevo, nodo_abb_t *actual, nodo_abb_t *anterior,
		   abb_comparador f)
{
	if (actual == NULL) {
		if (f(anterior->elemento, nuevo->elemento) >= 0)
			anterior->izquierda = nuevo;
		else
			anterior->derecha = nuevo;
		return;
	}
	if (f(actual->elemento, nuevo->elemento) >= 0)
		insertar_nodo(nuevo, actual->izquierda, actual, f);
	else
		insertar_nodo(nuevo, actual->derecha, actual, f);
}

/*
 * Busca el predecesor inorden a partir de actual.
 */
void *buscar_predecesor(nodo_abb_t *actual, nodo_abb_t *anterior)
{
	if (actual->derecha == NULL) {
		if (anterior != NULL)
			anterior->derecha = actual->izquierda;
		return actual;
	}
	return buscar_predecesor(actual->derecha, actual);
}

/*
 * Remplaza el nodo a eliminar con el predecesor inorden. Tambien devuelve el predecesor que remplazo 
 * al nodo eliminar.
 */
void *eliminar_dos_hijos(nodo_abb_t *eliminar, nodo_abb_t *anterior,
			 abb_comparador f)
{
	nodo_abb_t *predecesor = buscar_predecesor(eliminar->izquierda, NULL);

	predecesor->derecha = eliminar->derecha;
	if (eliminar->izquierda != predecesor)
		predecesor->izquierda = eliminar->izquierda;

	if (f(anterior->elemento, eliminar->elemento) >= 0)
		anterior->izquierda = predecesor;
	else
		anterior->derecha = predecesor;

	return predecesor;
}

/*
 * Elimina el nodo que tiene el elemento que se quiere eliminar.
 */
void *eliminar_nodo(abb_t *abb, nodo_abb_t *eliminar, nodo_abb_t *anterior)
{
	void *removido = eliminar->elemento;
	void *ptr = NULL;

	if (eliminar->derecha && eliminar->izquierda)
		ptr = eliminar_dos_hijos(eliminar, anterior, abb->comparador);

	else if (abb->comparador(anterior->elemento, removido) >= 0) {
		anterior->izquierda = eliminar->derecha == NULL ?
					      eliminar->izquierda :
					      eliminar->derecha;
		ptr = anterior->izquierda;
	} else {
		anterior->derecha = eliminar->derecha == NULL ?
					    eliminar->izquierda :
					    eliminar->derecha;
		ptr = anterior->derecha;
	}

	if (abb->comparador(abb->nodo_raiz->elemento, removido) == 0)
		abb->nodo_raiz = ptr;

	free(eliminar);
	abb->tamanio--;
	if (abb->tamanio == 0)
		abb->nodo_raiz = NULL;

	return removido;
}

/*
 * Busca y elimina el nodo que contiene el elemento.
 */
void *buscar_nodo(abb_t *abb, void *elemento, nodo_abb_t *actual,
		  nodo_abb_t *anterior)
{
	if (actual == NULL)
		return NULL;

	if (abb->comparador(actual->elemento, elemento) == 0)
		return eliminar_nodo(abb, actual, anterior);

	if (abb->comparador(actual->elemento, elemento) > 0)
		return buscar_nodo(abb, elemento, actual->izquierda, actual);

	return buscar_nodo(abb, elemento, actual->derecha, actual);
}

/*
 * Busca el elemento pasado por parametro en el arbol, si lo encuentra lo devuelve.
 * Si no lo encuentra devuelve NULL.
 */
void *busqueda_binaria(void *elemento, nodo_abb_t *actual, abb_comparador f)
{
	if (actual == NULL)
		return NULL;
	if (f(elemento, actual->elemento) == 0)
		return actual->elemento;
	else if (f(actual->elemento, elemento) > 0)
		return busqueda_binaria(elemento, actual->izquierda, f);
	else
		return busqueda_binaria(elemento, actual->derecha, f);
}

/*
 * Recorre el arbol usando el recorrido Postorden y libera la memoria ocupada por cada nodo. 
 */
void liberar_nodos(nodo_abb_t *actual, void (*destructor)(void *))
{
	if (actual == NULL)
		return;

	liberar_nodos(actual->izquierda, destructor);
	liberar_nodos(actual->derecha, destructor);
	if (destructor != NULL)
		destructor(actual->elemento);
	free(actual);
	return;
}

/*
 * Recorre el arbol en PREORDEN (NID) y le aplica a cada elemento del arbol la funcion f. 
 * Si esta devuelve false, se deja de recorrer y se devulve la cantidad de elementos a la que se le aplico la funcion.
 */
bool iterar_preorden(nodo_abb_t *actual, bool (*f)(void *, void *), void *aux,
		     size_t *n)
{
	if (actual == NULL)
		return true;

	(*n)++;
	if (!f(actual->elemento, aux))
		return false;
	if (!iterar_preorden(actual->izquierda, f, aux, n))
		return false;
	return iterar_preorden(actual->derecha, f, aux, n);
}

/*
 * Recorre el arbol en INORDEN (IND) y le aplica a cada elemento del arbol la funcion f. 
 * Si esta devuelve false, se deja de recorrer y se devulve la cantidad de elementos a la que se le aplico la funcion.
 */
bool iterar_inorden(nodo_abb_t *actual, bool (*f)(void*, void*), void *aux,
		    size_t *n)
{
	if (actual == NULL)
		return true;

	if (!iterar_inorden(actual->izquierda, f, aux, n))
		return false;
	(*n)++;
	if (!f(actual->elemento, aux))
		return false;
	return iterar_inorden(actual->derecha, f, aux, n);
}

/*
 * Recorre el arbol en POSTORDEN (IDN) y le aplica a cada elemento del arbol la funcion f. 
 * Si esta devuelve false, se deja de recorrer y se devulve la cantidad de elementos a la que se le aplico la funcion.
 */
bool iterar_postorden(nodo_abb_t *actual, bool (*f)(void *, void *), void *aux,
		      size_t *n)
{
	if (actual == NULL)
		return true;

	if (!iterar_postorden(actual->izquierda, f, aux, n))
		return false;
	if (!iterar_postorden(actual->derecha, f, aux, n))
		return false;
	(*n)++;
	return f(actual->elemento, aux);
}

/*
 * Recorre el arbol en PREORDEN (NID) y carga en el array los elementos de este hasta llegar al tope del array.
 */
void cargar_preorden(nodo_abb_t *actual, void **array, size_t tope, size_t *n)
{
	if (actual == NULL)
		return;
	if (*n == tope)
		return;
	array[*n] = actual->elemento;
	(*n)++;
	cargar_preorden(actual->izquierda, array, tope, n);
	cargar_preorden(actual->derecha, array, tope, n);
}

/*
 * Recorre el arbol en INORDEN (IND) y carga en el array los elementos de este hasta llegar al tope del array.
 */
void cargar_inorden(nodo_abb_t *actual, void **array, size_t tope, size_t *n)
{
	if (actual == NULL)
		return;

	cargar_inorden(actual->izquierda, array, tope, n);
	if (*n == tope)
		return;
	array[*n] = actual->elemento;
	(*n)++;
	cargar_inorden(actual->derecha, array, tope, n);
}

/*
 * Recorre el arbol en POSTORDEN (IDN) y carga en el array los elementos de este hasta llegar al tope del array.
 */
void cargar_postorden(nodo_abb_t *actual, void **array, size_t tope, size_t *n)
{
	if (actual == NULL)
		return;

	cargar_postorden(actual->izquierda, array, tope, n);
	cargar_postorden(actual->derecha, array, tope, n);

	if (*n == tope)
		return;
	array[*n] = actual->elemento;
	(*n)++;
	return;
}

abb_t *abb_crear(abb_comparador comparador)
{
	if (comparador == NULL)
		return NULL;
	struct abb *arbol = calloc(1, sizeof(struct abb));
	if (arbol == NULL)
		return NULL;
	arbol->comparador = comparador;
	return arbol;
}

abb_t *abb_insertar(abb_t *arbol, void *elemento)
{
	if (arbol == NULL)
		return NULL;

	nodo_abb_t *nuevo = crear_nodo(elemento);
	if (nuevo == NULL)
		return NULL;

	if (arbol->tamanio != 0)
		insertar_nodo(nuevo, arbol->nodo_raiz, NULL, arbol->comparador);
	else
		arbol->nodo_raiz = nuevo;
	arbol->tamanio++;
	return arbol;
}

void *abb_quitar(abb_t *arbol, void *elemento)
{
	if (arbol == NULL)
		return NULL;
	if (arbol->tamanio == 0)
		return NULL;

	return buscar_nodo(arbol, elemento, arbol->nodo_raiz, arbol->nodo_raiz);
}

void *abb_buscar(abb_t *arbol, void *elemento)
{
	if (arbol == NULL)
		return NULL;
	if (arbol->tamanio == 0)
		return NULL;
	return busqueda_binaria(elemento, arbol->nodo_raiz, arbol->comparador);
}

bool abb_vacio(abb_t *arbol)
{
	return arbol != NULL ? arbol->tamanio == 0 : true;
}

size_t abb_tamanio(abb_t *arbol)
{
	return arbol != NULL ? arbol->tamanio : 0;
}

void abb_destruir(abb_t *arbol)
{
	if (arbol == NULL)
		return;
	if (arbol->tamanio != 0)
		liberar_nodos(arbol->nodo_raiz, NULL);
	free(arbol);
}

void abb_destruir_todo(abb_t *arbol, void (*destructor)(void *))
{
	if (arbol == NULL)
		return;
	if (arbol->tamanio != 0)
		liberar_nodos(arbol->nodo_raiz, destructor);
	free(arbol);
}

size_t abb_con_cada_elemento(abb_t *arbol, abb_recorrido recorrido,
			     bool (*funcion)(void *, void *), void *aux)
{
	if (arbol == NULL || funcion == NULL)
		return 0;

	size_t cantidad = 0;
	if (recorrido == PREORDEN)
		iterar_preorden(arbol->nodo_raiz, funcion, aux, &cantidad);
	else if (recorrido == INORDEN)
		iterar_inorden(arbol->nodo_raiz, funcion, aux, &cantidad);
	else if (recorrido == POSTORDEN)
		iterar_postorden(arbol->nodo_raiz, funcion, aux, &cantidad);

	return cantidad;
}

size_t abb_recorrer(abb_t *arbol, abb_recorrido recorrido, void **array,
		    size_t tamanio_array)
{
	if (arbol == NULL || array == NULL)
		return 0;

	size_t cantidad = 0;
	if (recorrido == PREORDEN)
		cargar_preorden(arbol->nodo_raiz, array, tamanio_array,
				&cantidad);
	else if (recorrido == INORDEN)
		cargar_inorden(arbol->nodo_raiz, array, tamanio_array,
			       &cantidad);
	else if (recorrido == POSTORDEN)
		cargar_postorden(arbol->nodo_raiz, array, tamanio_array,
				 &cantidad);

	return cantidad;
}
