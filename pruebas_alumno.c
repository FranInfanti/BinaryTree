#include "pa2m.h"
#include "src/abb.h"
#include "mostrar_abb.h"
#include "src/abb_estructura_privada.h"

void formateador(void *nodo_)
{
	nodo_abb_t *nodo = nodo_;
	int i = *(int *)nodo->elemento;
	printf("%2d", i);
}

int comparador(void *e1, void *e2)
{
	int *numero = e1;
	int *otro_numero = e2;
	if (*numero == *otro_numero)
		return 0;
	else if (*numero > *otro_numero)
		return 1;
	else
		return -1;
}

void destructor(void *elemento)
{
	return;
}

bool sigo_recorriendo_sin_corte(void *e1, void *e2)
{
	return true;
}

bool sigo_recorriendo_con_corte(void *e1, void *e2)
{
	return e1 != e2;
}

void se_puede_crear_un_arbol()
{
	abb_t *arbol = abb_crear(comparador);
	pa2m_afirmar(arbol != NULL, "Puedo crear un arbol :)");
	abb_destruir(arbol);
}

void no_se_puede_crear_un_arbol_con_un_comparador_nulo()
{
	abb_t *arbol = abb_crear(NULL);
	pa2m_afirmar(arbol == NULL,
		     "No puede crearse un arbol con un comparador nulo");
}

void un_arbol_recien_creado_tiene_cero_elementos()
{
	abb_t *arbol = abb_crear(comparador);
	pa2m_afirmar(abb_tamanio(arbol) == 0,
		     "Un arbol recien creado tiene cero elementos");
	abb_destruir(arbol);
}

void no_se_puede_insertar_elementos_en_un_arbol_nulo()
{
	abb_t *arbol = NULL;
	pa2m_afirmar(abb_insertar(arbol, NULL) == NULL,
		     "No se puede insertar elementos en un arbol nulo");
}

void podemos_insertar_un_elemento()
{
	abb_t *arbol = abb_crear(comparador);
	int numero = 15;
	arbol = abb_insertar(arbol, &numero);
	pa2m_afirmar(abb_buscar(arbol, &numero) == &numero,
		     "El elemento insertado es correcto");
	pa2m_afirmar(abb_tamanio(arbol) == 1,
		     "La cantidad de elementos agregada es correcta");
	abb_destruir(arbol);
}

void podemos_insertar_varios_elementos()
{
	abb_t *arbol = abb_crear(comparador);
	int numeros[] = { 15, 12, 21, 7, 14, 27, 24, 6, 23, 25, 26, 8, 15 };
	for (int i = 0; i < sizeof(numeros) / sizeof(int); i++)
		arbol = abb_insertar(arbol, &numeros[i]);
	pa2m_afirmar(abb_tamanio(arbol) == sizeof(numeros) / sizeof(int),
		     "La cantidad de elementos agregada es correcta");
	abb_destruir(arbol);
}

void no_puedo_borrar_de_un_arbol_nulo()
{
	abb_t *arbol = NULL;
	pa2m_afirmar(abb_quitar(arbol, NULL) == NULL,
		     "No puedo eliminar el elemento de un arbol nulo");
}

void no_puedo_borrar_un_elemento_de_un_arbol_vacio()
{
	abb_t *arbol = abb_crear(comparador);
	pa2m_afirmar(abb_quitar(arbol, NULL) == NULL,
		     "No puedo eliminar el elemento de un arbol vacio");
	abb_destruir(arbol);
}

void no_puedo_borrar_un_elemento_que_no_existe()
{
	abb_t *arbol = abb_crear(comparador);
	int numeros[] = { 15, 12, 21, 23, 7, 14, 15, 6 };
	for (int i = 0; i < sizeof(numeros) / sizeof(int); i++)
		arbol = abb_insertar(arbol, &numeros[i]);
	int numero = 9;
	pa2m_afirmar(abb_quitar(arbol, &numero) == NULL,
		     "No puedo borrar un elemento que no existe");
	pa2m_afirmar(abb_tamanio(arbol) == sizeof(numeros) / sizeof(int),
		     "El tamaño del arbol es correcto");
	abb_destruir(arbol);
}

