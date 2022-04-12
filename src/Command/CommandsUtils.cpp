#include "Command.hpp"
#include "CommunicationManager.hpp"
#include "Commons.hpp"

bool Command::isKnownCommand(std::string cmd) {
	std::vector<std::string> commandNames = split(COMMANDS, " ");
	for (int i = 0; i < NB_COMMANDS; i++) {
		if (cmd.compare(commandNames[i]) == 0)
			return true;
	}
	return false;
}

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

std::string Command::buildCmdResponse(Client & client, std::string cmd, int mode) {
	std::string msg_to_send;
	std::string sender;

	switch (mode) {
		case OPT_CLIENT:
			sender = client.getNickname() + "!~" + client.getUsername() + "@" + client.getAddress();
			break;
		case OPT_SERVER:
			sender = SERVER_NAME;
			break;
		default:
			return "";
	}
	msg_to_send = ":" + sender + " " + cmd + CRLF;
	return msg_to_send;
}

std::string Command::buildMultipleCmdResponse(Client & client, std::vector<std::string> raw_cmds, int mode) {
	std::string msg_to_send;

	for (std::vector<std::string>::iterator it = raw_cmds.begin(); it != raw_cmds.end(); ++it) {
		if (!it->empty())
			msg_to_send += buildCmdResponse(client, *it, mode);
	}
	return msg_to_send;
}

void Command::addClientChannel(Client * client, Channel * channel, bool creator)
{
	if (!(client->isInChannel(channel->getName())))
		client->addChannel(channel->getName());
	if (!(channel->verifIfRegisteredUser(client->getNickname())))
		channel->addUser(client->getNickname());
	_communicationManager->sendToOne("", "", client->getSocket(), _communicationManager->RPL_TOPIC_builder(client, "JOIN " + channel->getName()));
	channel->addMode(F_NOEXTERNMSGS | F_SECRET | F_TOPICOP);
	if (creator)
		_communicationManager->sendToOne("", "", client->getSocket(), _communicationManager->RPL_CHANNELMODEIS_builder(SERVER_NAME, channel->getName(), channel->getChannelmode()));
	_communicationManager->sendToOne("", "", client->getSocket(), _communicationManager->RPL_NAMREPLY_builder(SERVER_NAME, *channel, *client));
	_communicationManager->sendToOne("", "", client->getSocket(), _communicationManager->RPL_ENDOFNAMES_builder(SERVER_NAME, *channel, *client));
	_communicationManager->sendToChannel(*client, *channel, "JOIN " + channel->getName() + CRLF, 1);
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
			Channel *channel = _communicationManager->returnChannel(channel_name[i]);
			if (!(channel->getUserList().size() < (size_t)channel->getMaxUsers()) && !channel->verifIfRegisteredUser(client->getNickname()))
				throw Exception::ERR_CHANNELISFULL(channel_name[i]);
			if (channel->isBan(client->getAddress()))
				throw Exception::ERR_BANNEDFROMCHAN(channel_name[i]);
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
			if (i < channel_pass.size())
				_communicationManager->addChannel(channel_name[i], channel_pass[i], client->getNickname());
			else
				_communicationManager->addChannel(channel_name[i], "", client->getNickname());
			Channel *channel = _communicationManager->returnChannel(channel_name[i]);
			addClientChannel(client, channel, true);
		}
	}
}

std::string Command::toUpper(std::string arg) {
	for (size_t i = 0; i < arg.size(); i++)
	{
		if (arg[i] >= 97 && arg[i] <= 122)
			arg[i] = arg[i] - 32;
	}
	return (arg);
}
