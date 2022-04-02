#include "ClientManager.hpp"

void ClientManager::addSocket(SOCKET sock)
{
	FD_SET(sock, &_readfds);
	if (sock > _maxSocket)
		_maxSocket = sock;
}

void ClientManager::deleteClient(Client & client) {
	delete &client;
}

std::vector<Client>::iterator ClientManager::disconnectClient(std::vector<Client>::iterator it) {
	std::cout << "Client with socket " << it->getSocket() << " (" << it->getNickname() << ") disconnected." << std::endl;
	return removeClient(it);
}