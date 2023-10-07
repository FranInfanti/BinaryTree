# TDA ABB

## Repositorio de Francisco Infanti - 110822 - finfanti@fi.uba.ar

- Para compilar:

```bash
make 
```

- Para ejecutar:

```bash
./pruebas_alumno
```

- Para ejecutar con valgrind:
```bash
make valgrind-chanutron 
```
---
##  Funcionamiento

El programa consiste en la implementacion de un **ABB**, el cual es un tipo de arbol con todas sus caracteristicas explicadas en el punto teorico.

La implementacion que se uitilizo para crear este arbol consiste de dos estructuras. Una principal, `abb_t`, la cual almacena la direccion de memoria del primer nodo del arbol, la cantidad de elementos del arbol y un comparador proporcionado por el usuario. Este comparador me permitia comparar los elementos que se estan insertando y borrando, todo esto con el objetivo de mantener cierto orden en el arbol. 

*(**COMENTARIO**: En esta implementacion se permiten insertar elementos repetidos, y se tomo la convencion de mandarlos hacia la izquierda. A su vez, si queremos eliminar un elemento con dos hijos, se tomara el predecesor inorden para remplazarlo)*

La segunda estructura que se utilizo, `nodo_abb_t`, cumple la funcion de almacenar elemento del arbol, la direccion de memoria del elemento de su izquierda y derecha. Tambien es muy importane que si un nodo no tiene izquierda o derecha, que este apunte a `NULL`. De este modo se sabra si hay que seguir recorriendo por dicha rama. 

El usuario puede almacenar los elementos que desee en el arbol, por dicho motivo es que hago uso de los `void*`, los cuales me permiten almacenar direcciones de memoria sin necesidad de saber que hay en dichas direcciones. Por este motivo es importante el comparador, pues yo no se como comparar los elementos que me ingresa el usuario. 

Para comenzar a hacer uso del programa, lo logico seria que se cree un arbol. Para poder crear uno, lo que se hace es reservar un bloque de memoria en el heap de tamaño adecuado *(Para que pueda almacenar todo lo mencionado anteriormente)*. Tambien el usuario debe proporcionar el comparador para que se pueda almacenar la direccion de memoria de este, en el resto de los campos se incializaran en 0. En el caso de que haya algun fallo en el proceso, ya sea que no se pueda reservar memoria o el comparadaror sea invalido, se devolvera `NULL`. Notemos que la complejidad de esta operacion es constante `O(1)`, pues si creamos `n` arboles, siempre estaremos haciendo las mismas operaciones simples.

<div align="center">
<img width="45%" src="img/abb_crear.svg">
</div>

---
En el caso de que se termine de usar el arbol, este debe ser destruido. Para dicho objetivo se proporcionan dos funciones, ambas liberan toda la memoria que esta siendo usada por el arbol, la diferencia es que una aplica una funcion destructora a cada elemento del arbol. Para poder implementar estas funciones decidi hacerlo implementando una funcion recursiva que recorre el arbol en **postorden**. De este modo la eliminacion es muy simple, pues el recorrido **postorden** da el camino mas optimo para eliminar un arbol. La complejidad de destruir un arbol siempre sera `O(n)`, pues si o si debemos recorrer los `n` elementos que este tiene.

<div align="center">
<img width="85%" src="img/abb_destruir.svg">
</div>

---
Para poder insertar un elemento lo que se hace es crear un nuevo nodo con el elemento y recorrer el arbol de manera recursiva e ir comparando el elemento a insertar con los elementos que ya se encuentran en el arbol. Siguiendo la logica de que si es mayor comparamos con los elementos del subarbol derecho, caso contrariro con el izquierdo, llegamos al final del arbol, posicion donde debemos insertar el elemento. Una vez en dicha posicion lo que se hace es hacer que el nodo que era el ultimo apunte al nuevo que queremos insertar, obviamente siguiendo la logica de que si es menor o igual lo apunta por izquierda y sino por derecha. Veamos que la complejidad de insertar un elemento es `O(log(n))`, pues despues de comparar siempre estamos partiendo el problema a la mitad. Las otras operaciones de hacer que el ultimo apunte al nuevo nodo, son constantes `O(1)` y no aportan al tamaño del problema.

