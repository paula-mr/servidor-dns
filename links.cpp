#include "links.h"

set< pair<string, string> > links;

void saveLink(string ip, string port) {
    links.insert(pair<string, string> (ip, port));
    cout << "Salvo link ip: " << ip << "; porta: " << port << endl;
}

set< pair<string, string> > listLinks() {
    for (auto itr = links.begin(); itr != links.end(); ++itr) { 
        cout << itr->first 
             << '\t' << itr->second << '\n'; 
    } 
    return links;
}