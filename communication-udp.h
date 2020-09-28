#pragma once

#include <stdlib.h>

#include <arpa/inet.h>

#define BUFSZ 1024
#define VERSION "v4"

int createServer(int port);
int parseAddress(const char *addrstr, const char *portstr, struct sockaddr_storage *storage);
void printAddress(const struct sockaddr *addr);
