#include "CommunicationManager.hpp"

CommunicationManager::CommunicationManager() {}

CommunicationManager::CommunicationManager(ClientManager* _clientManager) : _clientManager(_clientManager) {}

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

Channel* CommunicationManager::getChannel(std::string channelName) {
	for (std::vector<Channel>::iterator it = _channels_server.begin(); it != _channels_server.end(); ++it) {
		if (it->getName() == channelName)
			return &(*it);
	}
	return NULL;
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

	if (sock < 0) return ;
	ssize_t ret_send = send(sock, msg.c_str(), msgSize, 0);
	if (ret_send != (ssize_t)msgSize)
		throw Exception::SendFailed();
}

void CommunicationManager::sendToOne(std::string sender, std::string channel, SOCKET sock, std::string rawMsg) {
	// std::string msg_to_send("[" + sender + "]");
	// if (!channel.empty())
	// 	msg_to_send = msg_to_send + "[" + channel + "]";
	// msg_to_send = msg_to_send + ": " + rawMsg + CRLF;
	(void)channel;
	(void)sender;
	std::string msg_to_send(rawMsg);
	sendMsg(sock, msg_to_send);
}

void CommunicationManager::sendToChannel(Client client, Channel channel, std::string msg, bool server_msg)
{
	std::string sujet = client.getSujet();
	if (!server_msg && (channel.getModeSettings() & F_MODERATED) && !channel.canUserSpeak(client.getNickname()))
		throw Exception::ERR_CANTSPEAKINCHANNEL(channel.getName());
	if ((channel.getModeSettings() & F_ANONYMOUS))
		sujet = "anonymous!anonymous@anonymous.";
	if (server_msg && (channel.getModeSettings() & F_QUIET))
		return ;
	for (size_t i = 0; i < channel.getUserList().size(); i++)
	{
		if (channel.getUserList()[i].nickname != client.getNickname())
			sendToOne(client.getUsername(), channel.getName(), _clientManager->retSocketClient(channel.getUserList()[i].nickname), sujet + " " + msg);
	}
}

void CommunicationManager::processClientActivity(void) {
	char* buffer = new char[BUFFER_SIZE];
	bool shouldDelete = false;
	int ret_read;

	for (std::vector<Client>::iterator it = _clientManager->getClients()->begin(); it != _clientManager->getClients()->end(); it++)
	{
		if (FD_ISSET(it->getSocket(), _clientManager->getReadfds()))
		{
			ret_read = read(it->getSocket(), buffer, BUFFER_SIZE);
			if (ret_read == SOCKET_ERROR) throw Exception::ReadFailed();
			else if (ret_read == 0) it = _clientManager->disconnectClient(it);
			else if (ret_read != 1) // ignore empty messages
			{
				buffer[ret_read] = '\0';
				shouldDelete = _interpreter.interpret(buffer, &(*it));
				if (shouldDelete) it = _clientManager->disconnectClient(it);
			}
		}
		if (it == _clientManager->getClients()->end()) break;
	}
	_clientManager->disconnectClientsToKill();
	delete[] buffer;
}

void CommunicationManager::addClientToKill(std::string client_nickname) {
	_clientManager->addClientToKill(client_nickname);
}

bool CommunicationManager::verifExistChannel(std::string channel)
{
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

void CommunicationManager::addChannel(std::string channel, std::string password, std::string admin)
{
	Channel new_channel(channel, password, admin);
	_channels_server.push_back(new_channel);
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

std::string CommunicationManager::RPL_TOPIC_builder(Client * client, std::string sujet)
{
	std::string ret(client->getSujet() + " " + sujet + CRLF);
	return (ret);
}

std::string CommunicationManager::RPL_CHANNELMODEIS_builder(std::string canal, std::string channel, std::string param_mode)
{
	std::string ret (":" + canal + " MODE " + channel + " " + param_mode + CRLF);
	return (ret);
}

std::string CommunicationManager::RPL_NAMREPLY_builder(std::string canal, Channel channel, Client client)
{
	std::string ret (":" + canal + " 353 " + client.getNickname() + " @ " + channel.getName() + " :");
	std::vector<Client> iencli = *_clientManager->getClients();
	bool f = false;
	for (size_t i = 0; i < iencli.size(); i++)
	{
		if (channel.verifIfRegisteredUser(iencli[i].getNickname()))
		{
			if (f == true)
				ret = ret + " ";
			f = true;
			if (channel.verifIfRegisteredAdmin(iencli[i].getNickname()))
				ret = ret + "@" + iencli[i].getNickname();
			else if (channel.canUserSpeak(iencli[i].getNickname()))
				ret = ret + "+" + iencli[i].getNickname();
			else
				ret = ret + iencli[i].getNickname();
		}
	}
	ret = ret + CRLF;
	return (ret);
}

std::string CommunicationManager::RPL_ENDOFNAMES_builder(std::string canal, Channel channel, Client client)
{
	std::string ret (":" + canal + " 366 " + client.getNickname() + " " + channel.getName() + " :End of /NAMES list." + CRLF);
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

void CommunicationManager::sendToHisChannels(Client client, std::string msg)
{
	for (std::vector<Client>::iterator it = _clientManager->getClients()->begin(); it != _clientManager->getClients()->end(); ++it)
	{
		if (it->hasCommonChannel(client))
			sendToOne(client.getUsername(), "", it->getSocket(), msg);
	}
}
