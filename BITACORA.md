# Bitácora de Diseño - Cwitter (Sprints 1 y 2)

Este documento registra las decisiones arquitectónicas, alternativas consideradas, justificaciones y el uso de Inteligencia Artificial para el desarrollo de Cwitter.

---

## SPRINT 1: Fundamentos (Colas)

### 1. Identificación de Entidades
Para el Sprint 1 se definieron las entidades `Usuario` (nombre y clave) y `Tweet` (id, autor, contenido).

### 2. Estructuras de Datos y Justificación
Siguiendo la directiva de **prohibición de listas**, se seleccionó la estructura de **Cola Dinámica (Queue)** para usuarios y tweets.
*   **Justificación:** Garantiza un acceso ordenado FIFO y cumple con la restricción normativa de no usar listas genéricas.

---

## SPRINT 2: Procesamiento y Verificación

En este sprint, evolucionamos la arquitectura para soportar navegación interactiva y servicios externos, incorporando nuevas estructuras de datos permitidas.

### 1. Nuevas Estructuras de Datos y Justificación

#### A. Navegación del Feed: Lista Doblemente Enlazada
*   **Decisión:** Para el modo de visualización "Historia" (un tweet a la vez), hemos implementado una **Lista Doblemente Enlazada**.
*   **Justificación:** El requerimiento de "volver al anterior" de forma fluida hace que la Cola (FIFO) del Sprint 1 sea insuficiente. Una lista doble permite punteros `siguiente` y `anterior`, logrando una navegación bidireccional en tiempo constante $O(1)$ entre nodos una vez generada la vista.
*   **Alternativa descartada:** Uso de dos Pilas. Aunque funcional, la gestión de memoria y el traspaso de elementos entre pilas resulta más costoso y menos intuitivo para una navegación repetitiva.

#### B. Ranking Top 5: Lista Simple Ordenada
*   **Decisión:** Para el ranking de usuarios verificados, utilizamos una **Lista Enlazada Simple con Inserción Ordenada**.
*   **Justificación:** Dado que los datos de publicaciones llegan desordenados desde el servicio externo, insertar cada usuario en su posición correcta según su contador de tweets mantiene el ranking actualizado en todo momento. Al finalizar el proceso, solo se toman los primeros 5 nodos.

### 2. Integración con Servicio Externo (FameCheck)

#### A. Verificación y Persistencia
*   Se añade el campo `es_verificado` a la entidad `Usuario`. 
*   **Decisión:** La consulta al servicio se realiza durante el login o registro. El estado se persiste en el archivo `usuarios.txt` para evitar consultas innecesarias en cada inicio de sesión, respetando la autoridad del servicio externo.

#### B. Tolerancia a Fallos y Logging
*   **Estrategia:** "Fail-safe". Si el reporte de un tweet a FameCheck falla, la publicación prosigue para no afectar la experiencia del usuario.
*   **Implementación de Logs:** Se crea el archivo `service_errors.log` donde se registran los fallos con marca temporal. Se eligió un formato de texto plano (Append) por su simplicidad y bajo costo de escritura.

### 3. Algoritmo de Ordenamiento del Feed

*   **Lógica:** Priorización por tipo de cuenta.
*   **Algoritmo:** Al generar la vista del feed, se realiza un filtrado en dos pasadas sobre la Cola Global de Tweets:
    1.  Pasada 1: Extraer tweets de autores con `es_verificado == 1`.
    2.  Pasada 2: Extraer tweets de autores con `es_verificado == 0`.
*   Esto garantiza que los verificados aparezcan primero, manteniendo el orden cronológico dentro de cada grupo.

---

## Registro de Interacciones con la IA (Sprint 2)

### Interacción 1 (Planificación de Estructuras)
*   **Prompt:** "¿Cuál es la mejor estructura para un feed que permite ir hacia adelante y atrás?"
*   **Resumen:** La IA recomendó la Lista Doblemente Enlazada por su capacidad natural de navegación bidireccional.
*   **Decisión:** Se adoptó esta estructura para el modo interactivo del feed.

### Interacción 2 (Gestión de Errores)
*   **Prompt:** "¿Cómo registrar errores de red en C sin detener la ejecución principal?"
*   **Resumen:** La IA sugirió el uso de funciones de logging que escriban en archivos en modo "append" (`a`) y el manejo de códigos de retorno para decidir si mostrar un mensaje al usuario o solo loguear el error de forma silenciosa.
*   **Decisión:** Implementación de `registrarErrorServicio()` para el archivo de logs.
