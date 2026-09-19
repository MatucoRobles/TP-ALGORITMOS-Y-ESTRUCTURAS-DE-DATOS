# Plan de Pruebas - Cwitter (Sprint 1)

Este documento detalla los casos de prueba diseñados para validar las funcionalidades de Cwitter. De acuerdo con las `RULES.md`, estas pruebas se definen **antes** de la implementación.

---

## 1. Casos de Prueba Obligatorios

| ID | Situación a probar | Operación realizada | Resultado esperado | Salida obtenida |
|:---|:---|:---|:---|:---|
| **CP-01** | Plataforma vacía | Iniciar el programa por primera vez sin archivos de datos. | El programa inicia correctamente, muestra el menú y el feed indica que no hay tweets. | (Pendiente) |
| **CP-02** | Usuario sin tweets | Loguear un usuario nuevo y seleccionar "Ver mi perfil" o filtrar sus tweets. | El sistema informa que el usuario aún no ha realizado publicaciones. | (Pendiente) |
| **CP-03** | Búsqueda de tweet inexistente | Buscar una palabra o autor que no está en la base de datos. | El sistema informa que no se encontraron coincidencias para la búsqueda. | (Pendiente) |
| **CP-04** | Eliminación del primer tweet | Eliminar el tweet que aparece primero en el feed (el más reciente). | El tweet desaparece y el que era segundo pasa a ser el primero. | (Pendiente) |
| **CP-05** | Eliminación del último tweet | Eliminar el tweet que aparece al final del feed (el más antiguo). | El tweet desaparece y el anterior queda como el nuevo límite de la lista. | (Pendiente) |
| **CP-06** | Eliminación de tweet intermedio | Eliminar un tweet que tiene otros antes y después en la lista. | Los punteros se reasignan correctamente; el tweet desaparece sin romper la cadena. | (Pendiente) |
| **CP-07** | Acción sin login | Intentar publicar un tweet o ver el feed sin haber iniciado sesión. | El sistema deniega la acción y solicita al usuario loguearse primero. | (Pendiente) |
| **CP-08** | Persistencia | Registrar un usuario, publicar un tweet, cerrar el programa y volver a abrirlo. | El usuario puede loguearse de nuevo y el tweet publicado sigue apareciendo en el feed. | (Pendiente) |

---

## 2. Casos de Prueba Adicionales (Propios)

Estos casos buscan probar los límites o robustez del sistema.

| ID | Situación a probar | Operación realizada | Resultado esperado | Salida obtenida |
|:---|:---|:---|:---|:---|
| **CP-09** | Límite de caracteres en Tweet | Intentar publicar un mensaje con más de 140 caracteres. | El sistema debe truncar el mensaje a 140 o rechazar la publicación con un error. | (Pendiente) |
| **CP-10** | Registro de usuario duplicado | Intentar crear un usuario con un `nombre_usuario` que ya existe. | El sistema informa que el nombre no está disponible y solicita uno diferente. | (Pendiente) |

---

## 3. Notas de Validación
*   Las pruebas se considerarán exitosas solo si no hay fugas de memoria (verificado con herramientas de análisis si es posible).
*   Se debe verificar que los IDs de los tweets sigan siendo únicos y secuenciales tras múltiples eliminaciones y reinicios.
