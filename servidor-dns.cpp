#include "hosts.h"
#include "links.h"
#include "thread.h"
#include "communication-udp.h"

#include <unistd.h>
#include <string.h>

void initializeFromFile(string fileName);
void callCommand(string line);

int main(int argc, char **argv) {   
    if (argc < 2) {
        cout << "É necessário especificar a porta.";
        exit(1);
    }

    if (argc == 3) {
       initializeFromFile(argv[2]);
    }

    char* port = argv[1];
    startConnectionHandler(port);
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
            string ip;
            int porta;
            cin >> ip >> porta;
            saveLink(ip, porta);
        } else {
            cout << "Comando não encontrado." << endl;
        }
        
    }

    return 0;
}

void initializeFromFile(string fileName) {
    FILE *file = fopen(fileName.c_str(), "r");
    char *line;
    if (file == NULL){   
        cout << "Arquivo " << fileName << " não encontrado.";                   
        exit(1);
    }
    else {
        cout << "Inicializando servidor a partir do arquivo..." << endl;
        while (fgets(line, 1024, file)) {
            line[strcspn(line, "\n")] = '\0';
            callCommand(line);            
        }      
        cout << "Inicialização finalizada." << endl << endl;
    }
}

void callCommand(string line) {
    string comando = line.substr(0, line.find(' '));
    line.erase(0, line.find(' ') + 1);
    string primeiroParametro = line.substr(0, line.find(' '));
    line.erase(0, line.find(' ') + 1);
    string segundoParametro = line;

    if (comando.compare("add") == 0) {
        saveHost(primeiroParametro, segundoParametro);
    } else if (comando.compare("link") == 0) {
        saveLink(primeiroParametro, atoi(segundoParametro.c_str()));
    } else {
        cout << "Comando inválido para inicialização." << endl;
    }
}