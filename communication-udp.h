#pragma once

#include <stdlib.h>

#include <string>
#include <arpa/inet.h>

#define BUFSZ 1024
#define VERSION "v4"

using namespace std;

int createServer(int port, struct sockaddr *storage);
int parseAddress(const char *addrstr, int portValue, struct sockaddr_storage *storage);
void printAddress(const struct sockaddr *addr);
char* receiveMessage(struct sockaddr *address);
void sendMessage(string ip, int port, char* message);