void puedo_borrar_un_elemento_sin_hijos()
{
	abb_t *arbol = abb_crear(comparador);
	int numeros[] = { 15, 12, 21, 23, 7, 14, 15, 6, 8 };
	for (int i = 0; i < sizeof(numeros) / sizeof(int); i++)
		arbol = abb_insertar(arbol, &numeros[i]);

	pa2m_afirmar(abb_quitar(arbol, &numeros[8]) == &numeros[8],
		     "Puedo borrar un elemento sin hijos corretamente");
	pa2m_afirmar(abb_tamanio(arbol) == 8, "El tamaño es correcto");
	pa2m_afirmar(abb_buscar(arbol, &numeros[8]) == NULL,
		     "Busco el elemento eliminado y no lo encuentro");

	pa2m_afirmar(abb_quitar(arbol, &numeros[7]) == &numeros[7],
		     "Puedo borrar otro elemento sin hijos correctamente");
	pa2m_afirmar(abb_tamanio(arbol) == 7, "El tamaño es correcto");
	pa2m_afirmar(abb_buscar(arbol, &numeros[7]) == NULL,
		     "Busco el elemento borrado pero no lo encuentro");

	abb_destruir(arbol);
}

void puedo_borrar_un_elemento_con_un_hijo()
{
	abb_t *arbol = abb_crear(comparador);
	int numeros[] = { 15, 12, 21, 27, 7, 14, 6, 8, 24, 25, 26, 23 };
	for (int i = 0; i < sizeof(numeros) / sizeof(int); i++)
		arbol = abb_insertar(arbol, &numeros[i]);
	size_t posicion = 0;
	for (size_t i = 0; i < sizeof(numeros) / sizeof(int); i++) {
		if (numeros[i] == 21)
			posicion = i;
	}

	pa2m_afirmar(abb_quitar(arbol, &numeros[posicion]) ==
			     &numeros[posicion],
		     "Puedo borrar un elemento con un hijo correctamente");
	pa2m_afirmar(abb_tamanio(arbol) == 11, "El tamaño es correcto");
	pa2m_afirmar(abb_buscar(arbol, &numeros[posicion]) == NULL,
		     "Busco el elemento eliminado y no lo encuentro");
	abb_destruir_todo(arbol, destructor);
}

void puedo_borrar_un_elemento_con_dos_hijos()
{
	abb_t *arbol = abb_crear(comparador);
	int numeros[] = { 15, 12, 21, 27, 7, 14, 6, 8, 24, 25, 26, 23 };
	for (int i = 0; i < sizeof(numeros) / sizeof(int); i++)
		arbol = abb_insertar(arbol, &numeros[i]);
	size_t posicion = 0;
	for (size_t i = 0; i < sizeof(numeros) / sizeof(int); i++) {
		if (numeros[i] == 24)
			posicion = i;
	}
	pa2m_afirmar(abb_quitar(arbol, &numeros[posicion]) ==
			     &numeros[posicion],
		     "Se puede eliminar un elemento con dos hijos :)");
	abb_destruir(arbol);
}

void puedo_borrar_otro_elemento_con_dos_hijos()
{
	abb_t *arbol = abb_crear(comparador);
	int numeros[] = { 15, 10, 13, 7, 6, 9, 8 };
	for (int i = 0; i < sizeof(numeros) / sizeof(int); i++)
		arbol = abb_insertar(arbol, &numeros[i]);
	size_t posicion = 0;
	for (size_t i = 0; i < sizeof(numeros) / sizeof(int); i++) {
		if (numeros[i] == 10)
			posicion = i;
	}
	pa2m_afirmar(abb_quitar(arbol, &numeros[posicion]) ==
			     &numeros[posicion],
		     "Se puede eliminar un elemento con dos hijos :)");
	abb_destruir(arbol);
}

void puedo_borrar_la_raiz()
{
	abb_t *arbol = abb_crear(comparador);
	int numeros[] = { 15, 12, 21, 27, 7, 14, 6, 8, 24, 25, 26, 23, 13 };
	for (int i = 0; i < sizeof(numeros) / sizeof(int); i++)
		arbol = abb_insertar(arbol, &numeros[i]);
	pa2m_afirmar(abb_quitar(arbol, &numeros[0]) == &numeros[0],
		     "Se puede borrar la raiz con dos hijos correctamente :)");
	abb_destruir(arbol);
}

