# Arreglos estáticos y ciclos

**Menú de consola de Sonora**

---

El catálogo de Sonora vive en un `std::vector<Cancion>`, una lista que crece o se achica según lo que necesites. Hoy Sonora agrega un dato distinto: cuántas reproducciones tuvo el catálogo completo cada día de la semana. Ese dato siempre tiene exactamente siete posiciones, una por día, ni una más ni una menos. Para datos con un tamaño que no cambia, C++ ofrece una estructura más simple que un vector: el **arreglo estático**.

Con ese arreglo en su lugar, esta sesión repite un patrón que ya conoces de Python (recorrer una colección de datos posición por posición) y construye cuatro operaciones sobre él: transformar cada valor en uno nuevo, acumular varios valores en uno solo, contar cuántos cumplen una condición, y filtrar los que la cumplen en una lista aparte. Cierra con el ciclo indefinido, la otra forma de repetir código en C++, que no depende de un contador sino de una condición que puede tardar un número distinto de vueltas en cumplirse.

### Sobre las soluciones de esta guía

Cada ejercicio trae su solución en un bloque plegable, como este:

<details>
<summary>🔓 Ver solución</summary>

Aquí va la solución.

</details>

Esas soluciones están para que verifiques lo que ya intentaste, no para abrirlas antes de escribir tu propia respuesta. Ábrelas después de tu intento, así esté incompleto o creas que está mal: el objetivo de esta guía es que entiendas arreglos y ciclos, no que produzcas texto idéntico al de la solución.

### Sobre el vocabulario técnico

Vienes de 192 horas de Python, así que ya *hiciste* muchas de las cosas de esta guía sin necesariamente haberles puesto nombre técnico: recorrer una lista con `for elemento in lista:`, revisar una condición con `if`, acumular un total en una variable. Esta guía le pone nombre formal a esas acciones, y cada vez que aparece un término nuevo lo vas a ver marcado así:

> 📖 **Palabra nueva:** el término, su significado en una frase, y cómo se relaciona con algo que ya sabes de Python.

Si en algún punto no recuerdas qué significa un término, busca hacia atrás la primera vez que aparece marcado de esta forma.

## Tabla de contenido

