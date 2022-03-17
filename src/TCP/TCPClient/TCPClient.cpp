#include "TCPClient.hpp"

TCPClient::TCPClient() {}

TCPClient::TCPClient(SOCKET sock, SOCKADDR_IN sin) : _socket(sock), _sin(sin), _isAuthenticated(false) {}

TCPClient::~TCPClient() {

}

SOCKET TCPClient::getSocket(void) const {
	return _socket;
}

char* TCPClient::getAddress(void) const {
	return inet_ntoa(this->_sin.sin_addr);
}

int TCPClient::getPort(void) const {
	return ntohs(this->_sin.sin_port);
}

bool TCPClient::isAuthenticated(void) const {
	return _isAuthenticated;
}