void puedo_borrar_la_raiz_con_un_hijo()
{
	abb_t *arbol = abb_crear(comparador);
	int numeros[] = { 15, 15 };
	for (int i = 0; i < sizeof(numeros) / sizeof(int); i++)
		arbol = abb_insertar(arbol, &numeros[i]);
	pa2m_afirmar(abb_quitar(arbol, &numeros[0]) == &numeros[0],
		     "Se puede borrar la raiz con un hijo correctamente :)");
	abb_destruir(arbol);
}

void puedo_borrar_la_raiz_sin_hijos()
{
	abb_t *arbol = abb_crear(comparador);
	int numeros[] = { 15 };
	for (int i = 0; i < sizeof(numeros) / sizeof(int); i++)
		arbol = abb_insertar(arbol, &numeros[i]);
	size_t posicion = 0;
	for (size_t i = 0; i < sizeof(numeros) / sizeof(int); i++) {
		if (numeros[i] == 15)
			posicion = i;
	}
	pa2m_afirmar(abb_quitar(arbol, &numeros[posicion]) ==
			     &numeros[posicion],
		     "Se puede borrar la raiz sin hijos :)");
	abb_destruir(arbol);
}

void no_puedo_buscar_en_un_arbol_nulo()
{
	abb_t *arbol = NULL;
	pa2m_afirmar(abb_buscar(arbol, NULL) == NULL,
		     "No puedo buscar un elemento en un arbol nulo");
}

void no_puedo_buscar_en_un_arbol_vacio()
{
	abb_t *arbol = abb_crear(comparador);
	pa2m_afirmar(abb_buscar(arbol, NULL) == NULL,
		     "No puedo buscar en un arbol vacio");
	abb_destruir_todo(arbol, destructor);
}

void puedo_buscar_un_elemento_que_existe()
{
	abb_t *arbol = abb_crear(comparador);
	int numeros[] = { 15, 21, 12, 15, 23, 7, 14 };
	for (size_t i = 0; i < sizeof(numeros) / sizeof(int); i++)
		arbol = abb_insertar(arbol, &numeros[i]);
	for (size_t i = 0; i < sizeof(numeros) / sizeof(int); i++)
		pa2m_afirmar(*(int *)abb_buscar(arbol, &numeros[i]) ==
				     numeros[i],
			     "Busco un elemento que existe y lo encuentro");
	abb_destruir(arbol);
}

void busco_un_elemento_que_no_existe_y_no_lo_encuentro()
{
	abb_t *arbol = abb_crear(comparador);
	int numeros[] = { 15, 21, 12, 15, 23, 7, 14 };
	for (size_t i = 0; i < sizeof(numeros) / sizeof(int); i++)
		arbol = abb_insertar(arbol, &numeros[i]);
	int numero = 77;
	pa2m_afirmar(abb_buscar(arbol, &numero) == NULL,
		     "Busco un elemento que no existe y devuelve NULL");
	abb_destruir(arbol);
}

void busco_el_elemento_de_la_raiz()
{
	abb_t *arbol = abb_crear(comparador);
	int numeros[] = { 15, 21, 12, 15, 23, 7, 14 };
	for (size_t i = 0; i < sizeof(numeros) / sizeof(int); i++)
		arbol = abb_insertar(arbol, &numeros[i]);
	pa2m_afirmar(abb_buscar(arbol, &numeros[0]) == &numeros[0],
		     "Busco el elemento de la raiz y lo encuentro");
	abb_destruir(arbol);
}

void no_se_recorre_un_arbol_nulo()
{
	pa2m_afirmar(abb_con_cada_elemento(NULL, POSTORDEN,
					   sigo_recorriendo_con_corte,
					   NULL) == 0,
		     "No se puede recorrer un arbol nulo");
}

void no_se_recorre_con_una_funcion_nula()
{
	abb_t *arbol = abb_crear(comparador);
	pa2m_afirmar(abb_con_cada_elemento(arbol, INORDEN, NULL, NULL) == 0,
		     "No se puede aplicar una funcion nula");
	abb_destruir(arbol);
}

void se_recorre_un_arbol_sin_elementos()
{
	abb_t *arbol = abb_crear(comparador);
	pa2m_afirmar(abb_con_cada_elemento(arbol, INORDEN,
					   sigo_recorriendo_sin_corte,
					   NULL) == 0,
		     "La cantidad recorrida es la esperada");
	abb_destruir(arbol);
}

