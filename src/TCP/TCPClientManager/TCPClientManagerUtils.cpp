#include "TCPClientManager.hpp"

void TCPClientManager::deleteClient(t_client & client) {
	close(client.socket);
}