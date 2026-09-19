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

Usuario* buscarUsuario(ColaUsuarios* c, const char* nombre) {
    NodoUsuario* actual = c->frente;
    while (actual != NULL) {
        if (strcmp(actual->data.nombre_usuario, nombre) == 0) {
            return &(actual->data);
        }
        actual = actual->siguiente;
    }
    return NULL;
}

Usuario* autenticarUsuario(ColaUsuarios* c, const char* nombre, const char* clave) {
    Usuario* u = buscarUsuario(c, nombre);
    if (u != NULL && strcmp(u->clave, clave) == 0) {
        return u;
    }
    return NULL;
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

int generarSiguienteIdTweet(ColaTweets* c) {
    int max_id = 0;
    NodoTweet* actual = c->frente;
    while (actual != NULL) {
        if (actual->data.id > max_id) {
            max_id = actual->data.id;
        }
        actual = actual->siguiente;
    }
    return max_id + 1;
}

Tweet* buscarTweet(ColaTweets* c, int id, const char* autor) {
    NodoTweet* actual = c->frente;
    while (actual != NULL) {
        if (actual->data.id == id && strcmp(actual->data.autor, autor) == 0) {
            return &(actual->data);
        }
        actual = actual->siguiente;
    }
    return NULL;
}

int eliminarTweet(ColaTweets* c, int id, const char* autor) {
    if (estaVaciaTweets(c)) return 0;

    NodoTweet* actual = c->frente;
    NodoTweet* anterior = NULL;

    while (actual != NULL) {
        if (actual->data.id == id && strcmp(actual->data.autor, autor) == 0) {
            if (anterior == NULL) {
                c->frente = actual->siguiente;
                if (c->frente == NULL) c->final = NULL;
            } else {
                anterior->siguiente = actual->siguiente;
                if (actual->siguiente == NULL) c->final = anterior;
            }
            free(actual);
            return 1;
        }
        anterior = actual;
        actual = actual->siguiente;
    }
    return 0;
}
