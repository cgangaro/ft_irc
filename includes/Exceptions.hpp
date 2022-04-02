#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP

#include <exception>
#include <string>

#define CRLF "\r\n"

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
		IRC_EXCEPTION(ERR_NOTEXTTOSEND, "412 :No text to send\r\n")
		IRC_EXCEPTION_CUSTOM(ERR_NEEDMOREPARAMS, ERR_NEEDMOREPARAMS_BUILDER)
		IRC_EXCEPTION_CUSTOM(ERR_ERRONEOUSNICKNAME, ERR_ERRONEOUSNICKNAME_BUILDER)
		IRC_EXCEPTION_CUSTOM(ERR_NICKNAMEINUSE, ERR_NICKNAMEINUSE_BUILDER)
		IRC_EXCEPTION_CUSTOM(ERR_CHANNELISFULL, ERR_CHANNELISFULL_BUILDER)
		IRC_EXCEPTION_CUSTOM(ERR_NOSUCHCHANNEL, ERR_NOSUCHCHANNEL_BUILDER)
		IRC_EXCEPTION_CUSTOM(ERR_TOOMANYCHANNELS, ERR_TOOMANYCHANNELS_BUILDER)
		IRC_EXCEPTION_CUSTOM(ERR_BADCHANNELKEY, ERR_BADCHANNELKEY_BUILDER)
		IRC_EXCEPTION_CUSTOM(ERR_CANNOTSENDTOCHAN, ERR_CANNOTSENDTOCHAN_BUILDER)
		IRC_EXCEPTION_CUSTOM(ERR_TOOMANYTARGETS, ERR_TOOMANYTARGETS_BUILDER)
		IRC_EXCEPTION_CUSTOM(ERR_NOSUCHNICK, ERR_NOSUCHNICK_BUILDER)
};

#endif