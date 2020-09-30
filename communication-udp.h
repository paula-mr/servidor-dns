#pragma once

#include <stdlib.h>

#include <arpa/inet.h>

#define BUFSZ 1024
#define VERSION "v4"

int createServer(int port, struct sockaddr *storage);
int parseAddress(const char *addrstr, int portValue, struct sockaddr_storage *storage);
void printAddress(const struct sockaddr *addr);
void receiveMessage(struct sockaddr *address);
void sendMessage(string ip, int port, char* message);