<div align="center">
<img width="55%" src="img/abb_insertar.svg">
</div>

---
Para eliminar un elemento de el arbol tambien se recorre este de manera recursiva hasta encontrar el elemento que queremos eliminar. Una vez que lo hayamos encontrado se pueden dar dos casos diferentes: 

- El primero seria que se este eliminando un elemento con un hijo o niguno, en este caso se procede eliminando el elemento y haciendo que el padre del que queremos eliminar apunte al hijo del que queremos eliminar. Como sabemos que tiene como maximo un hijo y si no tiene apunta a `NULL`, entonces no estariamos perdiendo nigun elemento.

<div align="center">
<img width="55%" src="img/abb_eliminar_con_un_hijo.svg">
</div>

---
- El segundo caso seria que estemos eliminado un elemento con dos hijos, en este caso lo que se hace es buscar a partir del elemento que queremos eliminar el predecesor inorden, que vendria a ser la mayor cota menor. Una vez obtenemos dicho elemento, lo remplazamos por el cual queriamos eliminar y de esta manera se seguiria conservando el orden del arbol. En el caso de que el prdecesesor tenga un hijo o niguno, se procede como el primer caso. 

---

<div align="center">
<img width="50%" src="img/abb_eliminar_con_dos_hijo.svg">
</div>

---
Veamos que para ambos casos la complejidad es `O(log(n))`, pues cada vez que comparamos el elemento que buscamos con el del arbol, se nos descarta una parte del arbol. El resto de operaciones son reasignar punteros y liberar memoria, es decir, operaciones constantes `O(1)`.

(FALTA EXPLICAR BUSQUEDA, VACIO, TAMAÑO, ITERADOR Y RECORRIDOS).


## Respuestas a las preguntas teóricas

Un arbol es un tipo de dato abstracto **(TDA)**. Se dice que este es una coleccion de nodos, que a su vez, pueden estar conectados a otros nodos. Un nodo puede apuntar a `n` nodos, pero solamente puede ser apuntado por uno. Ademas nigun nodo apunte a la `raiz` del arbol, en el caso de que eso ocurra dejaria de ser un arbol. Que un nodo apunte a `NULL`, indica que este no tiene mas nodos debajo de el. Esto nos permite tener una condicion de corte cuando estamos recorriendo un arbol.

La idea general de porque se crean los arboles, es porque cuando nosotros tenemos una lista simplemente enlazada o doblemente enlazada, el tiempo de busqueda de un elemento en el peor de los casos es `O(n)`, en cambio con la implementacion de un arbol veremos que en algunos casos esto el tiempo puede llegar a ser `O(log(n))`.

Las operaciones que se definen sobre los arboles son las siguientes: **Crear**, **Destruir**, **Insertar** **Eliminar**, **Buscar**, **Recorrer** y **Vacio**.

- La operacion de **Crear**, como lo dice el nombre, consiste en crear un arbol. Tambien la operacion de **Destruir** consiste en destruir todo el arbol y por ultimo la operacion de **Vacio**, nos permite saber si un arbol tiene elementos o no. Las operaciones de **Insertar**, **Eliminar**, **Recorrer** y **Buscar** dependen del arbol que se este implementando. Explicare estas en detalle en los *Arboles Binarios* y **ABB**.

---

<div align="center">
<img width="40%" src="img/arbol.svg">
</div>


El nodo principal del arbol se lo conoce como la `raiz`, por este nodo sera donde se entra si se quiere hacer alguna operacion con el arbol. El arbol puede o no estar dividido en subarboles, pero cada subarbol de alguna manera debe estar concetado con la `raiz`. Algunas definiciones comunes de los arboles son las siguientes:

