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

void ClientManager::disconnectClient(SOCKET client) {
	std::cout << "Client with socket " << client << " disconnected." << std::endl;
	removeClient(client);
}