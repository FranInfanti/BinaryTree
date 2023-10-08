# TDA ABB

## Repositorio de Francisco Infanti - 110822 - finfanti@fi.uba.ar

- Para compilar:

```bash
make 
```

- Para ejecutar:

```bash
./pruebas_chanutron
```

- Para ejecutar con valgrind:
```bash
make valgrind-chanutron 
```
---
##  Funcionamiento

El programa consiste en la implementación de un **ABB**, este es un tipo de árbol con todas sus características explicadas en el punto teórico. Como la forma mas simple de implementar un arbol es recursiva, todas las funciones de recorrer, insertar, eliminar, etc..., fueron implementadas de manera recursiva.

La implementación que se utilizó para crear este árbol consiste de dos estructuras. Una principal, `abb_t`, la cual almacena la dirección de memoria del primer nodo, la cantidad de elementos y un comparador proporcionado por el usuario. Este comparador me permitía comparar los elementos que se están insertando y borrando, todo esto con el objetivo de mantener un orden.


*(**COMENTARIO**: En esta implementación se permiten insertar elementos repetidos y se tomó la convención de mandarlos hacia la izquierda. A su vez, si queremos eliminar un elemento con dos hijos, se tomará el predecesor inorden para reemplazarlo)*

La segunda estructura que se utilizó, `nodo_abb_t`, cumple la función de almacenar la dirección de memoria del elemento y del nodo de su izquierda y derecha. También es muy importante que si un nodo no tiene izquierda o derecha, que éste apunte a `NULL`. De este modo se sabrá si hay que seguir recorriendo por dicha rama.

El usuario puede almacenar los elementos que desee en el árbol, por dicho motivo es que hago uso de los `void*`, los cuales me permiten almacenar direcciones de memoria sin necesidad de saber que hay en dichas direcciones. Por este motivo es importante el comparador, pues yo no se como comparar los elementos que me ingresa el usuario.

---
Para comenzar a hacer uso del programa, lo lógico sería que se cree un árbol. Para poder crear uno, lo que se hace es reservar un bloque de memoria en el heap de tamaño adecuado *(Para que pueda almacenar todo lo mencionado anteriormente)*. También el usuario debe proporcionar el comparador para que se pueda almacenar, el resto de los campos se inicializan en 0. En el caso de que haya algún fallo en el proceso, ya sea que no se pueda reservar memoria o el comparador sea invalido, se devolverá `NULL`. 

Notemos que la complejidad de esta operación es constante `O(1)`, pues si creamos `n` árboles, siempre estaremos haciendo las mismas operaciones simples.

---
<div align="center">
<img width="45%" src="img/abb_crear.svg">
</div>

---
En el caso de que se termine de usar el árbol, este debe ser destruido. Para dicho objetivo se proporcionan dos funciones, ambas liberan toda la memoria que está siendo usada por el árbol, la diferencia es que una aplica una función destructora a cada elemento del árbol. Para poder implementar estas funciones decidí hacerlo implementando una función recursiva que recorre el árbol en **postorden**. De este modo la eliminación es muy simple, pues el recorrido **postorden** da el camino mas optimo para eliminar un árbol.

La complejidad de destruir un árbol siempre será `O(n)`, pues si o si debemos recorrer los `n` elementos que este tiene para así ir liberando la memoria de cada nodo.

---
<div align="center">
<img width="85%" src="img/abb_destruir.svg">
</div>

---
Si se quisiera insertar un elemento lo que se hace es reservar un bloque de memoria en el heap de tamaño `nodo_abb_t`, en dicho bloque se almacenará el nuevo elemento que se quiere insertar, a su vez los punteros de izquierda y derecha, que en este caso son `NULL`.

Una vez tenemos dicho bloque reservado, debemos recorrer el árbol de manera recursiva e ir comparando el elemento a insertar con los elementos que ya se encuentran en el árbol. Siguiendo la lógica de que si es mayor comparamos con los elementos del subárbol derecho, caso contrario con el izquierdo, así hasta llegar al final del árbol (posición donde debe insertarse el elemento). Una vez en dicha posición lo que se hace es hacer que el nodo que era el último apunte al nuevo que queremos insertar, si es menor o igual lo apunta por izquierda y sino por derecha.

---
<div align="center">
<img width="55%" src="img/abb_insertar.svg">
</div>

