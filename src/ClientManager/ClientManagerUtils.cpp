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

// std::vector<Client>::iterator ClientManager::disconnectClient(std::vector<Client>::iterator client) {
// 	std::vector<Client>::iterator ret;
// 	std::vector<std::string> channels = client->getChannels();
// 	std::string nickname = client->getNickname();
// 	SOCKET sock = client->getSocket();

// 	for (std::vector<Channel*>::iterator it = channels.begin(); it != channels.end(); ++it) {
// 		(*it)->removeUser(nickname);
// 	}
// 	ret = removeClient(client);
// 	std::cout << "Client with socket " << sock << " (" << nickname << ") disconnected." << std::endl;
// 	return ret;
// }
