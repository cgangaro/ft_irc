#include "CommunicationManager.hpp"

CommunicationManager::CommunicationManager() {}

CommunicationManager::CommunicationManager(ClientManager* _clientManager) : _clientManager(_clientManager) {
/* 	std::cout << "=== CommunicationManager constructor ===" << std::endl;
	std::cout << "\tthis: " << this << std::endl;
	std::cout << "\t_clientManager: " << _clientManager << std::endl;
	std::cout << "=== CommunicationManager END ===" << std::endl; */
}

CommunicationManager::~CommunicationManager() {}

void CommunicationManager::setInterpreter(Command interpreter) {
	this->_interpreter = interpreter;
}

CommunicationManager& CommunicationManager::operator=(const CommunicationManager& cm) {
	this->_clientManager = cm._clientManager;
	this->_interpreter = cm._interpreter;
	return *this;
}

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

void CommunicationManager::sendToOne(std::string sender, std::string channel, SOCKET sock, std::string rawMsg) {
	std::string msg_to_send("[" + sender + "]");
	if (!channel.empty())
		msg_to_send = msg_to_send + "[" + channel + "]";
	msg_to_send = msg_to_send + ": " + rawMsg + CRLF;
	sendMsg(sock, msg_to_send);
}

void CommunicationManager::sendToChannel(Client client, Channel channel, std::string msg)
{
	for (size_t i = 0; i < channel.getListUser().size(); i++)
	{
		if (channel.getListUser()[i] != client.getSocket())
			sendToOne(client.getUsername(), channel.getName(), channel.getListUser()[i], msg);
	}
}

void CommunicationManager::processClientActivity(void) {
	char* buffer = new char[BUFFER_SIZE];
	std::vector<SOCKET> clientsToDelete;
	bool shouldDelete = false;
	int ret_read;

/* 	std::cout << "=== " << __func__ << " ===" << std::endl;
	std::cout << "\tthis: " << this << std::endl;
	std::cout << "\t_clientManager: " << _clientManager << std::endl;
	std::cout << "\tnbClients(): " << _clientManager->getNbClient() << std::endl; */
	for (std::vector<Client>::iterator it = _clientManager->getClients()->begin(); it != _clientManager->getClients()->end(); it++)
	{
		if (FD_ISSET(it->getSocket(), _clientManager->getReadfds()))
		{
			ret_read = read(it->getSocket(), buffer, BUFFER_SIZE);
			if (ret_read == SOCKET_ERROR) throw Exception::ReadFailed();
			else if (ret_read == 0) clientsToDelete.push_back(it->getSocket());
			else if (ret_read != 1) // ignore empty messages
			{
				buffer[ret_read] = '\0';
				shouldDelete = _interpreter.interpret(buffer, &(*it));
				if (shouldDelete) clientsToDelete.push_back(it->getSocket());
			}
		}
	}
	for (std::vector<SOCKET>::iterator it = clientsToDelete.begin(); it != clientsToDelete.end(); it++) {
		_clientManager->disconnectClient(*it);
	}
	delete[] buffer;
}

bool CommunicationManager::verifExistChannel(std::string channel)
{
	std::cout << "size = " << _channels_server.size() << std::endl;
	for (size_t i = 0; i < _channels_server.size(); i++)
	{
		if (_channels_server[i].getName().compare(channel) == 0)
		{
			return (true);
		}
	}
	return (false);
}

bool CommunicationManager::verifChannelPassword(std::string channel, std::string password)
{
	for (size_t i = 0; i < _channels_server.size(); i++)
	{
		if (_channels_server[i].getName().compare(channel) == 0)
		{
			if (_channels_server[i].getPassword().compare(password) == 0)
				return (true);
			else
				return (false);
		}
	}
	return (false);
}

void CommunicationManager::addChannel(std::string channel, std::string password, SOCKET admin)
{
	std::cout << "test addChannel 1" << std::endl;
	Channel new_channel(channel, password, admin);
	std::cout << "new_channel name = " << new_channel.getName() << ", new_Channel password = " << new_channel.getPassword() << std::endl;
	_channels_server.push_back(new_channel);
	std::cout << "test addChannel 2" << std::endl;
}

Channel * CommunicationManager::returnChannel(std::string channel)
{
	for (size_t i = 0; i < _channels_server.size(); i++)
	{
		if (_channels_server[i].getName().compare(channel) == 0)
		{
			return (&_channels_server[i]);
		}
	}
	Channel *ret = NULL;
	return (ret);
}

void CommunicationManager::test_printChannels(void)
{
	std::cout << "Print server channels" << std::endl;
	std::cout << "size = " << _channels_server.size() << std::endl;
	for (size_t i = 0; i < _channels_server.size(); i++)
	{
		std::cout << _channels_server[i].getName() << std::endl;
	}
	std::cout << "End print server channels" << std::endl;
}
