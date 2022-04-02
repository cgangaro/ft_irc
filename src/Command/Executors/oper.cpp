#include "Command.hpp"
#include "CommunicationManager.hpp"

bool Command::commandOper(Client * client, std::vector<std::string> tokens) {
	if (tokens.size() < 3) throw Exception::ERR_NEEDMOREPARAMS(tokens[0]);
	if (tokens[2] != OPER_PASSWORD) throw Exception::ERR_PASSWDMISMATCH();

	std::string msg = buildCmdResponse(*client, RPL_YOUREOPER(client->getNickname()));
	client->setOperator(true);
	this->_communicationManager->sendMsg(client->getSocket(), msg);
	return false;
}