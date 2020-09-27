#include "hosts.h"
#include "links.h"
#include "thread.h"

int main() 
{   
    pthread_t thread_id;

    char* port = "8080";

    start_connection_handler(port);

    while (true) {
        string comando;
        cin >> comando;

        if (comando.compare("add") == 0) {
            string hostname, ip;
            cin >> hostname >> ip;
            saveHost(hostname, ip);
        } else if (comando.compare("search") == 0) {
            string hostname, ip;
            cin >> hostname;
            ip = searchHost(hostname);
        } else if (comando.compare("link") == 0) {
            string porta;
            string ip;
            cin >> ip;
            cin >> porta;

            saveLink(ip, porta);
            listLinks();
        } else {
            cout << "Comando não encontrado." << endl;
        }
        
    }

    return 0;
} 