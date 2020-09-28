#include "thread.h"
#include "communication-udp.h"

#include <iostream> 
#include <pthread.h>

using namespace std; 

void *connection_handler(void *);

void start_connection_handler(char* port) {
    pthread_t thread_id;
    if (pthread_create(&thread_id, NULL, connection_handler, (void*) port) < 0) {
        perror("Não foi possível iniciar a thread.");
    }
    cout << "Thread de conexões aberta com sucesso! Iniciando servidor...\n";
}

void *connection_handler(void *portValue) {
    char* port = (char*)portValue; 
    createServer(atoi(port));
    cout << "Servidor iniciado!\n";

    return 0;
}