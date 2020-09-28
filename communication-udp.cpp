#include "communication-udp.h"

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <arpa/inet.h>

int createServer(int port) {
    int sock; 
    const struct sockaddr *addressConnected;

    if (0 == strcmp(VERSION, "v4")) {
        struct sockaddr_in address; 
        if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0) { 
            perror("Erro ao iniciar socker"); 
            exit(EXIT_FAILURE); 
        } 
        memset(&address, 0, sizeof(address)); 
        
        address.sin_family = AF_INET; 
        address.sin_addr.s_addr = INADDR_ANY; 
        address.sin_port = htons(port); 

        int enable = 1;
        if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) != 0)
        {
            perror("Erro ao configurar socket");
            exit(EXIT_FAILURE);
        }
        
        addressConnected = (const struct sockaddr *)&address;
        if (bind(sock, addressConnected, sizeof(address)) < 0) { 
            perror("Erro ao fazer bind"); 
            exit(EXIT_FAILURE); 
        } 
    } else {
        struct sockaddr_in6 address; 
        if ((sock = socket(AF_INET6, SOCK_DGRAM, 0)) < 0) { 
            perror("Erro ao iniciar socker"); 
            exit(EXIT_FAILURE); 
        } 
        memset(&address, 0, sizeof(address)); 
        
        address.sin6_family = AF_INET6;
        address.sin6_port = htons(port);
        address.sin6_addr = in6addr_any;

        int enable = 1;
        if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) != 0)
        {
            perror("Erro ao configurar socket");
            exit(EXIT_FAILURE);
        }
        
        addressConnected = (const struct sockaddr *)&address;
        if (bind(sock, addressConnected, sizeof(address)) < 0) { 
            perror("Erro ao fazer bind"); 
            exit(EXIT_FAILURE); 
        } 
    }

    printAddress(addressConnected);

    return sock;
}

int parseAddress(const char *addrstr, const char *portstr, struct sockaddr_storage *storage) {
    if (addrstr == NULL || portstr == NULL)
    {
        return -1;
    }

    uint16_t port = (uint16_t)atoi(portstr);
    if (port == 0)
    {
        return -1;
    }
    port = htons(port);

    struct in_addr inaddr4;
    if (inet_pton(AF_INET, addrstr, &inaddr4))
    {
        struct sockaddr_in *addr4 = (struct sockaddr_in *)storage;
        addr4->sin_family = AF_INET;
        addr4->sin_port = port;
        addr4->sin_addr = inaddr4;
        return 0;
    }

    struct in6_addr inaddr6;
    if (inet_pton(AF_INET6, addrstr, &inaddr6))
    {
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

    if (addr->sa_family == AF_INET)
    {
        version = 4;
        struct sockaddr_in *addr4 = (struct sockaddr_in *)addr;
        if (!inet_ntop(AF_INET, &(addr4->sin_addr), addrstr,
                       INET6_ADDRSTRLEN + 1))
        {
            perror("Erro ao converter endereço");
            exit(EXIT_FAILURE);
        }
        port = ntohs(addr4->sin_port);
    }
    else if (addr->sa_family == AF_INET6)
    {
        version = 6;
        struct sockaddr_in6 *addr6 = (struct sockaddr_in6 *)addr;
        if (!inet_ntop(AF_INET6, &(addr6->sin6_addr), addrstr,
                       INET6_ADDRSTRLEN + 1))
        {
            perror("Erro ao converter endereço");
            exit(EXIT_FAILURE);
        }
        port = ntohs(addr6->sin6_port);
    }
    else
    {
        printf("Protocolo desconhecido");
        exit(EXIT_FAILURE);
    }

    snprintf(str, BUFSZ, "IPv%d %s %hu", version, addrstr, port);
    printf("Conectado em %s.\n", str);
}