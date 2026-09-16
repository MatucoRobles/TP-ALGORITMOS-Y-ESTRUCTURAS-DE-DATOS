# Reglas del Trabajo Práctico (AyED)

Este documento resume las normas de trabajo, desarrollo y entrega basadas en la modalidad del curso.

## 1. Git y GitHub
* **Repositorio:** Privado. Integrantes del grupo y profesores como colaboradores.
* **Commits:** Deben ser frecuentes y descriptivos. No se permite un único commit al final del sprint.
* **Ramas:** Uso de ramas para separar desarrollo de código estable (basado en GitFlow).
* **Identificación de Sprints:**
    * **Tags:** `v1-fundamentos`, `v2-procesamiento`, `v3-final`.
    * **Ramas:** Se debe usar su rama de `release` correspondiente.

## 2. Bitácora de Diseño
* **Registro de Decisiones:** Debe registrarse el problema, alternativas, elección y justificación, observaciones y posibles modificaciones posteriores para cada decisión importante en cada sprint.
* **Uso de IA:**
    * **Registro de interacciones:** Al menos 2 por sprint (prompt, resumen propio de la respuesta, evaluación, decisión final).
    * **Respuestas incorrectas/subóptimas:** Registrar al menos un caso donde la IA falló, qué hizo darse cuenta del problema y la solución adoptada.
    * **Planteo previo:** Antes de decidir algo importante, cada integrante debe escribir brevemente su planteo inicial y dudas.

## 3. Testing
* Los casos de prueba deben pensarse *antes* de implementar.
* Para cada caso de prueba, registrar:
    1. Situación a probar.
    2. Operación realizada.
    3. Resultado esperado.
    4. Salida obtenida (a partir del sprint 2, completando los casos del sprint 1).

## 4. Requisitos de Código y Desarrollo
* **Lenguaje:** ANSI C (compatibilidad multiplataforma).
* **Eficiencia:**
    * Sin uso innecesario de vectores/matrices auxiliares.
    * Sin archivos temporales o auxiliares innecesarios.
    * Optimizar ciclos de procesador y recorridos de archivos.
* **Seguridad y Prolijidad:**
    * Sin accesos a memoria no permitidos.
    * Sin dejar archivos abiertos.
    * Código dividido en funciones, con nombres descriptivos y significativos para variables.
* **Archivos:** No mezclar funciones de archivos de texto con funciones de archivos binarios.

## 5. Entrega
* **Formato Zip:** `NOMBREDEGRUPO_TP_SPRINTX.zip`.
* **Limpieza:** Eliminar carpetas `bin` y `obj`.
* **Miel:** Incluir la URL al repositorio de GitHub en el mensaje de entrega.