0. [Repaso: cómo se conectan reproductor.h, reproductor.cpp y main.cpp](#0-repaso-cómo-se-conectan-reproductorh-reproductorcpp-y-maincpp)
1. [Arreglos estáticos](#1-arreglos-estáticos)
2. [Recorrer un arreglo con un ciclo definido](#2-recorrer-un-arreglo-con-un-ciclo-definido)
3. [Transformación](#3-transformación)
4. [Acumulación](#4-acumulación)
5. [Conteo](#5-conteo)
6. [Filtrado](#6-filtrado)
7. [Ciclos indefinidos: while](#7-ciclos-indefinidos-while)
8. [Cierra el menú de Sonora](#8-cierra-el-menú-de-sonora)
9. [Ejercicios sueltos de práctica adicional](#ejercicios-sueltos-de-práctica-adicional)

---

Abre el Codespace del curso igual que siempre. En `src/` vas a encontrar `main.cpp`, `reproductor.h` y `reproductor.cpp` con el catálogo y las cinco primeras opciones del menú ya funcionando. Compila y ejecuta con:

```bash
g++ src/main.cpp src/reproductor.cpp -o sonora
./sonora
```

Esta sesión agrega cinco opciones nuevas al menú, entre la opción 5 (`Interpretar una calificacion`) y la opción 11 (`Salir`). Las opciones 6 a 10 ya están en `src/main.cpp`, comentadas: cada sección de esta guía te dice cuándo descomentar la que le corresponde.

## 0. Repaso: cómo se conectan reproductor.h, reproductor.cpp y main.cpp

Ya tienes tres archivos trabajando juntos: `reproductor.h` **declara** qué funciones existen, `reproductor.cpp` **implementa** el cuerpo de cada una, y `main.cpp` **usa** esas funciones sin necesitar saber cómo están escritas por dentro. Antes de agregar nada nuevo, vale la pena practicar esa conexión, porque el resto de esta guía va a vivir exactamente ahí.

![Cómo se conectan reproductor.h, reproductor.cpp y main.cpp, desde el código fuente hasta el ejecutable](img/relacion_h_cpp_main.svg)

`g++ src/main.cpp src/reproductor.cpp -o sonora` en realidad hace dos cosas: primero compila cada `.cpp` por separado, generando un archivo intermedio por cada uno; después, una etapa que se llama el **enlazador** (*linker*) une esos dos archivos intermedios en un solo ejecutable. Ahí es donde vive un error que todavía no has visto: qué pasa cuando `main.cpp` llama una función que `reproductor.h` declara, pero que nadie llegó a escribir en `reproductor.cpp`.

### El patrón de función de prueba que vas a usar toda la guía

`src/main.cpp` ya tiene toda la lógica del menú dentro de una función, `iniciar_sonora()`, y `main()` solo la llama:

```cpp
void iniciar_sonora() {
    // ... todo el catalogo y el ciclo del menu
}

int main() {
    iniciar_sonora();
    return 0;
}
```

Cuando un ejercicio de esta guía te pida "prueba tal función", no vas a crear ningún archivo nuevo. Vas a agregar una función corta arriba de `iniciar_sonora()`, y en `main()` vas a comentar la llamada a `iniciar_sonora()` y descomentar (o agregar) la llamada a tu función de prueba:

```cpp
// Funcion de prueba, solo para este ejercicio: en un programa real no
// existiria, aqui sirve para probar una funcion de forma aislada.
void prueba_ejemplo() {
    std::cout << "Esto es una prueba\n";
}

int main() {
    // iniciar_sonora();
    prueba_ejemplo();
    return 0;
}
```

El comando de compilación no cambia nunca: siempre `g++ src/main.cpp src/reproductor.cpp -o sonora`, siempre `./sonora`. Cuando termines la prueba, comenta de nuevo tu función y descomenta `iniciar_sonora();`, para volver al menú completo.

### Ejercicio: provocar y resolver un error del enlazador

Este ejercicio no tiene solución plegable: es un procedimiento con dos partes, y el resultado esperado es el mensaje de error mismo, que vas a comprobar en tu propia máquina.

**Parte 1.** En `reproductor.h`, agrega esta declaración, sin tocar nada más:

```cpp
void mostrar_bienvenida_sonora();
```

En `main.cpp`, siguiendo el patrón de arriba, agrega una función de prueba que la llame, y actívala en lugar de `iniciar_sonora()`:

```cpp
void prueba_bienvenida() {
    mostrar_bienvenida_sonora();
}

int main() {
    // iniciar_sonora();
    prueba_bienvenida();
    return 0;
}
```

Compila con `g++ src/main.cpp src/reproductor.cpp -o sonora`. Vas a obtener un error parecido a este:

```
/usr/bin/ld: /tmp/xxxxxx.o: in function `prueba_bienvenida()':
main.cpp:(.text+0xdbd): undefined reference to `mostrar_bienvenida_sonora()'
collect2: error: ld returned 1 exit status
```

(El nombre del archivo temporal y el número después de `.text+` van a ser distintos en tu máquina; lo que se mantiene igual es `undefined reference to` con el nombre de tu función.)

`undefined reference` (referencia sin definir) es el mensaje propio del enlazador, distinto a los errores de compilación que ya conoces. `reproductor.h` prometió que la función existía, y `main.cpp` confió en esa promesa, pero nadie escribió el cuerpo en `reproductor.cpp`. El compilador, que revisa cada `.cpp` por separado, no tiene forma de detectarlo antes: el problema solo aparece cuando el enlazador intenta unir las dos partes.

**Parte 2.** Agrega la implementación en `reproductor.cpp`:

```cpp
void mostrar_bienvenida_sonora() {
    std::cout << "Bienvenido a Sonora\n";
}
```

Compila de nuevo con el mismo comando. Esta vez compila y corre, y al ejecutar `./sonora` ves:

```
Bienvenido a Sonora
```

Cuando termines, quita la declaración de `mostrar_bienvenida_sonora()` de `reproductor.h`, su implementación de `reproductor.cpp`, y la función `prueba_bienvenida()` de `main.cpp`; y vuelve a activar `iniciar_sonora();` en `main()`. Todo el resto de esta guía asume que `main()` está llamando `iniciar_sonora()`.

## 1. Arreglos estáticos

🐍 **Recordatorio rápido:** `std::vector<int>` es la versión en C++ de una lista de Python. Guarda una secuencia de valores, uno detrás de otro, y su tamaño puede crecer con `.push_back(valor)` (el equivalente a `.append()` en Python) o reducirse con `.pop_back()`. Accedes a cada valor con un índice entre corchetes, igual que en Python: `vector[0]`, `vector[1]`.

Sonora necesita guardar el total de reproducciones del catálogo completo para cada día de la semana. Un `std::vector<int>` funcionaría, pero un vector está pensado para un tamaño que cambia con `push_back`, y una semana siempre tiene siete días, ni uno más. Para ese caso, C++ tiene una estructura más simple.

🐍 **Puente con Python:** en Python, una lista (`lista = [12000, 8500, ...]`) puede crecer o encogerse en cualquier momento con `.append()` o `.pop()`, sin que tengas que decidir su tamaño de antemano. El arreglo estático que vas a ver aquí no tiene equivalente directo en Python: es una estructura que existe justamente porque, a veces, sabes con certeza que el tamaño nunca va a cambiar (los 7 días de la semana), y esa certeza te permite usar algo más simple y liviano que una lista.

```cpp
int reproducciones_semana[7];
```

Esto declara un **arreglo**, un bloque de memoria contiguo que guarda siete valores `int` seguidos, uno detrás de otro. El número entre corchetes es el tamaño del arreglo, y tiene que ser un valor que el compilador conozca antes de ejecutar el programa, no una variable que cambie mientras corre.

> 📖 **Palabra nueva: posición e índice.** Cada casilla de un arreglo se llama una **posición**, y el número que usas para señalar cuál posición quieres (el `0`, el `1`, el `2`...) se llama **índice**. Es la misma idea que el número entre corchetes de una lista en Python (`lista[0]`, `lista[1]`), solo que en C++ tiene nombre propio, porque los índices van a ser protagonistas de esta sesión.

Accedes a cada posición con un índice entre corchetes, empezando en cero igual que con un vector:

```cpp
int reproducciones_semana[7];
reproducciones_semana[0] = 12000;  // lunes
reproducciones_semana[1] = 8500;   // martes
reproducciones_semana[6] = 18500;  // domingo

std::cout << reproducciones_semana[0] << "\n";  // 12000
```

Declarar las siete posiciones una por una es tedioso. Igual que con `std::vector`, puedes inicializar todo el arreglo en una sola línea:

```cpp
int reproducciones_semana[7] = {12000, 8500, 15300, 9800, 22000, 31000, 18500};
```

Cada canción de Sonora también necesita un nombre para su día. Un arreglo puede guardar cualquier tipo, no solo `int`:

```cpp
std::string nombres_dias[7] = {
    "Lunes", "Martes", "Miercoles", "Jueves", "Viernes", "Sabado", "Domingo"
};
```

`reproducciones_semana` y `nombres_dias` son dos arreglos separados que comparten el mismo índice: la posición 2 de uno (`15300`) corresponde a la posición 2 del otro (`"Miercoles"`). Vas a recorrer los dos juntos, en el mismo índice, durante toda la sesión.

> 📖 **Palabra nueva: recorrer.** Es la palabra técnica para lo que ya hacías en Python con `for elemento in lista:`: visitar cada posición de una colección de datos, una por una, en orden, generalmente para hacer algo con cada una (imprimirla, sumarla, revisarla). "Recorrer un arreglo" significa visitar sus posiciones una por una, del principio al final.

![Declaración, inicialización y memoria de un arreglo estático, con sus 7 posiciones](img/declaracion_arreglo_memoria.svg)

### Cómo vive un arreglo en la memoria del computador

Cuando declaras `int reproducciones_semana[7]`, C++ reserva un bloque de memoria contiguo, siete posiciones seguidas, una justo después de la otra, sin espacios entre ellas. Cada posición ocupa exactamente `sizeof(int)` bytes, y esa cantidad es la misma para las siete: no importa qué valor guardes, el espacio que ocupa `reproducciones_semana[0]` es idéntico al de `reproducciones_semana[6]`.

Esto significa que la dirección de memoria de cualquier posición se calcula con una fórmula fija, sin tener que recorrer el arreglo desde el principio para llegar hasta ahí:

```
direccion(reproducciones_semana[i]) = direccion_base + i * sizeof(int)
```

> 📖 **Palabra nueva: los dos usos de `&`.** El símbolo `&` significa algo distinto según dónde aparece. Antes de un nombre de variable, como en `&reproducciones_semana[dia]`, pide la **dirección de memoria** donde vive esa variable, la "posición física" en la memoria, no su valor. Después de un tipo, en un parámetro de función, como en `Cancion& cancion`, significa **referencia**: le dice a la función que trabaje directamente sobre la variable original, no sobre una copia. Son dos usos distintos del mismo símbolo, y se distinguen por dónde aparece: pegado a una variable (dirección) o pegado a un tipo (referencia).

Puedes comprobarlo pidiéndole a C++ la dirección de cada posición con el operador `&`, el mismo que usaste para el paso por referencia:

```cpp
int reproducciones_semana[7] = {12000, 8500, 15300, 9800, 22000, 31000, 18500};
for (int dia = 0; dia < 7; dia++) {
    std::cout << "reproducciones_semana[" << dia << "] = " << reproducciones_semana[dia]
               << "   direccion: " << &reproducciones_semana[dia] << "\n";
}
```

En una ejecución concreta, esto imprimió:

```
reproducciones_semana[0] = 12000   direccion: 0x7ffe6d62dd30
reproducciones_semana[1] = 8500    direccion: 0x7ffe6d62dd34
reproducciones_semana[2] = 15300   direccion: 0x7ffe6d62dd38
reproducciones_semana[3] = 9800    direccion: 0x7ffe6d62dd3c
reproducciones_semana[4] = 22000   direccion: 0x7ffe6d62dd40
reproducciones_semana[5] = 31000   direccion: 0x7ffe6d62dd44
reproducciones_semana[6] = 18500   direccion: 0x7ffe6d62dd48
```

Cada dirección salta exactamente 4 bytes respecto a la anterior (`0x...d30`, `0x...d34`, `0x...d38`...), y 4 bytes es justo `sizeof(int)` en este sistema. Esa dirección base (`0x7ffe6d62dd30`) va a cambiar en cada ejecución del programa, porque el sistema operativo decide en qué parte de la memoria ubicar el arreglo cada vez, pero el salto de 4 bytes entre una posición y la siguiente no cambia nunca, porque depende únicamente del tipo `int`, no de dónde quedó ubicado el arreglo.

💡 **Por qué importa:** esta fórmula es la razón por la que acceder a `reproducciones_semana[dia]` tarda lo mismo sin importar si `dia` vale `0` o `6`. C++ no necesita "caminar" por las posiciones anteriores para llegar a la que buscas: multiplica el índice por el tamaño de un elemento, suma esa cantidad a la dirección donde empieza el arreglo, y llega directo. Se llama **acceso directo** o **acceso aleatorio**, y es lo que hace que un ciclo `for` sobre un arreglo, como el de la sección 2, sea una **operación barata**: en programación, "barata" no se refiere a dinero, sino a que consume poco tiempo y poco procesamiento, lo opuesto a una operación "cara", que tarda más o exige más trabajo del computador.

Un `std::vector` también guarda sus datos en un bloque contiguo por dentro, así que acceder a `catalogo[i]` usa la misma fórmula. La diferencia está en un paso previo a esa cuenta: el vector en sí ocupa poco espacio, y por dentro guarda la ubicación de otro bloque de memoria, reservado aparte, donde en realidad viven los datos. Llegar a un elemento del vector implica primero ir hasta ese bloque de datos, y solo después aplicar la misma fórmula de dirección base más índice. Un arreglo estático como `reproducciones_semana` se salta ese paso: sus datos viven directamente donde lo declaraste, sin ningún bloque adicional que buscar primero ni ninguna reserva de memoria extra. Por eso un arreglo estático es más liviano de crear y ligeramente más directo de recorrer que un vector del mismo tamaño, aunque para la mayoría de programas esa diferencia es demasiado pequeña para notarla sin medirla.

Este curso llama **arreglo estático** a `int reproducciones_semana[7]` para distinguirlo del `std::vector` que ya conoces, porque su tamaño queda fijo desde que se declara.

🎓 **¿Sabías qué?** Un `std::vector` en realidad guarda sus datos en un arreglo por dentro, solo que gestiona ese arreglo por ti: cuando lo llenas más allá de su capacidad actual, reserva un bloque de memoria más grande, copia los datos existentes ahí, y libera el bloque anterior. Un arreglo estático se salta toda esa gestión porque nunca cambia de tamaño, y por eso es más liviano cuando ya sabes cuántos elementos vas a guardar.

| | `int arreglo[7]` | `std::vector<int> vector` |
|---|---|---|
| Tamaño | Fijo, se decide al declararlo | Cambia con `push_back`, `pop_back` |
| Memoria | Un bloque fijo, reservado una sola vez | Puede reasignarse a un bloque más grande |
| Cuándo usarlo | El número de elementos no cambia (los 7 días de una semana) | El número de elementos crece o se reduce en tiempo de ejecución (el catálogo de canciones) |

![Comparación entre un arreglo estático de 7 posiciones y un std::vector que crece con push_back](img/arreglo_estatico_vs_vector.svg)

⚠️ **Error frecuente:** GCC, el compilador que usa este curso, acepta como extensión propia declarar el tamaño de un arreglo con una variable en lugar de un número fijo, sin marcar ni error ni advertencia con el comando de compilación que usas en este curso:

```cpp
int dias = 7;
int reproducciones_semana[dias];  // GCC lo acepta, pero no es C++ estandar
```

Ese código no es C++ estándar. Un compilador distinto, como el de Visual Studio, lo rechaza. Este curso trata el tamaño de un arreglo estático como un número fijo, escrito directamente o conocido antes de compilar, sin depender de que GCC sea permisivo en este caso puntual.

### Ejercicios

🔧 **Consejo de entorno:** compila con `g++ src/main.cpp src/reproductor.cpp -o sonora` y ejecuta con `./sonora`.

#### 🧩 Antes de programar

Sin escribir ni compilar nada, empareja cada expresión con el valor que produce, usando `reproducciones_semana = {12000, 8500, 15300, 9800, 22000, 31000, 18500}` y `nombres_dias = {"Lunes", "Martes", "Miercoles", "Jueves", "Viernes", "Sabado", "Domingo"}`.

| Expresión | Valor |
|---|---|
| A. `reproducciones_semana[0]` | 1. `"Viernes"` |
| B. `nombres_dias[4]` | 2. `31000` |
| C. `reproducciones_semana[5]` | 3. `12000` |

<details>
<summary>🔓 Ver solución</summary>

A-3, B-1, C-2. `reproducciones_semana[0]` es la primera posición (índice 0), `12000`. `nombres_dias[4]` es la quinta posición (índice 4, contando desde 0: Lunes=0, Martes=1, Miercoles=2, Jueves=3, Viernes=4), `"Viernes"`. `reproducciones_semana[5]` es la sexta posición, `31000`.

</details>

#### Básico

Sigue el patrón de la sección 0: agrega esta función arriba de `iniciar_sonora()`, en `src/main.cpp`, y actívala comentando la llamada a `iniciar_sonora()`.

Declara `int reproducciones_semana[7]`, inicialízalo con `{12000, 8500, 15300, 9800, 22000, 31000, 18500}`, y declara `std::string nombres_dias[7]` con los nombres de los siete días en el mismo orden. Imprime la posición 2 de cada arreglo por separado, sin usar ningún ciclo todavía.

```cpp
void prueba_posiciones() {
    // Tu codigo aqui
}

int main() {
    // iniciar_sonora();
    prueba_posiciones();
    return 0;
}
```

Compila con `g++ src/main.cpp src/reproductor.cpp -o sonora` y ejecuta con `./sonora`.

La salida esperada es:

```
Miercoles
15300
```

<details>
<summary>🔓 Ver solución</summary>

```cpp
void prueba_posiciones() {
    int reproducciones_semana[7] = {12000, 8500, 15300, 9800, 22000, 31000, 18500};
    std::string nombres_dias[7] = {
        "Lunes", "Martes", "Miercoles", "Jueves", "Viernes", "Sabado", "Domingo"
    };

    std::cout << nombres_dias[2] << "\n";
    std::cout << reproducciones_semana[2] << "\n";
}
```

</details>

#### Intermedio

Sin compilar todavía, decide qué imprime este fragmento.

```cpp
int reproducciones_semana[7] = {12000, 8500, 15300, 9800, 22000, 31000, 18500};
std::cout << reproducciones_semana[7] << "\n";
```

<details>
<summary>🔓 Ver solución</summary>

El arreglo tiene posiciones válidas de 0 a 6, y `reproducciones_semana[7]` pide la octava posición, que no existe. C++ no revisa ese límite al ejecutar el programa: el resultado es un valor indeterminado, lo que se llama **comportamiento indefinido**, un dato que puede ser cualquier número, incluida basura de memoria que no le pertenece al arreglo, y que puede cambiar entre una ejecución y otra. A diferencia del `sizeof` de la sección siguiente, este error no siempre avisa con un mensaje: a veces el programa corre sin fallar y muestra un valor incorrecto sin ningún aviso.

</details>

#### Avanzado

Declara en `reproductor.h`, justo después del struct `Cancion`, un comentario que documente el nuevo dato que va a manejar Sonora esta sesión. No hace falta escribir ninguna función todavía, solo deja este comentario antes del primer prototipo nuevo:

```cpp
// reproducciones_semana[7] guarda el total de reproducciones
// del catalogo completo para cada dia (0 = Lunes, 6 = Domingo).
```

No hay salida que verificar en este ejercicio: es preparación para las funciones que vas a declarar en las secciones siguientes.

#### Reto

Sonora también podría guardar la duración total reproducida por día, en vez de solo el conteo. Declara `int segundos_escuchados_semana[7]` con valores que decidas tú, y escribe una expresión (sin ciclo todavía) que calcule cuántos minutos se escucharon el sábado, dividiendo esa posición entre 60.

**🧭 Pistas**

- La división entre dos `int` en C++ trunca el resultado, descarta la parte decimal. Si necesitas los minutos con decimales, uno de los dos operandos tiene que ser `double`.
- Prueba `static_cast<double>(segundos_escuchados_semana[5]) / 60` y compara el resultado contra la división entera sin el `cast`.

---

## 2. Recorrer un arreglo con un ciclo definido

### Qué es un ciclo, y en qué se diferencia de un condicional

Un condicional como `if` revisa una condición una sola vez, y según el resultado, ejecuta un bloque de código o lo salta. Ya usaste esto en `es_recomendable`:

```cpp
if (es_recomendable(catalogo[0].reproducciones, catalogo[0].calificacion)) {
    std::cout << "Recomendable\n";
}
```

Esto decide, una única vez, si la primera canción del catálogo es recomendable. Si quisieras la misma decisión para la segunda canción, tendrías que escribir el mismo `if` otra vez, con `catalogo[1]`, y luego otra vez con `catalogo[2]`, una copia del mismo bloque por cada canción del catálogo.

Un **ciclo** resuelve justo ese problema: repite un bloque de código varias veces, revisando su condición antes de cada repetición, no solo antes de la primera. En el caso 4 del menú de Sonora ya usaste uno, sin llamarlo todavía por su nombre:

```cpp
for (Cancion& cancion : catalogo) {
    bool recomendable = es_recomendable(cancion.reproducciones, cancion.calificacion);
    std::cout << cancion.titulo << ": "
               << (recomendable ? "Recomendable" : "No recomendable")
               << "\n";
}
```

Ese `for` no decide una sola vez: repite el mismo bloque, con `cancion` apuntando a una canción distinta en cada vuelta, hasta que recorre el catálogo completo. La diferencia con el `if` no es qué se decide dentro del bloque, es cuántas veces se vuelve a revisar la condición antes de seguir.

> 📖 **Palabra nueva: vuelta (o iteración).** Cada vez que el cuerpo de un ciclo se ejecuta completo, de principio a fin, es una **vuelta**. El término más formal es **iteración**, y significa lo mismo: en Python, cada paso de un `for elemento in lista:` es una iteración: procesa un elemento, y sigue con el siguiente.

![Comparación entre un condicional, que decide una sola vez, y un ciclo, que repite la decisión varias veces](img/condicional_vs_ciclo.svg)

Esta sesión trabaja sobre esa misma idea, repetir un bloque de código varias veces en lugar de una sola, aplicada a un arreglo en lugar de un vector, y con dos formas distintas de escribir esa repetición según lo que necesites en cada vuelta.

Ya recorriste el catálogo con `for (Cancion& cancion : catalogo)`. Ese ciclo te entrega cada canción, una por una, pero nunca te dice en qué posición del vector va cada una: si necesitaras saber si estás en la primera canción o en la última, ese `for` no te lo dice por sí solo.

C++ tiene dos formas de escribir un ciclo `for`, y cuál conviene usar depende de una sola pregunta: **¿necesitas la posición de cada elemento, o te basta con su valor?**

### Cuando no necesitas la posición: el for basado en rango

Es el que ya conoces:

```cpp
for (Cancion& cancion : catalogo) {
    mostrar_cancion(cancion);
}
```

`cancion` toma, una vuelta a la vez, cada elemento de `catalogo`. Nunca sabes si vas en la posición 0 o en la posición 2, y para lo que hace `mostrar_cancion` no hace falta saberlo.

### Cuando sí necesitas la posición: el for clásico

Es el que necesitas cuando la posición misma es un dato que vas a usar dentro del ciclo, no solo el valor. Sonora necesita justo eso: para imprimir `reproducciones_semana[dia]` junto con `nombres_dias[dia]`, el ciclo tiene que reutilizar la misma posición `dia` en dos arreglos distintos, algo que el `for` basado en rango no puede darte, porque solo te entrega el valor de una colección a la vez, nunca una posición que puedas usar en otra.

```cpp
for (int dia = 0; dia < 7; dia++) {
    std::cout << reproducciones_semana[dia] << "\n";
}
```

Este `for` tiene tres partes, separadas por `;`, dentro de los paréntesis:

1. **Inicialización** (`int dia = 0`): se ejecuta una sola vez, antes de la primera vuelta, y declara la variable que va a contar las vueltas.
2. **Condición** (`dia < 7`): se revisa antes de cada vuelta. Mientras sea verdadera, el ciclo continúa; en cuanto es falsa, el ciclo termina.
3. **Incremento** (`dia++`): se ejecuta al final de cada vuelta, después del cuerpo del ciclo.

![Anatomía del ciclo for clásico: inicialización, condición e incremento sobre mostrar_reproducciones_semana](img/ciclo_for_definido_partes.svg)

`dia++` suma 1 a `dia`, lo mismo que escribir `dia = dia + 1`. Se llama **ciclo definido** porque el número de vueltas queda fijo desde antes de empezar: la condición `dia < 7` garantiza exactamente siete repeticiones, ni una más ni una menos, sin importar los valores que haya dentro del arreglo.

### Una limitación más de los arreglos: el for basado en rango no siempre funciona

Además de la razón anterior, hay un motivo puramente práctico para usar el `for` clásico con `reproducciones_semana`: dentro de una función que recibe un arreglo estático como parámetro, el `for` basado en rango deja de funcionar, incluso si solo necesitaras el valor de cada posición, sin importarte el índice. Agrega esta función, comentada, arriba de `iniciar_sonora()` en `src/main.cpp`:

```cpp
// void mostrar_arreglo(int reproducciones_semana[7]) {
//     for (int valor : reproducciones_semana) {
//         std::cout << valor << "\n";
//     }
// }
```

Descoméntala, llámala desde una función de prueba activada en lugar de `iniciar_sonora()`, y compila con `g++ src/main.cpp src/reproductor.cpp -o sonora`. Vas a ver algo parecido a esto:

```
main.cpp: In function ‘void mostrar_arreglo(int*)’:
main.cpp:3:22: error: ‘begin’ was not declared in this scope; did you mean ‘std::begin’?
    3 |     for (int valor : reproducciones_semana) {
      |                      ^~~~~~~~~~~~~~~~~~~~~
      |                      std::begin
(el compilador sigue con más líneas despues de esta, señalando el mismo problema con ‘end’)
```

Este error no te deja compilar nada más mientras esté ahí, así que después de verlo, vuelve a comentar `mostrar_arreglo` completa (función y llamado) antes de seguir.

Dentro de `main()`, donde declaraste el arreglo directamente, `for (int valor : reproducciones_semana)` sí compila sin problema. El error solo aparece cuando el arreglo llegó como parámetro de una función, como en `mostrar_arreglo`. Esto es una limitación propia de los arreglos que no tiene que ver con si necesitas o no la posición de cada elemento: un arreglo que entra como parámetro de una función deja de comportarse como el arreglo completo que declaraste en `main()`. Todavía no vas a estudiar por qué pasa esto exactamente, es un tema que vas a ver más adelante en el curso. Por ahora, la regla práctica es esta: **cuando un arreglo llegue como parámetro de una función, recórrelo siempre con el `for` clásico**, nunca con el basado en rango, sin importar si necesitas la posición o no.

Con las funciones ya declaradas en `reproductor.h`, la primera de esta sesión recorre `reproducciones_semana` y `nombres_dias` juntos, en el mismo índice:

```cpp
// En reproductor.h:
/**
 * Imprime las reproducciones de cada dia de la semana.
 *
 * @param reproducciones_semana Arreglo con 7 posiciones, una por dia.
 * @param nombres_dias Arreglo con el nombre de cada dia, en el mismo orden.
 */
void mostrar_reproducciones_semana(int reproducciones_semana[7], std::string nombres_dias[7]);

// En reproductor.cpp:
void mostrar_reproducciones_semana(int reproducciones_semana[7], std::string nombres_dias[7]) {
    for (int dia = 0; dia < 7; dia++) {
        std::cout << nombres_dias[dia] << ": " << reproducciones_semana[dia] << "\n";
    }
}
```

Con `reproducciones_semana = {12000, 8500, 15300, 9800, 22000, 31000, 18500}`, la salida es:

```
Lunes: 12000
Martes: 8500
Miercoles: 15300
Jueves: 9800
Viernes: 22000
Sabado: 31000
Domingo: 18500
```

Fíjate en la firma de `mostrar_reproducciones_semana`: ningún parámetro lleva `&`. Ya viste que sin `&` una función recibe una copia y no puede modificar el original. Con un arreglo, esa regla no aplica: un arreglo que llega como parámetro de una función siempre le da a la función acceso directo al arreglo original, incluso sin `&`. Es una diferencia con los tipos sueltos como `int` o `Cancion`, que sí necesitan `&` de forma explícita para modificarse; en un arreglo, esa modificación directa viene incluida siempre, sin que tengas que pedirla. Compruébalo con esta función, siguiendo el patrón de prueba de la sección 0: agrégala arriba de `iniciar_sonora()` y actívala en `main()` en su lugar.

```cpp
void duplicar_reproducciones(int reproducciones_semana[7]) {
    for (int dia = 0; dia < 7; dia++) {
        reproducciones_semana[dia] = reproducciones_semana[dia] * 2;
    }
}

void prueba_duplicar() {
    int reproducciones_semana[7] = {100, 200, 300, 400, 500, 600, 700};
    duplicar_reproducciones(reproducciones_semana);
    for (int dia = 0; dia < 7; dia++) {
        std::cout << reproducciones_semana[dia] << " ";
    }
    std::cout << "\n";
}

int main() {
    // iniciar_sonora();
    prueba_duplicar();
    return 0;
}
```

```
200 400 600 800 1000 1200 1400
```

`reproducciones_semana` cambió en `main()` aunque la función no tenga `&` en su parámetro. Un arreglo, a diferencia de un `int` o un `Cancion` sueltos, siempre se comporta como si tuviera `&`, porque nunca llega copiado a la función: llega el mismo bloque de memoria.

### Ejercicios

🔧 **Consejo de entorno:** compila con `g++ src/main.cpp src/reproductor.cpp -o sonora` y ejecuta con `./sonora`.

#### Inducción al error

Agrega esta función, comentada, arriba de `iniciar_sonora()`:

```cpp
// void mostrar_tamano(int reproducciones_semana[7]) {
//     std::cout << "Dentro de la funcion: " << sizeof(reproducciones_semana) << " bytes\n";
// }
//
// void prueba_tamano() {
//     int reproducciones_semana[7] = {100, 200, 300, 400, 500, 600, 700};
//     std::cout << "En main: " << sizeof(reproducciones_semana) << " bytes\n";
//     mostrar_tamano(reproducciones_semana);
// }
```

Descoméntala, actívala en `main()` en lugar de `iniciar_sonora()`, y compila con `g++ src/main.cpp src/reproductor.cpp -o sonora`. El compilador muestra una advertencia (no un error) apuntando a la línea del `sizeof` dentro de la función, y aun así el programa compila y corre. La salida es:

```
En main: 28 bytes
Dentro de la funcion: 8 bytes
```

Dentro de `main()`, `reproducciones_semana` todavía es un arreglo completo de 7 `int`, y `sizeof` reporta el tamaño real de ese bloque. Dentro de la función, `reproducciones_semana` ya perdió esa información, y `sizeof` reporta otro tamaño (8 bytes en este sistema) sin ninguna relación con las 7 posiciones que tenía originalmente. Es la misma limitación de esta sección: un arreglo que llega como parámetro de una función deja de comportarse como el arreglo completo que declaraste en `main()`. Contar cuántos elementos tiene un arreglo con `sizeof` solo funciona en el mismo bloque `{ }` donde se declaró, nunca dentro de una función a la que llegó como parámetro. Por eso `mostrar_reproducciones_semana` recibe el número de días como una constante fija en el ciclo (`dia < 7`), en lugar de intentar calcularlo con `sizeof` dentro de la función.

Cuando termines, vuelve a comentar `mostrar_tamano` y `prueba_tamano` completas.

#### 🧩 Antes de programar

Encuentra el error sin corregirlo todavía. Este `for`, que debería imprimir las 7 posiciones de `reproducciones_semana`, tiene un error de una sola línea:

```cpp
for (int dia = 1; dia < 7; dia++) {
    std::cout << reproducciones_semana[dia] << "\n";
}
```

¿Cuál línea está mal, y qué posición se queda sin imprimir?

<details>
<summary>🔓 Ver solución</summary>

La inicialización, `int dia = 1`, debería ser `int dia = 0`. Con `dia` empezando en 1, la posición 0 (`reproducciones_semana[0]`, el lunes) nunca se imprime: el ciclo hace 6 vueltas en lugar de 7, de la posición 1 a la 6.

</details>

#### Básico

Declara e implementa `mostrar_reproducciones_semana(int reproducciones_semana[7], std::string nombres_dias[7])` tal como se ve en esta sección, en `reproductor.h` y `reproductor.cpp`.

Sigue el patrón de la sección 0 para probarla:

```cpp
void prueba_mostrar_semana() {
    int reproducciones_semana[7] = {12000, 8500, 15300, 9800, 22000, 31000, 18500};
    std::string nombres_dias[7] = {
        "Lunes", "Martes", "Miercoles", "Jueves", "Viernes", "Sabado", "Domingo"
    };
    mostrar_reproducciones_semana(reproducciones_semana, nombres_dias);
}
```

Compila con `g++ src/main.cpp src/reproductor.cpp -o sonora` y ejecuta con `./sonora`.

La salida esperada es:

```
Lunes: 12000
Martes: 8500
Miercoles: 15300
Jueves: 9800
Viernes: 22000
Sabado: 31000
Domingo: 18500
```

<details>
<summary>🔓 Ver solución</summary>

```cpp
// En reproductor.h:
/**
 * Imprime las reproducciones de cada dia de la semana.
 *
 * @param reproducciones_semana Arreglo con 7 posiciones, una por dia.
 * @param nombres_dias Arreglo con el nombre de cada dia, en el mismo orden.
 */
void mostrar_reproducciones_semana(int reproducciones_semana[7], std::string nombres_dias[7]);

// En reproductor.cpp:
void mostrar_reproducciones_semana(int reproducciones_semana[7], std::string nombres_dias[7]) {
    for (int dia = 0; dia < 7; dia++) {
        std::cout << nombres_dias[dia] << ": " << reproducciones_semana[dia] << "\n";
    }
}
```

</details>

#### Intermedio

Sin compilar todavía, decide cuántas veces se imprime `"Vuelta"` en este ciclo.

```cpp
for (int i = 3; i < 10; i = i + 2) {
    std::cout << "Vuelta\n";
}
```

<details>
<summary>🔓 Ver solución</summary>

Se imprime 4 veces, con `i` tomando los valores 3, 5, 7 y 9. En cuanto `i` llega a 11, `i < 10` es falsa y el ciclo termina, sin que 11 llegue a imprimirse. El incremento no tiene que ser `i++`: puede ser cualquier expresión que cambie la variable de control, y aquí avanza de dos en dos en lugar de uno en uno.

</details>

#### Avanzado

📂 `src/main.cpp`

Con `mostrar_reproducciones_semana` ya implementada, agrega dentro de `main()`, antes del ciclo del menú, la declaración de los dos arreglos:

```cpp
int reproducciones_semana[7] = {12000, 8500, 15300, 9800, 22000, 31000, 18500};
std::string nombres_dias[7] = {
    "Lunes", "Martes", "Miercoles", "Jueves", "Viernes", "Sabado", "Domingo"
};
```

Y descomenta el bloque de `case 6:`:

```cpp
case 6:
    mostrar_reproducciones_semana(reproducciones_semana, nombres_dias);
    break;
```

Compila con `g++ src/main.cpp src/reproductor.cpp -o sonora` y ejecuta con `./sonora`.

La salida esperada al elegir la opción 6 es la misma de esta sección.

<details>
<summary>🔓 Ver solución</summary>

```cpp
int main() {
    std::vector<Cancion> catalogo = {
        {"La Gota Fria", "Carlos Vives", "Vallenato", 245, 1250000, 4.6},
        {"La Rebelion", "Joe Arroyo", "Salsa", 260, 82000, 4.2},
        {"Rio", "Bomba Estereo", "Electronica", 210, 15300, 3.8},
    };

    int reproducciones_semana[7] = {12000, 8500, 15300, 9800, 22000, 31000, 18500};
    std::string nombres_dias[7] = {
        "Lunes", "Martes", "Miercoles", "Jueves", "Viernes", "Sabado", "Domingo"
    };

    // ... el resto de main() sigue igual, con case 6 descomentado:
    // case 6:
    //     mostrar_reproducciones_semana(reproducciones_semana, nombres_dias);
    //     break;
}
```

</details>

#### Reto

Escribe una función `mostrar_reproducciones_semana_invertida` que recorra los mismos arreglos de atrás hacia adelante, de Domingo a Lunes, en un solo ciclo `for`.

**🧭 Pistas**

- La inicialización puede empezar en `dia = 6` en lugar de `dia = 0`.
- La condición para seguir recorriendo hacia atrás es `dia >= 0`, no `dia < 7`.
- El incremento tiene que restar en lugar de sumar: `dia--` en vez de `dia++`.

---

## 3. Transformación

Sonora quiere mostrar, además del número absoluto de reproducciones, qué porcentaje del total semanal representó cada día. Ese porcentaje no reemplaza el dato original: es un dato nuevo, calculado a partir de él, del mismo tamaño que el arreglo de entrada. Esta operación, recorrer un arreglo y producir otro con un valor derivado en cada posición, se llama **transformación**.

```cpp
// En reproductor.h:
/**
 * Calcula que porcentaje del total semanal representa cada dia.
 *
 * @param reproducciones_semana Arreglo con las reproducciones de cada dia.
 * @param porcentajes Arreglo de salida donde se guarda el porcentaje de cada dia.
 */
void calcular_porcentaje_diario(int reproducciones_semana[7], double porcentajes[7]);

// En reproductor.cpp:
void calcular_porcentaje_diario(int reproducciones_semana[7], double porcentajes[7]) {
    int total = sumar_reproducciones_semana(reproducciones_semana);
    for (int dia = 0; dia < 7; dia++) {
        porcentajes[dia] = (reproducciones_semana[dia] * 100.0) / total;
    }
}
```

`calcular_porcentaje_diario` usa `sumar_reproducciones_semana`, la función de acumulación que vas a construir en la sección siguiente. Por ahora, dala por hecha: retorna la suma de las siete posiciones del arreglo.

`porcentajes` llega vacío, sin valores útiles todavía, y la función lo llena posición por posición. Es un **arreglo de salida**: quien llama a la función lo declara vacío y la función se encarga de darle contenido, en lugar de retornar un valor nuevo con `return`. Ya viste este mismo patrón con el paso por referencia, solo que ahí modificabas un único `int` o un único `Cancion`; aquí modificas las siete posiciones de un arreglo completo.

Con `reproducciones_semana = {12000, 8500, 15300, 9800, 22000, 31000, 18500}` (total 117100), la salida es:

```cpp
double porcentajes[7];
calcular_porcentaje_diario(reproducciones_semana, porcentajes);
for (int dia = 0; dia < 7; dia++) {
    std::cout << nombres_dias[dia] << ": " << porcentajes[dia] << "%\n";
}
```

```
Lunes: 10.2477%
Martes: 7.25875%
Miercoles: 13.0658%
Jueves: 8.36892%
Viernes: 18.7874%
Sabado: 26.4731%
Domingo: 15.7985%
```

`reproducciones_semana[dia] * 100.0` multiplica primero por `100.0`, no por `100`. Si multiplicaras por el entero `100`, la operación completa seguiría siendo entre `int` hasta la división, y perderías la parte decimal del porcentaje antes de que `/ total` tuviera oportunidad de calcularla. El `.0` en `100.0` es suficiente para que C++ trate toda la expresión como `double` desde el principio.

⚠️ **Error frecuente:** declarar `porcentajes` con `int` en lugar de `double`. Un porcentaje casi nunca es un número entero exacto, y un arreglo `int` trunca cada valor a la baja: `10.2477` se guardaría como `10`, perdiendo toda la parte decimal sin ningún aviso del compilador.

### Ejercicios

🔧 **Consejo de entorno:** compila con `g++ src/main.cpp src/reproductor.cpp -o sonora` y ejecuta con `./sonora`.

#### Inducción al error

Un estudiante escribe `calcular_porcentaje_diario` así, con `porcentajes` declarado como `int` dentro de la función que la prueba:

```cpp
int porcentajes[7];
calcular_porcentaje_diario_int(reproducciones_semana, porcentajes);  // version con int
for (int dia = 0; dia < 7; dia++) {
    std::cout << porcentajes[dia] << "%\n";
}
```

Con la misma lógica de la sección, pero guardando cada resultado como `int` en lugar de `double`, la salida sería:

```
10%
7%
13%
8%
18%
26%
15%
```

El programa compila y corre sin ningún error. El problema es que cada porcentaje pierde su parte decimal en el momento de guardarse en el arreglo `int`, no en el cálculo. Declarar el arreglo de salida con el tipo correcto, `double` en este caso, es tan importante como la fórmula misma.

#### 🧩 Antes de programar

Estas líneas, en el orden correcto, forman una función que transforma un arreglo de segundos a un arreglo de minutos. Están desordenadas: escribe el orden correcto (por ejemplo, `C, A, D, B`) sin necesidad de compilar nada.

```
A. minutos[i] = segundos[i] / 60.0;
B. }
C. void transformar_a_minutos(int segundos[7], double minutos[7]) {
D. for (int i = 0; i < 7; i++) {
```

<details>
<summary>🔓 Ver solución</summary>

`C, D, A, B`. Primero la firma de la función (`C`), después el `for` que abre el ciclo (`D`), después la línea que hace la transformación en sí (`A`), y por último la llave que cierra tanto el `for` como la función (`B`).

</details>

#### Básico

📂 `src/reproductor.h` y `src/reproductor.cpp`

Declara e implementa `calcular_porcentaje_diario` tal como se ve en esta sección. Como todavía no implementaste `sumar_reproducciones_semana` (la ves en la sección 4), usa temporalmente esta versión con el total escrito directamente, y reemplázala cuando llegues a esa sección:

```cpp
void calcular_porcentaje_diario(int reproducciones_semana[7], double porcentajes[7]) {
    int total = 117100;  // temporal, hasta la seccion 4
    for (int dia = 0; dia < 7; dia++) {
        porcentajes[dia] = (reproducciones_semana[dia] * 100.0) / total;
    }
}
```

Prueba con el arreglo de esta sección y compara tu salida contra la de arriba. Compila con `g++ src/main.cpp src/reproductor.cpp -o sonora` y ejecuta con `./sonora`.

<details>
<summary>🔓 Ver solución</summary>

```cpp
// En reproductor.h:
/**
 * Calcula que porcentaje del total semanal representa cada dia.
 *
 * @param reproducciones_semana Arreglo con las reproducciones de cada dia.
 * @param porcentajes Arreglo de salida donde se guarda el porcentaje de cada dia.
 */
void calcular_porcentaje_diario(int reproducciones_semana[7], double porcentajes[7]);

// En reproductor.cpp (version temporal, hasta la seccion 4):
void calcular_porcentaje_diario(int reproducciones_semana[7], double porcentajes[7]) {
    int total = 117100;
    for (int dia = 0; dia < 7; dia++) {
        porcentajes[dia] = (reproducciones_semana[dia] * 100.0) / total;
    }
}
```

</details>

#### Intermedio

Escribe una función `transformar_a_minutos(int reproducciones_semana[7], double minutos[7])` de práctica, sin relación con el catálogo, que convierta un arreglo cualquiera de segundos a minutos, dividiendo cada posición entre 60.0.

<details>
<summary>🔓 Ver solución</summary>

```cpp
void transformar_a_minutos(int segundos[7], double minutos[7]) {
    for (int i = 0; i < 7; i++) {
        minutos[i] = segundos[i] / 60.0;
    }
}
```

</details>

#### Avanzado

📂 `src/main.cpp`

Con `calcular_porcentaje_diario` ya implementada (con el total temporal o el real, según en qué sección vayas), descomenta el bloque de `case 7:`:

```cpp
case 7: {
    double porcentajes[7];
    calcular_porcentaje_diario(reproducciones_semana, porcentajes);
    for (int dia = 0; dia < 7; dia++) {
        std::cout << nombres_dias[dia] << ": " << porcentajes[dia] << "%\n";
    }
    break;
}
```

Compila con `g++ src/main.cpp src/reproductor.cpp -o sonora` y ejecuta con `./sonora`.

La salida esperada al elegir la opción 7 es la misma de esta sección.

<details>
<summary>🔓 Ver solución</summary>

El bloque ya está completo arriba. Las llaves `{ }` adicionales dentro de `case 7:` son necesarias porque el bloque declara una variable (`porcentajes`) dentro de un `case` que no es el último del `switch`, el mismo motivo que ya viste con otro `case` anterior.

</details>

#### Reto

Agrega `transformar_a_categoria(int reproducciones_semana[7], std::string categorias[7])`, que clasifique cada día como `"Alto"` si superó las 20000 reproducciones, o `"Normal"` en caso contrario, reutilizando la lógica de comparación que ya conoces de `clasificar_por_reproducciones`.

**🧭 Pistas**

- Recorre el arreglo con el mismo `for (int dia = 0; dia < 7; dia++)` de esta sección.
- Dentro del ciclo, un `if` / `else` simple decide qué texto guardar en `categorias[dia]`.
- Prueba con el arreglo `{12000, 8500, 15300, 9800, 22000, 31000, 18500}` y confirma que solo Viernes y Sabado queden como `"Alto"`.

---

## 4. Acumulación

Transformar produce un arreglo del mismo tamaño que el original. **Acumular** produce un solo valor, resultado de combinar todas las posiciones del arreglo, como una suma o un promedio.

```cpp
// En reproductor.h:
/**
 * Suma las reproducciones de los 7 dias de la semana.
 *
 * @param reproducciones_semana Arreglo con las reproducciones de cada dia.
 * @return Total de reproducciones de la semana.
 */
int sumar_reproducciones_semana(int reproducciones_semana[7]);

// En reproductor.cpp:
int sumar_reproducciones_semana(int reproducciones_semana[7]) {
    int total = 0;
    for (int dia = 0; dia < 7; dia++) {
        total = total + reproducciones_semana[dia];
    }
    return total;
}
```

`total` empieza en `0`, antes de que el ciclo revise una sola posición del arreglo. Esa inicialización no es un detalle menor: si `total` empezara sin inicializar, la suma final incluiría el valor indeterminado que ya viste en la sección 1, un número que puede ser cualquier cosa. Cada vuelta suma una posición más a `total`, y al terminar las siete vueltas, `total` acumuló las siete.

Con `reproducciones_semana = {12000, 8500, 15300, 9800, 22000, 31000, 18500}`:

```cpp
std::cout << "Total: " << sumar_reproducciones_semana(reproducciones_semana) << "\n";
```

```
Total: 117100
```

El promedio reutiliza esta misma función, en lugar de recorrer el arreglo por segunda vez:

```cpp
// En reproductor.h:
/**
 * Calcula el promedio diario de reproducciones de la semana.
 *
 * @param reproducciones_semana Arreglo con las reproducciones de cada dia.
 * @return Promedio de reproducciones por dia.
 */
double promedio_reproducciones_semana(int reproducciones_semana[7]);

// En reproductor.cpp:
double promedio_reproducciones_semana(int reproducciones_semana[7]) {
    return sumar_reproducciones_semana(reproducciones_semana) / 7.0;
}
```

```cpp
std::cout << "Promedio: " << promedio_reproducciones_semana(reproducciones_semana) << "\n";
```

```
Promedio: 16728.6
```

`/ 7.0`, no `/ 7`. Dividir un `int` entre otro `int` en C++ trunca el resultado, descarta la parte decimal. `sumar_reproducciones_semana(...)` retorna un `int`, y dividirlo entre el `double` `7.0` obliga a C++ a convertir esa suma a `double` antes de dividir, conservando los decimales del resultado.

💡 **Por qué importa:** contar cuántos elementos tiene el arreglo (el `7` de esta sesión) es el mismo patrón que vas a usar para acumular cualquier dato de Sonora: la duración total del catálogo, el promedio de calificaciones, el total de reproducciones de un género. Cambia el dato que se suma en cada vuelta, no la estructura del ciclo.

### Ejercicios

🔧 **Consejo de entorno:** compila con `g++ src/main.cpp src/reproductor.cpp -o sonora` y ejecuta con `./sonora`.

#### Inducción al error

Agrega esto arriba de `iniciar_sonora()`, actívalo en lugar de ella, y compila con `g++ src/main.cpp src/reproductor.cpp -o sonora`:

```cpp
int sumar_con_error(int arreglo[7]) {
    int total;  // sin inicializar
    for (int i = 0; i < 7; i++) {
        total = total + arreglo[i];
    }
    return total;
}

void prueba_suma_error() {
    int arreglo[7] = {1, 2, 3, 4, 5, 6, 7};
    std::cout << sumar_con_error(arreglo) << "\n";
}
```

El compilador no marca ningún error, y en algunos sistemas el programa incluso imprime `28`, el resultado correcto, por pura coincidencia del valor que había en esa posición de memoria antes de declarar `total`. Ese resultado no está garantizado: en otra ejecución, en otro sistema, o con otro compilador, `total` puede arrancar con cualquier otro número y la suma sale mal sin ningún aviso. `int total;` sin `= 0` deja la variable con el valor que hubiera en esa dirección de memoria justo antes, ni siquiera necesariamente `0`. Toda variable acumuladora se inicializa en el valor neutro de su operación: `0` para sumar, `1` para multiplicar.

#### 🧩 Antes de programar

Completa la tabla de trazo de `sumar_reproducciones_semana` con `reproducciones_semana = {10, 20, 30}` (usa un arreglo de 3 posiciones para esta tabla, no de 7, así es más corto de trazar a mano).

```cpp
int total = 0;
for (int dia = 0; dia < 3; dia++) {
    total = total + reproducciones_semana[dia];
}
```

| Vuelta | dia | reproducciones_semana[dia] | total (después de sumar) |
|---|---|---|---|
| 1 | | | |
| 2 | | | |
| 3 | | | |

<details>
<summary>🔓 Ver solución</summary>

| Vuelta | dia | reproducciones_semana[dia] | total (después de sumar) |
|---|---|---|---|
| 1 | 0 | 10 | 10 |
| 2 | 1 | 20 | 30 |
| 3 | 2 | 30 | 60 |

</details>

#### Básico

📂 `src/reproductor.h` y `src/reproductor.cpp`

Declara e implementa `sumar_reproducciones_semana` y `promedio_reproducciones_semana` tal como se ven en esta sección. Reemplaza también el total temporal (`117100`) de `calcular_porcentaje_diario` por una llamada real a `sumar_reproducciones_semana`.

Sigue el patrón de la sección 0:

```cpp
void prueba_acumulacion() {
    int reproducciones_semana[7] = {12000, 8500, 15300, 9800, 22000, 31000, 18500};
    std::cout << "Total: " << sumar_reproducciones_semana(reproducciones_semana) << "\n";
    std::cout << "Promedio: " << promedio_reproducciones_semana(reproducciones_semana) << "\n";
}
```

Compila con `g++ src/main.cpp src/reproductor.cpp -o sonora` y ejecuta con `./sonora`.

La salida esperada es la misma de esta sección.

<details>
<summary>🔓 Ver solución</summary>

```cpp
// En reproductor.h:
/**
 * Suma las reproducciones de los 7 dias de la semana.
 *
 * @param reproducciones_semana Arreglo con las reproducciones de cada dia.
 * @return Total de reproducciones de la semana.
 */
int sumar_reproducciones_semana(int reproducciones_semana[7]);

/**
 * Calcula el promedio diario de reproducciones de la semana.
 *
 * @param reproducciones_semana Arreglo con las reproducciones de cada dia.
 * @return Promedio de reproducciones por dia.
 */
double promedio_reproducciones_semana(int reproducciones_semana[7]);

// En reproductor.cpp:
int sumar_reproducciones_semana(int reproducciones_semana[7]) {
    int total = 0;
    for (int dia = 0; dia < 7; dia++) {
        total = total + reproducciones_semana[dia];
    }
    return total;
}

double promedio_reproducciones_semana(int reproducciones_semana[7]) {
    return sumar_reproducciones_semana(reproducciones_semana) / 7.0;
}

void calcular_porcentaje_diario(int reproducciones_semana[7], double porcentajes[7]) {
    int total = sumar_reproducciones_semana(reproducciones_semana);
    for (int dia = 0; dia < 7; dia++) {
        porcentajes[dia] = (reproducciones_semana[dia] * 100.0) / total;
    }
}
```

</details>

#### Intermedio

Escribe `maximo_reproducciones_semana(int reproducciones_semana[7])`, que retorne el valor más alto del arreglo, sin usar ninguna función de la biblioteca estándar.

<details>
<summary>🔓 Ver solución</summary>

```cpp
int maximo_reproducciones_semana(int reproducciones_semana[7]) {
    int maximo = reproducciones_semana[0];
    for (int dia = 1; dia < 7; dia++) {
        if (reproducciones_semana[dia] > maximo) {
            maximo = reproducciones_semana[dia];
        }
    }
    return maximo;
}
```

`maximo` arranca en la primera posición, no en `0`, porque si todas las reproducciones fueran negativas (algo que no debería pasar en este dominio, pero que la función no puede descartar sin revisarlo) arrancar en `0` daría un máximo incorrecto. El ciclo empieza en `dia = 1`, no en `0`, porque la posición `0` ya se usó para inicializar `maximo`.

</details>

#### Avanzado

📂 `src/main.cpp`

Con las dos funciones ya implementadas, descomenta el bloque de `case 8:`:

```cpp
case 8:
    std::cout << "Total: " << sumar_reproducciones_semana(reproducciones_semana) << "\n";
    std::cout << "Promedio: " << promedio_reproducciones_semana(reproducciones_semana) << "\n";
    break;
```

Compila con `g++ src/main.cpp src/reproductor.cpp -o sonora` y ejecuta con `./sonora`.

La salida esperada al elegir la opción 8 es la misma de esta sección.

<details>
<summary>🔓 Ver solución</summary>

El bloque ya está completo arriba.

</details>

#### Reto

Escribe `promedio_calificaciones(std::vector<Cancion>& catalogo)`, que retorne el promedio de calificación de todas las canciones del catálogo. A diferencia de las funciones de esta sección, el parámetro es un `std::vector<Cancion>&`, no un arreglo, así que puedes volver a usar `for (Cancion& cancion : catalogo)`.

**🧭 Pistas**

- Necesitas acumular dos cosas en el mismo ciclo: la suma de calificaciones y cuántas canciones recorriste, para no depender de un tamaño fijo como `7`.
- `catalogo.size()` retorna cuántos elementos tiene el vector.
- Divide la suma acumulada entre `catalogo.size()`, con el mismo cuidado de convertir a `double` que viste en esta sección.

---

## 5. Conteo

Contar es una acumulación con una regla adicional: en lugar de sumar el valor de cada posición, sumas 1 solo cuando esa posición cumple una condición. Sonora quiere saber cuántos días de la semana superaron un umbral de reproducciones, sin necesitar todavía cuáles fueron.

```cpp
// En reproductor.h:
/**
 * Cuenta cuantos dias superaron un umbral de reproducciones.
 *
 * @param reproducciones_semana Arreglo con las reproducciones de cada dia.
 * @param umbral Numero minimo de reproducciones para considerarse un dia pico.
 * @return Cantidad de dias que superaron el umbral.
 */
int contar_dias_pico(int reproducciones_semana[7], int umbral);

// En reproductor.cpp:
int contar_dias_pico(int reproducciones_semana[7], int umbral) {
    int contador = 0;
    for (int dia = 0; dia < 7; dia++) {
        if (reproducciones_semana[dia] > umbral) {
            contador = contador + 1;
        }
    }
    return contador;
}
```

`contador` arranca en `0`, igual que `total` en la sección anterior, y por la misma razón: es el valor neutro de la operación que acumula. La diferencia con `sumar_reproducciones_semana` es el `if` dentro del ciclo: en vez de sumar `reproducciones_semana[dia]` en cada vuelta, suma `1` únicamente cuando esa posición pasa la condición.

Con `reproducciones_semana = {12000, 8500, 15300, 9800, 22000, 31000, 18500}` y un umbral de `15000`:

```cpp
std::cout << "Dias pico: " << contar_dias_pico(reproducciones_semana, 15000) << "\n";
```

```
Dias pico: 4
```

Cuatro días superan 15000: Miércoles (15300), Viernes (22000), Sábado (31000) y Domingo (18500).

### Ejercicios

🔧 **Consejo de entorno:** compila con `g++ src/main.cpp src/reproductor.cpp -o sonora` y ejecuta con `./sonora`.

#### Inducción al error

Un estudiante escribe la condición al revés, comparando el umbral contra el contador en vez de contra cada posición del arreglo:

```cpp
int contar_con_error(int arreglo[7], int umbral) {
    int contador = 0;
    for (int i = 0; i < 7; i++) {
        if (umbral > contador) {  // deberia ser arreglo[i] > umbral
            contador = contador + 1;
        }
    }
    return contador;
}
```

Con `umbral = 15000`, el resultado siempre es `7`, sin importar los valores del arreglo, porque `contador` nunca llega ni cerca de `15000` en ninguna de las siete vueltas, y la condición resulta verdadera todas las veces. El programa compila sin errores y produce un número que parece razonable a primera vista, un `7` dentro del rango esperado de 0 a 7, pero no tiene relación real con cuántos días superaron el umbral. Revisar qué variable va a cada lado de una comparación es tan importante como la comparación misma.

#### 🧩 Antes de programar

Antes de escribir nada, predice qué retorna `contar_dias_pico(reproducciones_semana, 20000)`, con `reproducciones_semana = {12000, 8500, 15300, 9800, 22000, 31000, 18500}` (la versión correcta de la función, no la de "Inducción al error"). Después, cuando ya tengas `contar_dias_pico` implementada en el ejercicio "Básico", vuelve aquí y compruébalo.

<details>
<summary>🔓 Ver solución</summary>

`2`. Solo Viernes (22000) y Sabado (31000) superan 20000; los demás días (12000, 8500, 15300, 9800, 18500) quedan por debajo.

</details>

#### Básico

📂 `src/reproductor.h` y `src/reproductor.cpp`

Declara e implementa `contar_dias_pico` tal como se ve en esta sección.

Sigue el patrón de la sección 0:

```cpp
void prueba_conteo() {
    int reproducciones_semana[7] = {12000, 8500, 15300, 9800, 22000, 31000, 18500};
    std::cout << "Dias pico: " << contar_dias_pico(reproducciones_semana, 15000) << "\n";
}
```

Compila con `g++ src/main.cpp src/reproductor.cpp -o sonora` y ejecuta con `./sonora`.

La salida esperada es:

```
Dias pico: 4
```

<details>
<summary>🔓 Ver solución</summary>

```cpp
// En reproductor.h:
/**
 * Cuenta cuantos dias superaron un umbral de reproducciones.
 *
 * @param reproducciones_semana Arreglo con las reproducciones de cada dia.
 * @param umbral Numero minimo de reproducciones para considerarse un dia pico.
 * @return Cantidad de dias que superaron el umbral.
 */
int contar_dias_pico(int reproducciones_semana[7], int umbral);

// En reproductor.cpp:
int contar_dias_pico(int reproducciones_semana[7], int umbral) {
    int contador = 0;
    for (int dia = 0; dia < 7; dia++) {
        if (reproducciones_semana[dia] > umbral) {
            contador = contador + 1;
        }
    }
    return contador;
}
```

</details>

#### Intermedio

Sin compilar todavía, decide qué retorna `contar_dias_pico(reproducciones_semana, 31000)` con el arreglo de esta sección.

<details>
<summary>🔓 Ver solución</summary>

Retorna `0`. La condición es `reproducciones_semana[dia] > umbral`, estrictamente mayor, y ningún día supera 31000: Sabado llega exactamente a 31000, no lo supera. Si la intención fuera incluir el día que iguala el umbral, la condición necesitaría `>=` en lugar de `>`.

</details>

#### Avanzado

📂 `src/main.cpp`

Con `contar_dias_pico` ya implementada, descomenta el bloque de `case 9:`:

```cpp
case 9: {
    std::cout << "Ingresa el umbral de reproducciones: ";
    int umbral = 0;
    std::cin >> umbral;
    std::cout << "Dias pico: " << contar_dias_pico(reproducciones_semana, umbral) << "\n";
    break;
}
```

Compila con `g++ src/main.cpp src/reproductor.cpp -o sonora` y ejecuta con `./sonora`.

La salida esperada al elegir la opción 9 e ingresar `15000` es:

```
Ingresa el umbral de reproducciones: Dias pico: 4
```

<details>
<summary>🔓 Ver solución</summary>

El bloque ya está completo arriba.

</details>

#### Reto

Escribe `contar_canciones_por_genero(std::vector<Cancion>& catalogo, std::string genero)`, que cuente cuántas canciones del catálogo pertenecen a un género dado, aplicando el mismo patrón de conteo sobre un `std::vector` en lugar de un arreglo.

**🧭 Pistas**

- Recorre el catálogo con `for (Cancion& cancion : catalogo)`.
- La condición del `if` compara `cancion.genero == genero`, no `>`.
- Prueba con `"Vallenato"` sobre el catálogo de ejemplo y confirma que el resultado sea `1`.

---

## 6. Filtrado

Contar responde cuántos días superaron el umbral. **Filtrar** responde cuáles, construyendo una lista aparte solo con los elementos que cumplen la condición.

Un arreglo estático no es la estructura correcta para este resultado: no sabes de antemano cuántos días van a superar el umbral, puede ser cualquier número entre 0 y 7, y un arreglo necesita ese tamaño fijado desde que se declara. Compruébalo agregando esto arriba de `iniciar_sonora()`, y activándolo en su lugar:

```cpp
void prueba_arreglo_fijo() {
    int reproducciones_semana[7] = {12000, 8500, 15300, 9800, 22000, 31000, 18500};
    std::string nombres_dias[7] = {
        "Lunes", "Martes", "Miercoles", "Jueves", "Viernes", "Sabado", "Domingo"
    };
    int umbral = 15000;

    std::string dias_pico[7];  // mismo tamano que el arreglo original
    int cantidad_encontrados = 0;
    for (int dia = 0; dia < 7; dia++) {
        if (reproducciones_semana[dia] > umbral) {
            dias_pico[cantidad_encontrados] = nombres_dias[dia];
            cantidad_encontrados = cantidad_encontrados + 1;
        }
    }

    for (int i = 0; i < 7; i++) {
        std::cout << i << ": '" << dias_pico[i] << "'\n";
    }
}
```

Con el arreglo y el umbral de esta sesión, la salida es:

```
0: 'Miercoles'
1: 'Viernes'
2: 'Sabado'
3: 'Domingo'
4: ''
5: ''
6: ''
```

Las cuatro primeras posiciones traen el resultado correcto, y las tres restantes quedan con `std::string` vacíos, porque el arreglo se declaró con tamaño `7` sin importar cuántos elementos iban a usarse en realidad. Nada en el programa indica dónde termina el resultado útil y dónde empieza el relleno vacío, así que quien reciba `dias_pico` no tiene forma de saber cuántas posiciones son válidas sin que se lo digas por separado.

Un `std::vector` resuelve exactamente este problema, porque su tamaño crece según lo que agregues, sin que tengas que declararlo de antemano:

```cpp
// En reproductor.h:
/**
 * Filtra los nombres de los dias que superaron un umbral de reproducciones.
 *
 * @param reproducciones_semana Arreglo con las reproducciones de cada dia.
 * @param nombres_dias Arreglo con el nombre de cada dia (mismo orden que reproducciones_semana).
 * @param umbral Numero minimo de reproducciones para considerarse un dia pico.
 * @return Vector con los nombres de los dias que superaron el umbral.
 */
std::vector<std::string> filtrar_dias_pico(
    int reproducciones_semana[7], std::string nombres_dias[7], int umbral);

// En reproductor.cpp:
std::vector<std::string> filtrar_dias_pico(
    int reproducciones_semana[7], std::string nombres_dias[7], int umbral) {
    std::vector<std::string> dias_pico;
    for (int dia = 0; dia < 7; dia++) {
        if (reproducciones_semana[dia] > umbral) {
            dias_pico.push_back(nombres_dias[dia]);
        }
    }
    return dias_pico;
}
```

`dias_pico` se declara vacío, sin ningún tamaño entre paréntesis ni corchetes, y `push_back` agrega un elemento al final cada vez que se cumple la condición. Al terminar el ciclo, `dias_pico` tiene exactamente los elementos que pasaron el filtro, sin ninguna posición sobrante que limpiar.

Con `reproducciones_semana = {12000, 8500, 15300, 9800, 22000, 31000, 18500}` y umbral `15000`:

```cpp
std::vector<std::string> dias_pico = filtrar_dias_pico(reproducciones_semana, nombres_dias, 15000);
for (std::string& dia : dias_pico) {
    std::cout << dia << "\n";
}
```

```
Miercoles
Viernes
Sabado
Domingo
```

Fíjate en que el resultado del ciclo `for` cambia según la estructura que recorres. `reproducciones_semana` (arreglo, tamaño fijo `7`) usa el `for` clásico con índice de la sección 2. `dias_pico` (`std::vector`, tamaño variable) puede recorrerse con el `for` de rango, porque un vector siempre conserva su tamaño disponible, a diferencia de un arreglo que llegó como parámetro.

✅ **Buena práctica:** cuando el resultado de un ciclo es una cantidad de elementos que no puedes anticipar antes de correrlo, usa `std::vector` y `push_back`, no un arreglo del mismo tamaño que la entrada. Un arreglo estático encaja cuando el número de elementos es un dato fijo del dominio, como los siete días de la semana; un vector encaja cuando ese número depende de una condición que solo se conoce al ejecutar el programa.

### Ejercicios

🔧 **Consejo de entorno:** compila con `g++ src/main.cpp src/reproductor.cpp -o sonora` y ejecuta con `./sonora`.

#### 🧩 Antes de programar

Con `reproducciones_semana = {12000, 8500, 15300, 9800, 22000, 31000, 18500}` y `umbral = 10000`, marca con Sí o No si cada día pasaría el filtro (`reproducciones_semana[dia] > umbral`), sin escribir código todavía. Es la misma condición que evalúa un `if` dentro del ciclo, una vez por día.

| Día | Reproducciones | ¿Pasa el filtro? |
|---|---|---|
| Lunes | 12000 | |
| Martes | 8500 | |
| Miercoles | 15300 | |
| Jueves | 9800 | |
| Viernes | 22000 | |
| Sabado | 31000 | |
| Domingo | 18500 | |

<details>
<summary>🔓 Ver solución</summary>

Sí, No, Sí, No, Sí, Sí, Sí. Solo Martes (8500) y Jueves (9800) quedan por debajo o iguales a 10000; los otros cinco días superan el umbral.

</details>

#### Inducción al error

Reproduce, siguiendo el patrón de la sección 0, el intento con arreglo de tamaño fijo que abrió esta sección, y ejecútalo con el umbral `15000`. Confirma que las tres últimas posiciones queden con `std::string` vacíos, y decide por qué el problema no es la condición del `if`, sino el tipo de estructura elegida para guardar un resultado de tamaño desconocido.

#### Básico

📂 `src/reproductor.h` y `src/reproductor.cpp`

Declara e implementa `filtrar_dias_pico` tal como se ve en esta sección.

Sigue el patrón de la sección 0:

```cpp
void prueba_filtrado() {
    int reproducciones_semana[7] = {12000, 8500, 15300, 9800, 22000, 31000, 18500};
    std::string nombres_dias[7] = {
        "Lunes", "Martes", "Miercoles", "Jueves", "Viernes", "Sabado", "Domingo"
    };
    std::vector<std::string> dias_pico = filtrar_dias_pico(reproducciones_semana, nombres_dias, 15000);
    for (std::string& dia : dias_pico) {
        std::cout << dia << "\n";
    }
}
```

Compila con `g++ src/main.cpp src/reproductor.cpp -o sonora` y ejecuta con `./sonora`.

La salida esperada es la misma de esta sección.

<details>
<summary>🔓 Ver solución</summary>

```cpp
// En reproductor.h:
/**
 * Filtra los nombres de los dias que superaron un umbral de reproducciones.
 *
 * @param reproducciones_semana Arreglo con las reproducciones de cada dia.
 * @param nombres_dias Arreglo con el nombre de cada dia (mismo orden que reproducciones_semana).
 * @param umbral Numero minimo de reproducciones para considerarse un dia pico.
 * @return Vector con los nombres de los dias que superaron el umbral.
 */
std::vector<std::string> filtrar_dias_pico(
    int reproducciones_semana[7], std::string nombres_dias[7], int umbral);

// En reproductor.cpp:
std::vector<std::string> filtrar_dias_pico(
    int reproducciones_semana[7], std::string nombres_dias[7], int umbral) {
    std::vector<std::string> dias_pico;
    for (int dia = 0; dia < 7; dia++) {
        if (reproducciones_semana[dia] > umbral) {
            dias_pico.push_back(nombres_dias[dia]);
        }
    }
    return dias_pico;
}
```

</details>

#### Intermedio

Escribe `filtrar_reproducciones_bajas(int reproducciones_semana[7], int umbral)`, que retorne un `std::vector<int>` con las reproducciones (no los nombres) de los días que quedaron por debajo del umbral, en lugar de por encima.

<details>
<summary>🔓 Ver solución</summary>

```cpp
std::vector<int> filtrar_reproducciones_bajas(int reproducciones_semana[7], int umbral) {
    std::vector<int> dias_bajos;
    for (int dia = 0; dia < 7; dia++) {
        if (reproducciones_semana[dia] < umbral) {
            dias_bajos.push_back(reproducciones_semana[dia]);
        }
    }
    return dias_bajos;
}
```

</details>

#### Avanzado

📂 `src/main.cpp`

Con `filtrar_dias_pico` ya implementada, descomenta el bloque de `case 10:`:

```cpp
case 10: {
    std::cout << "Ingresa el umbral de reproducciones: ";
    int umbral = 0;
    std::cin >> umbral;
    std::vector<std::string> dias_pico = filtrar_dias_pico(reproducciones_semana, nombres_dias, umbral);
    for (std::string& dia : dias_pico) {
        std::cout << dia << "\n";
    }
    break;
}
```

Compila con `g++ src/main.cpp src/reproductor.cpp -o sonora` y ejecuta con `./sonora`.

La salida esperada al elegir la opción 10 e ingresar `15000` es:

```
Ingresa el umbral de reproducciones: Miercoles
Viernes
Sabado
Domingo
```

<details>
<summary>🔓 Ver solución</summary>

El bloque ya está completo arriba.

</details>

#### Reto

Escribe `filtrar_por_genero(std::vector<Cancion>& catalogo, std::string genero)`, que retorne un `std::vector<Cancion>` solo con las canciones del género recibido, combinando el patrón de filtrado de esta sección con un `std::vector<Cancion>&` en lugar de un arreglo.

**🧭 Pistas**

- El tipo de retorno es `std::vector<Cancion>`, no `std::vector<std::string>`: cada elemento filtrado es la canción completa, no solo un dato suyo.
- `push_back(cancion)` agrega la canción completa al vector de resultado.
- Prueba con `"Vallenato"` sobre el catálogo de ejemplo y confirma que el resultado tenga exactamente una canción, `"La Gota Fria"`.

---

## 7. Ciclos indefinidos: while

Todos los ciclos de esta sesión repiten el cuerpo un número de veces que queda fijo antes de empezar: siete días, ni uno más. El ciclo del menú de Sonora, en cambio, no sabe cuántas vueltas va a dar: depende de cuántas veces el usuario elija seguir antes de salir. Ese es un **ciclo indefinido**, y `while` es la estructura que lo expresa:

```cpp
bool ejecutando = true;
while (ejecutando) {
    // ... el menu completo
}
```

Ya usaste `while` para el ciclo del menú, sin haberlo estudiado todavía como estructura aparte. `while (condicion)` revisa esa condición antes de cada vuelta, igual que la condición de un `for`, pero sin ninguna inicialización ni incremento fijados en la misma línea. Cuántas vueltas dé un `while` depende por completo de lo que pase dentro del cuerpo, no de un contador que avanza de forma predecible.

Sonora necesita pedirle al usuario un umbral de reproducciones antes de contar o filtrar los días pico, y ese umbral solo tiene sentido si es un número positivo. Si el usuario escribe `0` o un número negativo, hay que volver a pedirlo, sin saber de antemano cuántas veces:

```cpp
int umbral = -1;
while (umbral <= 0) {
    std::cout << "Ingresa un umbral positivo de reproducciones: ";
    std::cin >> umbral;
    if (umbral <= 0) {
        std::cout << "El umbral debe ser mayor que cero.\n";
    }
}
std::cout << "Umbral valido: " << umbral << "\n";
```

Con las entradas `-5`, `0` y `15000`, en ese orden, la salida es:

```
Ingresa un umbral positivo de reproducciones: El umbral debe ser mayor que cero.
Ingresa un umbral positivo de reproducciones: El umbral debe ser mayor que cero.
Ingresa un umbral positivo de reproducciones: Umbral valido: 15000
```

`umbral` arranca en `-1`, un valor que garantiza que la condición `umbral <= 0` sea verdadera antes de la primera vuelta, para que el ciclo entre al menos una vez y le pregunte al usuario. Esa técnica, inicializar la variable de control en un valor que fuerce la primera entrada al ciclo, es habitual cuando el dato real todavía no existe y tiene que pedirse dentro del propio ciclo.

Esta es la misma idea que quedó pendiente antes, cuando `std::cin >> opcion` fallaba si el usuario escribía texto en lugar de un número. Ese fragmento usaba `std::cin.fail()`, `std::cin.clear()` y `std::cin.ignore(...)` para descartar la entrada inválida y no romper las lecturas siguientes:

```cpp
int opcion = 0;
std::cin >> opcion;

if (std::cin.fail()) {
    std::cin.clear();
    std::cin.ignore(1000, '\n');
    std::cout << "Opcion invalida.\n";
    continue;
}
```

Ahí, `continue` salta a la siguiente vuelta del `while` del menú sin llegar al `switch`, cuando la entrada no fue un número válido. Con un `while` dedicado como el de arriba, la misma idea de "seguir pidiendo hasta que sea válido" no necesita `continue`: la condición del propio `while` ya se encarga de mantener el ciclo activo mientras el valor siga siendo inválido.

| | `for` | `while` |
|---|---|---|
| Número de vueltas | Se conoce antes de empezar | Depende de una condición que cambia durante la ejecución |
| Uso típico | Recorrer un arreglo o un rango fijo | Validar una entrada, repetir un menú, esperar a que algo cambie |
| Ejemplo en Sonora | Recorrer `reproducciones_semana[7]` | Pedir un umbral hasta que sea positivo |

⚠️ **Error frecuente:** olvidar actualizar la variable que controla la condición dentro del cuerpo del `while`. Si en el ejemplo del umbral olvidaras la línea `std::cin >> umbral;`, la condición `umbral <= 0` seguiría siendo verdadera para siempre, porque nada dentro del ciclo cambia el valor de `umbral`. El programa quedaría repitiendo el mensaje sin parar, lo que se llama un **ciclo infinito**. Todo `while` necesita que su cuerpo, en algún punto, modifique la variable que la condición revisa.

### Ejercicios

🔧 **Consejo de entorno:** compila con `g++ src/main.cpp src/reproductor.cpp -o sonora` y ejecuta con `./sonora`.

#### Inducción al error

Agrega esto arriba de `iniciar_sonora()`, actívalo en su lugar, compílalo y prepárate para interrumpirlo con Ctrl+C si lo ejecutas:

```cpp
void prueba_ciclo_infinito() {
    int umbral = -1;
    while (umbral <= 0) {
        std::cout << "Ingresa un umbral positivo: ";
        int nuevo_umbral = 0;
        std::cin >> nuevo_umbral;
        // Aqui falta: umbral = nuevo_umbral;
    }
    std::cout << "Umbral valido: " << umbral << "\n";
}
```

`nuevo_umbral` recibe el número que escribe el usuario, pero nunca se lo asigna a `umbral`, la variable que revisa la condición del `while`. Sin importar qué escribas, `umbral` sigue en `-1` para siempre, y el ciclo nunca termina. Confirma cuál línea falta y en qué posición del cuerpo debería ir.

#### 🧩 Antes de programar

Completa la tabla de trazo del `while` de validación (la versión correcta, con `umbral = nuevo_umbral;` incluido), con las entradas `-5`, `0`, `15000`, en ese orden.

```cpp
int umbral = -1;
while (umbral <= 0) {
    // pide un numero y lo guarda en umbral
}
```

| Vuelta | umbral antes de leer | ¿`umbral <= 0`? | Entrada leída | umbral después |
|---|---|---|---|---|
| 1 | -1 | | -5 | |
| 2 | | | 0 | |
| 3 | | | 15000 | |

<details>
<summary>🔓 Ver solución</summary>

| Vuelta | umbral antes de leer | ¿`umbral <= 0`? | Entrada leída | umbral después |
|---|---|---|---|---|
| 1 | -1 | Sí | -5 | -5 |
| 2 | -5 | Sí | 0 | 0 |
| 3 | 0 | Sí | 15000 | 15000 |

Después de la vuelta 3, la condición `umbral <= 0` se revisa una vez más con `umbral = 15000`, es falsa, y el ciclo termina sin ejecutar una cuarta vuelta. A diferencia del `for` de las secciones anteriores, aquí el número de vueltas (3) no se sabía antes de empezar: dependía de cuántas veces el usuario escribiera un número inválido.

</details>

#### Básico

📂 `src/main.cpp`

Antes de `case 9:`, agrega la validación de esta sección para que el umbral solo se acepte si es mayor que cero:

```cpp
case 9: {
    int umbral = -1;
    while (umbral <= 0) {
        std::cout << "Ingresa un umbral positivo de reproducciones: ";
        std::cin >> umbral;
        if (umbral <= 0) {
            std::cout << "El umbral debe ser mayor que cero.\n";
        }
    }
    std::cout << "Dias pico: " << contar_dias_pico(reproducciones_semana, umbral) << "\n";
    break;
}
```

Compila con `g++ src/main.cpp src/reproductor.cpp -o sonora` y ejecuta con `./sonora`. Elige la opción 9 e ingresa `-5`, luego `0`, luego `15000`.

La salida esperada es:

```
Ingresa un umbral positivo de reproducciones: El umbral debe ser mayor que cero.
Ingresa un umbral positivo de reproducciones: El umbral debe ser mayor que cero.
Ingresa un umbral positivo de reproducciones: Dias pico: 4
```

<details>
<summary>🔓 Ver solución</summary>

El bloque ya está completo arriba.

</details>

#### Intermedio

Sin compilar todavía, decide cuántas veces se imprime `"Vuelta"` en este ciclo.

```cpp
int contador = 0;
while (contador < 5) {
    std::cout << "Vuelta\n";
    contador = contador + 2;
}
```

<details>
<summary>🔓 Ver solución</summary>

Se imprime 3 veces, con `contador` tomando los valores 0, 2 y 4 antes de cada impresión. Al llegar a `contador = 6`, la condición `contador < 5` es falsa y el ciclo termina. A diferencia de un `for`, ningún incremento está escrito en la misma línea que la condición: `contador = contador + 2` vive dentro del cuerpo, y hay que leer el cuerpo completo para saber cómo avanza.

</details>

#### Avanzado

📂 `src/main.cpp`

Aplica la misma validación de esta sección a `case 10:`, para que el umbral de `filtrar_dias_pico` también rechace valores menores o iguales a cero.

Compila con `g++ src/main.cpp src/reproductor.cpp -o sonora` y ejecuta con `./sonora`.

<details>
<summary>🔓 Ver solución</summary>

```cpp
case 10: {
    int umbral = -1;
    while (umbral <= 0) {
        std::cout << "Ingresa un umbral positivo de reproducciones: ";
        std::cin >> umbral;
        if (umbral <= 0) {
            std::cout << "El umbral debe ser mayor que cero.\n";
        }
    }
    std::vector<std::string> dias_pico = filtrar_dias_pico(reproducciones_semana, nombres_dias, umbral);
    for (std::string& dia : dias_pico) {
        std::cout << dia << "\n";
    }
    break;
}
```

</details>

#### Reto

Retoma el bloque de validación de entrada que quedó pendiente, con `std::cin.fail()`, `std::cin.clear()` e `std::cin.ignore(...)`, y combínalo con el `while` de esta sección para que la lectura del umbral rechace tanto números negativos o cero como texto que no sea un número en absoluto.

**🧭 Pistas**

- `std::cin.fail()` se revisa inmediatamente después de `std::cin >> umbral`, antes de comparar `umbral <= 0`.
- Si `std::cin.fail()` es verdadero, `std::cin.clear()` y `std::cin.ignore(1000, '\n')` descartan la entrada inválida antes de que el `while` vuelva a pedir el dato.
- Prueba ingresando la palabra `"abc"` antes de un número válido y confirma que el programa vuelva a pedir el umbral en lugar de quedarse atascado o cerrarse.

---

## 8. Cierra el menú de Sonora

Con los ejercicios de las secciones 2 a 7, ya descomentaste `case 6` a `case 10`, y agregaste la validación con `while` a los umbrales de `case 9` y `case 10`. El menú de Sonora ahora tiene once opciones completas.

### Ejercicios

🔧 **Consejo de entorno:** compila con `g++ src/main.cpp src/reproductor.cpp -o sonora` y ejecuta con `./sonora`.

#### Inducción al error

Al agregar una opción nueva al menú (como la `12` del ejercicio "Intermedio" más abajo), un estudiante agrega el `case` nuevo pero olvida mover el número de `Salir`:

```cpp
std::cout << "11. Salir\n";  // deberia decir 12, si se agrego una opcion nueva
...
case 12: {
    // logica de la opcion nueva
    break;
}
case 11:
    ejecutando = false;
    break;
```

El programa compila y corre sin ningún error, porque `case 11` y `case 12` son válidos los dos. El problema aparece solo al usarlo: el usuario lee `"11. Salir"` en pantalla, escribe `11`, y cae en el `case` de la opción nueva en lugar de salir del programa. El texto que se imprime en cada línea del menú y el número que el `switch` espera tienen que coincidir exactamente; agregar una opción nueva en el `switch` sin mover el número de `Salir` (y su texto) deja el menú funcionando con números que ya no corresponden a lo que el usuario lee.

#### Básico

📂 `src/main.cpp`

Con los cinco bloques descomentados en las secciones 2 a 6, y la validación de la sección 7 en los `case 9` y `case 10`, ejecuta el programa completo y recorre las opciones 1, 6, 7, 8, 9 y 10 en orden, ingresando `15000` cuando el programa pida un umbral, y termina con la opción 11.

```bash
g++ src/main.cpp src/reproductor.cpp -o sonora
./sonora
```

<details>
<summary>🔓 Ver solución</summary>

Con las cinco funciones nuevas conectadas al menú, elegir `1`, `6`, `7`, `8`, `9` (con umbral `15000`), `10` (con umbral `15000`) y `11`, en ese orden, produce:

```
=== Sonora ===
1. Mostrar catalogo
2. Registrar una reproduccion
3. Clasificar una cancion por reproducciones
4. Ver si una cancion es recomendable
5. Interpretar una calificacion (1 a 5)
6. Mostrar reproducciones de la semana
7. Ver porcentaje de reproducciones por dia
8. Ver total y promedio semanal
9. Contar dias pico
10. Ver dias pico
11. Salir
Elige una opcion: La Gota Fria - Carlos Vives (Vallenato, 1250000 reproducciones)
La Rebelion - Joe Arroyo (Salsa, 82000 reproducciones)
Rio - Bomba Estereo (Electronica, 15300 reproducciones)

=== Sonora ===
...
Elige una opcion: Lunes: 12000
Martes: 8500
Miercoles: 15300
Jueves: 9800
Viernes: 22000
Sabado: 31000
Domingo: 18500

=== Sonora ===
...
Elige una opcion: Lunes: 10.2477%
Martes: 7.25875%
Miercoles: 13.0658%
Jueves: 8.36892%
Viernes: 18.7874%
Sabado: 26.4731%
Domingo: 15.7985%

=== Sonora ===
...
Elige una opcion: Total: 117100
Promedio: 16728.6

=== Sonora ===
...
Elige una opcion: Ingresa un umbral positivo de reproducciones: Dias pico: 4

=== Sonora ===
...
Elige una opcion: Ingresa un umbral positivo de reproducciones: Miercoles
Viernes
Sabado
Domingo

=== Sonora ===
...
Elige una opcion: Hasta pronto.
```

</details>

#### Intermedio

📂 `src/main.cpp`

Agrega una opción `12. Mostrar el dia con mas reproducciones` que use `maximo_reproducciones_semana` (la función del Reto de la sección 4) para encontrar el valor más alto del arreglo, y `nombres_dias` para mostrar a qué día corresponde. Ajusta el texto del menú, el número de `case 11: Salir`, que ahora debería pasar a `13`, y el `default`.

Compila con `g++ src/main.cpp src/reproductor.cpp -o sonora` y ejecuta con `./sonora`.

<details>
<summary>🔓 Ver solución</summary>

```cpp
case 12: {
    int maximo = maximo_reproducciones_semana(reproducciones_semana);
    for (int dia = 0; dia < 7; dia++) {
        if (reproducciones_semana[dia] == maximo) {
            std::cout << nombres_dias[dia] << ": " << maximo << "\n";
            break;
        }
    }
    break;
}
```

Con el catálogo de ejemplo, esta opción imprime `Sabado: 31000`. El `break` interior sale del `for` en cuanto encuentra el día que coincide con el máximo; sin él, el ciclo seguiría revisando el resto del arreglo aunque ya encontró lo que buscaba.

</details>

#### Avanzado

📂 `src/main.cpp`

Agrega una validación para toda opción del menú, no solo para los umbrales: si el usuario ingresa un número fuera de 1 a 13, o texto en lugar de un número, el programa debe mostrar `"Opcion invalida."` sin cerrarse. El `default` del `switch` ya cubre los números fuera de rango; la parte nueva es qué pasa si `std::cin >> opcion` falla porque el usuario escribió texto.

> Retoma el patrón con `std::cin.fail()`, `std::cin.clear()` e `std::cin.ignore(...)` que quedó pendiente desde antes, y que ya aplicaste a los umbrales en la sección 7 de esta guía.

Compila con `g++ src/main.cpp src/reproductor.cpp -o sonora` y ejecuta con `./sonora`.

<details>
<summary>🔓 Ver solución</summary>

```cpp
int opcion = 0;
std::cin >> opcion;

if (std::cin.fail()) {
    std::cin.clear();
    std::cin.ignore(1000, '\n');
    std::cout << "Opcion invalida.\n";
    continue;
}
```

</details>

#### Reto

Cada canción de Sonora podría tener su propio arreglo `int reproducciones_semana[7]`, en lugar de un único arreglo agregado para todo el catálogo. Diseña cómo cambiaría el struct `Cancion` para guardar ese dato por canción, y qué función nueva necesitarías para sumar el total semanal de una sola canción. Todavía no vas a estudiar arreglos dentro de un struct a fondo (llega en una sesión posterior), así que trata este ejercicio como un diseño en papel, sin necesidad de compilarlo.

**🧭 Pistas**

- Un arreglo puede vivir como campo de un struct, igual que `std::string` o `int`: `int reproducciones_semana[7];` dentro de las llaves de `Cancion`.
- La función de suma por canción reutiliza la misma lógica de `sumar_reproducciones_semana`, solo que el arreglo llega desde `cancion.reproducciones_semana` en lugar de una variable suelta.
- Piensa qué pasaría con el arreglo agregado de esta sesión si cada canción ya trae el suyo: ¿siguen siendo necesarios los dos, o uno se puede calcular a partir del otro?

---

## Entregable: bitácora de errores

Durante las horas de trabajo independiente de esta sesión, vas a encontrarte con errores reales, de compilación, de enlazado, o de lógica. Llevar un registro corto de cada uno, en el momento en que pasa, es más útil de lo que parece: nombrar qué esperabas y qué pasó en realidad es el primer paso para entender la causa, en lugar de solo probar cambios hasta que compile.

### Durante la práctica: registro continuo

Cada vez que un error real te detenga (no los de "Inducción al error", que ya sabes que van a fallar), antes de seguir buscando la solución, anótalo en una tabla como esta:

| Error | Qué esperaba | Qué pasó | Qué lo arregló |
|---|---|---|---|
| | | | |

Una fila por error, unas 15 palabras por celda, nada más. No hace falta que sea elegante, es un registro de trabajo, no un informe.

### Al final: selecciona y entrega

De todos los errores que registraste, escoge **5**, los que más te costó resolver o los que más aprendiste de ellos, y entrega:

1. **Una captura de pantalla por error**, con la terminal y la barra de fecha/hora del sistema visibles (no hace falta la pantalla completa del escritorio, solo que se vea la fecha).
2. **Las cuatro columnas de la tabla** (qué esperaba, qué pasó, qué lo arregló) para cada uno de los 5 errores.
3. **Un texto corto, al final**, con las 3 cosas que aprendiste a partir de esos errores. No una por error: una síntesis de lo que te llevas en general.

```
## Bitácora de errores, [tu nombre]

### Error 1
**Captura:** (pantalla con la terminal y la fecha/hora visibles)
**Qué esperaba:** ...
**Qué pasó:** ...
**Qué lo arregló:** ...

### Error 2
...
(hasta 5)

### Lo que aprendí
1. ...
2. ...
3. ...
```

---

## Ejercicios sueltos de práctica adicional

Estos ejercicios no siguen el caso de Sonora: son problemas independientes, cada uno con su propio contexto, para practicar arreglos, ciclos y condicionales por separado. Úsalos como repaso adicional, en cualquier orden dentro de cada tema.

### Arreglos

#### 🧩 Trazar

Con `int numeros[5] = {4, 8, 15, 16, 23};`, responde sin compilar:

1. ¿Qué valor tiene `numeros[0]`?
2. ¿Qué valor tiene `numeros[4]`?
3. ¿Qué posición ocupa el valor `15`?

<details>
<summary>🔓 Ver solución</summary>

1. `4` (la primera posición, índice 0)
2. `23` (la última posición, índice 4)
3. La posición 2 (`numeros[2]`)

</details>

#### Predecir

Sin compilar todavía, decide qué imprime este programa.

```cpp
int numeros[5] = {4, 8, 15, 16, 23};
int total = 0;
for (int i = 0; i < 5; i++) {
    total = total + numeros[i];
}
std::cout << total << "\n";
```

<details>
<summary>🔓 Ver solución</summary>

`66`. Es la suma de las 5 posiciones: 4 + 8 + 15 + 16 + 23 = 66.

</details>

#### Encontrar el error

Este programa quiere imprimir las 4 posiciones de `temperaturas`, pero tiene un error:

```cpp
int temperaturas[4] = {18, 22, 19, 25};
for (int i = 0; i <= 4; i++) {
    std::cout << temperaturas[i] << " ";
}
```

¿Cuál es el error, y qué problema causa?

<details>
<summary>🔓 Ver solución</summary>

La condición debería ser `i < 4`, no `i <= 4`. El arreglo tiene posiciones válidas de 0 a 3; con `i <= 4`, la última vuelta accede a `temperaturas[4]`, una posición que no existe. C++ no detiene el programa por esto: el resultado es un valor indeterminado, distinto en cada ejecución, el mismo problema de comportamiento indefinido que ya viste con los arreglos.

</details>

#### Escribir

Escribe una función `encontrar_maximo(int numeros[5])` que retorne el valor más alto del arreglo, sin usar ninguna función de la biblioteca estándar.

Pruébala con `{7, 2, 9, 4, 5}`. La salida esperada es:

```
9
```

<details>
<summary>🔓 Ver solución</summary>

```cpp
int encontrar_maximo(int numeros[5]) {
    int maximo = numeros[0];
    for (int i = 1; i < 5; i++) {
        if (numeros[i] > maximo) {
            maximo = numeros[i];
        }
    }
    return maximo;
}
```

</details>

#### Escribir

Con dos arreglos paralelos, `std::string nombres[4]` y `int edades[4]`, escribe un programa que imprima el nombre de cada persona mayor de edad (18 años o más).

Prueba con `nombres = {"Ana", "Luis", "Marta", "Pedro"}` y `edades = {17, 20, 16, 22}`. La salida esperada es:

```
Luis es mayor de edad
Pedro es mayor de edad
```

<details>
<summary>🔓 Ver solución</summary>

```cpp
std::string nombres[4] = {"Ana", "Luis", "Marta", "Pedro"};
int edades[4] = {17, 20, 16, 22};
for (int i = 0; i < 4; i++) {
    if (edades[i] >= 18) {
        std::cout << nombres[i] << " es mayor de edad\n";
    }
}
```

</details>

### Ciclos

#### 🧩 Trazar

Completa la tabla de trazo de este ciclo:

```cpp
int contador = 1;
while (contador <= 20) {
    contador = contador * 2;
}
```

| Vuelta | contador antes | ¿`contador <= 20`? | contador después |
|---|---|---|---|
| 1 | 1 | | |
| 2 | | | |
| 3 | | | |
| 4 | | | |
| 5 | | | |

<details>
<summary>🔓 Ver solución</summary>

| Vuelta | contador antes | ¿`contador <= 20`? | contador después |
|---|---|---|---|
| 1 | 1 | Sí | 2 |
| 2 | 2 | Sí | 4 |
| 3 | 4 | Sí | 8 |
| 4 | 8 | Sí | 16 |
| 5 | 16 | Sí | 32 |

Después de la vuelta 5, la condición se revisa con `contador = 32`, es falsa, y el ciclo termina. El programa imprimiría `32`.

</details>

#### Predecir

Sin compilar todavía, decide qué imprime este programa.

```cpp
int contador = 1;
while (contador <= 20) {
    contador = contador * 2;
}
std::cout << contador << "\n";
```

<details>
<summary>🔓 Ver solución</summary>

`32`. Confirma tu respuesta contra la tabla de trazo del ejercicio anterior.

</details>

#### Encontrar el error

Este programa se cuelga y nunca termina. No lo ejecutes tal cual, o vas a tener que interrumpirlo con Ctrl+C.

```cpp
int contador = 10;
while (contador > 0) {
    std::cout << contador << " ";
    contador = contador + 1;
}
```

¿Por qué nunca termina?

<details>
<summary>🔓 Ver solución</summary>

`contador` empieza en 10, positivo, y la condición sigue siendo `contador > 0`. Pero el cuerpo del ciclo hace `contador = contador + 1`, sumando en vez de restar: `contador` crece cada vez más, nunca deja de ser positivo, y la condición nunca se vuelve falsa. Es un **ciclo infinito**. La corrección sería `contador = contador - 1`, para que eventualmente llegue a 0.

</details>

#### Escribir

Escribe un programa que cuente cuántos múltiplos de 3 hay entre 1 y 30 (incluidos ambos extremos), usando un `for`.

La salida esperada es:

```
10
```

<details>
<summary>🔓 Ver solución</summary>

```cpp
int multiplos_de_3 = 0;
for (int i = 1; i <= 30; i++) {
    if (i % 3 == 0) {
        multiplos_de_3 = multiplos_de_3 + 1;
    }
}
std::cout << multiplos_de_3 << "\n";
```

`%` es el operador módulo: `i % 3 == 0` es verdadero cuando `i` es divisible entre 3, sin residuo.

</details>

#### Escribir

Con `int valores[5] = {4, 7, 2, -1, 9};`, escribe un `while` que sume los valores del arreglo uno por uno, deteniéndose apenas encuentre un `-1` (sin sumarlo), sin usar un `for`. El `-1` funciona como un **centinela**: una marca que indica "hasta aquí llegan los datos válidos", sin ser parte del dato en sí.

La salida esperada es:

```
13
```

<details>
<summary>🔓 Ver solución</summary>

```cpp
int valores[5] = {4, 7, 2, -1, 9};
int suma = 0;
int i = 0;
while (valores[i] != -1) {
    suma = suma + valores[i];
    i = i + 1;
}
std::cout << suma << "\n";
```

Este es un ejemplo genuino de ciclo indefinido: el número de vueltas (3, en este caso) depende de dónde aparezca el centinela, no de un contador fijo como en un `for`.

</details>

### Condicionales

#### Predecir

Sin compilar todavía, decide qué imprime este programa con `numero = -6`.

```cpp
int numero = -6;
if (numero > 0) {
    if (numero % 2 == 0) {
        std::cout << "Positivo y par\n";
    } else {
        std::cout << "Positivo e impar\n";
    }
} else if (numero < 0) {
    std::cout << "Negativo\n";
} else {
    std::cout << "Cero\n";
}
```

<details>
<summary>🔓 Ver solución</summary>

`Negativo`. `numero > 0` es falso (-6 no es mayor que 0), así que ni siquiera se revisa el condicional anidado de par/impar; C++ pasa directo a `else if (numero < 0)`, que sí es verdadero.

</details>

#### Encontrar el error

Este programa siempre imprime `"Aprobado"`, sin importar el valor de `nota`. El compilador no marca ningún error ni advertencia con el comando de compilación de este curso.

```cpp
int nota = 3;
if (nota = 5) {
    std::cout << "Aprobado\n";
} else {
    std::cout << "Reprobado\n";
}
```

¿Cuál es el error?

<details>
<summary>🔓 Ver solución</summary>

`nota = 5` es una **asignación** (un solo `=`), no una **comparación** (`==`, dos signos). `nota = 5` le asigna 5 a `nota` y, como resultado de la expresión completa, produce el valor recién asignado (`5`), que C++ interpreta como verdadero porque no es `0`. El `if` siempre entra al bloque `"Aprobado"`, y de paso `nota` termina valiendo `5`, aunque originalmente era `3`. La corrección es `if (nota == 5)`. Este es uno de los errores más comunes en C++, precisamente porque no avisa con ningún mensaje.

</details>

#### Escribir

Escribe una función `clasificar_numero(int numero)` que retorne `"Cero"` si el número es 0, `"Par"` si es par (y distinto de cero), o `"Impar"` si es impar.

Pruébala con `7`, `0`, y `-4`. La salida esperada es:

```
Impar
Cero
Par
```

<details>
<summary>🔓 Ver solución</summary>

```cpp
std::string clasificar_numero(int numero) {
    if (numero == 0) {
        return "Cero";
    } else if (numero % 2 == 0) {
        return "Par";
    } else {
        return "Impar";
    }
}
```

El orden importa: si `numero == 0` no fuera la primera condición, `0 % 2 == 0` también sería verdadero, y `0` se clasificaría como `"Par"` en lugar de `"Cero"`.

</details>

#### Escribir

Escribe una función `dia_de_la_semana(int numero)` que use un `switch` para retornar el nombre del día (1 = "Lunes", 2 = "Martes", ..., 7 = "Domingo"), y `"Numero invalido"` para cualquier otro valor.

Pruébala con `3` y `9`. La salida esperada es:

```
Miercoles
Numero invalido
```

<details>
<summary>🔓 Ver solución</summary>

```cpp
std::string dia_de_la_semana(int numero) {
    switch (numero) {
        case 1: return "Lunes";
        case 2: return "Martes";
        case 3: return "Miercoles";
        case 4: return "Jueves";
        case 5: return "Viernes";
        case 6: return "Sabado";
        case 7: return "Domingo";
        default: return "Numero invalido";
    }
}
```

</details>

#### 🧩 Trazar

Con `edad = 16` y `tiene_permiso = true`, evalúa la condición sin compilar:

```cpp
if (edad >= 18 || (edad >= 16 && tiene_permiso)) {
    std::cout << "Puede entrar\n";
} else {
    std::cout << "No puede entrar\n";
}
```

1. ¿Cuánto vale `edad >= 18`?
2. ¿Cuánto vale `edad >= 16 && tiene_permiso`?
3. ¿Cuánto vale la condición completa, y qué se imprime?

<details>
<summary>🔓 Ver solución</summary>

1. Falso (16 no es mayor o igual a 18).
2. Verdadero (16 >= 16 es verdadero, y `tiene_permiso` es verdadero, así que el `&&` completo es verdadero).
3. `falso || verdadero` es verdadero, así que se imprime `"Puede entrar"`. Con `||` (or), basta con que uno de los dos lados sea verdadero para que toda la condición lo sea.

</details>

---

## Referencias

- **cppreference.com, arreglos**: referencia técnica completa sobre arreglos de C++, incluido el decaimiento a puntero:
  [https://en.cppreference.com/w/cpp/language/array](https://en.cppreference.com/w/cpp/language/array)
- **cppreference.com, `for`**: documentación formal de la sentencia `for`:
  [https://en.cppreference.com/w/cpp/language/for](https://en.cppreference.com/w/cpp/language/for)
- **cppreference.com, `while`**: documentación formal de la sentencia `while`:
  [https://en.cppreference.com/w/cpp/language/while](https://en.cppreference.com/w/cpp/language/while)
- **cppreference.com, `std::vector`**: referencia de la clase, incluido `push_back`:
  [https://en.cppreference.com/w/cpp/container/vector](https://en.cppreference.com/w/cpp/container/vector)
