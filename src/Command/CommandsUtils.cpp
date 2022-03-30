#include "Command.hpp"
#include "CommunicationManager.hpp"
#include "Commons.hpp"

bool Command::isValidStringData(std::string & data) {
	unsigned long pos;

	if (data.empty())
		return false;
	pos = data.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_#!+&\r\n");
	return (pos == std::string::npos);
}

void Command::eraseSubstr(std::string & str, const std::string & substr) {
	size_t pos = 0;

	while ((pos = str.find(substr, pos)) != std::string::npos) {
		str.erase(pos, substr.length());
	}
}

std::vector<std::string> Command::split(const char *buffer, std::string separators)
{
	std::string buf(buffer);

    std::vector<std::string> ret;

    size_t pos = 0;
    while ((pos = buf.find_first_of(separators)) != std::string::npos)
	{
        ret.push_back(buf.substr(0, pos));
        buf.erase(0, pos + 1);
    }
	if (!buf.empty())
		ret.push_back(buf.substr(0, buf.length()));
	buf.erase(0, buf.length());
	return (ret);
}

void Command::addClientChannel(Client * client, Channel * channel, bool creator)
{
	//(void)creator;
	if (!(client->verifIfRegisteredChannel(channel)))
		client->addChannel(channel);
	// if (!(channel->verifIfRegisteredAdmin(client->getSocket())))
	// 	channel->addAdmin(client->getSocket());
	if (!(channel->verifIfRegisteredUser(client->getSocket())))
		channel->addUser(client->getSocket());
	std::cout << "adress = |" << client->getAddress() << "|" << std::endl;
	_communicationManager->sendToOne("", "", client->getSocket(), _communicationManager->RPL_TOPIC_builder(client, "JOIN " + channel->getName()));
	if (creator)
		_communicationManager->sendToOne("", "", client->getSocket(), _communicationManager->RPL_CHANNELMODEIS_builder("localhost", channel->getName(), "+Cnst"));
	_communicationManager->sendToOne("", "", client->getSocket(), _communicationManager->RPL_NAMREPLY_builder("localhost", *channel, *client));
	_communicationManager->sendToOne("", "", client->getSocket(), _communicationManager->RPL_ENDOFNAMES_builder("localhost", *channel, *client));
}

void Command::joinChannel(Client * client, std::string tokens_name, std::string tokens_pass)
{
	std::vector<std::string> channel_name = split(tokens_name.c_str(), ",");
	std::vector<std::string> channel_pass = split(tokens_pass.c_str(), ",");

	for (size_t i = 0; i < channel_name.size(); i++)
	{
		if ((channel_name[i][0] != '&' && channel_name[i][0] != '#' && channel_name[i][0] != '+' && channel_name[i][0] != '!')
			|| !isValidStringData(channel_name[i]))
			throw Exception::ERR_NOSUCHCHANNEL(channel_name[i]);
		if (!(client->getChannels().size() < MAX_CHANNELS_PER_USER))
			throw Exception::ERR_TOOMANYCHANNELS(channel_name[i]);
		if (_communicationManager->verifExistChannel(channel_name[i]))
		{
			std::cout << "channel exist" << std::endl;
			Channel *channel = _communicationManager->returnChannel(channel_name[i]);
			if (!(channel->getListUser().size() < MAX_USERS_PER_CHANNEL) && !channel->verifIfRegisteredUser(client->getSocket()))
				throw Exception::ERR_CHANNELISFULL(channel_name[i]);
			if (i < channel_pass.size())
			{
				if (channel->getPassword().compare(channel_pass[i]) == 0)
					addClientChannel(client, channel, false);
				else
					throw Exception::ERR_BADCHANNELKEY(channel_name[i]);
			}
			else
			{
				if (channel->getPassword().compare("") == 0)
					addClientChannel(client, channel, false);
				else
					throw Exception::ERR_BADCHANNELKEY(channel_name[i]);
			}
		}
		else
		{
			std::cout << "channel not exist" << std::endl;
			if (i < channel_pass.size())
				_communicationManager->addChannel(channel_name[i], channel_pass[i], client->getSocket());
			else
				_communicationManager->addChannel(channel_name[i], "", client->getSocket());
			Channel *channel = _communicationManager->returnChannel(channel_name[i]);
			addClientChannel(client, channel, true);
		}
	}
}
