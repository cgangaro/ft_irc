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

/*
** Flags for the User MODE command
*/
#define UMODE_FLAGS "aiwroOs"
#define F_AWAY 0x01
#define F_INVISIBLE (0x01 << 1)
#define F_WALLOPS (0x01 << 2)
#define F_RESTRICTED (0x01 << 3)
#define F_OPER (0x01 << 4)
#define F_LOCALOPER (0x01 << 5)

/*
** Flags for the Channel MODE command
*/
#define CMODE_FLAGS "OovaimnqpsrtklbeI"

typedef int SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;

#endif
