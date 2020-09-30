#pragma once

#include <set>
#include <list>
#include <string>
#include <iostream> 

using namespace std; 

void saveLink(char* ip, int port);
set< pair<char*, int> > listLinks();