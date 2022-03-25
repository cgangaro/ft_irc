#include "ClientManager.hpp"

ClientManager::ClientManager() {
	FD_ZERO(&_readfds);
	_maxSocket = 0;
}

ClientManager::~ClientManager() {
	std::for_each(this->_clients.begin(), this->_clients.end(), ClientManager::deleteClient);
	this->_clients.clear();
}

int ClientManager::getMaxSocket(void) const {
	return (this->_maxSocket);
}

int ClientManager::getNbClient(void) const {
	return (this->_clients.size());
}

fd_set* ClientManager::getReadfds(void) {
	return (&this->_readfds);
}

void ClientManager::addClient(SOCKET sock, SOCKADDR_IN sin) {
	Client newClient(sock, sin);

	FD_SET(sock, &_readfds);
	if (sock > _maxSocket)
		_maxSocket = sock;
	this->_clients.push_back(newClient);
}

void ClientManager::removeClient(SOCKET csock) {
	for (std::vector<Client>::iterator it = _clients.begin(); it != _clients.end(); ++it) {
		if (it->getSocket() == csock) {
			FD_CLR(csock, &_readfds);
			close(csock);
			this->_clients.erase(it);
			break;
		}
	}
	refreshMaxSocket();
}

std::vector<Client>* ClientManager::getClients(void) {
	return &this->_clients;
}

void ClientManager::refreshMaxSocket() {
	this->_maxSocket = 0;
	for (std::vector<Client>::iterator it = _clients.begin(); it != _clients.end(); ++it) {
		if (it->getSocket() > _maxSocket)
			_maxSocket = it->getSocket();
	}
}

bool ClientManager::isNicknameTaken(std::string nickname) const {
	//std::cout << __func__ << " nbClients(): " << this->getNbClient() << std::endl;
	for (std::vector<Client>::const_iterator it = _clients.begin(); it != _clients.end(); ++it) {
		if (it->getNickname() == nickname)
			return true;
	}
	return false;
}