---
Veamos que la complejidad de insertar un elemento es `O(log(n))`, pues después de comparar siempre estamos partiendo el problema a la mitad. Las otras operaciones de hacer que el último apunte al nuevo nodo, son constantes `O(1)` y no aportan al tamaño del problema.

Para eliminar un elemento del árbol también se recorre de manera recursiva hasta encontrar el elemento que queremos eliminar. Una vez que lo hayamos encontrado se pueden dar dos casos diferentes:

- El primero sería que se está eliminando un elemento con un hijo o ninguno, en este caso se procede eliminando el elemento y haciendo que el padre del que queremos eliminar apunte al hijo del que queremos eliminar. Como sabemos que tiene como máximo un hijo y si no tiene apunta a `NULL`, entonces no estaríamos perdiendo ningún elemento.

---
<div align="center">
<img width="55%" src="img/abb_eliminar_con_un_hijo.svg">
</div>

---
- El segundo caso sería que estemos eliminado un elemento con dos hijos, en este caso lo que se hace es buscar a partir del elemento que queremos eliminar el predecesor inorden, que vendría a ser la mayor cota menor. Una vez obtenemos dicho elemento, lo reemplazamos por el cual queremos eliminar, haciendo que este apunte a los hijos del que queremos eliminar. También debemos hacer que el padre del que queremos eliminar ahora apunte al predecesor. De esta manera se seguiría conservando el orden del árbol. En el caso de que el predecesor tenga un hijo o ninguno, se procede como el primer caso.
Por último debemos liberar la memoria que está siendo usada por el nodo.

---
<div align="center">
<img width="70%" src="img/abb_eliminar_con_dos_hijos.svg">
</div>

---
Veamos que para ambos casos la complejidad es `O(log(n))`, pues cada vez que comparamos el elemento que buscamos con el del árbol, se nos descarta una parte del árbol. El resto de operaciones son asignar punteros y liberar memoria, es decir, operaciones constantes `O(1)`.

Si queremos buscar un elemento de un árbol, lo que se debe hacer es muy similar al proceso de insertar y eliminar. Debemos recorrer el árbol comparando el elemento que buscamos con el nodo actual sobre el cual estamos parados, si es mas grande nos quedamos con el subárbol de la izquierda y si es mas chico con el de la derecha. En mi caso decidí hacer este proceso de forma recursiva, pues es más claro de entender el código. En el caso de que el elemento que se esté buscando no exista, se devolverá `NULL`.

Veamos que al ser casi el mismo proceso que insertar y eliminar, la complejidad de esta operación es `O(log(n))`.

También se proporciona una función para saber el tamaño del árbol y si este está vacío. Ambas operaciones tienen complejidad constante `O(1)`, pues solamente estamos accediendo a un valor en un bloque de memoria sobre el cual tenemos un puntero directo, que vendría a ser el puntero al `árbol`.

El usuario también puede hacer uso de un iterador interno. Este funciona de manera recursiva, recorriendo los elementos del árbol y aplicando la función proporcionada. Esta función al ser de tipo `bool`, puede indicar cuándo debe dejar de recorrer. Una vez se termina de recorrer el árbol, se devuelve la cantidad de elementos a la cual fue posible aplicarles la función. El recorrido del árbol puede ser **preorden**, **inorden** o **postorden**. Veamos que la complejidad de esta operación es `O(n)`, pues en el peor de los casos debo recorrer todo el árbol.

Por último el usuario puede hacer uso de una función la cual le permite cargar la cantidad de elementos que quiera del árbol en un array. También como en el iterador interno, el árbol se recorre de manera recursiva y en **preorden**, **inorden** o **postorden**. También, como en el iterador, la complejidad en el peor de los casos es `O(n)`, pues debería recorrer todo el árbol.

## Respuestas a las preguntas teóricas
Un árbol es un tipo de dato abstracto **(TDA)**. Se dice que este es una colección de nodos, que a su vez, pueden estar conectados a otros nodos. Un nodo puede apuntar a `n` nodos, pero solamente puede ser apuntado por uno. Además ningún nodo apunta a la `raíz` del árbol, en el caso de que eso ocurra dejaría de ser un árbol. Que un nodo apunte a `NULL`, indica que este no tiene más nodos debajo de él. Esto nos permite tener una condición de corte cuando estamos recorriendo un árbol.

