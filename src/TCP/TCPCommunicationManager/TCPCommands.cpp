#include "TCPCommunicationManager.hpp"

void TCPCommunicationManager::command(const char *buffer, std::vector<TCPClient>::iterator it)
{
	std::vector<std::string> buf = split(buffer, " ");
	std::string buf_str(buffer);
	if (buf[0].compare("/USER") == 0)
		commandUser(buf, it);
	else if (buf[0].compare("/NICK") == 0)
		commandNickname(buf, it);
	else if (buf[0].compare("/PASS") == 0)
		commandPass(buf, it);
	else if (buf[0].compare("/JOIN") == 0)
		commandJoin(buf, it);
	else if (buf[0].compare("/MSG") == 0)
		commandMsg(buf, buf_str, it);
	buf.clear();
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

void TCPCommunicationManager::commandMsg(std::vector<std::string> buf, std::string buf_str, std::vector<TCPClient>::iterator it)
{
	if (verifExistChannel(buf[1]) && returnChannel(buf[1]).verifIfUser(it->getUser()))
	{
		std::string msg_to_send(buf_str);
		msg_to_send.erase(0, msg_to_send.find(" ") + 1);
		msg_to_send.erase(0, msg_to_send.find(" ") + 1);
		sendToChannel(it->getUser().getUsername(), msg_to_send, buf[1]);
	}
}