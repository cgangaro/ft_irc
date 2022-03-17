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