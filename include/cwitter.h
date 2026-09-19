#ifndef CWITTER_H
#define CWITTER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Definiciones de constantes */
#define MAX_USUARIO 50
#define MAX_CLAVE 50
#define MAX_TWEET 140

/* --- Entidad: Usuario --- */
typedef struct {
    char nombre_usuario[MAX_USUARIO];
    char clave[MAX_CLAVE];
} Usuario;

typedef struct NodoUsuario {
    Usuario data;
    struct NodoUsuario* siguiente;
} NodoUsuario;

typedef struct {
    NodoUsuario* frente;
    NodoUsuario* final;
} ColaUsuarios;

/* --- Entidad: Tweet --- */
typedef struct {
    int id;
    char autor[MAX_USUARIO];
    char contenido[MAX_TWEET + 1];
} Tweet;

typedef struct NodoTweet {
    Tweet data;
    struct NodoTweet* siguiente;
} NodoTweet;

typedef struct {
    NodoTweet* frente;
    NodoTweet* final;
} ColaTweets;

/* --- Funciones de Gestión de Usuarios (Cola) --- */
void inicializarColaUsuarios(ColaUsuarios* c);
int estaVaciaUsuarios(ColaUsuarios* c);
void encolarUsuario(ColaUsuarios* c, Usuario u);
/* Operaciones adicionales: buscar, login, persistencia */

/* --- Funciones de Gestión de Tweets (Cola) --- */
void inicializarColaTweets(ColaTweets* c);
int estaVaciaTweets(ColaTweets* c);
void encolarTweet(ColaTweets* c, Tweet t);
/* Operaciones adicionales: eliminar, mostrar feed, buscar, persistencia */

#endif /* CWITTER_H */
