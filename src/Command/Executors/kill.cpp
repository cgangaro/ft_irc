#include "Command.hpp"
#include "CommunicationManager.hpp"

bool Command::commandKill(Client * client, std::vector<std::string> tokens) {
	if (tokens.size() < 3) throw Exception::ERR_NEEDMOREPARAMS(tokens[0]);
	if (!client->isOperator()) throw Exception::ERR_NOPRIVILEGES();
	if (!_communicationManager->getClientManager()->isNicknameTaken(tokens[1])) throw Exception::ERR_NOSUCHNICK(tokens[1]);

	/*
	** TODO : kill the requested client
	** Pseudo-code :
	** Client toKill = clientManager.getClientByNickname(tokens[1]); // this function needs to be added
	** cl
	*/
	return false;
}