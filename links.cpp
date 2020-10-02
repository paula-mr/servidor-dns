#include "links.h"
#include "communication-udp.h"
#include <unistd.h>
#include <string.h>

set< pair<char*, int> > links;
list< pair<sockaddr_storage, int> > sockets;

void saveLink(char* ip, int port) {
    if (links.find(pair<char*, int> (ip, port)) == links.end()) {
        struct sockaddr_storage storage;
        memset(&storage, 0, sizeof(storage));

        parseAddress(ip, port, &storage);

        links.insert(pair<char*, int> (ip, port));
        sockets.push_back(pair<sockaddr_storage, int> (storage, initializeSocket()));
        cout << "Salvo link ip: " << ip << "; porta: " << port << endl;
    } else {
        cout << "Link já existente." << endl;
    }
    
}

list< pair<sockaddr_storage, int> > listSockets() {
    return sockets;
}