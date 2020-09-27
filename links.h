#pragma once

#include <set>
#include <string>
#include <iostream> 

using namespace std; 

void saveLink(string ip, string port);
set< pair<string, string> > listLinks();