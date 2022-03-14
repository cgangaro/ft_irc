#include "TCPServer.hpp"

static std::string exceptionMessageBuilder(const std::string &function, const std::string &message) {
	std::stringstream ss;
	ss << function << ": " << message;
	return (ss.str());
}

const char* TCPServer::BindFailed::what() const throw() {
	static std::string message = exceptionMessageBuilder("bind", std::strerror(errno));
	return (message.c_str());
}

const char* TCPServer::SocketCreationFailed::what() const throw() {
	static std::string message = exceptionMessageBuilder("socket", std::strerror(errno));
	return (message.c_str());
}

const char* TCPServer::ListenFailed::what() const throw() {
	static std::string message = exceptionMessageBuilder("listen", std::strerror(errno));
	return (message.c_str());
}

const char* TCPServer::AcceptFailed::what() const throw() {
	static std::string message = exceptionMessageBuilder("accept", std::strerror(errno));
	return (message.c_str());
}

const char* TCPServer::SelectFailed::what() const throw() {
	static std::string message = exceptionMessageBuilder("select", std::strerror(errno));
	return (message.c_str());
}

const char* TCPServer::SendFailed::what() const throw() {
	static std::string message = exceptionMessageBuilder("select", std::strerror(errno));
	return (message.c_str());
}

const char* TCPServer::ReadFailed::what() const throw() {
	static std::string message = exceptionMessageBuilder("select", std::strerror(errno));
	return (message.c_str());
}