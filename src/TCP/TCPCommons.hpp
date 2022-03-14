#ifndef TCP_COMMONS_H
#define TCP_COMMONS_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <cstring>
#include <cerrno>
#include <iostream>
#include <sstream>

#define DEFAULT_PORT 1024
#define INVALID_SOCKET -1
#define SOCKET_ERROR -1

typedef int SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;

typedef struct s_client {
	SOCKET socket;
	SOCKADDR_IN sin;
} t_client;

#endif