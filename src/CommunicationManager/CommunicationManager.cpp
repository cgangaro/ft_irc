#include "CommunicationManager.hpp"

CommunicationManager::CommunicationManager() {}

CommunicationManager::CommunicationManager(ClientManager* _clientManager) : _clientManager(_clientManager) {}

CommunicationManager::~CommunicationManager() {}

ClientManager* CommunicationManager::getClientManager(void) const {
	return this->_clientManager;
}

std::string CommunicationManager::messageBuilder(std::string sender, const char* msg) const {
	std::stringstream ss;

	ss << sender << " -- | " << msg;
	return ss.str();
}

void CommunicationManager::sendMsg(SOCKET sock, std::string msg)
{
	std::cout << "sendMsg to " << sock << std::endl;
	int msgSize = msg.length();
	ssize_t ret_send = send(sock, msg.c_str(), msgSize, 0);
	if (ret_send != (ssize_t)msgSize)
		throw Exception::SendFailed();
}

void CommunicationManager::sendToOne(std::string sender, SOCKET sock, const char* rawMsg) {
	std::string msg = sender;
	msg.append(": ");
	msg.append(rawMsg);
	sendMsg(sock, msg);
}

void CommunicationManager::sendToChannel(std::string sender, std::string msg, std::string channel_str)
{
	std::string msg_to_send("[");
	msg_to_send.append(channel_str);
	msg_to_send.append("][");
	msg_to_send.append(sender);
	msg_to_send.append("] ");
	msg_to_send.append(msg);
	std::vector<Client> list = returnChannel(channel_str).getListUser();
	for (size_t i = 0; i < list.size(); i++)
	{
		if (list[i].getUsername() != sender)
			sendMsg(list[i].getSocket(), msg_to_send.c_str());
	}
}

void CommunicationManager::sendToAll(std::string sender, const char* msg) {
	for (std::vector<Client>::iterator it = _clientManager->getClients()->begin(); it != _clientManager->getClients()->end(); it++)
		sendToOne(sender, it->getSocket(), msg);
}

void CommunicationManager::processClientActivity(void) {
	char* buffer = new char[BUFFER_SIZE];
	std::vector<SOCKET> clientsToDelete;

	for (std::vector<Client>::iterator it = _clientManager->getClients()->begin(); it != _clientManager->getClients()->end(); it++)
	{
		if (FD_ISSET(it->getSocket(), _clientManager->getReadfds()))
		{
			int ret_read = read(it->getSocket(), buffer, BUFFER_SIZE);
			if (ret_read == SOCKET_ERROR)
				throw Exception::ReadFailed();
			else if (ret_read == 0)
				clientsToDelete.push_back(it->getSocket());
			else if (ret_read != 1) // ignore empty messages
			{
				buffer[ret_read] = '\0';
				if (buffer[0] == '/')
					command(buffer, it);
				else
				{
					if (it->getUsername().empty() || it->getNickname().empty() || it->getPassword().empty())
						sendToOne(SERVER_NAME, it->getSocket(), "Enter your username, your nickname and your password to communicate\n");
					else
						sendToAll(it->getUsername(), buffer);
				}		
			}
		}
	}
	for (std::vector<SOCKET>::iterator it = clientsToDelete.begin(); it != clientsToDelete.end(); it++)
		_clientManager->disconnectClient(*it);
}
