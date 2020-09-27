#include "hosts.h"

int main() 
{   
    while (true) {
        string comando;
        cin >> comando;

        if (comando.compare("add") == 0) {
            string hostname, ip;
            cin >> hostname >> ip;
            save(hostname, ip);
        } else if (comando.compare("search") == 0) {
            string hostname, ip;
            cin >> hostname;
            ip = search(hostname);
        } else if (comando.compare("link") == 0) {
            string porta;
            string ip;
            cin >> ip;
            cin >> porta;

            cout << "ip: " << ip << " porta: " << porta << endl;
        } else {
            cout << "Comando não encontrado." << endl;
        }
        
    }

    return 0;
} 