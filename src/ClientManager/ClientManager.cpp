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

std::vector<Client>::iterator ClientManager::removeClient(std::vector<Client>::iterator it) {
	std::vector<Client>::iterator newIt;
	SOCKET csock = it->getSocket();

	FD_CLR(csock, &_readfds);
	close(csock);
	newIt = this->_clients.erase(it);
	refreshMaxSocket();
	return newIt;
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
	for (std::vector<Client>::const_iterator it = _clients.begin(); it != _clients.end(); ++it) {
		if (it->getNickname() == nickname)
			return true;
	}
	return false;
}

bool ClientManager::checkListUsers(std::string user) const {
	for (size_t i = 0; i < _clients.size(); i++)
	{
		if (_clients[i].getUsername().compare(user) == 0)
			return (true);
	}
	return (false);
}

SOCKET ClientManager::retSocketClient(std::string client_name) const {
	for (size_t i = 0; i < _clients.size(); i++)
	{
		if (_clients[i].getUsername().compare(client_name) == 0)
			return (_clients[i].getSocket());
	}
	return (-1);
}

void ClientManager::addClientToKill(std::string client_nickname) {
	for (size_t i = 0; i < _clients.size(); i++)
	{
		if (_clients[i].getNickname().compare(client_nickname) == 0) {
			_clients[i].setToKill();
			break ;
		}
	}
}

void ClientManager::disconnectClientsToKill(void) {
	for (std::vector<Client>::iterator it = _clients.begin(); it != _clients.end(); ++it) {
		if (it->getToKill())
		{
			it = disconnectClient(it);
			if (it == _clients.end()) break;
		}
	}
}