- Se dice que un nodo es `padre`, cuando este apunta a otros nodos. 
- Se dice que un nodo es `hijo`, cuando tiene un padre, es decir, cuando es apuntado por un nodo. 
- Se dice que un nodo es una `hoja`, si es que este no tiene hijos.
- Se puede dividir a un arbol segun sus `niveles`, siendo el 1er nivel el de la `raiz` y aumentando hacia abajo.
- La `altura` de un arbol se representa segun la cantidad de niveles que este tiene.

Existen diferentes tipos de arboles, los *Arboles Binarios*, *Arboles Binarios de Busqueda* **(ABB)**, *Arboles N-Arios*, *Arboles de Rotacion* **(AVL)**, etc...

En mi caso solamente voy a explicar que son los *Arboles Binarios* y los **ABB**. Como los **ABB** son un tipo de los *Aboles Binarios*, conviene primero explicar que es un *Arbol Binario*. Estos, como lo dice el nombre, son un arbol que surgen con la idea de aproximarnos a la busqueda binaria. En este tipo de arbol un nodo puede tener como maximo dos `hijos`. Esto nos permite dar una nocion de izquierda y derecha dentro del arbol. Es decir, si estamos parados en un nodo, podemos ir para la izquierda o par la derecha.

---

<div align="center">
<img width="25%" src="img/arbol_binario.svg">
</div>

---
Para los *Arboles Binarios* se definen una serie de recorridos, lo cual como dice el nombre, nos permite recorrer el arbol. Todos los recorridos comienzan en la `raiz` del arbol y constan de tres operaciones. Se dice que un nodo fue recorrido cuando se visita su contenido **(N)**, hijo derecho **(D)** e hijo izquierdo **(I)**. La complejidad que tienen todos los reocorridos es `O(n)`, pues si en nuestro arbol tenemos `n` elementos, debemos recorrelos todos.

Existen en total una cantidad de `3!` de reocorridos, pero los que explicare seran los siguientes: **Preorden**, **Inorden** y **Postorden**.

---

<div align="center">
<img width="45%" src="img/arbol_binario_recorridos.svg">
</div>


- La primera operacion que se realiza en el recorrido *Preorden* es visitar el contenido que tiene el nodo, luego se debe ir hacia la izquierda de dicho nodo y por ultimo a la derecha, **NID**. Este recorrido suele ser utilizado para copiar un arbol en otro.
- En el recorrido *Inorden* lo primero que se hace es ir hacia la izquierda del nodo, luego se visita su contenido y por ultimo se va hacia la derecha, **IND**. Este recorrido suele ser utilizado para recorrer el arbol en orden.
- Por ultimo en el recorrido *Postorden* lo primero que se hace es ir hacia la izquierda, luego la derecha y por ulltimo se visita el contenido del nodo, **IDN**. Este recorrido nos da el camino mas optimo para poder eliminar un arbol. 

Notemos que el tiempo de ejecucion para los recorridos siempre sera `O(n)`, pues siempre estamos recorriendo los `n` elementos del arbol.

---
En cuanto a los **ABB**, estos son un tipo de *Arboles Binarios*, los cuales cumplen con un orden determinado. Cada nodo tiene una clave, con la cual se comparara con la claves de los otros nodos. Dicha comparacion nos permita mantener un cierto orden a la hora de realizar operaciones con el arbol.

---

<div align="center">
<img width="25%" src="img/ABB.svg">
</div>

<div align="center"><font size="2">
En el dibujo las claves mayores estarian en el subarbol derecho y las menores en el subarbol izquierdo
</font></div>

