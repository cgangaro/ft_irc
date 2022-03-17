#include "TCPClientManager.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>

TCPClientManager::TCPClientManager() {
	FD_ZERO(&_readfds);
	_maxSocket = 0;
}

TCPClientManager::~TCPClientManager() {
	std::for_each(this->_clients.begin(), this->_clients.end(), TCPClientManager::deleteClient);
	this->_clients.clear();
}

int TCPClientManager::getMaxSocket(void) const {
	return (this->_maxSocket);
}

int TCPClientManager::getNbClient(void) const {
	return (this->_clients.size());
}

fd_set* TCPClientManager::getReadfds(void) {
	return (&this->_readfds);
}

void TCPClientManager::addClient(SOCKET sock, SOCKADDR_IN sin) {
	TCPClient* newClient = new TCPClient(sock, sin);

	FD_SET(sock, &_readfds);
	if (sock > _maxSocket)
		_maxSocket = sock;
	this->_clients.push_back(*newClient);
}

void TCPClientManager::removeClient(SOCKET csock) {
	for (std::vector<TCPClient>::iterator it = _clients.begin(); it != _clients.end(); ++it) {
		if (it->getSocket() == csock) {
			FD_CLR(csock, &_readfds);
			TCPClientManager::deleteClient(*it);
			_clients.erase(it);
			break;
		}
	}
}

std::vector<TCPClient>* TCPClientManager::getClients(void) {
	return &this->_clients;
}
