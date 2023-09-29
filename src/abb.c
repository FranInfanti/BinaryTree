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
			    struct nodo_abb *anterior,
			    abb_comparador comparador)
{
	if (actual == NULL)
		return anterior;
	if (comparador(actual->elemento, elemento) >= 0)
		return buscar_fin(elemento, actual->izquierda, actual,
				  comparador);
	else
		return buscar_fin(elemento, actual->derecha, actual,
				  comparador);
}

/*
 * Busca el elemento pasado por parametro en el arbol, si lo encuentra lo devuelve.
 * Si no lo encuentra devuelve NULL.
 */
void *buscar_elemento(void *elemento, struct nodo_abb *actual,
		      abb_comparador comparador)
{
	if (actual == NULL)
		return NULL;
	if (comparador(elemento, actual->elemento) == 0)
		return actual->elemento;
	else if (comparador(elemento, actual->elemento) > 0)
		return buscar_elemento(elemento, actual->derecha, comparador);
	else
		return buscar_elemento(elemento, actual->izquierda, comparador);
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

void recorrido_preorden(struct nodo_abb *actual, bool (*f)(void *, void *),
			void *aux, size_t *n, bool *sigo)
{
	if (actual == NULL || !(*sigo))
		return;

	if (!f(actual->elemento, aux))
		*sigo = false;

	if (*sigo)
		recorrido_preorden(actual->izquierda, f, aux, n, sigo);
	if (*sigo)
		recorrido_preorden(actual->derecha, f, aux, n, sigo);
	if (*sigo)
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
	else if (arbol->comparador(ultimo->elemento, nuevo->elemento) > 0)
		ultimo->izquierda = nuevo;
	else
		ultimo->derecha = nuevo;
	arbol->tamanio++;
	return arbol;
}

void *abb_quitar(abb_t *arbol, void *elemento)
{
	return elemento;
}

void *abb_buscar(abb_t *arbol, void *elemento)
{
	if (arbol == NULL)
		return NULL;
	if (arbol->tamanio == 0)
		return NULL;

	return buscar_elemento(elemento, arbol->nodo_raiz, arbol->comparador);
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
	bool sigo_recorriendo = true;
	if (recorrido == PREORDEN)
		recorrido_preorden(arbol->nodo_raiz, funcion, aux, &contador,
				   &sigo_recorriendo);

	return contador;
}

size_t abb_recorrer(abb_t *arbol, abb_recorrido recorrido, void **array,
		    size_t tamanio_array)
{
	return 0;
}
