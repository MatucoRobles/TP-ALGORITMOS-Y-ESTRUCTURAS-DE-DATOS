#include "include/cwitter.h"
#include <string.h>

void menuPrincipal(Usuario* logueado) {
    printf("\n--- Menú Cwitter ---\n");
    if (logueado == NULL) {
        printf("1. Registrarse\n");
        printf("2. Iniciar Sesión\n");
    } else {
        printf("Usuario actual: @%s\n", logueado->nombre_usuario);
        printf("3. Publicar Tweet (Paso 3.4)\n");
        printf("4. Ver Feed (Paso 3.7)\n");
        printf("8. Buscar Tweet\n");
        printf("6. Modificar Tweet\n");
        printf("7. Eliminar Tweet\n");
        printf("5. Cerrar Sesión\n");
    }
    printf("0. Salir\n");
    printf("Seleccione una opción: ");
}

void registrarUsuarioUI(ColaUsuarios* cola) {
    Usuario nuevo;
    printf("\n--- Registro de Usuario ---\n");
    printf("Nombre de usuario (sin espacios): ");

    // " %[^\n]" le dice a scanf que lea todo hasta que el usuario presione Enter,
    // permitiendo capturar la cadena completa aunque tenga espacios.
    scanf(" %[^\n]", nuevo.nombre_usuario);

    // strchr busca si hay algún caracter de espacio (' ') dentro del string
    if (strchr(nuevo.nombre_usuario, ' ') != NULL) {
        printf("Error: El nombre de usuario no puede contener espacios.\n");
        return;
    }

    if (buscarUsuario(cola, nuevo.nombre_usuario) != NULL) {
        printf("Error: El nombre de usuario ya existe.\n");
        return;
    }

    printf("Clave (sin espacios): ");
    scanf(" %[^\n]", nuevo.clave);

    if (strchr(nuevo.clave, ' ') != NULL) {
        printf("Error: La clave no puede contener espacios.\n");
        return;
    }

    encolarUsuario(cola, nuevo);
    printf("Usuario registrado exitosamente.\n");
}

void publicarTweetUI(ColaTweets* cola, Usuario* usuario) {
    Tweet nuevo;
    char buffer[MAX_TWEET + 2];
    printf("\n--- Publicar Tweet ---\n");
    printf("Contenido (máx 140 caracteres): ");
    
    /* Consumir el salto de línea anterior si existe */
    fgets(buffer, sizeof(buffer), stdin);
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) return;

    /* Eliminar el salto de línea de fgets */
    buffer[strcspn(buffer, "\n")] = 0;

    if (strlen(buffer) > MAX_TWEET) {
        printf("Error: El tweet supera los 140 caracteres.\n");
        return;
    }

    nuevo.id = generarSiguienteIdTweet(cola);
    strcpy(nuevo.autor, usuario->nombre_usuario);
    strcpy(nuevo.contenido, buffer);

    encolarTweet(cola, nuevo);
    printf("Tweet publicado con éxito (ID: %d).\n", nuevo.id);
}

void modificarTweetUI(ColaTweets* cola, Usuario* usuario) {
    int id;
    printf("\n--- Modificar Tweet ---\n");
    printf("Ingrese el ID del tweet a modificar: ");
    scanf("%d", &id);

    Tweet* t = buscarTweet(cola, id, usuario->nombre_usuario);
    if (t == NULL) {
        printf("Error: Tweet no encontrado o no autorizado.\n");
        return;
    }

    printf("Contenido actual: %s\n", t->contenido);
    printf("Nuevo contenido (máx 140 caracteres): ");
    
    char buffer[MAX_TWEET + 2];
    fgets(buffer, sizeof(buffer), stdin);
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) return;
    buffer[strcspn(buffer, "\n")] = 0;

    if (strlen(buffer) > MAX_TWEET) {
        printf("Error: El tweet supera los 140 caracteres.\n");
        return;
    }

    strcpy(t->contenido, buffer);
    printf("Tweet modificado con éxito.\n");
}

void eliminarTweetUI(ColaTweets* cola, Usuario* usuario) {
    int id;
    printf("\n--- Eliminar Tweet ---\n");
    printf("Ingrese el ID del tweet a eliminar: ");
    scanf("%d", &id);

    if (eliminarTweet(cola, id, usuario->nombre_usuario)) {
        printf("Tweet eliminado con éxito.\n");
    } else {
        printf("Error: Tweet no encontrado o no autorizado.\n");
    }
}

void buscarTweetUI(ColaTweets* cola) {
    char termino[MAX_TWEET];
    printf("\n--- Buscar Tweet ---\n");
    printf("Ingrese término de búsqueda (contenido o autor): ");
    scanf("%s", termino);

    buscarTweetsPorTermino(cola, termino);
}

Usuario* loginUI(ColaUsuarios* cola) {
    char nombre[MAX_USUARIO];
    char clave[MAX_CLAVE];
    printf("\n--- Inicio de Sesión ---\n");
    printf("Nombre de usuario: ");
    scanf("%s", nombre);
    printf("Clave: ");
    scanf("%s", clave);

    Usuario* u = autenticarUsuario(cola, nombre, clave);
    if (u != NULL) {
        printf("Bienvenido @%s!\n", u->nombre_usuario);
        return u;
    } else {
        printf("Error: Usuario o clave incorrectos.\n");
        return NULL;
    }
}

int main() {
    ColaUsuarios cola_usuarios;
    ColaTweets cola_tweets;
    Usuario* usuario_logueado = NULL;
    int opcion;

    /* Inicialización de estructuras */
    inicializarColaUsuarios(&cola_usuarios);
    inicializarColaTweets(&cola_tweets);
    cargarUsuarios(&cola_usuarios);
    cargarTweets(&cola_tweets);

    do {
        menuPrincipal(usuario_logueado);
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                if (usuario_logueado == NULL) registrarUsuarioUI(&cola_usuarios);
                else printf("Ya tienes una sesión iniciada.\n");
                break;
            case 2:
                if (usuario_logueado == NULL) usuario_logueado = loginUI(&cola_usuarios);
                else printf("Ya tienes una sesión iniciada.\n");
                break;
            case 3:
                if (usuario_logueado != NULL) {
                    publicarTweetUI(&cola_tweets, usuario_logueado);
                    guardarTweets(&cola_tweets);
                }
                else printf("Debes iniciar sesión para publicar.\n");
                break;
            case 4:
                mostrarFeed(&cola_tweets);
                break;
            case 8:
                buscarTweetUI(&cola_tweets);
                break;
            case 6:
                if (usuario_logueado != NULL) {
                    modificarTweetUI(&cola_tweets, usuario_logueado);
                    guardarTweets(&cola_tweets);
                }
                else printf("Debes iniciar sesión para modificar.\n");
                break;
            case 7:
                if (usuario_logueado != NULL) {
                    eliminarTweetUI(&cola_tweets, usuario_logueado);
                    guardarTweets(&cola_tweets);
                }
                else printf("Debes iniciar sesión para eliminar.\n");
                break;
            case 5:
                if (usuario_logueado != NULL) {
                    printf("Sesión cerrada para @%s.\n", usuario_logueado->nombre_usuario);
                    usuario_logueado = NULL;
                } else printf("No hay sesión activa.\n");
                break;
            case 0:
                guardarUsuarios(&cola_usuarios);
                guardarTweets(&cola_tweets);
                printf("Datos guardados. Saliendo de Cwitter...\n");
                break;
            default:
                printf("Opción no válida o funcionalidad en desarrollo.\n");
        }
    } while (opcion != 0);

    /* TODO: Liberar memoria de las colas antes de salir */

    return 0;
}
