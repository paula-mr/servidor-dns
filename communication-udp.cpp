#include "communication-udp.h"

#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 
#include <string.h>

#include <arpa/inet.h>

#define MAXLINE 1024 

int SOCKET_VALUE;

int createServer(int port, struct sockaddr *addressConnected) {
    if (0 == strcmp(VERSION, "v4")) {
        struct sockaddr_in address; 
        if ((SOCKET_VALUE = socket(AF_INET, SOCK_DGRAM, 0)) < 0) { 
            perror("Erro ao iniciar socket"); 
            exit(EXIT_FAILURE); 
        } 
        memset(&address, 0, sizeof(address)); 
        
        address.sin_family = AF_INET; 
        address.sin_addr.s_addr = INADDR_ANY; 
        address.sin_port = htons(port); 

        int enable = 1;
        if (setsockopt(SOCKET_VALUE, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) != 0)
        {
            perror("Erro ao configurar socket");
            exit(EXIT_FAILURE);
        }
        
        addressConnected = (struct sockaddr *)&address;
        if (bind(SOCKET_VALUE, addressConnected, sizeof(address)) < 0) { 
            perror("Erro ao fazer bind"); 
            exit(EXIT_FAILURE); 
        } 
    } else {
        struct sockaddr_in6 address; 
        if ((SOCKET_VALUE = socket(AF_INET6, SOCK_DGRAM, 0)) < 0) { 
            perror("Erro ao iniciar socker"); 
            exit(EXIT_FAILURE); 
        } 
        memset(&address, 0, sizeof(address)); 
        
        address.sin6_family = AF_INET6;
        address.sin6_port = htons(port);
        address.sin6_addr = in6addr_any;

        int enable = 1;
        if (setsockopt(SOCKET_VALUE, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) != 0)
        {
            perror("Erro ao configurar socket");
            exit(EXIT_FAILURE);
        }
        
        addressConnected = (struct sockaddr *)&address;
        if (bind(SOCKET_VALUE, addressConnected, sizeof(address)) < 0) { 
            perror("Erro ao fazer bind"); 
            exit(EXIT_FAILURE); 
        } 
    }

    printAddress(addressConnected);

    return SOCKET_VALUE;
}

void sendMessage(struct sockaddr *address, char* message) {
    printf("cheguei");

    socklen_t len = sizeof(*address);
    //TODO trocar 0 para MSG_CONFIRM
    sendto(SOCKET_VALUE, (const char *)message, strlen(message), 0, (const struct sockaddr *) &address, len); 
    printf("enviada com sucesso");

}

void receiveMessage(struct sockaddr *address) {
    char buffer[MAXLINE]; 
    struct sockaddr_in servaddr, cliaddr; 
    memset(&cliaddr, 0, sizeof(cliaddr)); 
    socklen_t len = sizeof(*address);
    printf("estoy aqui");
    int n = recvfrom(SOCKET_VALUE, (char *)buffer, MAXLINE, MSG_WAITALL, (struct sockaddr *) &cliaddr, &len); 
    buffer[n] = '\0'; 
    printf("estoy aqui 2");

    printf(buffer);
}

int parseAddress(const char *addrstr, int portValue, struct sockaddr_storage *storage) {
    if (addrstr == NULL || portValue == NULL) {
        return -1;
    }

    uint16_t port = htons(portValue);

    printf("ate aq ok\n");

    struct in_addr inaddr4;
    if (inet_pton(AF_INET, addrstr, &inaddr4)) {
        struct sockaddr_in *addr4 = (struct sockaddr_in *)storage;
        addr4->sin_family = AF_INET;
        addr4->sin_port = port;
        addr4->sin_addr = inaddr4;
        return 0;
    }

    struct in6_addr inaddr6;
    if (inet_pton(AF_INET6, addrstr, &inaddr6)) {
        struct sockaddr_in6 *addr6 = (struct sockaddr_in6 *)storage;
        addr6->sin6_family = AF_INET6;
        addr6->sin6_port = port;
        memcpy(&(addr6->sin6_addr), &inaddr6, sizeof(inaddr6));
        return 0;
    }

    return -1;
}

void printAddress(const struct sockaddr *addr) {
    int version;
    char addrstr[INET6_ADDRSTRLEN + 1] = "";
    uint16_t port;
    char str[BUFSZ];

    if (addr->sa_family == AF_INET) {
        version = 4;
        struct sockaddr_in *addr4 = (struct sockaddr_in *)addr;
        if (!inet_ntop(AF_INET, &(addr4->sin_addr), addrstr,
                       INET6_ADDRSTRLEN + 1))
        {
            perror("Erro ao converter endereço");
            exit(EXIT_FAILURE);
        }
        port = ntohs(addr4->sin_port);
    } else if (addr->sa_family == AF_INET6) {
        version = 6;
        struct sockaddr_in6 *addr6 = (struct sockaddr_in6 *)addr;
        if (!inet_ntop(AF_INET6, &(addr6->sin6_addr), addrstr,
                       INET6_ADDRSTRLEN + 1))
        {
            perror("Erro ao converter endereço");
            exit(EXIT_FAILURE);
        }
        port = ntohs(addr6->sin6_port);
    } else {
        printf("Protocolo desconhecido");
        exit(EXIT_FAILURE);
    }

    snprintf(str, BUFSZ, "IPv%d %s %hu", version, addrstr, port);
    printf("Conectado em %s.\n", str);
}