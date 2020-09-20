#include <iostream> 
#include <map>
#include <string>

using namespace std; 

int main() 
{ 
	map<string, string> hosts;
    
    while (true) {
        string comando;
        cin >> comando;

        if (comando.compare("add") == 0) {
            string hostname;
            string ip;
            cin >> hostname;
            cin >> ip;

            cout << "hostname: " << hostname << " ip: " << ip << endl;
        } else if (comando.compare("search") == 0) {
            string hostname;
            cin >> hostname;

            cout << "hostname: " << hostname << endl;
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