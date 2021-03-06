#include "communication-udp.h"

#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 

#define MAXLINE 1024 

int initializeSocketAddress(const char *proto, int port, struct sockaddr_storage *storage);

int createServer(int port, struct sockaddr *addressConnected) {
    struct sockaddr_storage storage;
    memset(&storage, 0, sizeof(storage)); 
    if (initializeSocketAddress(VERSION, port, &storage) != 0)
    {
        printf("Argumentos passados incorretos. Necessário especificar tipo de endereço e porta.");
        exit(EXIT_FAILURE);
    }

    int sock = initializeSocket(storage.ss_family);

    int enable = 1;	
    if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) != 0)	
    {	
        perror("Erro ao configurar socket");	
        exit(EXIT_FAILURE);	
    }

    addressConnected = (struct sockaddr *)&storage;
    if (bind(sock, addressConnected, sizeof(storage)) < 0) { 
        perror("Erro ao fazer bind"); 
        exit(EXIT_FAILURE); 
    } 

    printAddress(addressConnected);

    return sock;
}

void sendMessage(const struct sockaddr *address, size_t size, int sock, char* message) {
    sendto(sock, (const char *)message, strlen(message), MSG_CONFIRM, address, size); 
}

string receiveMessage(struct sockaddr *address, int sock) {
    char buffer[MAXLINE]; 
    socklen_t len = sizeof(address);
    int n = recvfrom(sock, (char *)buffer, MAXLINE, MSG_WAITALL, address, &len); 
    if (n > 0) {
        buffer[n] = '\0'; 
        return string(buffer);
    }

    return "2-1";
}

int parseAddress(const char *addrstr, int portValue, struct sockaddr_storage *storage) {
    if (addrstr == NULL) {
        return -1;
    }

    uint16_t port = htons(portValue);

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
    char str[MAXLINE];

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

    snprintf(str, MAXLINE, "IPv%d %s %hu", version, addrstr, port);
    printf("Conectado em %s.\n\n\n", str);
}

int initializeSocketAddress(const char *proto, int portString,
                            struct sockaddr_storage *storage)
{
    uint16_t port = htons(portString);

    memset(storage, 0, sizeof(*storage));
    if (0 == strcmp(proto, "v4"))
    {
        struct sockaddr_in *addr4 = (struct sockaddr_in *)storage;
        addr4->sin_family = AF_INET;
        addr4->sin_addr.s_addr = INADDR_ANY;
        addr4->sin_port = port;
        return 0;
    }
    else if (0 == strcmp(proto, "v6"))
    {
        struct sockaddr_in6 *addr6 = (struct sockaddr_in6 *)storage;
        addr6->sin6_family = AF_INET6;
        addr6->sin6_addr = in6addr_any;
        addr6->sin6_port = port;
        return 0;
    }
    else
    {
        return -1;
    }
}

int initializeSocket(int version) {
    int sock;
    if ((sock = socket(version, SOCK_DGRAM, 0)) < 0) { 
        perror("Erro ao iniciar socket"); 
        exit(EXIT_FAILURE); 
    } 
    return sock;
}