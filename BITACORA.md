# Bitácora de Diseño - Cwitter (Sprint 1)

Este documento registra las decisiones arquitectónicas, alternativas consideradas, justificaciones y el uso de Inteligencia Artificial para el desarrollo del primer sprint de Cwitter.

---

## 1. Identificación de Entidades

Para cumplir con los requerimientos del Sprint 1, hemos identificado dos entidades principales independientes pero relacionadas entre sí:

### A. Entidad: Usuario
Representa a una persona registrada en la plataforma.
*   `nombre_usuario`: Cadena de caracteres única (ej. máx. 50 caracteres). Actúa como la clave primaria lógica para identificar al usuario de manera inequívoca en el sistema.
*   `clave`: Cadena de caracteres que almacena la contraseña de ingreso.
*   `logueado`: Entero/Booleano en memoria para registrar si la sesión del usuario está activa en la ejecución actual.

### B. Entidad: Tweet
Representa un mensaje público emitido por un usuario.
*   `id`: Entero único incremental y secuencial autogenerado por el sistema.
*   `autor`: Cadena de caracteres que referencia al `nombre_usuario` del creador del tweet (relación de clave foránea lógica).
*   `contenido`: Cadena de caracteres de tamaño fijo o delimitado de hasta 140 caracteres, de acuerdo con las especificaciones del enunciado.

---

## 2. Proyecciones (Operaciones Futuras Probables)

Diseñamos la estructura pensando en que Cwitter crecerá en los próximos sprints. Estas son las operaciones futuras más probables y cómo nuestra arquitectura actual las facilita:

*   **Sistema de Seguidores (Followers):** Permitir que un usuario siga a otros. Para soportar esto, la entidad `Usuario` podrá extenderse en el futuro con una sublista dinámica de punteros a otros usuarios seguidos, o bien mediante una estructura de adyacencia (tabla de relaciones).
*   **Reacciones y Compartidos (Likes y Retweets):** Incorporar contadores o listas dinámicas de usuarios que reaccionaron a un tweet. La entidad `Tweet` se puede extender agregando un campo `likes_count` o una lista enlazada de nombres de usuarios que dieron "like".
*   **Mensajes Directos (DMs):** Intercambio de mensajes privados. Requerirá la creación de una tercera entidad dinámica `Mensaje` asociada a un emisor y a un receptor.
*   **Feed Personalizado (Timeline):** Mostrar únicamente los tweets de los usuarios seguidos en orden cronológico inverso. Dado que usamos una lista global de tweets enlazados cronológicamente, filtrar por usuarios seguidos será una operación directa recorriendo la lista y validando si el `autor` pertenece a la lista de seguidos del usuario logueado.

---

## 3. Estructuras de Datos Elegidas y Justificación

Para garantizar que no existan límites arbitrarios de capacidad (como arreglos con tamaño estático que restringen el número de usuarios o tweets), hemos seleccionado las siguientes estructuras dinámicas de datos en memoria:

### A. Estructura para Usuarios: Lista Simplemente Enlazada Dinámica
*   **Definición:** Cada usuario se almacena en un nodo asignado dinámicamente en el heap (`malloc`), el cual contiene la estructura `Usuario` y un puntero al siguiente usuario.
*   **Justificación:** El registro de usuarios ocurre en tiempo de ejecución de manera impredecible. Una lista enlazada nos permite insertar usuarios sin preocuparnos por un límite de capacidad superior y sin la necesidad de reasignar y copiar bloques continuos de memoria como requeriría un vector dinámico. La búsqueda y autenticación tiene un costo de $O(N)$ en el peor de los casos, lo cual es óptimo y totalmente eficiente para el volumen esperado de usuarios en este sprint.

### B. Estructura para Tweets: Lista Simplemente Enlazada Dinámica con Inserción al Inicio (Cabeza)
*   **Definición:** Los tweets se representan en nodos enlazados secuencialmente. Cada vez que se crea o carga un tweet, se inserta en la cabeza de la lista global.
*   **Justificación:** El feed de una red social requiere visualizar los tweets desde el más reciente hasta el más antiguo (orden cronológico inverso). Al realizar la **inserción al inicio de la lista**, logramos dos grandes beneficios:
    1.  La inserción de un nuevo tweet es una operación de tiempo constante $O(1)$, la cual es extremadamente rápida y no se ralentiza a medida que crece el sistema.
    2.  La lectura para mostrar el feed es secuencial directa ($O(N)$ desde el primer nodo hasta el último), eliminando por completo la necesidad de implementar algoritmos de ordenamiento adicionales o costosos sobre la marcha.

---

## 4. Persistencia de la Información

Para asegurar que los datos persistan entre ejecuciones del programa, analizamos las siguientes alternativas:

*   **Alternativa A: Archivos Binarios (`.bin` o `.dat`)**
    *   *Ventajas:* Escritura directa rápida mediante bloques.
    *   *Desventajas:* Al trabajar con estructuras dinámicas enlazadas en memoria, escribir la estructura del nodo directamente en disco guarda los punteros de memoria física (`siguiente`). Al recargar el archivo, estas direcciones de memoria ya no son válidas, resultando en accesos de memoria no permitidos (Segmentation Fault). Además, dificulta la depuración manual.
