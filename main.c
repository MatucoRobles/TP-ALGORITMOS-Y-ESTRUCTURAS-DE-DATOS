#include "include/cwitter.h"

int main() {
    ColaUsuarios cola_usuarios;
    ColaTweets cola_tweets;
    char *usuario_logueado = NULL;

    /* Inicialización de estructuras */
    inicializarColaUsuarios(&cola_usuarios);
    inicializarColaTweets(&cola_tweets);

    printf("--- Bienvenido a Cwitter ---\n");
    printf("Sistema iniciado con estructuras de Cola.\n");

    /* TODO: Cargar datos desde persistencia */
    /* TODO: Implementar menú principal y lógica de flujo */

    return 0;
}