La idea general de porqué se crean los árboles, es porque cuando nosotros tenemos una lista simplemente enlazada o doblemente enlazada, el tiempo de búsqueda de un elemento en el peor de los casos es `O(n)`, en cambio con la implementación de un árbol veremos que en algunos casos esto el tiempo puede llegar a ser `O(log(n))`.

Las operaciones que se definen sobre los árboles son las siguientes: **Crear**, **Destruir**, **Insertar** **Eliminar**, **Buscar**, **Recorrer** y **Vacío**.

- La operación de **Crear**, como lo dice el nombre, consiste en crear un árbol, **Destruir** en destruir todo el árbol y por último la operación de **Vacío**, nos permite saber si un árbol tiene elementos o no. Las operaciones de **Insertar**, **Eliminar**, **Recorrer** y **Buscar** dependen del árbol que se esté implementando. Explicare estás en detalle en los *Arboles Binarios* y **ABB**.

---
<div align="center">
<img width="40%" src="img/arbol.svg">
</div>

---
El nodo principal del árbol se lo conoce como la `raíz`, por este nodo será donde se entra si se quiere hacer alguna operación con el árbol. El árbol puede o no estar dividido en subárboles, pero cada subárbol de alguna manera debe estar conectado con la `raíz`. Algunas definiciones comunes de los árboles son las siguientes:

- Se dice que un nodo es `padre`, cuando éste apunta a otros nodos.
- Se dice que un nodo es `hijo`, cuando tiene un padre, es decir, cuando es apuntado por un nodo.
- Se dice que un nodo es una `hoja`, si es que este no tiene hijos.
- Se puede dividir a un árbol según sus `niveles`, siendo el 1er nivel el de la `raíz` y aumentando hacia abajo.
- La `altura` de un árbol se representa según la cantidad de niveles que este tiene.

Existen diferentes tipos de árboles, los *Arboles Binarios*, *Árboles Binarios de Búsqueda* **(ABB)**, *Árboles N-Arios*, *Árboles de Rotación* **(AVL)**, etc...

En mi caso solamente voy a explicar qué son los *Arboles Binarios* y los **ABB**. Como los **ABB** son un tipo de los *Aboles Binarios*, conviene primero explicar que es un *Arbol Binario*. Estos, como lo dice el nombre, son un árbol que surge con la idea de aproximarnos a la búsqueda binaria. En este tipo de árbol un nodo puede tener como máximo dos `hijos`. Esto nos permite dar una noción de izquierda y derecha dentro del árbol. Es decir, si estamos parados en un nodo, podemos ir a la izquierda o la derecha.

---
<div align="center">
<img width="25%" src="img/arbol_binario.svg">
</div>

---
Para los *Arboles Binarios* se definen una serie de recorridos, lo cual como dice el nombre, nos permite recorrer el árbol. Todos los recorridos comienzan en la `raíz` del árbol y constan de tres operaciones. Se dice que un nodo fue recorrido cuando se visita su contenido **(N)**, hijo derecho **(D)** e hijo izquierdo **(I)**. La complejidad que tienen todos los recorridos es `O(n)`, pues si en nuestro árbol tenemos `n` elementos, debemos recorrerlos todos.

Existen en total una cantidad de `3!` de recorridos, pero los que explicare serán los siguientes: **Preorden**, **Inorden** y **Postorden**.

---
<div align="center">
<img width="45%" src="img/arbol_binario_recorridos.svg">
</div>

---
- La primera operación que se realiza en el recorrido *Preorden* es visitar el contenido que tiene el nodo, luego se debe ir hacia la izquierda de dicho nodo y por último a la derecha, **NID**. Este recorrido suele ser utilizado para copiar un árbol en otro.
- En el recorrido *Inorden* lo primero que se hace es ir hacia la izquierda del nodo, luego se visita su contenido y por último se va hacia la derecha, **IND**. Este recorrido suele ser utilizado para recorrer el árbol en orden.
- Por último en el recorrido *Postorden* lo primero que se hace es ir hacia la izquierda, luego la derecha y por último se visita el contenido del nodo, **IDN**. Este recorrido nos da el camino más óptimo para poder eliminar un árbol.

---
En cuanto a los **ABB**, estos son un tipo de *Arboles Binarios*, los cuales cumplen con un orden determinado. Cada nodo tiene una clave, con la cual se comparará con las claves de los otros nodos. Dicha comparación nos permite mantener un cierto orden a la hora de realizar operaciones con el árbol.

