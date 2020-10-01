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
string convertToString(char* a);

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
        struct sockaddr_storage storage;
        memset(&storage, 0, sizeof(storage));  

        string buffer = receiveMessage((struct sockaddr *) &storage);
        cout << "BUFFER " << buffer << endl;
        if (buffer.at(0) == '1') {
            string host = "";
            for (int i=0; i<buffer.length()-1; i++) {
                host += buffer[i+1];
            }

            cout << "Host procurado: " << host << endl;

            string result = searchHost(host);

            if (result.compare("") == 0) {
                cout << "Host não encontrado: " << host << endl;
                char buffer[3];
                buffer[0] = '2';
                buffer[1] = '-';
                buffer[2] = '1';

                printAddress((const struct sockaddr *)&storage);

                sendMessage((const struct sockaddr *)&storage, sizeof(storage), buffer);
            } else {
                cout << "Endereço do host encontrado: " << host << ": " << result << endl;
                char buffer[50];
                buffer[0] = '2';
                
                for (int i=0; i<result.length(); i++) {
                    buffer[i+1] = result.at(0);
                }

                printAddress((const struct sockaddr *)&storage);

                sendMessage((const struct sockaddr *)&storage, sizeof(storage), buffer);
            }
        }
    }

    return 0;
}
  