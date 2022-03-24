#include "Client.hpp"

Client::Client() {}

Client::Client(SOCKET sock, SOCKADDR_IN sin) : _socket(sock), _sin(sin), _isAuthenticated(false) {
	_data.setSocket(sock);
}

Client::Client(Client const & src) {
	*this = src;
}

Client::~Client() {
}


Client & Client::operator=(Client const &rhs) {
	if (this == &rhs)
		return (*this);
	this->_socket = rhs.getSocket();
	this->_sin = rhs.getSin();
	this->_isAuthenticated = rhs.isAuthenticated();
	this->_data = rhs.getUser();
	return (*this);
}

SOCKET Client::getSocket(void) const {
	return _socket;
}

SOCKADDR_IN Client::getSin(void) const {
	return _sin;
}

char* Client::getAddress(void) const {
	return inet_ntoa(this->_sin.sin_addr);
}

int Client::getPort(void) const {
	return ntohs(this->_sin.sin_port);
}

User Client::getUser(void) const {
	return this->_data;
}

bool Client::isAuthenticated(void) const {
	return _isAuthenticated;
}