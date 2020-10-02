#pragma once

#include <set>
#include <list>
#include <string>
#include <iostream> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 

using namespace std; 

void saveLink(char* ip, int port);
list< pair<sockaddr_storage, int> > listSockets();