void no_se_recorre_con_un_recorrido_invalido()
{
	abb_t *arbol = abb_crear(comparador);
	pa2m_afirmar(abb_con_cada_elemento(
			     arbol, -1, sigo_recorriendo_sin_corte, NULL) == 0,
		     "No se recorre con un recorrido invalido");
	abb_destruir(arbol);
}

void prueba_recorrido_preorden_todo_el_arbol()
{
	abb_t *arbol = abb_crear(comparador);
	int numeros[] = { 15, 21, 12, 23, 7, 14, 15 };
	for (size_t i = 0; i < sizeof(numeros) / sizeof(int); i++)
		arbol = abb_insertar(arbol, &numeros[i]);
	pa2m_afirmar(abb_con_cada_elemento(arbol, PREORDEN,
					   sigo_recorriendo_sin_corte, NULL) ==
			     sizeof(numeros) / sizeof(int),
		     "Se recorrieron todos los elementos en preorden");
	abb_destruir(arbol);
}

void prueba_recorrido_preorden_algunos_elementos()
{
	abb_t *arbol = abb_crear(comparador);
	int numeros[] = { 15, 21, 12, 23, 7, 14, 15 };
	for (size_t i = 0; i < sizeof(numeros) / sizeof(int); i++)
		arbol = abb_insertar(arbol, &numeros[i]);
	pa2m_afirmar(abb_con_cada_elemento(arbol, PREORDEN,
					   sigo_recorriendo_con_corte,
					   &numeros[4]) == 3,
		     "Se recorrieron algunos elementos en preorden");
	abb_destruir(arbol);
}

void prueba_recorrido_inorder_todo_el_arbol()
{
	abb_t *arbol = abb_crear(comparador);
	int numeros[] = { 15, 21, 12, 23, 7, 14, 15 };
	for (size_t i = 0; i < sizeof(numeros) / sizeof(int); i++)
		arbol = abb_insertar(arbol, &numeros[i]);
	pa2m_afirmar(abb_con_cada_elemento(arbol, INORDEN,
					   sigo_recorriendo_sin_corte, NULL) ==
			     sizeof(numeros) / sizeof(int),
		     "Se recorrieron todos los elementos en inorden");
	abb_destruir(arbol);
}

void prueba_recorrido_inorder_algunos_elementos()
{
	abb_t *arbol = abb_crear(comparador);
	int numeros[] = { 15, 21, 12, 23, 7, 14, 15 };
	for (size_t i = 0; i < sizeof(numeros) / sizeof(int); i++)
		arbol = abb_insertar(arbol, &numeros[i]);
	pa2m_afirmar(abb_con_cada_elemento(arbol, INORDEN,
					   sigo_recorriendo_con_corte,
					   &numeros[1]) == 6,
		     "Se recorrieron algunos elementos en inorden");
	abb_destruir(arbol);
}

void prueba_recorrido_postorden_todo_el_arbol()
{
	abb_t *arbol = abb_crear(comparador);
	int numeros[] = { 15, 21, 12, 23, 7, 14, 15 };
	for (size_t i = 0; i < sizeof(numeros) / sizeof(int); i++)
		arbol = abb_insertar(arbol, &numeros[i]);
	pa2m_afirmar(abb_con_cada_elemento(arbol, POSTORDEN,
					   sigo_recorriendo_sin_corte, NULL) ==
			     sizeof(numeros) / sizeof(int),
		     "Se recorrieron todos los elementos en postorden");
	abb_destruir(arbol);
}

void prueba_recorrido_postorden_algunos_elementos()
{
	abb_t *arbol = abb_crear(comparador);
	int numeros[] = { 15, 21, 12, 23, 7, 14, 15 };
	for (size_t i = 0; i < sizeof(numeros) / sizeof(int); i++)
		arbol = abb_insertar(arbol, &numeros[i]);
	pa2m_afirmar(abb_con_cada_elemento(arbol, POSTORDEN,
					   sigo_recorriendo_con_corte,
					   &numeros[5]) == 3,
		     "Se recorrieron todos los elementos en postorden");
	abb_destruir(arbol);
}

