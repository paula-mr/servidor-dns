#include "hosts.h"
#include "links.h"
#include "communication-udp.h"

#include <list>
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 
#include <arpa/inet.h>
#include <string.h>

string searchOtherServers(string hostname);

map<string, string> hosts;

void saveHost(string hostname, string ip) {
    hosts[hostname] = ip;

    cout << "Salvo hostname: " << hostname << "; ip: " << ip << endl;
}

string searchHost(string hostname) {
    if (hosts.find(hostname) != hosts.end()) {
        cout << "Hostname: " << hosts[hostname] << endl;
        return hosts[hostname];
    } else {
        cout << "Hostname \"" << hostname << "\" não encontrado. Procurando outros servers..." << endl;
        return searchOtherServers(hostname);
    }
}

string searchOtherServers(string hostname) {
    list< pair<sockaddr_storage, int> > links  = listSockets();
    printf("Procurando em outros servers\n");

    char buffer[1 + hostname.length()];
    buffer[0] = '1';

    for (int i=0; i < hostname.length(); i++) {
        buffer[i+1] = hostname[i];
    }

    bool encontrado = false;
    string hostEncontrado = "";
    for (auto itr = links.begin(); itr != links.end() && !encontrado; ++itr) { 
        printf("Enviando mensagem\n");
        const struct sockaddr *address = (const struct sockaddr*) &(itr->first);
        int sock = itr->second;

        sendMessage(address, sizeof(itr->first), itr->second, buffer);

        struct sockaddr_storage storage;
        memset(&storage, 0, sizeof(storage));  

        string buffer = receiveMessage((struct sockaddr *) &storage, sock);
        cout << "Mensagem do host: " << buffer << endl;

        if (buffer.at(0) == '2') {
            string host = buffer.substr(1, buffer.length());
            cout << "Host retornado: " << host << endl;
            if (host.compare("-1")) {
                encontrado = true;
                hostEncontrado = host;
            }
        }
    }

    if (encontrado) {
        cout << "Host encontrado: " << hostEncontrado << endl;
    } else {
        cout << "Host não encontrado." << endl;
    }

    return hostEncontrado;
}