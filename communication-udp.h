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
string receiveMessage(struct sockaddr *address, int sock);
int initializeSocket();
void sendMessage(const struct sockaddr *address, size_t size, int sock, char* message);