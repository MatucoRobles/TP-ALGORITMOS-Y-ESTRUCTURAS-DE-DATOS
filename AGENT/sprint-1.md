# Sprint 1: Cwitter - Fundamentos

Este archivo detalla los pasos estructurados, objetivos, requerimientos y entregables para el primer sprint del proyecto Cwitter.

## Paso 1: Planificación y Diseño (Bitácora de Diseño)
* **1.1.** Identificar y definir las entidades necesarias para el sistema Cwitter (usuarios, tweets).
* **1.2.** Proyectar operaciones futuras probables y justificar su viabilidad en la arquitectura planteada.
* **1.3.** Elegir y justificar el diseño de las estructuras de datos para usuarios y tweets utilizando **Colas**, asegurando que no se definan límites arbitrarios de capacidad.
* **1.4.** Determinar y justificar el formato elegido para la persistencia de la información (por ejemplo, archivos de texto o binarios) entre ejecuciones.
* **1.5.** Documentar en `BITACORA.md` el planteo inicial de cada integrante, las interacciones obligatorias con IA (mínimo 2), los errores/fallas de la IA corregidos y las decisiones de diseño adoptadas.

## Paso 2: Diseño y Preparación de Pruebas (Testing)
* **2.1.** Crear y estructurar la hoja de pruebas en `TESTS.md` antes de comenzar la implementación del código.
* **2.2.** Definir y documentar el caso obligatorio 1: Comportamiento con la plataforma vacía.
* **2.3.** Definir y documentar el caso obligatorio 2: Comportamiento de un usuario que no posee tweets en su **cola**.
* **2.4.** Definir y documentar el caso obligatorio 3: Búsqueda de un tweet que no existe en el sistema.
* **2.5.** Definir y documentar el caso obligatorio 4: Eliminación del primer tweet de la **cola** (Frente).
* **2.6.** Definir y documentar el caso obligatorio 5: Eliminación del último tweet de la **cola** (Final).
* **2.7.** Definir y documentar el caso obligatorio 6: Eliminación de un tweet en posición intermedia de la **cola**.
* **2.8.** Definir y documentar el caso obligatorio 7: Intentar publicar un tweet o visualizar el feed sin haber iniciado sesión.
* **2.9.** Definir y documentar el caso obligatorio 8: Cerrar y reabrir el programa para verificar la correcta persistencia de la información.
* **2.10.** Diseñar e incorporar al menos 2 casos de prueba adicionales propios orientados a probar los límites del sistema o posibles fallas críticas.

## Paso 3: Desarrollo de la Plataforma Cwitter (Implementación con Colas)
* **3.1.** Configurar la estructura de archivos en ANSI C dividida en `main.c`, `include/cwitter.h` y `src/cwitter.c`.
* **3.2.** Implementar la estructura de **Cola** dinámica para el registro de nuevos usuarios, asegurando la gestión de frente y final sin límites fijos.
* **3.3.** Implementar la funcionalidad de inicio de sesión (login) y cierre de sesión (logout) recorriendo la **cola** de usuarios.
* **3.4.** Implementar la funcionalidad de publicación de tweets insertando al final de la **cola** de tweets global, con un límite estricto de hasta 140 caracteres.
* **3.5.** Implementar la funcionalidad de modificación de tweets publicados por el usuario activo dentro de la **cola**.
* **3.6.** Implementar la funcionalidad de eliminación de tweets específicos de la **cola**, manteniendo la integridad de los punteros del frente y el final.
* **3.7.** Implementar la funcionalidad de consulta del feed global (visualizar todos los tweets recorriendo la **cola**).
* **3.8.** Implementar la funcionalidad de búsqueda de tweets (por término, contenido o autor) sobre la **cola**.
* **3.9.** Implementar la persistencia de datos (carga de usuarios y tweets en sus respectivas **colas** al iniciar el programa; guardado automático al realizar cambios o cerrar la sesión).

## Paso 4: Validación y Ejecución de Pruebas
* **4.1.** Compilar el sistema asegurando compatibilidad multiplataforma y ausencia de warnings o pérdidas de memoria.
* **4.2.** Ejecutar los casos de prueba diseñados en el Paso 2 sobre la aplicación implementada.
* **4.3.** Completar el archivo `TESTS.md` con los resultados obtenidos en cada caso de prueba.

## Paso 5: Entrega del Sprint 1
* **5.1.** Realizar una limpieza profunda del espacio de trabajo eliminando las carpetas temporales de compilación `bin` y `obj`.
* **5.2.** Crear y posicionarse en la rama de Git denominada `release/v1-fundamentos`.
* **5.3.** Etiquetar el último commit de la entrega con el tag `v1-fundamentos`.
* **5.4.** Comprimir el proyecto con el nombre `NOMBREDEGRUPO_TP_SPRINT1.zip` (asegurando no incluir carpetas de compilación).
* **5.5.** Subir la entrega a la plataforma MIeL e incluir en el mensaje de entrega el enlace al repositorio privado de GitHub.
