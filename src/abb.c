#include "abb.h"
#include "abb_estructura_privada.h"
#include <stddef.h>
#include <stdlib.h>

/*
 * Crea un nodo con el elemento pasado por parametro.
 */
struct nodo_abb *crear_nodo(void *elemento)
{
	struct nodo_abb *nodo = calloc(1, sizeof(struct nodo_abb));
	if (nodo == NULL)
		return NULL;
	nodo->elemento = elemento;
	return nodo;
}

/*
 * Recorre el arbol hasta encontrar la posicion donde se puede insertar el nuevo elemento.
 * Una vez la encuentre devuelve un puntero a su padre.
 */
struct nodo_abb *buscar_fin(void *elemento, struct nodo_abb *actual,
			    struct nodo_abb *anterior, abb_comparador f)
{
	if (actual == NULL)
		return anterior;
	if (f(actual->elemento, elemento) >= 0)
		return buscar_fin(elemento, actual->izquierda, actual, f);
	else
		return buscar_fin(elemento, actual->derecha, actual, f);
}

/*
 * Busca el elemento pasado por parametro en el arbol, si lo encuentra lo devuelve.
 * Si no lo encuentra devuelve NULL.
 */
void *busqueda_binaria(void *elemento, struct nodo_abb *actual,
		       abb_comparador f)
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
void eliminar_nodos(struct nodo_abb *actual, void (*destructor)(void *))
{
	if (actual == NULL)
		return;

	eliminar_nodos(actual->izquierda, destructor);
	eliminar_nodos(actual->derecha, destructor);
	if (destructor != NULL)
		destructor(actual->elemento);
	free(actual);
	return;
}

/*
 * 
 * 
 */
bool recorrido_preorden_it(struct nodo_abb *actual, bool (*f)(void *, void *),
			   void *aux, size_t *n)
{
	if (actual == NULL)
		return true;
	(*n)++;
	if (f(actual->elemento, aux)) {
		if (recorrido_preorden_it(actual->izquierda, f, aux, n))
			return recorrido_preorden_it(actual->derecha, f, aux,
						     n);
		return false;
	}
	return false;
}

/*
 * 
 * 
 */
bool recorrido_inorden_it(struct nodo_abb *actual, bool (*f)(void *, void *),
			  void *aux, size_t *n)
{
	if (actual == NULL)
		return true;

	if (recorrido_inorden_it(actual->izquierda, f, aux, n)) {
		(*n)++;
		if (f(actual->elemento, aux))
			return recorrido_inorden_it(actual->derecha, f, aux, n);
		return false;
	}
	return false;
}

/*
 * 
 * 
 */
bool recorrido_postorden_it(struct nodo_abb *actual, bool (*f)(void *, void *),
			    void *aux, size_t *n)
{
	if (actual == NULL)
		return true;

	if (recorrido_postorden_it(actual->izquierda, f, aux, n)) {
		if (recorrido_postorden_it(actual->derecha, f, aux, n)) {
			(*n)++;
			return f(actual->elemento, aux);
		}
		return false;
	}
	return false;
}

void cargar_vector_preorden(struct nodo_abb *actual, void **array, size_t tope,
			    size_t *n)
{
	if (actual == NULL)
		return;
	if (*n == tope)
		return;
	array[*n] = actual->elemento;
	(*n)++;
	cargar_vector_preorden(actual->izquierda, array, tope, n);
	cargar_vector_preorden(actual->derecha, array, tope, n);
}

void cargar_vector_inorden(struct nodo_abb *actual, void **array, size_t tope,
			   size_t *n)
{
	if (actual == NULL)
		return;
	if (*n == tope)
		return;
	cargar_vector_inorden(actual->izquierda, array, tope, n);
	array[*n] = actual->elemento;
	(*n)++;
	cargar_vector_inorden(actual->derecha, array, tope, n);
}

void cargar_vector_postorden(struct nodo_abb *actual, void **array, size_t tope,
			     size_t *n)
{
	if (actual == NULL)
		return;
	cargar_vector_postorden(actual->izquierda, array, tope, n);
	cargar_vector_postorden(actual->derecha, array, tope, n);
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

	struct nodo_abb *nuevo = crear_nodo(elemento);
	if (nuevo == NULL)
		return NULL;

	struct nodo_abb *ultimo =
		buscar_fin(elemento, arbol->nodo_raiz, NULL, arbol->comparador);
	if (ultimo == NULL)
		arbol->nodo_raiz = nuevo;
	else if (arbol->comparador(ultimo->elemento, elemento) >= 0)
		ultimo->izquierda = nuevo;
	else
		ultimo->derecha = nuevo;
	arbol->tamanio++;
	return arbol;
}

void *abb_quitar(abb_t *arbol, void *elemento)
{
	if (arbol == NULL)
		return NULL;
	return elemento;
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
	if (arbol == NULL)
		return true;
	return arbol->tamanio == 0;
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
		eliminar_nodos(arbol->nodo_raiz, NULL);
	free(arbol);
}

void abb_destruir_todo(abb_t *arbol, void (*destructor)(void *))
{
	if (arbol == NULL)
		return;
	if (arbol->tamanio != 0)
		eliminar_nodos(arbol->nodo_raiz, destructor);
	free(arbol);
}

size_t abb_con_cada_elemento(abb_t *arbol, abb_recorrido recorrido,
			     bool (*funcion)(void *, void *), void *aux)
{
	if (arbol == NULL || funcion == NULL)
		return 0;

	size_t contador = 0;
	if (recorrido == PREORDEN)
		recorrido_preorden_it(arbol->nodo_raiz, funcion, aux,
				      &contador);
	else if (recorrido == INORDEN)
		recorrido_inorden_it(arbol->nodo_raiz, funcion, aux, &contador);
	else if (recorrido == POSTORDEN)
		recorrido_postorden_it(arbol->nodo_raiz, funcion, aux,
				       &contador);

	return contador;
}

size_t abb_recorrer(abb_t *arbol, abb_recorrido recorrido, void **array,
		    size_t tamanio_array)
{
	if (arbol == NULL || array == NULL)
		return 0;

	size_t cantidad = 0;

	if (recorrido == PREORDEN)
		cargar_vector_preorden(arbol->nodo_raiz, array, tamanio_array,
				       &cantidad);
	else if (recorrido == INORDEN)
		cargar_vector_inorden(arbol->nodo_raiz, array, tamanio_array,
				      &cantidad);
	else if (recorrido == POSTORDEN)
		cargar_vector_postorden(arbol->nodo_raiz, array, tamanio_array,
					&cantidad);

	return cantidad;
}
