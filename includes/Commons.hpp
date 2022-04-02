#ifndef COMMONS_H
#define COMMONS_H

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
#include <string>
#include <map>
#include "Replies.hpp"
#include "Exceptions.hpp"

#define DEFAULT_PORT 1024
#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
#define BUFFER_SIZE 1024
#define MAX_USERS_PER_CHANNEL 5
#define MAX_CHANNELS_PER_USER 6
#define OPER_PASSWORD "oper"

/*
** Those are used in buildCmdResponse in Command class
*/
#define OPT_CLIENT 0
#define OPT_SERVER 1

typedef int SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;

#endif
