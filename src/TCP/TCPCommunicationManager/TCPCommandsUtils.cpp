#include "TCPCommunicationManager.hpp"

bool TCPCommunicationManager::verifExistChannel(std::string channel)
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

bool TCPCommunicationManager::verifPasswordChannel(std::string channel, std::string password)
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
void TCPCommunicationManager::addUserChannel(std::string channel, std::string user)
{
	for (size_t i = 0; i < _channels_server.size(); i++)
	{
		if (_channels_server[i].getName().compare(channel) == 0)
		{
			_channels_server[i].addUser(user);
			return ;
		}
	}
	return ;
}

void TCPCommunicationManager::commandJoin_Verif(std::vector<std::string> buf, std::vector<TCPClient>::iterator it)
{
	std::vector<std::string> cmd_channels = split(buf[1].c_str(), ",");
	std::vector<std::string> cmd_pass = split(buf[2].c_str(), ",");
	if (it->getUser().getChannels().size() + buf.size() > 10)
	{
		sendToOne(SERVER_NAME, it->getSocket(), "Max channels per user: 10\n");
		return ;
	}
	for (size_t i = 0; i < cmd_channels.size(); i++)
	{
		if (verifExistChannel(cmd_channels[i]))
		{
			if ((i < cmd_pass.size() && verifPasswordChannel(cmd_channels[i], cmd_pass[i])) || (i >= cmd_pass.size() && verifPasswordChannel(cmd_channels[i], "")))
			{
				it->_data.addChannel(cmd_channels[i]);
				addUserChannel(cmd_channels[i], it->getUser().getUsername());
			}
			else
			{
				std::string msg = "Wrong password for channel ";
				msg.append(cmd_channels[i]);
				msg.append("\n");
				sendToOne(SERVER_NAME, it->getSocket(), msg.c_str());
			}
		}
		else
		{
			if (i < cmd_pass.size())
			{
				Channel new_channel(cmd_channels[i], cmd_pass[i], it->getUser().getUsername());
				_channels_server.push_back(new_channel);
			}
			else
			{
				Channel new_channel(cmd_channels[i], "", it->getUser().getUsername());
				_channels_server.push_back(new_channel);
			}
			it->_data.addChannel(cmd_channels[i]);
		}
	}
}