#include "CommunicationManager.hpp"

CommunicationManager::CommunicationManager() {}

CommunicationManager::CommunicationManager(ClientManager* _clientManager, std::string pwd) : _clientManager(_clientManager) {
	_interpreter = Command(this, pwd);	
}

CommunicationManager::~CommunicationManager() {}

ClientManager* CommunicationManager::getClientManager(void) const {
	return this->_clientManager;
}

std::string CommunicationManager::messageBuilder(std::string sender, Channel & channel, const char* msg) const {
	std::stringstream ss;

	(void)channel;

	ss << sender << " -- | " << msg;
	return ss.str();
}

void CommunicationManager::sendMsg(SOCKET sock, std::string msg)
{
	int msgSize = msg.length();
	ssize_t ret_send = send(sock, msg.c_str(), msgSize, 0);
	if (ret_send != (ssize_t)msgSize)
		throw Exception::SendFailed();
}

void CommunicationManager::sendToOne(std::string sender, Channel & channel, SOCKET sock, const char* rawMsg) {
	std::string msg = rawMsg;

	(void)channel;
	(void)sender;

	sendMsg(sock, msg);
}

void CommunicationManager::sendToChannel(std::string sender, Channel & channel, std::string msg)
{
	(void)sender;
	(void)channel;
	(void)msg;
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
				_interpreter.interpret(buffer, *it);
				if (!it->isAuthenticated())
					clientsToDelete.push_back(it->getSocket());
			}
		}
	}
	for (std::vector<SOCKET>::iterator it = clientsToDelete.begin(); it != clientsToDelete.end(); it++) {
		_clientManager->disconnectClient(*it);
	}
	delete[] buffer;
}
