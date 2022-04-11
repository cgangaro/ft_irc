#include "Command.hpp"
#include "CommunicationManager.hpp"

bool Command::commandTopic(Client * client, std::vector<std::string> tokens) {
	bool broadcast = false;
	std::string msg;
	int opt;

	if (tokens.size() < 2) throw Exception::ERR_NEEDMOREPARAMS(tokens[0]);
	Channel * channel = _communicationManager->getChannel(tokens[1]);
	if (!channel || !client->isInChannel(channel->getName())) throw Exception::ERR_NOTONCHANNEL(tokens[1]);
	if (tokens.size() == 3) {
		if ((channel->getModeSettings() & F_TOPICOP) && (!channel->verifIfRegisteredAdmin(client->getNickname())))
			throw Exception::ERR_CHANOPRIVSNEEDED(tokens[1]);
		if (tokens[2] == ":") channel->setTopic("");
		else channel->setTopic(tokens[2]);
		broadcast = true;
	}
	if (channel->getTopic() == "") msg = RPL_NOTOPIC(client->getNickname(), channel->getName());
	else msg = RPL_TOPIC(client->getNickname(), channel->getName(), channel->getTopic());

	if (tokens.size() == 2) opt = OPT_SERVER;
	else opt = OPT_CLIENT;
	msg = buildCmdResponse(*client, msg, opt);
	_communicationManager->sendMsg(client->getSocket(), msg);
	if (broadcast) _communicationManager->sendMsgToChannel(*client, *channel, msg);
	return false;
}