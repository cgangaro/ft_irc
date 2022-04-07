#include "Command.hpp"
#include "CommunicationManager.hpp"

bool Command::commandModeUser(Client * client, std::vector<std::string> tokens) {
	std::vector<std::string> operations;

	if (tokens[1] != client->getNickname()) throw Exception::ERR_USERSDONTMATCH();
	
	operations = getOperations(tokens, UMODE_FLAGS);
	if (!operations.empty()) {
		for (std::vector<std::string>::iterator it = operations.begin(); it != operations.end(); ++it) {
			execOperation(client, *it);
		}
	}
	std::string msg = buildCmdResponse(*client, RPL_UMODEIS(client->getNickname(), client->getUsermode()));
	this->_communicationManager->sendMsg(client->getSocket(), msg);
	return false;
}

bool Command::commandModeChannel(Client * client, std::vector<std::string> tokens) {
	Channel * channel;
	std::vector<std::string> operations;
	std::vector<std::string> arg;

	channel = this->_communicationManager->getChannel(tokens[1]);
	if (!channel) return false;
	if (!channel->isOperator(client->getSocket()))
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
		return false;
		}
	}
	else if (tokens.size() == 2) {
		std::string msg = buildCmdResponse(*client, RPL_UMODEIS(client->getNickname(), client->getUsermode()));
		this->_communicationManager->sendMsg(client->getSocket(), msg);
	}
	else throw Exception::ERR_NEEDMOREPARAMS("MODE");
	return false;
}

bool Command::commandMode(Client * client, std::vector<std::string> tokens) {
	if (tokens.size() < 2) throw Exception::ERR_NEEDMOREPARAMS(tokens[0]);
	if (channelPrefix.find(tokens[1][0]) != std::string::npos)
		return commandModeChannel(client, tokens);
	return commandModeUser(client, tokens);
}