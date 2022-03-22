#include "TCPCommunicationManager.hpp"

std::vector<std::string> TCPCommunicationManager::split(const char *buffer, std::string space_delimiter)
{
	std::string buf(buffer);

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
		sendToOne(SERVER_NAME, it->getSocket(), "Enter your username with the commands /USER your_username\n");
	}
	else
	{
		if (buf[1].empty())
			sendToOne(SERVER_NAME, it->getSocket(), "Your username cannot be empty\n");
		else if (buf[1].find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ01234567890_", 0) != std::string::npos)
			sendToOne(SERVER_NAME, it->getSocket(), "Wrongs arguments, characters accepted: abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ01234567890_\n");
		else
			it->_data.setUsername(buf[1]);
	}
}

void TCPCommunicationManager::commandNickname(std::vector<std::string> buf, std::vector<TCPClient>::iterator it)
{
	if (buf.size() != 2)
	{
		sendToOne(SERVER_NAME, it->getSocket(), "Wrongs arguments\n");
		sendToOne(SERVER_NAME, it->getSocket(), "Enter your nickname with the command: /NICK your_nickname");
	}
	else
	{
		if (buf[1].empty())
			sendToOne(SERVER_NAME, it->getSocket(), "Your nickname cannot be empty\n");
		else if (buf[1].find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ01234567890_", 0) != std::string::npos)
			sendToOne(SERVER_NAME, it->getSocket(), "Wrongs arguments, characters accepted: abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ01234567890_\n");
		else
			it->_data.setNickname(buf[1]);
	}
}

void TCPCommunicationManager::commandPass(std::vector<std::string> buf, std::vector<TCPClient>::iterator it)
{
	if (buf.size() != 2)
	{
		sendToOne(SERVER_NAME, it->getSocket(), "Wrongs arguments\n");
		sendToOne(SERVER_NAME, it->getSocket(), "Enter your password with the command: /PASS your_password");
	}
	else
	{
		if (buf[1].empty())
			sendToOne(SERVER_NAME, it->getSocket(), "Your password cannot be empty\n");
		else if (buf[1].find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ01234567890_", 0) != std::string::npos)
			sendToOne(SERVER_NAME, it->getSocket(), "Wrongs arguments, characters accepted: abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ01234567890_\n");
		else
			it->_data.setPassword(buf[1]);
	}
}

void TCPCommunicationManager::commandJoin(std::vector<std::string> buf, std::vector<TCPClient>::iterator it)
{
	if (buf.size() != 3 && buf.size() != 2)
	{
		sendToOne(SERVER_NAME, it->getSocket(), "Wrongs arguments\n");
		sendToOne(SERVER_NAME, it->getSocket(), "/JOIN is used like this: /PASS <canal>,{<canal>} <clé>,{<clé>}");
	}
	else
		commandJoin_Verif(buf, it);
}

// void TCPCommunicationManager::commandMsg(std::vector<std::string> buf, std::vector<TCPClient>::iterator it)
// {
// 	if (verifExistChannel(buf[1]))
// 	{

// 	}
// 	else
// 		std::cout << "Channel existe pas" << std::endl;
// }

void TCPCommunicationManager::command(const char *buffer, std::vector<TCPClient>::iterator it)
{
	std::vector<std::string> buf = split(buffer, " ");
	if (buf[0].compare("/USER") == 0)
		commandUser(buf, it);
	else if (buf[0].compare("/NICK") == 0)
		commandNickname(buf, it);
	else if (buf[0].compare("/PASS") == 0)
		commandPass(buf, it);
	else if (buf[0].compare("/JOIN") == 0)
		commandJoin(buf, it);
	// else if (buf[0].compare("/MSG") == 0)
	// 	commandMsg(buf, it);
	buf.clear();
}