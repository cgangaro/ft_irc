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
#include <string>

#define DEFAULT_PORT 1024
#define INVALID_SOCKET -1
#define SOCKET_ERROR -1

typedef int SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;

typedef struct s_client {
	SOCKET socket;
	SOCKADDR_IN sin;
	std::string user;
	std::string nickname;
} t_client;

#define TCP_EXCEPTION(name, function)																			\
class name : public std::exception {																			\
		private:																								\
			std::string exceptionMessageBuilder(const std::string &func, const std::string &message) const {	\
				std::stringstream ss;																			\
				ss << func << ": " << message;																	\
				return (ss.str());																				\
			}																									\
		public:																									\
			virtual const char* what() const throw() {															\
				static std::string message = exceptionMessageBuilder(function, std::strerror(errno));			\
				return (message.c_str());																		\
			}																									\
};

namespace TCPException {
		TCP_EXCEPTION(BindFailed, "bind")
		TCP_EXCEPTION(SocketCreationFailed, "socket");
		TCP_EXCEPTION(ListenFailed, "listen")
		TCP_EXCEPTION(AcceptFailed, "accept")
		TCP_EXCEPTION(SelectFailed, "select")
		TCP_EXCEPTION(SendFailed, "send")
		TCP_EXCEPTION(ReadFailed, "read")
};

#endif