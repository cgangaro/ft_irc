#include "Command.hpp"
#include "CommunicationManager.hpp"

bool Command::commandPing(Client * client, std::vector<std::string> tokens) {
	if (tokens.size() != 2) throw Exception::ERR_NEEDMOREPARAMS(tokens[0]);
	// :serv PONG serv :serv
	std::string response;

	response = "PONG ft_irc_server :ft_irc_server";
	this->_communicationManager->sendMsg(client->getSocket(), buildCmdResponse(*client, response));
	return false;
}