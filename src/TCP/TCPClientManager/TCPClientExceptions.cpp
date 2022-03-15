#include "TCPClientManager.hpp"

static std::string exceptionMessageBuilder(const std::string &function, const std::string &message) {
	std::stringstream ss;
	ss << function << ": " << message;
	return (ss.str());
}

const char* TCPClientManager::SendFailed::what() const throw() {
	static std::string message = exceptionMessageBuilder("select", std::strerror(errno));
	return (message.c_str());
}