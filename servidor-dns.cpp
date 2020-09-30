#include "hosts.h"
#include "links.h"
#include "thread.h"
#include "communication-udp.h"

#include <unistd.h>
#include <string.h>

string searchOtherServers(string hostname);

int main(int argc, char **argv) 
{   
    pthread_t thread_id;

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
    set< pair<char*, int> > links  = listLinks();
    printf("Procurando em outros servers\n");

    char buffer[1 + hostname.length()];
    buffer[0] = '1';

    for (int i=0; i < hostname.length(); i++) {
        buffer[i+1] = hostname[i];
    }

    for (auto itr = links.begin(); itr != links.end(); ++itr) { 
        printf("enviando mensagem");
        sendMessage(itr->first, itr->second, buffer);
    }

    return "";
}