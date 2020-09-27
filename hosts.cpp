#include "hosts.h"

map<string, string> hosts;

void save(string hostname, string ip) {
    hosts[hostname] = ip;

    cout << "salvo hostname: " << hostname << " ip: " << ip << endl;
}

string search(string hostname) {
    if (hosts.find(hostname) != hosts.end()) {
        cout << "hostname: " << hosts[hostname] << endl;
        return hosts[hostname];
    } else {
        cout << "hostname \"" << hostname << "\" não encontrado" << endl;
    }
    return "";
}