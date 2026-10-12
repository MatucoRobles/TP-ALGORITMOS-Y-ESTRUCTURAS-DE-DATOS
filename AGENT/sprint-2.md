# Sprint 2: Cwitter - Procesamiento y Verificación

Este archivo detalla los pasos estructurados para el segundo sprint, enfocado en la integración con servicios externos y el procesamiento avanzado de datos.

## Paso 1: Planificación y Diseño (Bitácora de Diseño)
* [ ] **1.1.** Identificar la "nueva herramienta" (Estructura de Datos) necesaria para permitir la navegación hacia atrás en el feed y el ranking.
* [ ] **1.2.** Definir la lógica de integración con `FameCheck` (Simulación o uso de `ejemplo_api.c`).
* [ ] **1.3.** Diseñar el algoritmo de ordenamiento para el feed (Verificados primero, luego cronológico).
* [ ] **1.4.** Documentar en `BITACORA.md` la elección de estructuras, justificando por qué son mejores que otras opciones conocidas.
* [ ] **1.5.** Registrar en la bitácora las interacciones con IA, fallos encontrados y decisiones de diseño.

## Paso 2: Diseño de Pruebas (Testing)
* [ ] **2.1.** Actualizar `TESTS.md` con los casos obligatorios del Sprint 2.
* [ ] **2.2.** Definir caso: Usuario que se verifica exitosamente vs. usuario que no.
* [ ] **2.3.** Definir caso: Reporte de publicación cuando el servicio externo está caído (verificar log).
* [ ] **2.4.** Definir caso: Top 5 con menos de 5 usuarios registrados.
* [ ] **2.5.** Definir caso: Top 5 con empate en cantidad de publicaciones.
* [ ] **2.6.** Definir caso: Feed mixto (verificados y no verificados) para validar el orden prioritario.
* [ ] **2.7.** Definir caso: Navegación del feed (Avanzar, retroceder varias veces, llegar al final/inicio).
* [ ] **2.8.** Definir caso: Persistencia de la verificación tras reiniciar el programa.
* [ ] **2.9.** Diseñar 2 casos de prueba adicionales propios.

## Paso 3: Desarrollo y Funcionalidades
* [x] **3.1.** Implementar la consulta al servicio externo `FameCheck` durante el registro/login.
* [x] **3.2.** Implementar el reporte automático de publicaciones para usuarios verificados.
* [x] **3.3.** Crear el sistema de Logs para fallos del servicio externo.
* [x] **3.4.** Implementar la lógica del "Top 5" de usuarios verificados (procesamiento y ordenamiento).
* [x] **3.5.** Refactorizar la visualización del feed para aplicar la prioridad de cuentas verificadas.
* [x] **3.6.** Implementar el modo de navegación interactiva (uno por vez, adelante y atrás).
* [ ] **3.7.** Asegurar que la persistencia incluya el estado de "verificado" de los usuarios.

## Paso 4: Validación y Calidad
* [ ] **4.1.** Verificar que no existan fugas de memoria (especialmente en la nueva estructura de navegación).
* [ ] **4.2.** Ejecutar la suite completa de pruebas de `TESTS.md`.
* [ ] **4.3.** Asegurar que el código siga siendo ANSI C y esté dividido correctamente.

## Paso 5: Entrega del Sprint 2
* [ ] **5.1.** Limpiar carpetas `bin` y `obj`.
* [ ] **5.2.** Crear/Posicionarse en la rama `release/v2-procesamiento`.
* [ ] **5.3.** Etiquetar el commit final con el tag `v2-procesamiento`.
* [ ] **5.4.** Comprimir como `NOMBREDEGRUPO_TP_SPRINT2.zip`.
