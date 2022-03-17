#include "TCPClientManager.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>

TCPClientManager::TCPClientManager() {
	FD_ZERO(&_readfds);
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

void TCPClientManager::removeClient(SOCKET client) {
	for (std::vector<TCPClient>::iterator it = this->_clients.begin(); it != this->_clients.end(); ++it) {
		if (it->getSocket() == client) {
			FD_CLR(client, &_readfds);
			TCPClientManager::deleteClient(*it);
			this->_clients.erase(it);
			break;
		}
	}
}

int TCPClientManager::readClient()
{
	char buffer[1025];
	SOCKET tab_client_to_delete[SOMAXCONN];
	int i = 0;

	for (std::vector<TCPClient>::iterator it = _clients.begin(); it != _clients.end(); it++)
	{
		if (FD_ISSET(it->getSocket(), &_readfds))
		{
			int ret_read = read(it->getSocket(), buffer, 1024);
			if (ret_read == SOCKET_ERROR)
				return (-1);
			else if (ret_read == 0) //client déco. Je ne sais pas encore pourquoi mais quand on donne une socket qui n'est pas connecté, FD_ISSET laisse passer. ret_read toujours > 0 lors d'une réception d'un msg d'un client, donc ret_read == 0 -> client déco
			{
				std::cout << "Client disconnected. His socket: " << it->getSocket() << ", his address: " << it->getAddress() << std::endl;
				tab_client_to_delete[i] = it->getSocket();
				i++;
			}
			else
			{
				buffer[ret_read] = '\0';
				// 	std::cout << "ret_read = " << ret_read << ", buff: |" << buffer << "|" << std::endl;
				std::cout << "username" << ": " << buffer << std::endl;
				std::string received(buffer);
				sendToOthersClient(it->getSocket(), "username", received);
			}
		}
	}
	for(int y = 0; y < i; y++)
	{
		removeClient(tab_client_to_delete[y]);
	}
	return (0);
}

void	TCPClientManager::sendToOthersClient(SOCKET sock_sender, std::string sender, std::string received)
{
	for (std::vector<TCPClient>::iterator it = _clients.begin(); it != _clients.end(); it++)
	{
		if (it->getSocket() != sock_sender)
		{
			std::string to_send(sender);
			to_send.append(": ");
			to_send.append(received);
			ssize_t ret_send = send(it->getSocket(), to_send.c_str(), to_send.size(), 0);
			if (ret_send != (ssize_t)to_send.size())
				throw TCPException::SendFailed();
		}
	}
}

std::vector<TCPClient> TCPClientManager::getClients(void) const {
	return this->_clients;
}
