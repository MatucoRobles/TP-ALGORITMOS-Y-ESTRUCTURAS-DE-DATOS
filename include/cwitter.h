#ifndef CWITTER_H
#define CWITTER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* Definiciones de constantes */
#define MAX_USUARIO 50
#define MAX_CLAVE 50
#define MAX_TWEET 140

/* --- Entidad: Usuario --- */
typedef struct {
    char nombre_usuario[MAX_USUARIO];
    char clave[MAX_CLAVE];
    int es_verificado; /* 0: No, 1: Sí */
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
Usuario* buscarUsuario(ColaUsuarios* c, const char* nombre);
Usuario* autenticarUsuario(ColaUsuarios* c, const char* nombre, const char* clave);
int esUsuarioVerificado(ColaUsuarios* c, const char* nombre);
/* Operaciones adicionales: persistencia */

/* --- Funciones de Gestión de Tweets (Cola) --- */
void inicializarColaTweets(ColaTweets* c);
int estaVaciaTweets(ColaTweets* c);
void encolarTweet(ColaTweets* c, Tweet t);
int generarSiguienteIdTweet(ColaTweets* c);
Tweet* buscarTweet(ColaTweets* c, int id, const char* autor);
int eliminarTweet(ColaTweets* c, int id, const char* autor);
void mostrarFeed(ColaTweets* tweets, ColaUsuarios* usuarios);
void buscarTweetsPorTermino(ColaTweets* c, const char* termino);
void cargarUsuarios(ColaUsuarios* c);
void guardarUsuarios(ColaUsuarios* c);
void liberarColaUsuarios(ColaUsuarios* c);
void cargarTweets(ColaTweets* c);
void guardarTweets(ColaTweets* c);
void liberarColaTweets(ColaTweets* c);

/* --- Funciones de Servicio Externo (FameCheck) y Logs --- */
int consultarVerificacionFameCheck(const char* nombre_usuario);
int reportarPublicacionFameCheck(const char* nombre_usuario, int tweet_id);
void registrarErrorServicio(const char* mensaje);
void mostrarLogsServicio(void);
void configurarDisponibilidadFameCheck(int disponible);
int obtenerDisponibilidadFameCheck(void);

/* --- Entidad y Funciones: Ranking Top 5 (Lista Simple Ordenada) --- */
typedef struct NodoRanking {
    char nombre_usuario[MAX_USUARIO];
    int cantidad_tweets;
    struct NodoRanking* siguiente;
} NodoRanking;

NodoRanking* insertarOrdenadoRanking(NodoRanking* cabeza, const char* nombre_usuario, int cantidad_tweets);
int contarTweetsUsuario(ColaTweets* cola_tweets, const char* nombre_usuario);
void mostrarTop5Verificados(ColaUsuarios* cola_usuarios, ColaTweets* cola_tweets);
void liberarRanking(NodoRanking* cabeza);

/* --- Entidad y Funciones: Feed Interactivo / Modo Historia (Lista Doblemente Enlazada) --- */
typedef struct NodoTweetDoble {
    Tweet data;
    int autor_es_verificado;
    struct NodoTweetDoble* anterior;
    struct NodoTweetDoble* siguiente;
} NodoTweetDoble;

typedef struct {
    NodoTweetDoble* cabeza;
    NodoTweetDoble* cola;
    int cantidad;
} ListaDobleFeed;

void inicializarListaDoble(ListaDobleFeed* lista);
void agregarTweetListaDoble(ListaDobleFeed* lista, Tweet t, int es_verificado);
ListaDobleFeed* crearFeedInteractivo(ColaTweets* cola_tweets, ColaUsuarios* cola_usuarios);
void liberarFeedInteractivo(ListaDobleFeed* lista);
void navegarFeedInteractivo(ColaTweets* cola_tweets, ColaUsuarios* cola_usuarios);

#endif /* CWITTER_H */
