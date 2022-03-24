#include "CommunicationManager.hpp"

Channel CommunicationManager::returnChannel(std::string channel)
{
	for (size_t i = 0; i < _channels_server.size(); i++)
	{
		if (_channels_server[i].getName().compare(channel) == 0)
		{
			return (_channels_server[i]);
		}
	}
	Channel ret;
	return (ret);
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

bool CommunicationManager::verifPasswordChannel(std::string channel, std::string password)
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

void CommunicationManager::addUserChannel(std::string channel, Client user)
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

void CommunicationManager::commandJoin_Verif(std::vector<std::string> buf, std::vector<Client>::iterator it)
{
	if (buf.size() <= 2)
		joinChannel_withoutPass(buf, it);
	else
		joinChannel_withPass(buf, it);
}

void CommunicationManager::joinChannel_withPass(std::vector<std::string> buf, std::vector<Client>::iterator it)
{
	std::cout << "joinChannel_withPass" << std::endl;
	std::vector<std::string> cmd_channels = split(buf[1].c_str(), ",");
	std::vector<std::string> cmd_pass = split(buf[2].c_str(), ",");
	if (it->getChannels().size() + buf.size() > 10)
	{
		sendToOne(SERVER_NAME, it->getSocket(), "Max channels per user: 10\n");
		return ;
	}
	std::cout << "cmd_channels.size()" << cmd_channels.size() << std::endl;
	for (size_t i = 0; i < cmd_channels.size(); i++)
	{
		if (verifExistChannel(cmd_channels[i]))
		{
			std::cout << "channel exist" << std::endl;
			if ((i < cmd_pass.size() && verifPasswordChannel(cmd_channels[i], cmd_pass[i])) || (i >= cmd_pass.size() && verifPasswordChannel(cmd_channels[i], "")))
			{
				it->addChannel(cmd_channels[i]);
				addUserChannel(cmd_channels[i], *it);
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
			std::cout << "channel not exist" << std::endl;
			if (i < cmd_pass.size())
			{
				Channel new_channel(cmd_channels[i], cmd_pass[i], *it);
				_channels_server.push_back(new_channel);
			}
			else
			{
				Channel new_channel(cmd_channels[i], "", *it);
				std::cout << "new_channel name = " << new_channel.getName() << "new_Channel password = " << new_channel.getPassword() << std::endl;
				_channels_server.push_back(new_channel);
			}
			it->addChannel(cmd_channels[i]);
		}
	}
}

void CommunicationManager::joinChannel_withoutPass(std::vector<std::string> buf, std::vector<Client>::iterator it)
{
	std::cout << "joinChannel_withoutpass" << std::endl;
	std::vector<std::string> cmd_channels = split(buf[1].c_str(), ",");
	if (it->getChannels().size() + buf.size() > 10)
	{
		sendToOne(SERVER_NAME, it->getSocket(), "Max channels per user: 10\n");
		return ;
	}
	std::cout << "cmd_channels.size() " << cmd_channels.size() << std::endl;
	for (size_t i = 0; i < cmd_channels.size(); i++)
	{
		if (verifExistChannel(cmd_channels[i]))
		{
			std::cout << "channel exist" << std::endl;
			addUserChannel(cmd_channels[i], *it);
		}
		else
		{
			std::cout << "channel not exist" << std::endl;
			Channel new_channel(cmd_channels[i], "", *it);
			std::cout << "new_channel name = " << new_channel.getName() << " new_Channel password = " << new_channel.getPassword() << std::endl;
			_channels_server.push_back(new_channel);
			it->addChannel(cmd_channels[i]);
		}
	}
}

std::vector<std::string> CommunicationManager::split(const char *buffer, std::string space_delimiter)
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
