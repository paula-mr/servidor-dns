#include "hosts.h"
#include "links.h"
#include "thread.h"
#include "communication-udp.h"

#include <unistd.h>
#include <string.h>

string searchOtherServers(string hostname);

int main(int argc, char **argv) {   
    if (argc < 2) {
        cout << "É necessário especificar a porta.";
        exit(1);
    }

    char* port = argv[1];

    start_connection_handler(port);
    sleep(1);

    while (true) {
        string comando;
        cout << "Digite o seu comando: ";
        cin >> comando;

        if (comando.compare("add") == 0) {
            string hostname, ip;
            cin >> hostname >> ip;
            saveHost(hostname, ip);
        } else if (comando.compare("search") == 0) {
            string hostname, ip;
            cin >> hostname;
            ip = searchHost(hostname);
            if (ip.compare("") == 0) {
                ip = searchOtherServers(hostname);
            }
        } else if (comando.compare("link") == 0) {
            char ip[45];
            int porta;
            cin >> ip >> porta;

            saveLink(ip, porta);
        } else {
            cout << "Comando não encontrado." << endl;
        }
        
    }

    return 0;
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
    string hostEncontrado;
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
            if (!host.compare("-1")) {
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

    return "";
}