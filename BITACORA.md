# Bitácora de Diseño - Cwitter (Sprint 1)

Este documento registra las decisiones arquitectónicas, alternativas consideradas, justificaciones y el uso de Inteligencia Artificial para el desarrollo del primer sprint de Cwitter, bajo la restricción de **no utilizar listas convencionales**.

---

## 1. Identificación de Entidades

Para cumplir con los requerimientos del Sprint 1, hemos identificado dos entidades principales independientes pero relacionadas entre sí:

### A. Entidad: Usuario
Representa a una persona registrada en la plataforma.
*   `nombre_usuario`: Cadena de caracteres única (ej. máx. 50 caracteres).
*   `clave`: Cadena de caracteres que almacena la contraseña de ingreso.
*   `logueado`: Booleano para el estado de sesión.

### B. Entidad: Tweet
Representa un mensaje público emitido por un usuario.
*   `id`: Entero único incremental.
*   `autor`: Referencia al `nombre_usuario`.
*   `contenido`: Cadena de hasta 140 caracteres.

---

## 2. Proyecciones (Operaciones Futuras Probables)

*   **Sistema de Seguidores:** Uso de colas de prioridad o estructuras de adyacencia para gestionar relaciones.
*   **Reacciones:** Acumuladores en la estructura de la cola de tweets.
*   **Feed Personalizado:** Recorrido eficiente de la cola global filtrando por autor.

---

## 3. Estructuras de Datos Elegidas y Justificación

Siguiendo la nueva directiva de **prohibición de listas**, hemos seleccionado la estructura de **Cola Dinámica (Queue)** para todas nuestras entidades.

### A. Estructura para Usuarios: Cola Dinámica (FIFO)
*   **Definición:** Los usuarios se encolan a medida que se registran. La estructura mantiene un puntero al `frente` y uno al `final`.
*   **Justificación:** El registro de usuarios es un flujo secuencial donde el orden de llegada (registro) es relevante para la gestión de la memoria. Al usar una cola, garantizamos un acceso ordenado y cumplimos con la restricción de no usar listas genéricas.

### B. Estructura para Tweets: Cola Dinámica (FIFO)
*   **Definición:** Cada nuevo tweet se añade al `final` de la cola global.
*   **Justificación:** 
    1.  **Inserción Eficiente:** El encolado es una operación $O(1)$ gracias al puntero al `final`.
    2.  **Cumplimiento Normativo:** Sustituimos la lista enlazada por una Cola, gestionando los tweets como un flujo de mensajes. Aunque la visualización del feed (de más nuevo a más viejo) requerirá un recorrido específico o una inversión lógica, la estructura base respeta la prohibición de listas del proyecto.

---

## 4. Persistencia de la Información

### Formato de Persistencia Elegido: Archivos de Texto Delimitados (CSV)
La información se desencola y se guarda en `usuarios.txt` y `tweets.txt` utilizando el delimitador `;`. Al cargar, se reconstruyen las **colas** dinámicas respetando el orden original de los datos.

---

## 5. Registro de Interacciones con la IA

### Interacción Obligatoria 1
*   **Prompt:** "¿Cómo implementar un sistema de tweets usando únicamente Colas en lugar de listas en C?"
*   **Resumen:** La IA sugirió definir una estructura `Cola` con punteros `frente` y `final` a nodos de tweets. Explicó que para eliminar elementos intermedios (requerido por el sprint), se debe realizar un recorrido cuidadoso manteniendo la integridad de la cola, o bien "desencolar y volver a encolar" los elementos que no se desean eliminar.
*   **Decisión final:** Implementar Colas Dinámicas con punteros dobles para gestión eficiente.

### Interacción Obligatoria 2 (Respuesta incorrecta de la IA)
*   **Prompt:** "Dame una función para eliminar el último elemento de una cola en C."
*   **Resumen:** La IA proporcionó una función de "pop" estándar que solo eliminaba el frente.
*   **Problema:** En una cola estándar, solo se accede al frente. Sin embargo, el sprint exige eliminar el último tweet (final).
*   **Solución:** Implementamos un recorrido desde el frente hasta el penúltimo nodo para actualizar el puntero `final`, asegurando que la estructura de Cola permanezca válida tras la eliminación en cualquier posición.
