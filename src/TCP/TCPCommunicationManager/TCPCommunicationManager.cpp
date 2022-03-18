#include "TCPCommunicationManager.hpp"

TCPCommunicationManager::TCPCommunicationManager() {}

TCPCommunicationManager::TCPCommunicationManager(TCPClientManager* _clientManager) : _clientManager(_clientManager) {}

TCPCommunicationManager::~TCPCommunicationManager() {}

TCPClientManager* TCPCommunicationManager::getClientManager(void) const {
	return this->_clientManager;
}

std::string TCPCommunicationManager::messageBuilder(std::string sender, const char* msg) const {
	std::stringstream ss;

	ss << sender << " -- | " << msg;
	return ss.str();
}

void TCPCommunicationManager::sendToOne(std::string sender, SOCKET sock, const char* rawMsg) {
	(void)sender;
	std::string msg = rawMsg;
	int msgSize = strlen(msg.c_str());

	ssize_t ret_send = send(sock, msg.c_str(), msgSize, 0);
	if (ret_send != (ssize_t)msgSize)
		throw TCPException::SendFailed();
}

void TCPCommunicationManager::sendToAll(std::string sender, const char* msg) {
	for (std::vector<TCPClient>::iterator it = _clientManager->getClients()->begin(); it != _clientManager->getClients()->end(); it++)
		sendToOne(sender, it->getSocket(), msg);
}

void TCPCommunicationManager::sendToChannel(std::string sender, const char* msg, std::string channel) {
	for (std::vector<TCPClient>::iterator it = _clientManager->getClients()->begin(); it != _clientManager->getClients()->end(); it++)
		if (it->getUser().getChannel() == channel)
			sendToOne(sender, it->getSocket(), msg);
}

void TCPCommunicationManager::processClientActivity(void) {
	char* buffer = new char[TCP_BUFFER_SIZE];
	std::vector<SOCKET> clientsToDelete;

	for (std::vector<TCPClient>::iterator it = _clientManager->getClients()->begin(); it != _clientManager->getClients()->end(); it++)
	{
		if (FD_ISSET(it->getSocket(), _clientManager->getReadfds()))
		{
			int ret_read = read(it->getSocket(), buffer, TCP_BUFFER_SIZE);
			if (ret_read == SOCKET_ERROR)
				throw TCPException::ReadFailed();
			else if (ret_read == 0)
				clientsToDelete.push_back(it->getSocket());
			else if (ret_read != 1) // ignore empty messages
			{
				buffer[ret_read] = '\0';
				sendToAll(it->getUser().getUsername(), buffer);
			}
		}
	}
	for (std::vector<SOCKET>::iterator it = clientsToDelete.begin(); it != clientsToDelete.end(); it++)
		_clientManager->disconnectClient(*it);
}