void no_se_puede_cargar_de_un_arbol_nulo()
{
	abb_t *arbol = NULL;
	void **array = calloc(1, sizeof(void *));
	pa2m_afirmar(abb_recorrer(arbol, PREORDEN, array, 1) == 0,
		     "No se puede cargar de un arbol nulo");
	free(array);
}

void no_se_puede_cargar_en_un_array_nulo()
{
	abb_t *arbol = abb_crear(comparador);
	int numeros[] = { 15, 21, 12, 23, 7, 14, 15 };
	for (size_t i = 0; i < sizeof(numeros) / sizeof(int); i++)
		arbol = abb_insertar(arbol, &numeros[i]);
	pa2m_afirmar(abb_recorrer(arbol, PREORDEN, NULL, 0) == 0,
		     "No se puede cargar de un array nulo");
	abb_destruir(arbol);
}

void no_se_cargan_elementos_de_un_arbol_vacio()
{
	abb_t *arbol = abb_crear(comparador);
	void **array = calloc(1, (5) * sizeof(void *));
	pa2m_afirmar(abb_recorrer(arbol, PREORDEN, array, 5) == 0,
		     "No se cargan elementos de un arbol vacio");
	free(array);
	abb_destruir(arbol);
}

void cargar_array_con_todos_los_elementos_recorrido_preorden()
{
	abb_t *arbol = abb_crear(comparador);
	int numeros[] = { 15, 21, 12, 23, 7, 14, 15 };
	for (size_t i = 0; i < sizeof(numeros) / sizeof(int); i++)
		arbol = abb_insertar(arbol, &numeros[i]);
	void **array =
		calloc(1, (sizeof(numeros) / sizeof(int)) * sizeof(void *));
	pa2m_afirmar(
		abb_recorrer(arbol, PREORDEN, array,
			     sizeof(numeros) / sizeof(int)) ==
			sizeof(numeros) / sizeof(int),
		"Se cargaron todos los elementos del arbol en el array correctamente, en PREORDEN");
	free(array);
	abb_destruir(arbol);
}

void cargar_array_con_algunos_elementos_recorrido_preorden()
{
	abb_t *arbol = abb_crear(comparador);
	int numeros[] = { 15, 21, 12, 23, 7, 14, 15 };
	for (size_t i = 0; i < sizeof(numeros) / sizeof(int); i++)
		arbol = abb_insertar(arbol, &numeros[i]);
	void **array = calloc(1, 20 * sizeof(void *));
	pa2m_afirmar(
		abb_recorrer(arbol, PREORDEN, array, 3) == 3,
		"Se cargaron algunos elementos del arbol en el array correctamente, en PREORDEN");
	free(array);
	abb_destruir(arbol);
}

void cargar_array_con_todos_los_elementos_recorrido_postorden()
{
	abb_t *arbol = abb_crear(comparador);
	int numeros[] = { 15, 21, 12, 23, 7, 14, 15 };
	for (size_t i = 0; i < sizeof(numeros) / sizeof(int); i++)
		arbol = abb_insertar(arbol, &numeros[i]);
	void **array =
		calloc(1, (sizeof(numeros) / sizeof(int)) * sizeof(void *));
	pa2m_afirmar(
		abb_recorrer(arbol, POSTORDEN, array,
			     sizeof(numeros) / sizeof(int)) ==
			sizeof(numeros) / sizeof(int),
		"Se cargaron todos los elementos del arbol en el array correctamente, en POSTORDEN");
	free(array);
	abb_destruir(arbol);
}

void cargar_array_con_algunos_elementos_recorrido_postorden()
{
	abb_t *arbol = abb_crear(comparador);
	int numeros[] = { 15, 21, 12, 23, 7, 14, 15 };
	for (size_t i = 0; i < sizeof(numeros) / sizeof(int); i++)
		arbol = abb_insertar(arbol, &numeros[i]);
	void **array =
		calloc(1, (sizeof(numeros) / sizeof(int)) * sizeof(void *));
	pa2m_afirmar(
		abb_recorrer(arbol, POSTORDEN, array, 2) == 2,
		"Se cargaron algunos elementos del arbol en el array correctamente, en POSTORDEN");
	free(array);
	abb_destruir(arbol);
}

