#include "hosts.h"

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
        cout << "Hostname \"" << hostname << "\" não encontrado." << endl;
    }
    return "";
}