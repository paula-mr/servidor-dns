#include "thread.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h> 
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

    uint16_t port = (uint16_t)atoi(portString);
    if (port == 0)
    {
        return (void*) 1;
    }
    port = htons(port);

    int socket_desc, client_sock, c;
    struct sockaddr_in server, client;

    socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_desc == -1)
    {
        printf("Could not create socket");
    }
    puts("Socket created");

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = port;

    if (bind(socket_desc, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        perror("bind failed. Error");
        return (void*) 1;
    }
    puts("bind done");

    listen(socket_desc, 3);
    //Accept and incoming connection
    puts("Waiting for incoming connections...");
    c = sizeof(struct sockaddr_in);

    client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t *)&c);
    puts("Connection accepted");
    
    //Get the socket descriptor
    size_t read_size;
    char *message, client_message[2000];

    //Receive a message from client
    while ((read_size = recv(client_sock, client_message, 10, NULL)) > 0) {
        //end of string marker
        client_message[read_size] = '\0';
        printf("Server receive: %s\n", client_message);

        //Send the message back to client
        write(client_sock, client_message, strlen(client_message));

        //clear the message buffer
        memset(client_message, 0, 2000);
    }

    if (read_size == 0) {
        puts("Client disconnected");
        fflush(stdout);
    }  else if (read_size == -1) {
        perror("recv failed");
    }

    return 0;
}