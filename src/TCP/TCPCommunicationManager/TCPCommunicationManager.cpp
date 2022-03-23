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

void TCPCommunicationManager::sendMsg(SOCKET sock, std::string msg)
{
	std::cout << "sendMsg to " << sock << std::endl;
	int msgSize = msg.length();
	ssize_t ret_send = send(sock, msg.c_str(), msgSize, 0);
	if (ret_send != (ssize_t)msgSize)
		throw TCPException::SendFailed();
}

void TCPCommunicationManager::sendToOne(std::string sender, SOCKET sock, const char* rawMsg) {
	std::string msg = sender;
	msg.append(": ");
	msg.append(rawMsg);
	sendMsg(sock, msg);
}

void TCPCommunicationManager::sendToChannel(std::string sender, std::string msg, std::string channel_str)
{
	std::string msg_to_send("[");
	msg_to_send.append(channel_str);
	msg_to_send.append("][");
	msg_to_send.append(sender);
	msg_to_send.append("] ");
	msg_to_send.append(msg);
	std::vector<User> list = returnChannel(channel_str).getListUser();
	for (size_t i = 0; i < list.size(); i++)
	{
		if (list[i].getUsername() != sender)
			sendMsg(list[i].getSocket(), msg_to_send.c_str());
	}
}

void TCPCommunicationManager::sendToAll(std::string sender, const char* msg) {
	for (std::vector<TCPClient>::iterator it = _clientManager->getClients()->begin(); it != _clientManager->getClients()->end(); it++)
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
				if (buffer[0] == '/')
					command(buffer, it);
				else
				{
					if (it->getUser().getUsername().empty() || it->getUser().getNickname().empty() || it->getUser().getPassword().empty())
						sendToOne(SERVER_NAME, it->getSocket(), "Enter your username, your nickname and your password to communicate\n");
					else
						sendToAll(it->getUser().getUsername(), buffer);
				}		
			}
		}
	}
	for (std::vector<SOCKET>::iterator it = clientsToDelete.begin(); it != clientsToDelete.end(); it++)
		_clientManager->disconnectClient(*it);
}
