# Sprint 1: Cwitter - Fundamentos

Este archivo detalla los objetivos, requerimientos y entregables para el primer sprint del proyecto Cwitter.

## 1. Objetivos y Alcance
El objetivo de este sprint es desarrollar la primera versión funcional de la plataforma de red social Cwitter, asegurando la persistencia de datos.

**Funcionalidades requeridas:**
* Registro de nuevos usuarios.
* Inicio y cierre de sesión.
* Publicación, modificación y eliminación de tweets (máx. 140 caracteres).
* Consulta del feed (tweets de todos los usuarios).
* Búsqueda de tweets.
* Conservación de usuarios y tweets entre ejecuciones del programa (persistencia).

**Consideración de diseño:**
* Diseñar pensando en el crecimiento futuro (no definir límites arbitrarios de usuarios o tweets).

## 2. Entregables
### A. Código
* Sistema funcionando con las funcionalidades solicitadas.
* Código en C, organizado en `main` y librerías propias.

### B. Bitácora de Diseño (`BITACORA.md`)
Debe incluir:
* **Entidades:** Identificación de entidades necesarias.
* **Proyecciones:** Operaciones futuras probables y justificación.
* **Estructuras:** Estructuras elegidas para usuarios y tweets, con justificación.
* **Persistencia:** Formato elegido para guardar la información.
* **IA:** Registro de interacciones con IA (según `RULES.md`).
* **Decisiones:** Cualquier otra decisión relevante.

### C. Testing
* Hoja de pruebas con los casos obligatorios y al menos 2 casos propios.
* **Casos obligatorios:**
    1. Plataforma vacía.
    2. Usuario sin tweets.
    3. Búsqueda de un tweet inexistente.
    4. Eliminación del primer tweet.
    5. Eliminación del último tweet.
    6. Eliminación de un tweet intermedio.
    7. Intentar publicar/ver feed sin estar logueado.
    8. Cerrar y reabrir el programa (verificación de persistencia).
* **Casos adicionales:** Agregar al menos 2 casos propios que puedan romper el sistema.

## 3. Formato de Entrega
* **Git:**
    * Tag: `v1-fundamentos` en el último commit.
    * Rama: `release/v1-fundamentos` conteniendo todo lo entregado.
* **Zip:** `NOMBREDEGRUPO_TP_SPRINT1.zip` (sin carpetas `bin` y `obj`).
* **Plataforma:** Entrega en MIeL, incluyendo el link al repositorio de GitHub.
