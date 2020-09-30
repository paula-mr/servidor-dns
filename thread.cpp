#include "thread.h"
#include "communication-udp.h"
#include "hosts.h"

#include <iostream> 
#include <pthread.h>
#include <string>
#include <stdio.h> 
#include <stdlib.h> 

using namespace std; 

void *connection_handler(void *);

void start_connection_handler(char* port) {
    pthread_t thread_id;
    if (pthread_create(&thread_id, NULL, connection_handler, (void*) port) < 0) {
        perror("Não foi possível iniciar a thread.");
    }
    cout << "Thread de conexões aberta com sucesso! Iniciando servidor...\n" << endl;
}

void *connection_handler(void *portValue) {
    char* port = (char*)portValue; 
    struct sockaddr addressConnected;

    createServer(atoi(port), &addressConnected);
    cout << "Servidor iniciado!\n";

    while (true) {
        char* host = receiveMessage(&addressConnected);
        string hostString(host);
        string result = searchHost(hostString);

        if (result.compare("") == 0) {
            printf("host não encontrado\n");
            char buffer[2];
            buffer[0] = '2';
            buffer[1] = '-1';

            //sendMessage();
        }
    }

    return 0;
}