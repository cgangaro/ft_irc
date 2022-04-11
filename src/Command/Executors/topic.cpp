#include "Command.hpp"
#include "CommunicationManager.hpp"

bool Command::commandTopic(Client * client, std::vector<std::string> tokens) {
	if (tokens.size() < 2) throw Exception::ERR_NEEDMOREPARAMS(tokens[0]);
	Channel * channel = _communicationManager->getChannel(tokens[1]);
	if (!channel || !client->isInChannel(channel->getName())) throw Exception::ERR_NOTONCHANNEL(tokens[1]);
	if ((channel->getModeSettings() & F_TOPICOP) && (!channel->verifIfRegisteredAdmin(client->getNickname())))
		throw Exception::ERR_CHANOPRIVSNEEDED(tokens[1]);
	if (tokens.size() == 3) {
		if (tokens[2] == ":") channel->setTopic("");
		else channel->setTopic(tokens[2]);
	}
	std::string msg = (channel->getTopic() == "") ?
		buildCmdResponse(*client, RPL_NOTOPIC(channel->getName())) :
		buildCmdResponse(*client, RPL_TOPIC(channel->getName(), channel->getTopic()));
	_communicationManager->sendMsg(client->getSocket(), msg);
	std::cout << "msg : " << msg << std::endl;
	return false;
}