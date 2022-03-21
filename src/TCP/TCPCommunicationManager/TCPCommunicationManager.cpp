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
	std::string msg = sender;
	msg.append(": ");
	msg.append(rawMsg);
	int msgSize = msg.length();

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

std::vector<std::string> TCPCommunicationManager::split(const char *buffer)
{
	std::string buf(buffer);
	std::string space_delimiter = " ";

    std::vector<std::string> ret;

    size_t pos = 0;
    while ((pos = buf.find(space_delimiter)) != std::string::npos)
	{
        ret.push_back(buf.substr(0, pos));
        buf.erase(0, pos + space_delimiter.length());
    }
	if (buf[buf.length() - 1] == '\n')
		buf.erase(buf.length() - 1, 1);
	ret.push_back(buf.substr(0, buf.length()));
    buf.erase(0, buf.length());
	// std::cout << "split ret[0] = " << ret[0] << std::endl;
	// std::cout << "size = " << ret.size() << std::endl;
	// for (size_t i = 0; i < ret.size(); i++)
	// 	std::cout << ret[i] << std::endl;
	return (ret);
}

void TCPCommunicationManager::commandUser(std::vector<std::string> buf, std::vector<TCPClient>::iterator it)
{
	if (buf.size() != 2)
	{
		sendToOne(SERVER_NAME, it->getSocket(), "Wrongs arguments\n");
		sendToOne(SERVER_NAME, it->getSocket(), "Enter your username with the commands /user your_username\n");
	}
	else
	{
		if (buf[1].empty())
			sendToOne(SERVER_NAME, it->getSocket(), "Your username cannot be empty\n");
		else
			it->_data.setUsername(buf[1]);
	}
}

void TCPCommunicationManager::commandNickname(std::vector<std::string> buf, std::vector<TCPClient>::iterator it)
{
	if (buf.size() != 2)
	{
		sendToOne(SERVER_NAME, it->getSocket(), "Wrongs arguments\n");
		sendToOne(SERVER_NAME, it->getSocket(), "Enter your nickname with the command: /nickname your_nickname");
	}
	else
	{
		if (buf[1].empty())
			sendToOne(SERVER_NAME, it->getSocket(), "Your nickname cannot be empty\n");
		else
			it->_data.setNickname(buf[1]);
	}
}

void TCPCommunicationManager::command(const char *buffer, std::vector<TCPClient>::iterator it)
{
	std::vector<std::string> buf = split(buffer);
	if (buf[0].compare("/user") == 0)
		commandUser(buf, it);
	else if (buf[0].compare("/nickname") == 0)
		commandNickname(buf, it);
	buf.clear();
	std::cout << "username = " << it->getUser().getUsername() << std::endl;
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
					if (it->getUser().getUsername().empty())
						sendToOne(SERVER_NAME, it->getSocket(), "Enter your username to communicate\n");
					else
						sendToAll(it->getUser().getUsername(), buffer);
				}		
			}
		}
	}
	for (std::vector<SOCKET>::iterator it = clientsToDelete.begin(); it != clientsToDelete.end(); it++)
		_clientManager->disconnectClient(*it);
}
