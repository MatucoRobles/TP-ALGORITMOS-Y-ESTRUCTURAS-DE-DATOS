#include "../include/cwitter.h"

/* --- Implementación: Cola de Usuarios --- */

void inicializarColaUsuarios(ColaUsuarios* c) {
    c->frente = NULL;
    c->final = NULL;
}

int estaVaciaUsuarios(ColaUsuarios* c) {
    return (c->frente == NULL);
}

void encolarUsuario(ColaUsuarios* c, Usuario u) {
    NodoUsuario* nuevo = (NodoUsuario*)malloc(sizeof(NodoUsuario));
    if (nuevo == NULL) {
        perror("Error al asignar memoria para usuario");
        return;
    }
    nuevo->data = u;
    nuevo->siguiente = NULL;
    
    if (estaVaciaUsuarios(c)) {
        c->frente = nuevo;
    } else {
        c->final->siguiente = nuevo;
    }
    c->final = nuevo;
}

/* --- Implementación: Cola de Tweets --- */

void inicializarColaTweets(ColaTweets* c) {
    c->frente = NULL;
    c->final = NULL;
}

int estaVaciaTweets(ColaTweets* c) {
    return (c->frente == NULL);
}

void encolarTweet(ColaTweets* c, Tweet t) {
    NodoTweet* nuevo = (NodoTweet*)malloc(sizeof(NodoTweet));
    if (nuevo == NULL) {
        perror("Error al asignar memoria para tweet");
        return;
    }
    nuevo->data = t;
    nuevo->siguiente = NULL;
    
    if (estaVaciaTweets(c)) {
        c->frente = nuevo;
    } else {
        c->final->siguiente = nuevo;
    }
    c->final = nuevo;
}
