#include "pa2m.h"
#include "src/abb.h"

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
	int *numero = elemento;
	printf(" (%i) ", *numero);
}

bool sigo_recorriendo_sin_corte(void *e1, void *e2)
{
	destructor(e1);
	return true;
}

bool sigo_recorriendo_con_corte(void *e1, void *e2)
{
	destructor(e1);
	return e1 != e2;
}

void se_puede_crear_un_arbol()
{
	abb_t *arbol = abb_crear(comparador);
	pa2m_afirmar(arbol != NULL, "Puedo crear un arbol");
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
		     "No se puede insertar elementos en una lista null");
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
	int numeros[] = { 15, 21, 12, 15, 24, 7,  14, 29, 5,  20, 23, 9, 11,
			  17, 20, 19, 27, 18, 30, 4,  6,  40, 28, 39, 0, 60,
			  50, 1,  51, 2,  59, 3,  55, 25, 26, 75, 52 };
	for (int i = 0; i < sizeof(numeros) / sizeof(int); i++)
		arbol = abb_insertar(arbol, &numeros[i]);
	bool son_correctos = true;
	for (size_t i = 0; i < sizeof(numeros) / sizeof(int); i++) {
		if (abb_buscar(arbol, &numeros[i]) == NULL)
			son_correctos = false;
	}
	pa2m_afirmar(son_correctos,
		     "Los elementos insertados son correctos :)");
	pa2m_afirmar(abb_tamanio(arbol) == sizeof(numeros) / sizeof(int),
		     "La cantidad de elementos agregada es correcta");
	abb_destruir_todo(arbol, NULL);
}

void prueba_insercion_masiva()
{
	abb_t *arbol = abb_crear(comparador);
	int numeros[] = { 50, 48, 21, 87,  5,  2,  0,	63,  52, 47, 45,
			  19, 20, 4,  43,  51, 16, 78,	102, 32, 65, 8,
			  10, 30, 17, 19,  57, 56, 96,	100, 23, 24, 26,
			  27, 10, 11, 2,   78, 75, 76,	44,  43, 33, 22,
			  21, 29, 91, 55,  66, 76, 111, 0,   15, 17, 18,
			  87, 50, 17, 555, 23, 61, 30,	35,  39, 48, 57,
			  67, 70, 52, 77,  78, 90, 101, 105 };
	for (size_t i = 0; i < sizeof(numeros) / sizeof(int); i++)
		arbol = abb_insertar(arbol, &numeros[i]);
	bool son_correctos = true;
	for (size_t i = 0; i < sizeof(numeros) / sizeof(int); i++) {
		if (abb_buscar(arbol, &numeros[i]) == NULL)
			son_correctos = false;
	}
	pa2m_afirmar(son_correctos,
		     "Los elementos insertados son correctos :)");
	pa2m_afirmar(abb_tamanio(arbol) == sizeof(numeros) / sizeof(int),
		     "La cantidad de elementos agregada es correcta");
	abb_destruir_todo(arbol, destructor);
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
	for (int i = 0; i < sizeof(numeros) / sizeof(int); i++)
		arbol = abb_insertar(arbol, &numeros[i]);
	pa2m_afirmar(*(int *)abb_buscar(arbol, &numeros[0]) == numeros[0],
		     "Busco un elemento que existe y lo encuentro");
	pa2m_afirmar(*(int *)abb_buscar(arbol, &numeros[1]) == numeros[1],
		     "Busco un elemento que existe y lo encuentro");
	pa2m_afirmar(*(int *)abb_buscar(arbol, &numeros[2]) == numeros[2],
		     "Busco un elemento que existe y lo encuentro");
	pa2m_afirmar(*(int *)abb_buscar(arbol, &numeros[3]) == numeros[3],
		     "Busco un elemento que existe y lo encuentro");
	pa2m_afirmar(*(int *)abb_buscar(arbol, &numeros[4]) == numeros[4],
		     "Busco un elemento que existe y lo encuentro");
	pa2m_afirmar(*(int *)abb_buscar(arbol, &numeros[5]) == numeros[5],
		     "Busco un elemento que existe y lo encuentro");
	pa2m_afirmar(*(int *)abb_buscar(arbol, &numeros[6]) == numeros[6],
		     "Busco un elemento que existe y lo encuentro");
	abb_destruir(arbol);
}

void busco_un_elemento_que_no_existe_y_no_lo_encuentro()
{
	abb_t *arbol = abb_crear(comparador);
	int numeros[] = { 15, 21, 12, 15, 23, 7, 14 };
	for (int i = 0; i < sizeof(numeros) / sizeof(int); i++)
		arbol = abb_insertar(arbol, &numeros[i]);
	int numero = 77;
	pa2m_afirmar(abb_buscar(arbol, &numero) == NULL,
		     "Busco un elemento que no existe y devuelve NULL");
	abb_destruir(arbol);
}

