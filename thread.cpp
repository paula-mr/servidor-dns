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

void *connection_handler(void *);

void start_connection_handler(char* port) {
    pthread_t thread_id;
    if (pthread_create(&thread_id, NULL, connection_handler, (void*) port) < 0) {
        perror("Não foi possível iniciar a thread");
    }
    cout << "Thread de conexões aberta com sucesso! Iniciando servidor..." << endl;
}

void *connection_handler(void *portValue) {
    char* port = (char*)portValue; 
    struct sockaddr addressConnected;

    int sock = createServer(atoi(port), &addressConnected);
    cout << "Servidor iniciado!" << endl;

    while (true) {
        struct sockaddr_storage storage;
        memset(&storage, 0, sizeof(storage));  

        string buffer = receiveMessage((struct sockaddr *) &storage, sock);
        cout << "BUFFER " << buffer << endl;
        if (buffer.at(0) == '1') {
            string host = buffer.substr(1, buffer.length());

            cout << "Host procurado: " << host << endl;

            string result = searchHost(host);

            if (result.compare("") == 0) {
                cout << "Host não encontrado: " << host << endl;
                char buffer[4];
                buffer[0] = '2';
                buffer[1] = '-';
                buffer[2] = '1';
                buffer[3] = '\0';

                printAddress((const struct sockaddr *)&storage);

                sendMessage((const struct sockaddr *)&storage, sizeof(storage), sock, buffer);
            } else {
                cout << "Endereço do host encontrado: " << host << ": " << result << endl;
                char buffer[50];
                buffer[0] = '2';
                
                for (long unsigned int i=0; i<result.length(); i++) {
                    buffer[i+1] = result.at(i);
                }
                buffer[result.length() + 1] = '\0';

                printAddress((const struct sockaddr *)&storage);

                sendMessage((const struct sockaddr *)&storage, sizeof(storage), sock, buffer);
            }
        }
    }

    return 0;
}
  