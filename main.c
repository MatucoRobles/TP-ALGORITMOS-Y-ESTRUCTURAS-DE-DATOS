#include "include/cwitter.h"

void menuPrincipal() {
    printf("\n--- Menú Cwitter ---\n");
    printf("1. Registrarse\n");
    printf("2. Iniciar Sesión\n");
    printf("0. Salir\n");
    printf("Seleccione una opción: ");
}

void registrarUsuarioUI(ColaUsuarios* cola) {
    Usuario nuevo;
    printf("\n--- Registro de Usuario ---\n");
    printf("Nombre de usuario: ");
    scanf("%s", nuevo.nombre_usuario);

    if (buscarUsuario(cola, nuevo.nombre_usuario) != NULL) {
        printf("Error: El nombre de usuario ya existe.\n");
        return;
    }

    printf("Clave: ");
    scanf("%s", nuevo.clave);

    encolarUsuario(cola, nuevo);
    printf("Usuario registrado exitosamente.\n");
}

int main() {
    ColaUsuarios cola_usuarios;
    ColaTweets cola_tweets;
    int opcion;

    /* Inicialización de estructuras */
    inicializarColaUsuarios(&cola_usuarios);
    inicializarColaTweets(&cola_tweets);

    do {
        menuPrincipal();
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                registrarUsuarioUI(&cola_usuarios);
                break;
            case 2:
                printf("Funcionalidad de Login en desarrollo (Paso 3.3).\n");
                break;
            case 0:
                printf("Saliendo de Cwitter...\n");
                break;
            default:
                printf("Opción no válida.\n");
        }
    } while (opcion != 0);

    /* TODO: Liberar memoria de las colas antes de salir */

    return 0;
}
