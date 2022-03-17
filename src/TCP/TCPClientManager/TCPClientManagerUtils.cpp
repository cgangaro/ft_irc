#include "TCPClientManager.hpp"

void TCPClientManager::addSocket(SOCKET sock)
{
	FD_SET(sock, &_readfds);
	if (sock > _maxSocket)
		_maxSocket = sock;
}

void TCPClientManager::deleteClient(TCPClient & client) {
	delete &client;
}

void TCPClientManager::disconnectClient(SOCKET client) {
	std::cout << "Client with socket " << client << " disconnected." << std::endl;
	removeClient(client);
}