void prueba_destructor()
{
	abb_t *arbol = abb_crear(comparador);
	int numeros[] = { 15, 21, 12, 15, 23, 7, 14 };
	for (int i = 0; i < sizeof(numeros) / sizeof(int); i++)
		arbol = abb_insertar(arbol, &numeros[i]);
	abb_destruir_todo(arbol, destructor);
}

void prueba_destructor_nulo()
{
	abb_t *arbol = abb_crear(comparador);
	int numeros[] = { 15, 21, 12, 15, 23, 7, 14 };
	for (int i = 0; i < sizeof(numeros) / sizeof(int); i++)
		arbol = abb_insertar(arbol, &numeros[i]);
	abb_destruir_todo(arbol, NULL);
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
	for (int i = 0; i < sizeof(numeros) / sizeof(int); i++)
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
	for (int i = 0; i < sizeof(numeros) / sizeof(int); i++)
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
	for (int i = 0; i < sizeof(numeros) / sizeof(int); i++)
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
	for (int i = 0; i < sizeof(numeros) / sizeof(int); i++)
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
	for (int i = 0; i < sizeof(numeros) / sizeof(int); i++)
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
	for (int i = 0; i < sizeof(numeros) / sizeof(int); i++)
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
	for (int i = 0; i < sizeof(numeros) / sizeof(int); i++)
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
	for (int i = 0; i < sizeof(numeros) / sizeof(int); i++)
		arbol = abb_insertar(arbol, &numeros[i]);
	void **array =
		calloc(1, (sizeof(numeros) / sizeof(int)) * sizeof(void *));
	pa2m_afirmar(
		abb_recorrer(arbol, PREORDEN, array,
			     sizeof(numeros) / sizeof(int)) ==
			sizeof(numeros) / sizeof(int),
		"Se cargaron todos los elementos del arbol en el array correctamente, en PREORDEN");
	for (size_t i = 0; i < sizeof(numeros) / sizeof(int); i++)
		printf(" [%i] ", *(int *)array[i]);
	printf("\n");
	free(array);
	abb_destruir(arbol);
}

void cargar_array_con_algunos_elementos_recorrido_preorden()
{
	abb_t *arbol = abb_crear(comparador);
	int numeros[] = { 15, 21, 12, 23, 7, 14, 15 };
	for (int i = 0; i < sizeof(numeros) / sizeof(int); i++)
		arbol = abb_insertar(arbol, &numeros[i]);
	void **array = calloc(1, 20 * sizeof(void *));
	pa2m_afirmar(
		abb_recorrer(arbol, PREORDEN, array, 3) == 3,
		"Se cargaron algunos elementos del arbol en el array correctamente, en PREORDEN");
	for (size_t i = 0; i < 3; i++)
		printf(" [%i] ", *(int *)array[i]);
	printf("\n");
	free(array);
	abb_destruir(arbol);
}

void cargar_array_con_todos_los_elementos_recorrido_postorden()
{
	abb_t *arbol = abb_crear(comparador);
	int numeros[] = { 15, 21, 12, 23, 7, 14, 15 };
	for (int i = 0; i < sizeof(numeros) / sizeof(int); i++)
		arbol = abb_insertar(arbol, &numeros[i]);
	void **array =
		calloc(1, (sizeof(numeros) / sizeof(int)) * sizeof(void *));
	pa2m_afirmar(
		abb_recorrer(arbol, POSTORDEN, array,
			     sizeof(numeros) / sizeof(int)) ==
			sizeof(numeros) / sizeof(int),
		"Se cargaron todos los elementos del arbol en el array correctamente, en POSTORDEN");
	for (size_t i = 0; i < sizeof(numeros) / sizeof(int); i++)
		printf(" [%i] ", *(int *)array[i]);
	printf("\n");
	free(array);
	abb_destruir(arbol);
}

void cargar_array_con_algunos_elementos_recorrido_postorden()
{
	abb_t *arbol = abb_crear(comparador);
	int numeros[] = { 15, 21, 12, 23, 7, 14, 15 };
	for (int i = 0; i < sizeof(numeros) / sizeof(int); i++)
		arbol = abb_insertar(arbol, &numeros[i]);
	void **array =
		calloc(1, (sizeof(numeros) / sizeof(int)) * sizeof(void *));
	pa2m_afirmar(
		abb_recorrer(arbol, POSTORDEN, array, 2) == 2,
		"Se cargaron algunos elementos del arbol en el array correctamente, en POSTORDEN");
	for (size_t i = 0; i < 2; i++)
		printf(" [%i] ", *(int *)array[i]);
	printf("\n");
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
	prueba_insercion_masiva();

	pa2m_nuevo_grupo("Pruebas de busqueda");
	no_puedo_buscar_en_un_arbol_nulo();
	no_puedo_buscar_en_un_arbol_vacio();
	puedo_buscar_un_elemento_que_existe();
	busco_un_elemento_que_no_existe_y_no_lo_encuentro();

	pa2m_nuevo_grupo("Pruebas de destructor");
	prueba_destructor();
	prueba_destructor_nulo();

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

	return pa2m_mostrar_reporte();
}
