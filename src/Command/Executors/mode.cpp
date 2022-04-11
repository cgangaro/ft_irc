#include "Command.hpp"
#include "CommunicationManager.hpp"

std::string buildModeChannelRep(Channel * channel, std::vector<std::string> tokens) {
	std::string ret;

	ret = "MODE " + channel->getName() + " :";
	for (std::vector<std::string>::iterator it = tokens.begin() + 2; it != tokens.end(); ++it)
		ret += *it;
	ret += CRLF;
	return ret;
}

std::string buildModeRep(Client * client, std::vector<std::string> tokens) {
	std::string ret;

	ret = "MODE " + client->getNickname() + " :";
	for (std::vector<std::string>::iterator it = tokens.begin() + 2; it != tokens.end(); ++it)
		ret += *it;
	return ret;
}

bool Command::commandModeUser(Client * client, std::vector<std::string> tokens) {
	std::vector<std::string> operations;
	std::string msg;

	if (tokens[1] != client->getNickname()) throw Exception::ERR_USERSDONTMATCH();
	
	operations = getOperations(tokens, UMODE_FLAGS);
	if (!operations.empty()) {
		for (std::vector<std::string>::iterator it = operations.begin(); it != operations.end(); ++it) {
			execOperation(client, *it);
		}
	}
	if (tokens.size() == 2)
 		msg = buildCmdResponse(*client, RPL_UMODEIS(client->getNickname(), client->getUsermode()));
	else
 		msg = buildCmdResponse(*client, buildModeRep(client, tokens), OPT_CLIENT);
	this->_communicationManager->sendMsg(client->getSocket(), msg);
	return false;
}

bool Command::commandModeChannel(Client * client, std::vector<std::string> tokens) {
	Channel * channel;
	std::vector<std::string> operations;
	std::vector<std::string> arg;
	
	channel = this->_communicationManager->getChannel(tokens[1]);
	if (!channel) return false;
	if (tokens.size() > 2 && !channel->isOperator(client->getNickname()))
	{
		throw Exception::ERR_CHANOPRIVSNEEDED(tokens[1]);
		return false;
	}
	operations = getOperations(tokens, CMODE_FLAGS);
	if (tokens.size() > 2)
	{
		arg = getArg(tokens);
		if (!operations.empty()) {
			for (std::vector<std::string>::iterator it = operations.begin(); it != operations.end(); ++it) {
				execChannelOperation(channel, *it, arg);
			}
		}
	}
	else if (tokens.size() == 2) {
 		std::string msg = ":" + (std::string)SERVER_NAME + " " + RPL_CHANNELMODEIS(client->getNickname(), channel->getName(), channel->getChannelmode());
		this->_communicationManager->sendMsg(client->getSocket(), msg);
		return false;
	}
	else throw Exception::ERR_NEEDMOREPARAMS("MODE");
	std::string msg = buildModeChannelRep(channel, tokens);
	this->_communicationManager->sendToChannel(*client, *channel, msg, false);
	this->_communicationManager->sendMsg(client->getSocket(), buildCmdResponse(*client, msg, OPT_CLIENT));
	return false;
}

bool Command::commandMode(Client * client, std::vector<std::string> tokens) {
	if (tokens.size() < 2) throw Exception::ERR_NEEDMOREPARAMS(tokens[0]);
	if (channelPrefix.find(tokens[1][0]) != std::string::npos)
		return commandModeChannel(client, tokens);
	return commandModeUser(client, tokens);
}
