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

#define DEFAULT_PORT 1024
#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
#define BUFFER_SIZE 1024
#define CRLF "\r\n"

#define SERVER_NAME "ft_irc_server"

typedef int SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;

#define RPL_WELCOME(nickname, username, hostname) "001 RPL_WELCOME Welcome to the IRC Network " + nickname + "!" + username + "@" + hostname + CRLF

#define SERVER_EXCEPTION(name, function)																		\
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

#define IRC_EXCEPTION(name, message)																			\
class name : public std::exception {																			\
		public:																									\
			virtual const char* what() const throw() {															\
				static std::string msg = message;																\
				return (msg.c_str());																			\
			}																									\
};

#define ERR_ERRONEOUSNICKNAME_BUILDER(nickname) ("432 * " + nickname + " :Erroneous nickname" + CRLF)
#define ERR_NICKNAMEINUSE_BUILDER(nickname) ("433 * " + nickname + " :Nickname is already in use" + CRLF)
#define ERR_NEEDMOREPARAMS_BUILDER(command) ("461 * " + command + " :Not enough parameters" + CRLF)

#define IRC_EXCEPTION_CUSTOM(name, messageBuilder)																\
class name : public std::exception {																			\
	std::string param;																							\
	public:																										\
		name(const std::string &param) : param(param) {}														\
		~name() throw() {}																						\
		virtual const char* what() const throw() {																\
			static std::string msg = messageBuilder(param);														\
			return (msg.c_str());																				\
		}																										\
};

namespace Exception {
		SERVER_EXCEPTION(BindFailed, "bind")
		SERVER_EXCEPTION(SocketCreationFailed, "socket");
		SERVER_EXCEPTION(ListenFailed, "listen")
		SERVER_EXCEPTION(AcceptFailed, "accept")
		SERVER_EXCEPTION(SelectFailed, "select")
		SERVER_EXCEPTION(SendFailed, "send")
		SERVER_EXCEPTION(ReadFailed, "read")

		IRC_EXCEPTION(ERR_PASSWDMISMATCH, "464 PASS :Password incorrect\r\n")
		IRC_EXCEPTION(ERR_ALREADYREGISTERED, "462 PASS :Unauthorized command (already registered)\r\n")
		IRC_EXCEPTION(ERR_NONICKNAMEGIVEN, "431 NICK :No nickname given\r\n")
		IRC_EXCEPTION(ERR_NOTREGISTERED, "451 :You have not registered\r\n")
		IRC_EXCEPTION_CUSTOM(ERR_NEEDMOREPARAMS, ERR_NEEDMOREPARAMS_BUILDER)
		IRC_EXCEPTION_CUSTOM(ERR_ERRONEOUSNICKNAME, ERR_ERRONEOUSNICKNAME_BUILDER)
		IRC_EXCEPTION_CUSTOM(ERR_NICKNAMEINUSE, ERR_NICKNAMEINUSE_BUILDER)
};

#endif
