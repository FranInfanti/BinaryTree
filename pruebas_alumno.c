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
	int numeros[] = { 15, 21, 12, 15, 24, 7, 14, 29, 5, 20, 23, 9, 11 };
	for (int i = 0; i < sizeof(numeros) / sizeof(int); i++) {
		arbol = abb_insertar(arbol, &numeros[i]);
		pa2m_afirmar(*(int *)abb_buscar(arbol, &numeros[i]) ==
				     numeros[i],
			     "El elemento insertado es correcto");
	}
	pa2m_afirmar(abb_tamanio(arbol) == sizeof(numeros) / sizeof(int),
		     "La cantidad de elementos agregada es correcta");
	abb_destruir_todo(arbol, destructor);
}

void prueba_destructor()
{
	abb_t *arbol = abb_crear(comparador);
	int numeros[] = { 15, 21, 12, 15, 23, 7, 14 };
	for (int i = 0; i < sizeof(numeros) / sizeof(int); i++) {
		arbol = abb_insertar(arbol, &numeros[i]);
	}
	abb_destruir_todo(arbol, destructor);
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

	pa2m_nuevo_grupo("Pruebas de destructor");
	prueba_destructor();

	return pa2m_mostrar_reporte();
}
