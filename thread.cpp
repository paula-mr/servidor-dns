#include "thread.h"
#include "communication-udp.h"

#include <iostream> 

using namespace std; 

void *connection_handler(void *);

void start_connection_handler(char* port) {
    pthread_t thread_id;
    if (pthread_create(&thread_id, NULL, connection_handler, (void*) port) < 0) {
        perror("Não foi possível iniciar a thread.");
    }
    cout << "Thread de conexões aberta com sucesso!\n";
}

void *connection_handler(void *portValue) {
    char *portString = (char *)portValue; 
    createServer(portString);
    cout << "Servidor iniciado!";

    return 0;
}