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

void mostrarFeed(ColaTweets* c) {
    if (estaVaciaTweets(c)) {
        printf("\nEl feed está vacío.\n");
        return;
    }

    printf("\n--- Feed Global ---\n");
    NodoTweet* actual = c->frente;
    while (actual != NULL) {
        printf("[%d] @%s: %s\n", actual->data.id, actual->data.autor, actual->data.contenido);
        actual = actual->siguiente;
    }
}

void buscarTweetsPorTermino(ColaTweets* c, const char* termino) {
    printf("\n--- Resultados de búsqueda: '%s' ---\n", termino);
    NodoTweet* actual = c->frente;
    int encontrados = 0;
    while (actual != NULL) {
        if (strstr(actual->data.contenido, termino) != NULL || 
            strcmp(actual->data.autor, termino) == 0) {
            printf("[%d] @%s: %s\n", actual->data.id, actual->data.autor, actual->data.contenido);
            encontrados = 1;
        }
        actual = actual->siguiente;
    }
    if (!encontrados) {
        printf("No se encontraron tweets que coincidan.\n");
    }
}

void cargarUsuarios(ColaUsuarios* c) {
    FILE* f = fopen("usuarios.txt", "r");
    if (!f) return;
    Usuario u;
    while (fscanf(f, "%[^;];%s\n", u.nombre_usuario, u.clave) == 2) {
        encolarUsuario(c, u);
    }
    fclose(f);
}

void guardarUsuarios(ColaUsuarios* c) {
    FILE* f = fopen("usuarios.txt", "w");
    if (!f) return;
    NodoUsuario* actual = c->frente;
    while (actual != NULL) {
        fprintf(f, "%s;%s\n", actual->data.nombre_usuario, actual->data.clave);
        actual = actual->siguiente;
    }
    fclose(f);
}

void cargarTweets(ColaTweets* c) {
    FILE* f = fopen("tweets.txt", "r");
    if (!f) return;
    Tweet t;
    while (fscanf(f, "%d;%[^;];%[^\n]\n", &t.id, t.autor, t.contenido) == 3) {
        encolarTweet(c, t);
    }
    fclose(f);
}

void guardarTweets(ColaTweets* c) {
    FILE* f = fopen("tweets.txt", "w");
    if (!f) return;
    NodoTweet* actual = c->frente;
    while (actual != NULL) {
        fprintf(f, "%d;%s;%s\n", actual->data.id, actual->data.autor, actual->data.contenido);
        actual = actual->siguiente;
    }
    fclose(f);
}