---
<div align="center">
<img width="25%" src="img/ABB.svg">
</div>

<div align="center"><font size="2">
En el dibujo las claves mayores estarían en el subárbol derecho y las menores en el subárbol izquierdo
</font></div>

---
- La operación de *insertar* un elemento en el árbol, debemos recorrer el árbol e ir comparando el elemento que queremos insertar con las claves de los nodos del árbol. El resultado de dicha comparación determinará de qué lado del árbol debemos insertar el elemento.

  ---
  <div align="center">
  <img width="50%" src="img/insertar.svg">
  </div>

  <div align="center"><font size="2">
  Comparamos con la raíz y vemos que el elemento a insertar es más grande, entonces lo "mandamos" para el subárbol derecho. Nuevamente hacemos la misma comparación con la "raíz" del subárbol derecho. Hasta finalmente encontrar la posición donde debemos insertarlo.
  </font></div>

  ---
     Veamos entonces que la complejidad de insertar un elemento en un árbol es `O(log(n))`. Pues siempre que hacemos una comparación, estamos quedándonos con la mitad del problema.

- En cuanto a la operación de *eliminar* un elemento de un árbol, se pueden dar tres situaciones diferentes:

  - Eliminar un nodo `hoja`.
  <div align="center">
  <img width="50%" src="img/eliminar_hoja.svg">
  </div>

  <div align="center"><font size="2">Lo que se hace es buscar el elemento que se quiera eliminar y quitarlo del árbol</font></div>

  ---
  - Eliminar un nodo con un `hijo`.
  <div align="center">
  <img width="50%" src="img/eliminar_con_hijo.svg">
  </div>

  <div align="center"><font size="2">Se busca el elemento recorriendo el árbol. Una vez que se lo encuentra se debe hacer que al anterior a el apunte al hijo del que queremos eliminar. Una vez hecho eso podemos eliminar el nodo</font></div>

  ---
  - Eliminar un nodo con dos `hijos`.
  <div align="center">
  <img width="70%" src="img/eliminar_con_hijos.svg">
  </div>

  <div align="center"><font size="2">Una vez encontramos el elemento que queremos eliminar, debemos encontrar el predecesor o el sucesor de este. El predecesor sería la mayor cota menor y el sucesor la menor cota superior. Luego debemos reemplazar el elemento que queremos eliminar por el predecesor o el sucesor. En el caso de que tengan un hijo, se procede como cuando queremos eliminar un elemento con un hijo. Es muy importante que se tome una convención según cual tomamos y mantener dicha convención para siempre</font></div> 

  ---
  También vemos que en este caso la complejidad de eliminar un elemento es `O(log(n))`, pues el proceso más costoso de todo sería encontrar el elemento que queremos eliminar y como sabemos de la inserción, este proceso es `O(log(n))`. El resto de las operaciones de eliminar tienen una complejidad constante `O(1)`, pues solamente estamos apuntando punteros.


- Para *buscar* un elemento en el árbol debemos ir comparando el elemento que buscamos con la clave del nodo. Como en el proceso de insertar, esta comparación determina de qué lado del árbol debemos buscar el elemento. Veamos que esta operación tiene una complejidad `O(log(n))`, pues al igual que *insertar* y *eliminar*, lo que hacemos es a medida que comparamos partimos el problema a la mitad.

---
<div align="center">
<img width="90%" src="img/buscar_elemento.svg">
</div>

---
- Los *recorridos* que se pueden hacer en un **ABB** son los mismo que los recorridos que los de un *Arbol Binario*.

Para analizar la complejidad de estas operaciones en un **ABB** se asume que el árbol estaba balanceado. Que un árbol esté balanceado implica que este no se degenera en una lista. En el caso de que el árbol se degenere en una lista las complejidades de las operaciones pasarían a ser `O(n)`, pues no estaríamos partiendo el problema a la mitad.

---
  <div align="center">
  <img width="25%" src="img/arbol_degenerado.svg">
  </div>
  <div align="center"><font size="2">Veamos que en este caso si queremos buscar o eliminar el elemento 23, deberíamos recorrer el árbol como si fuera una lista. También ocurriría lo mismo si quisiéramos insertar un elemento mayor a 15</font></div> 

---
Para solucionar este tipo de problemas se introducen las rotaciones.