---
- La operacion de *insertar* un elemento en el arbol, debemos recorrer el arbol e ir comparando el elemento que queremos insertar con las claves de los nodos del arbol. El resultado de dicha comparacion determinara de que lado del arbol debemos insertar el elemento. 

  ---
  <div align="center">
  <img width="50%" src="img/insertar.svg">
  </div>

  <div align="center"><font size="2">
  Comparamos con la raiz y vemos que el elemento a insertar es mas grande, entonces lo "mandamos" para el subarbol izquierdo. Nuevamente hacemos la misma comparacion con la "raiz" del subarbol izquierdo. Hasta finalmente encontrar la poscion donde debemos insertarlo.
  </font></div>

  ---
     Veamos entonces que la complejidad de insertar un elemento en un arbol es `O(log(n))`. Pues siempre que hacemos una comparacion, estamos quedandonos con la mitad del problema.

- En cuanto a la operacion de *eliminar* un elemento de un arbol, se pueden dar tres situaciones diferentes:

  - Eliminar un nodo `hoja`.
  <div align="center">
  <img width="50%" src="img/eliminar_hoja.svg">
  </div>

  <div align="center"><font size="2">Lo que se hace es buscar el elemento que se quiera eliminar y quitarlo del arbol</font></div>

  ---
  - Eliminar un nodo con un `hijo`.
  <div align="center">
  <img width="50%" src="img/eliminar_con_hijo.svg">
  </div>

  <div align="center"><font size="2">Se buscar el elemento recorriendo el arbol. Una vez que se lo encuentra se debe hacer que al anterior a el apunte al hijo del que queremos eliminar. Una vez hecho eso podemos eliminar el nodo</font></div>

  ---
  - Eliminar un nodo con dos `hijos`.
  <div align="center">
  <img width="70%" src="img/eliminar_con_hijos.svg">
  </div>

  <div align="center"><font size="2">Una vez encontramos el elemento que queremos eliminar, debemos encontrar el predecesor o el sucesor de este. El predecesor seria la mayor cota menor y el sucesor la menor cota superior. Luego debemos remplazar el elemento que queremos eliminar por el predecesor o el sucesor. En el caso de que el predecesor o sucesor tenga un hijo, se procede como cuando queremos eliminar un elemento con un hijo. Es muy importante que se tome una convencion segun si tomamos el predecesor o el sucesor y mantener dicha convencion para siempre</font></div> 

  ---
  Tambien veamos que en este caso la complejidad de eliminar un elemento es `O(log(n))`, pues el proceso mas costoso de todo seria encontrar el elemento que queremos eliminar y como sabemos de la insercion, este proceso es `O(log(n))`. El resto de las operaciones de eliminar tienen una complejidad constante `O(1)`, pues solamente estamos reapuntando punteros.

- Para *buscar* un elemento en el arbol debemos ir comparando el elemento que buscamos con la clave del nodo. Como en el proceso de insertar, esta comparacion determinara de que lado del arbol debemos buscar el elemento. Veamos que esta operacion tiene una complejidad `O(log(n))`, pues al igual que *insertar* y *eliminar*, lo que hacemos es a medida que comparamos nos quedamos con un subarbol.
<div align="center">
<img width="90%" src="img/buscar_elemento.svg">
</div>

- Los *recorridos* que se pueden hacer en un **ABB** son los mismo que los recorridos que los de un *Arbol Binario*.

Para analizar la complejidad de estas operaciones en un **ABB** se asumio que el arbol estaba balanceado. Que un arbol este balanceado implica que este no se degenera en una lista. En el caso de que el arbol se degenere en una lista las complejidades de las operaciones pasarian a ser `O(n)`, pues no estariamos partiendo el problema a la mitad.

---
  <div align="center">
  <img width="25%" src="img/arbol_degenerado.svg">
  </div>
  <div align="center"><font size="2">Veamos que en este caso si queremos buscar o eliminar el elemento 23, deberiamos recorrer el arbol como si fuera una lista. Tambien ocurriria lo mismo si quisieramos insertar un elemento mayor a 15.</font></div> 

---
Para solucionar este tipo de problemas se introducen las rotaciones.