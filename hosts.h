#pragma once

#include <map>
#include <string>
#include <iostream> 

using namespace std; 

map<string, string> hosts;

void save(string hostname, string ip);
void search(string hostname);