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

int esUsuarioVerificado(ColaUsuarios* c, const char* nombre) {
    Usuario* u = buscarUsuario(c, nombre);
    return (u != NULL && u->es_verificado == 1);
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

void mostrarFeed(ColaTweets* tweets, ColaUsuarios* usuarios) {
    if (estaVaciaTweets(tweets)) {
        printf("\nEl feed está vacío.\n");
        return;
    }

    printf("\n--- Feed Global (Prioridad: Verificados) ---\n");

    /* Algoritmo de dos pasadas (Sprint 2 - Paso 3.5) */
    /* Pasada 1: Tweets de autores verificados */
    NodoTweet* actual = tweets->frente;
    while (actual != NULL) {
        if (esUsuarioVerificado(usuarios, actual->data.autor)) {
            printf("[%d] @%s [✓]: %s\n", actual->data.id, actual->data.autor, actual->data.contenido);
        }
        actual = actual->siguiente;
    }

    /* Pasada 2: Tweets de autores no verificados */
    actual = tweets->frente;
    while (actual != NULL) {
        if (!esUsuarioVerificado(usuarios, actual->data.autor)) {
            printf("[%d] @%s: %s\n", actual->data.id, actual->data.autor, actual->data.contenido);
        }
        actual = actual->siguiente;
    }
    printf("-------------------------------------------\n");
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
    char linea[MAX_USUARIO + MAX_CLAVE + 20];
    Usuario u;
    while (fgets(linea, sizeof(linea), f) != NULL) {
        linea[strcspn(linea, "\r\n")] = '\0';
        if (strlen(linea) == 0) continue;
        u.es_verificado = 0;
        int campos = sscanf(linea, "%[^;];%[^;];%d", u.nombre_usuario, u.clave, &u.es_verificado);
        if (campos >= 2) {
            encolarUsuario(c, u);
        }
    }
    fclose(f);
}

void guardarUsuarios(ColaUsuarios* c) {
    FILE* f = fopen("usuarios.txt", "w");
    if (!f) return;
    NodoUsuario* actual = c->frente;
    while (actual != NULL) {
        fprintf(f, "%s;%s;%d\n", actual->data.nombre_usuario, actual->data.clave, actual->data.es_verificado);
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

/* --- Implementación: Servicio Externo (FameCheck) y Logs --- */

static int famecheck_disponible = 1;

void configurarDisponibilidadFameCheck(int disponible) {
    famecheck_disponible = disponible;
}

int obtenerDisponibilidadFameCheck(void) {
    return famecheck_disponible;
}

int consultarVerificacionFameCheck(const char* nombre_usuario) {
    if (!famecheck_disponible) {
        char msg[200];
        sprintf(msg, "ERROR: Fallo al consultar verificacion de @%s - Servicio FameCheck no disponible", nombre_usuario);
        registrarErrorServicio(msg);
        return 0;
    }

    /* Simulación: Algunos nombres son VIP por defecto */
    const char* vips[] = {"messi", "elonmusk", "billgates", "maradona", "ladygaga"};
    int i;
    for (i = 0; i < 5; i++) {
        if (strcmp(nombre_usuario, vips[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

int reportarPublicacionFameCheck(const char* nombre_usuario, int tweet_id) {
    /* Fallo si el servicio está caído o por fallo aleatorio (10% de probabilidad) */
    if (!famecheck_disponible || (rand() % 10 == 0)) {
        char msg[200];
        sprintf(msg, "ERROR: No se pudo reportar publicacion de @%s (Tweet ID: %d) - Servicio FameCheck no disponible", nombre_usuario, tweet_id);
        registrarErrorServicio(msg);
        return 0; /* Fallo */
    }
    return 1; /* Éxito */
}

void registrarErrorServicio(const char* mensaje) {
    FILE* f = fopen("service_errors.log", "a");
    if (!f) return;
    time_t ahora = time(NULL);
    struct tm* t = localtime(&ahora);
    char timestamp[32];
    if (t != NULL) {
        strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", t);
        fprintf(f, "[%s] %s\n", timestamp, mensaje);
    } else {
        fprintf(f, "[LOG] %s\n", mensaje);
    }
    fclose(f);
}

void mostrarLogsServicio(void) {
    FILE* f = fopen("service_errors.log", "r");
    if (!f) {
        printf("\nNo hay errores registrados en service_errors.log (el archivo no existe o esta vacio).\n");
        return;
    }
    printf("\n--- Registro de Errores del Servicio (service_errors.log) ---\n");
    char linea[300];
    int contador = 0;
    while (fgets(linea, sizeof(linea), f) != NULL) {
        printf("%s", linea);
        contador++;
    }
    if (contador == 0) {
        printf("El archivo de logs esta vacio.\n");
    }
    printf("--- Fin de Logs (%d registros encontrados) ---\n", contador);
    fclose(f);
}

/* --- Implementación: Ranking Top 5 (Lista Simple con Inserción Ordenada) --- */

NodoRanking* insertarOrdenadoRanking(NodoRanking* cabeza, const char* nombre_usuario, int cantidad_tweets) {
    NodoRanking* nuevo = (NodoRanking*)malloc(sizeof(NodoRanking));
    if (!nuevo) {
        perror("Error al asignar memoria para nodo de ranking");
        return cabeza;
    }
    strcpy(nuevo->nombre_usuario, nombre_usuario);
    nuevo->cantidad_tweets = cantidad_tweets;
    nuevo->siguiente = NULL;

    /* Si la lista está vacía o el nuevo tiene más tweets que el primero */
    if (cabeza == NULL || cantidad_tweets > cabeza->cantidad_tweets) {
        nuevo->siguiente = cabeza;
        return nuevo;
    }

    /* Recorrer hasta encontrar la posición adecuada (mantiene orden estable en empate) */
    NodoRanking* actual = cabeza;
    while (actual->siguiente != NULL && actual->siguiente->cantidad_tweets >= cantidad_tweets) {
        actual = actual->siguiente;
    }

    nuevo->siguiente = actual->siguiente;
    actual->siguiente = nuevo;
    return cabeza;
}

int contarTweetsUsuario(ColaTweets* cola_tweets, const char* nombre_usuario) {
    int contador = 0;
    NodoTweet* actual = cola_tweets->frente;
    while (actual != NULL) {
        if (strcmp(actual->data.autor, nombre_usuario) == 0) {
            contador++;
        }
        actual = actual->siguiente;
    }
    return contador;
}

void mostrarTop5Verificados(ColaUsuarios* cola_usuarios, ColaTweets* cola_tweets) {
    NodoRanking* ranking = NULL;

    /* Filtrar usuarios verificados e insertarlos ordenados por cantidad de tweets */
    NodoUsuario* actual_u = cola_usuarios->frente;
    while (actual_u != NULL) {
        if (actual_u->data.es_verificado) {
            int cant = contarTweetsUsuario(cola_tweets, actual_u->data.nombre_usuario);
            ranking = insertarOrdenadoRanking(ranking, actual_u->data.nombre_usuario, cant);
        }
        actual_u = actual_u->siguiente;
    }

    if (ranking == NULL) {
        printf("\nNo hay usuarios verificados registrados para generar el ranking.\n");
        return;
    }

    printf("\n--- Top 5 Usuarios Verificados con Mayor Actividad ---\n");
    NodoRanking* actual_r = ranking;
    int posicion = 1;
    while (actual_r != NULL && posicion <= 5) {
        printf("%d. @%s - %d tweet(s)\n", posicion, actual_r->nombre_usuario, actual_r->cantidad_tweets);
        actual_r = actual_r->siguiente;
        posicion++;
    }
    printf("------------------------------------------------------\n");

    /* Liberación de memoria de la lista simple ordenada */
    liberarRanking(ranking);
}

void liberarRanking(NodoRanking* cabeza) {
    while (cabeza != NULL) {
        NodoRanking* temp = cabeza;
        cabeza = cabeza->siguiente;
        free(temp);
    }
}

/* --- Implementación: Feed Interactivo / Modo Historia (Lista Doblemente Enlazada) --- */

void inicializarListaDoble(ListaDobleFeed* lista) {
    lista->cabeza = NULL;
    lista->cola = NULL;
    lista->cantidad = 0;
}

void agregarTweetListaDoble(ListaDobleFeed* lista, Tweet t, int es_verificado) {
    NodoTweetDoble* nuevo = (NodoTweetDoble*)malloc(sizeof(NodoTweetDoble));
    if (!nuevo) {
        perror("Error al asignar memoria para nodo doble");
        return;
    }
    nuevo->data = t;
    nuevo->autor_es_verificado = es_verificado;
    nuevo->siguiente = NULL;
    nuevo->anterior = lista->cola;

    if (lista->cabeza == NULL) {
        lista->cabeza = nuevo;
    } else {
        lista->cola->siguiente = nuevo;
    }
    lista->cola = nuevo;
    lista->cantidad++;
}

ListaDobleFeed* crearFeedInteractivo(ColaTweets* cola_tweets, ColaUsuarios* cola_usuarios) {
    ListaDobleFeed* lista = (ListaDobleFeed*)malloc(sizeof(ListaDobleFeed));
    if (!lista) return NULL;
    inicializarListaDoble(lista);

    /* Pasada 1: Tweets de autores verificados (prioridad) */
    NodoTweet* actual = cola_tweets->frente;
    while (actual != NULL) {
        if (esUsuarioVerificado(cola_usuarios, actual->data.autor)) {
            agregarTweetListaDoble(lista, actual->data, 1);
        }
        actual = actual->siguiente;
    }

    /* Pasada 2: Tweets de autores no verificados */
    actual = cola_tweets->frente;
    while (actual != NULL) {
        if (!esUsuarioVerificado(cola_usuarios, actual->data.autor)) {
            agregarTweetListaDoble(lista, actual->data, 0);
        }
        actual = actual->siguiente;
    }

    return lista;
}

void liberarFeedInteractivo(ListaDobleFeed* lista) {
    if (!lista) return;
    NodoTweetDoble* actual = lista->cabeza;
    while (actual != NULL) {
        NodoTweetDoble* temp = actual;
        actual = actual->siguiente;
        free(temp);
    }
    lista->cabeza = NULL;
    lista->cola = NULL;
    lista->cantidad = 0;
}

void navegarFeedInteractivo(ColaTweets* cola_tweets, ColaUsuarios* cola_usuarios) {
    if (estaVaciaTweets(cola_tweets)) {
        printf("\nEl feed está vacío. No hay publicaciones para navegar en Modo Historia.\n");
        return;
    }

    ListaDobleFeed* feed = crearFeedInteractivo(cola_tweets, cola_usuarios);
    if (!feed || feed->cantidad == 0) {
        printf("\nNo hay tweets disponibles para navegar.\n");
        if (feed) {
            liberarFeedInteractivo(feed);
            free(feed);
        }
        return;
    }

    NodoTweetDoble* actual = feed->cabeza;
    int indice = 1;
    char comando;

    printf("\n=== Modo Historia: Navegación Interactiva (Lista Doblemente Enlazada) ===\n");
    printf("Controles: [S] Siguiente | [A] Anterior | [X] Salir\n");

    while (actual != NULL) {
        printf("\n==========================================================\n");
        printf("[Tweet %d de %d]\n", indice, feed->cantidad);
        printf("Autor: @%s%s\n", actual->data.autor, actual->autor_es_verificado ? " [✓ Verificado]" : "");
        printf("Tweet ID: %d\n", actual->data.id);
        printf("Contenido: %s\n", actual->data.contenido);
        printf("==========================================================\n");
        printf("Navegar ([S] Siguiente / [A] Anterior / [X] Salir): ");

        if (scanf(" %c", &comando) != 1) break;

        if (comando == 'S' || comando == 's') {
            if (actual->siguiente != NULL) {
                actual = actual->siguiente;
                indice++;
            } else {
                printf("\n>>> [Límite alcanzado] Ya estás en el último tweet del feed. No hay más siguientes.\n");
            }
        } else if (comando == 'A' || comando == 'a') {
            if (actual->anterior != NULL) {
                actual = actual->anterior;
                indice--;
            } else {
                printf("\n>>> [Límite alcanzado] Ya estás en el primer tweet del feed. No hay tweets anteriores.\n");
            }
        } else if (comando == 'X' || comando == 'x') {
            printf("\nFinalizando Modo Historia y regresando al menú...\n");
            break;
        } else {
            printf("\nOpción no válida. Presione 'S' para avanzar, 'A' para retroceder o 'X' para salir.\n");
        }
    }

    /* Liberación crítica de la Lista Doblemente Enlazada */
    liberarFeedInteractivo(feed);
    free(feed);
}
