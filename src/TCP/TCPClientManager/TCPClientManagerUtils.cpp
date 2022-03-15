#include "TCPClientManager.hpp"

void TCPClientManager::deleteClient(t_client & client) {
	close(client.socket);
}

// void TCPClientManager::user(t_client *client, char *msg)
// {

// }