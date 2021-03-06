#include "links.h"
#include "communication-udp.h"

#include <unistd.h>
#include <string.h>

set< pair<const char*, int> > links;
list< pair<sockaddr_storage, int> > sockets;

void saveLink(string ip, int port) {
    if (links.find(pair<const char*, int> (ip.c_str(), port)) == links.end()) {
        struct sockaddr_storage storage;
        memset(&storage, 0, sizeof(storage));

        if (parseAddress(ip.c_str(), port, &storage) < 0) {
            cout << "Endereço inválido para link." << endl;
            return;
        }

        int sock = initializeSocket(storage.ss_family);

        struct timeval timeout;
        timeout.tv_sec = 0;
        timeout.tv_usec = 100000;
        if (setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout)) != 0) {
            perror("Erro ao configurar socket");
            exit(EXIT_FAILURE);
        }


        links.insert(pair<const char*, int> (ip.c_str(), port));
        sockets.push_back(pair<sockaddr_storage, int> (storage, sock));
        cout << "Salvo link ip: " << ip << "; porta: " << port << endl;
    } else {
        cout << "Link já existente." << endl;
    }
    
}

list< pair<sockaddr_storage, int> > listSockets() {
    return sockets;
}