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
	private:																									\
		std::string param;																						\
	public:																										\
		name(const std::string param) : param(param) {}															\
		~name() throw() {}																						\
		virtual const char* what() const throw() {																\
			static std::string msg;																				\
			msg = messageBuilder(param);																		\
			return (msg.c_str());																				\
		}																										\
};

#define IRC_EXCEPTION_CUSTOM_2(name, messageBuilder)															\
class name : public std::exception {																			\
	private:																									\
		std::string param1;																						\
		std::string param2;																						\
	public:																										\
		name(const std::string param1, const std::string param2) : param1(param1), param2(param2) {}								\
		~name() throw() {}																						\
		virtual const char* what() const throw() {																\
			static std::string msg;																				\
			msg = messageBuilder(param1, param2);																\
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
		IRC_EXCEPTION(ERR_NOVALIDADDRESS, "000 :No valid address\r\n")
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
		IRC_EXCEPTION_CUSTOM(ERR_NORECIPIENT_PRIVMSG, ERR_NORECIPIENT_PRIVMSG_BUILDER)
		IRC_EXCEPTION_CUSTOM(ERR_CHANOPRIVSNEEDED, ERR_CHANOPRIVSNEEDED_BUILDER)
		IRC_EXCEPTION_CUSTOM(ERR_CANTSPEAKINCHANNEL, ERR_CANTSPEAKINCHANNEL_BUILDER)
		IRC_EXCEPTION_CUSTOM(ERR_CANTSPEAKINCHANNELNOTICE, ERR_CANTSPEAKINCHANNELNOTICE_BUILDER)
		IRC_EXCEPTION_CUSTOM(ERR_INVITEONLYCHAN, ERR_INVITEONLYCHAN_BUILDER)
		IRC_EXCEPTION_CUSTOM(ERR_BANNEDFROMCHAN, ERR_BANNEDFROMCHAN_BUILDER)
		IRC_EXCEPTION_CUSTOM(ERR_NOTONCHANNEL, ERR_NOTONCHANNEL_BUILDER)
		IRC_EXCEPTION_CUSTOM_2(ERR_USERNOTINCHANNEL, ERR_USERNOTINCHANNEL_BUILDER)
		IRC_EXCEPTION(ERR_NOPRIVILEGES, "481 :Permission Denied- You're not an IRC operator\r\n")
		IRC_EXCEPTION(ERR_UMODEUNKNOWNFLAG, "501 :Unknown MODE flag\r\n")
		IRC_EXCEPTION(ERR_USERSDONTMATCH, "502 :Cannot change mode for other users\r\n")
};

#endif