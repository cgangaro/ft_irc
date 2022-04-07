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

std::vector<Client>::iterator ClientManager::disconnectClient(std::vector<Client>::iterator client) {
	std::vector<Client>::iterator ret;
	std::vector<Channel*> channels = client->getChannels();

	for (std::vector<Channel*>::iterator it = channels.begin(); it != channels.end(); ++it) {
		if ((*it)->verifIfRegisteredAdmin(client->getNickname()))
			(*it)->removeAdmin(client->getNickname());
		(*it)->removeUser(client->getNickname());
	}
	ret = removeClient(client);
	std::cout << "Client with socket " << client->getSocket() << " (" << client->getNickname() << ") disconnected." << std::endl;
	return ret;
}
