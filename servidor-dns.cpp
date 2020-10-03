#include "hosts.h"
#include "links.h"
#include "thread.h"
#include "communication-udp.h"

#include <unistd.h>
#include <string.h>

void chamarComando(string linha);

int main(int argc, char **argv) {   
    if (argc < 2) {
        cout << "É necessário especificar a porta.";
        exit(1);
    }

    if(argc == 3) {
        FILE *file = fopen(argv[2],"r");
        char *linha;
        if (file == NULL){                       
            return -1;
        }
        else {
            cout << "Inicializando servidor a partir do arquivo..." << endl;
            while(fgets(linha, 1024, file)) {
                linha[strcspn(linha, "\n")] = '\0';
                chamarComando(linha);            
            }       
        }
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

void chamarComando(string linha) {
    string comando = linha.substr(0, linha.find(' '));
    linha.erase(0, linha.find(' ') + 1);
    string primeiroParametro = linha.substr(0, linha.find(' '));
    linha.erase(0, linha.find(' ') + 1);
    string segundoParametro = linha;

    if (comando.compare("add") == 0) {
        saveHost(primeiroParametro, segundoParametro);
    } else if (comando.compare("link") == 0) {
        saveLink(primeiroParametro.c_str(), atoi(segundoParametro.c_str()));
    } else {
        cout << "Comando inválido para inicialização." << endl;
    }
}