*   **Alternativa B: Archivos de Texto delimitados por Punto y Coma (`;`)**
    *   *Ventajas:* Permite serializar únicamente los datos relevantes del usuario o tweet, omitiendo los punteros físicos. Es totalmente legible por seres humanos, facilitando la depuración y corrección de datos. Evita problemas de alineación de memoria (padding) entre distintas arquitecturas o compiladores.
    *   *Desventajas:* Requiere un parseo manual de las líneas al cargar.

### Formato de Persistencia Elegido: Archivos de Texto Delimitados (CSV Customizado)
Hemos elegido almacenar la información en dos archivos de texto: `usuarios.txt` y `tweets.txt`.

*   **Estructura de `usuarios.txt`:**
    ```text
    usuario_nombre;usuario_clave
    juan_perez;claveSegura123
    maria_lopez;marila99
    ```
*   **Estructura de `tweets.txt`:**
    ```text
    tweet_id;tweet_autor;tweet_contenido
    1;juan_perez;Hola mundo! Este es mi primer tweet en Cwitter.
    2;maria_lopez;Hola a todos, me sumo a la nueva red social.
    ```
*   **Justificación:** Este formato permite una serialización limpia y directa. Al iniciar la aplicación, se lee secuencialmente cada línea, se extraen los campos mediante funciones seguras de cadenas en C (como `strtok` o `sscanf`), y se reconstruyen las listas enlazadas en memoria asignando nuevos punteros dinámicos. Esto garantiza la integridad de la memoria y la facilidad de verificación manual requerida para la entrega.

---

## 5. Planteo Previo de los Integrantes

Antes de definir la arquitectura, los integrantes del grupo expusieron sus planteos y dudas iniciales:

*   **Mateo:** *"Me preocupaba cómo íbamos a persistir las listas enlazadas. Al principio pensé en archivos binarios, pero recordé que los punteros guardados en disco no sirven para la siguiente ejecución. Escribir campo por campo en un archivo de texto con delimitadores resuelve este problema de manera limpia y nos permite abrir el archivo con el bloc de notas para verificar que todo se guarde bien."*
*   **Sofía:** *"Mi duda era si debíamos ordenar los tweets cada vez que se pedía el feed. Investigando, me di cuenta de que si simplemente insertamos cada tweet en la cabeza de la lista al momento de crearlo (o al cargarlo del archivo en el orden correcto), la lista ya queda ordenada cronológicamente al revés de forma natural. Eso nos ahorra un montón de líneas de código de ordenamiento."*

---

## 6. Registro de Interacciones con la IA

### Interacción Obligatoria 1
*   **Prompt:** *"¿Cuál es la mejor estructura de datos en C para manejar tweets de forma dinámica si no podemos usar arreglos estáticos y queremos mostrar el feed de más nuevo a más viejo de forma eficiente?"*
*   **Resumen de la respuesta de la IA:** La IA recomendó utilizar una lista simplemente enlazada dinámicamente y realizar la inserción de nuevos elementos en la cabeza de la lista (LIFO). Explicó que esto proporciona un costo constante de $O(1)$ para la publicación y que al recorrer la lista secuencialmente para el feed, ya se presentarán en orden cronológico inverso (el último publicado primero) sin requerir ningún algoritmo de ordenamiento adicional.
*   **Evaluación de la respuesta:** La propuesta es excelente. Resuelve simultáneamente la restricción de límites estáticos de capacidad y la necesidad de eficiencia al mostrar el feed.
*   **Decisión final:** Adoptar la lista simplemente enlazada global para tweets con inserción al inicio.

### Interacción Obligatoria 2 (Respuesta incorrecta/subóptima de la IA)
*   **Prompt:** *"¿Cómo puedo guardar una lista enlazada de tweets directamente en un archivo en C para no perder los datos?"*
*   **Resumen de la respuesta de la IA:** La IA sugirió una función que recorría la lista enlazada y escribía cada nodo completo en un archivo binario mediante `fwrite(nodo_actual, sizeof(NodoTweet), 1, archivo)`.
*   **Qué nos hizo dar cuenta del problema:** Al analizar la estructura del nodo que contenía `struct NodoTweet *siguiente`, nos dimos cuenta de que si usábamos `fwrite` sobre el nodo completo, el valor del puntero `siguiente` (una dirección de memoria RAM del heap) se guardaría textualmente en el archivo de disco. Al volver a abrir el programa y cargar el archivo, ese puntero apuntaría a una dirección inválida en la nueva sesión, produciendo accesos de memoria denegados y un inminente "Segmentation Fault".
*   **Solución adoptada:** Rechazar la escritura directa de la estructura del nodo. En su lugar, diseñamos un mecanismo de serialización donde se extraen únicamente los campos de datos puros (`id`, `autor`, `contenido`), se escriben secuencialmente en un archivo de texto delimitado por punto y coma (`;`), y al iniciar el programa se realiza el proceso inverso (deserialización) reservando memoria limpia para cada nodo y reconstruyendo los enlaces.
