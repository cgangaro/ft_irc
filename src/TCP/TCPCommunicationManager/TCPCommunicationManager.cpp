#include "TCPCommunicationManager.hpp"

TCPCommunicationManager::TCPCommunicationManager() {}

TCPCommunicationManager::TCPCommunicationManager(TCPClientManager* _clientManager) : _clientManager(_clientManager) {}

TCPCommunicationManager::~TCPCommunicationManager() {}

TCPClientManager* TCPCommunicationManager::getClientManager(void) const {
	return this->_clientManager;
}

void TCPCommunicationManager::sendToOne(SOCKET sock, const char* msg) {
	int msgSize = strlen(msg);
	ssize_t ret_send = send(sock, msg, msgSize, 0);
	if (ret_send != (ssize_t)msgSize)
		throw TCPException::SendFailed();
}

void TCPCommunicationManager::sendToAll(const char* msg) {
	for (std::vector<TCPClient>::iterator it = _clientManager->getClients()->begin(); it != _clientManager->getClients()->end(); it++)
		sendToOne(it->getSocket(), msg);
}

void TCPCommunicationManager::sendToChannel(const char* msg, std::string channel) {
	for (std::vector<TCPClient>::iterator it = _clientManager->getClients()->begin(); it != _clientManager->getClients()->end(); it++)
		if (it->getUser().getChannel() == channel)
			sendToOne(it->getSocket(), msg);
}
