#include "links.h"
#include "communication-udp.h"

set< pair<char*, int> > links;
list<struct sockaddr*> sockets;

void saveLink(char* ip, int port) {
    cout << "oi" << endl;
    if (links.find(pair<char*, int> (ip, port)) == links.end()) {
        links.insert(pair<char*, int> (ip, port));
        struct sockaddr_storage *storage;
        cout << "entrei" << endl;
        parseAddress(ip, port, storage);
        cout << "parseei" << endl;
        sockets.push_back((struct sockaddr *) &storage);
        cout << "Salvo link ip: " << ip << "; porta: " << port << endl;
    } else {
        cout << "Link já existente." << endl;
    }
    
}

list<struct sockaddr*> listLinks() {
    return sockets;
}