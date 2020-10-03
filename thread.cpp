#include "thread.h"
#include "communication-udp.h"
#include "hosts.h"

#include <iostream> 
#include <pthread.h>
#include <string>
#include <stdio.h> 
#include <string.h>
#include <stdlib.h> 

using namespace std; 

void *connectionHandler(void *);
char* initializeBufferHostNotFound();
char* initializeBufferHostFound(string ip);

void startConnectionHandler(char* port) {
    pthread_t thread_id;
    if (pthread_create(&thread_id, NULL, connectionHandler, (void*) port) < 0) {
        perror("Não foi possível iniciar a thread");
    }
    cout << "Thread de conexões aberta com sucesso! Iniciando servidor..." << endl;
}

void *connectionHandler(void *portValue) {
    char* port = (char*)portValue; 
    struct sockaddr addressConnected;

    int sock = createServer(atoi(port), &addressConnected);

    while (true) {
        struct sockaddr_storage storage;
        memset(&storage, 0, sizeof(storage));  

        string buffer = receiveMessage((struct sockaddr *) &storage, sock);
        if (buffer.at(0) == '1') {
            string host = buffer.substr(1, buffer.length());

            cout << "Host procurado: " << host << endl;

            string result = searchHost(host);

            if (result.compare("") == 0) {
                cout << "Host não encontrado: " << host << endl;
                char* buffer = initializeBufferHostNotFound();

                sendMessage((const struct sockaddr *)&storage, sizeof(storage), sock, buffer);
            } else {
                cout << "Endereço do host encontrado: " << host << ": " << result << endl;
                char* buffer = initializeBufferHostFound(result);

                sendMessage((const struct sockaddr *)&storage, sizeof(storage), sock, buffer);
            }
        }
    }

    return 0;
}

char* initializeBufferHostNotFound() {
    char *buffer = (char *) malloc(4);
    buffer[0] = '2';
    buffer[1] = '-';
    buffer[2] = '1';
    buffer[3] = '\0';

    return buffer;
}

char* initializeBufferHostFound(string ip) {
    char *buffer = (char *) malloc(50);
    buffer[0] = '2';
    
    for (long unsigned int i=0; i<ip.length(); i++) {
        buffer[i+1] = ip.at(i);
    }
    buffer[ip.length() + 1] = '\0';

    return buffer;
}