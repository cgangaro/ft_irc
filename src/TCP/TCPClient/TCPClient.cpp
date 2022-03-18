#include "TCPClient.hpp"

TCPClient::TCPClient() {}

TCPClient::TCPClient(SOCKET sock, SOCKADDR_IN sin) : _socket(sock), _sin(sin), _isAuthenticated(false) {}

TCPClient::TCPClient(TCPClient const & src) {
	*this = src;
}

TCPClient::~TCPClient() {
}


TCPClient & TCPClient::operator=(TCPClient const &rhs) {
	if (this == &rhs)
		return (*this);
	this->_socket = rhs.getSocket();
	this->_sin = rhs.getSin();
	this->_isAuthenticated = rhs.isAuthenticated();
	this->_data = rhs.getUser();
	return (*this);
}

SOCKET TCPClient::getSocket(void) const {
	return _socket;
}

SOCKADDR_IN TCPClient::getSin(void) const {
	return _sin;
}

char* TCPClient::getAddress(void) const {
	return inet_ntoa(this->_sin.sin_addr);
}

int TCPClient::getPort(void) const {
	return ntohs(this->_sin.sin_port);
}

User TCPClient::getUser(void) const {
	return this->_data;
}

bool TCPClient::isAuthenticated(void) const {
	return _isAuthenticated;
}