#include "TCPClientManager.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>

TCPClientManager::TCPClientManager() {}

TCPClientManager::~TCPClientManager() {
	std::for_each(this->_clients.begin(), this->_clients.end(), TCPClientManager::deleteClient);
	this->_clients.clear();
}

void TCPClientManager::addClient(t_client & client, int nb_client) {
	std::string str("USER");
	std::stringstream ss;
	for (int i = 100; nb_client < i && i > 1; i = i / 10)
		ss << "0";
	ss << nb_client;
	str = ss.str();
	client.user = str;
	std::string str2("");
	client.nickname = str2;
	this->_clients.push_back(client);
}

void TCPClientManager::removeClient(SOCKET client) {
	for (std::vector<t_client>::iterator it = this->_clients.begin(); it != this->_clients.end(); ++it) {
		if (it->socket == client) {
			TCPClientManager::deleteClient(*it);
			this->_clients.erase(it);
			break;
		}
	}
}

SOCKET TCPClientManager::initReadfdsClient(fd_set *readfds, SOCKET max_socket)
{
	for(std::vector<t_client>::iterator it = _clients.begin(); it != _clients.end(); it++)
	{
		FD_SET(it->socket, readfds); //ajoute les sockets des clients au readfds
		if (it->socket > max_socket)
			max_socket = it->socket; //pour select()
	}
	return (max_socket);
}

int TCPClientManager::readClient(fd_set *readfds)
{
	char buffer[1025];
	SOCKET tab_client_to_delete[SOMAXCONN];
	int i = 0;

	for (std::vector<t_client>::iterator it = _clients.begin(); it != _clients.end(); it++)
	{
		if (FD_ISSET(it->socket, readfds))
		{
			int ret_read = read( it->socket, buffer, 1024);
			if (ret_read == SOCKET_ERROR)
				return (-1);
			else if (ret_read == 0) //client déco. Je ne sais pas encore pourquoi mais quand on donne une socket qui n'est pas connecté, FD_ISSET laisse passer. ret_read toujours > 0 lors d'une réception d'un msg d'un client, donc ret_read == 0 -> client déco
			{
				std::cout << "Client disconnected. His socket: " << it->socket << ", his address: " << inet_ntoa(it->sin.sin_addr) << std::endl;
				tab_client_to_delete[i] = it->socket;
				i++;
			}
			else
			{
				buffer[ret_read] = '\0';
				// 	std::cout << "ret_read = " << ret_read << ", buff: |" << buffer << "|" << std::endl;
				std::cout << it->user << ": " << buffer << std::endl;
				std::string received(buffer);
				sendToOthersClient(it->socket, it->user, received);
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
	for (std::vector<t_client>::iterator it = _clients.begin(); it != _clients.end(); it++)
	{
		if (it->socket != sock_sender)
		{
			std::string to_send(sender);
			to_send.append(": ");
			to_send.append(received);
			ssize_t ret_send = send(it->socket, to_send.c_str(), to_send.size(), 0);
			if (ret_send != (ssize_t)to_send.size())
				throw TCPClientManager::SendFailed();
		}
	}
}

std::vector<t_client> TCPClientManager::getClients(void) const {
	return this->_clients;
}
