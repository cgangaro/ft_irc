#include "Command.hpp"
#include "CommunicationManager.hpp"

bool Command::commandModeUser(Client * client, std::vector<std::string> tokens) {
	(void)client;
	(void)tokens;
	std::cout << __func__ << std::endl;
	return false;
}

bool Command::commandModeChannel(Client * client, std::vector<std::string> tokens) {
	(void)client;
	(void)tokens;
	std::cout << __func__ << std::endl;
	return false;
}

bool Command::commandMode(Client * client, std::vector<std::string> tokens) {
	if (tokens.size() < 2) throw Exception::ERR_NEEDMOREPARAMS(tokens[0]);
	if (channelPrefix.find(tokens[1][0]) != std::string::npos)
		return commandModeChannel(client, tokens);
	return commandModeUser(client, tokens);
}