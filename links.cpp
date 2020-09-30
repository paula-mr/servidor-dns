#include "links.h"
#include "communication-udp.h"

set< pair<char*, int> > links;

void saveLink(char* ip, int port) {
    if (links.find(pair<char*, int> (ip, port)) == links.end()) {
        links.insert(pair<char*, int> (ip, port));
        cout << "Salvo link ip: " << ip << "; porta: " << port << endl;
    } else {
        cout << "Link já existente." << endl;
    }
    
}

set< pair<char*, int> > listLinks() {
    return links;
}