void cargar_array_con_todos_los_elementos_recorrido_inorden()
{
	abb_t *arbol = abb_crear(comparador);
	int numeros[] = { 15, 21, 17, 23, 4, 14, 15 };
	for (size_t i = 0; i < sizeof(numeros) / sizeof(int); i++)
		arbol = abb_insertar(arbol, &numeros[i]);
	void **array =
		calloc(1, (sizeof(numeros) / sizeof(int)) * sizeof(void *));
	pa2m_afirmar(
		abb_recorrer(arbol, INORDEN, array,
			     sizeof(numeros) / sizeof(int)) ==
			sizeof(numeros) / sizeof(int),
		"Se cargaron todos los elementos del arbol en el array correctamente, en INORDEN");
	free(array);
	abb_destruir(arbol);
}

void cargar_array_con_algunos_elementos_recorrido_inorden()
{
	abb_t *arbol = abb_crear(comparador);
	int numeros[] = { 15, 21, 2, 23, 7, 14, 15, 8 };
	for (size_t i = 0; i < sizeof(numeros) / sizeof(int); i++)
		arbol = abb_insertar(arbol, &numeros[i]);
	void **array =
		calloc(1, (sizeof(numeros) / sizeof(int)) * sizeof(void *));
	pa2m_afirmar(
		abb_recorrer(arbol, POSTORDEN, array, 5) == 5,
		"Se cargaron algunos elementos del arbol en el array correctamente, en INORDEN");
	free(array);
	abb_destruir(arbol);
}

int main()
{
	pa2m_nuevo_grupo("Pruebas de crear un arbol");
	se_puede_crear_un_arbol();
	no_se_puede_crear_un_arbol_con_un_comparador_nulo();
	un_arbol_recien_creado_tiene_cero_elementos();

	pa2m_nuevo_grupo("Pruebas insercion elementos");
	no_se_puede_insertar_elementos_en_un_arbol_nulo();
	podemos_insertar_un_elemento();
	podemos_insertar_varios_elementos();

	pa2m_nuevo_grupo("Pruebas eliminar elementos");
	no_puedo_borrar_de_un_arbol_nulo();
	no_puedo_borrar_un_elemento_de_un_arbol_vacio();
	no_puedo_borrar_un_elemento_que_no_existe();
	puedo_borrar_un_elemento_sin_hijos();
	puedo_borrar_un_elemento_con_un_hijo();
	puedo_borrar_un_elemento_con_dos_hijos();
	puedo_borrar_otro_elemento_con_dos_hijos();
	puedo_borrar_la_raiz();
	puedo_borrar_la_raiz_con_un_hijo();
	puedo_borrar_la_raiz_sin_hijos();

	pa2m_nuevo_grupo("Pruebas de busqueda");
	no_puedo_buscar_en_un_arbol_nulo();
	no_puedo_buscar_en_un_arbol_vacio();
	puedo_buscar_un_elemento_que_existe();
	busco_un_elemento_que_no_existe_y_no_lo_encuentro();
	busco_el_elemento_de_la_raiz();

	pa2m_nuevo_grupo("Pruebas recorridos");
	no_se_recorre_un_arbol_nulo();
	no_se_recorre_con_una_funcion_nula();
	se_recorre_un_arbol_sin_elementos();
	no_se_recorre_con_un_recorrido_invalido();
	prueba_recorrido_preorden_todo_el_arbol();
	prueba_recorrido_preorden_algunos_elementos();
	prueba_recorrido_inorder_todo_el_arbol();
	prueba_recorrido_inorder_algunos_elementos();
	prueba_recorrido_postorden_todo_el_arbol();
	prueba_recorrido_postorden_algunos_elementos();

	pa2m_nuevo_grupo("Pruebas cargar array segun recorrido");
	no_se_puede_cargar_de_un_arbol_nulo();
	no_se_puede_cargar_en_un_array_nulo();
	no_se_cargan_elementos_de_un_arbol_vacio();
	cargar_array_con_todos_los_elementos_recorrido_preorden();
	cargar_array_con_algunos_elementos_recorrido_preorden();
	cargar_array_con_todos_los_elementos_recorrido_postorden();
	cargar_array_con_algunos_elementos_recorrido_postorden();
	cargar_array_con_todos_los_elementos_recorrido_inorden();
	cargar_array_con_algunos_elementos_recorrido_inorden();

	return pa2m_mostrar_reporte();
}
