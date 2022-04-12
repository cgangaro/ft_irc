#include "Command.hpp"
#include "CommunicationManager.hpp"

void Command::sendWelcomeMessage(Client * client) {
	std::string welcomeMsg = REGISTRATION_SUCCESS(client->getNickname());
	std::vector<std::string> reply = split(welcomeMsg.c_str(), CRLF);

	client->addMode(F_INVISIBLE | F_WALLOPS);
	_communicationManager->sendMsg(client->getSocket(),
		buildMultipleCmdResponse(*client, reply));
	_communicationManager->sendMsg(client->getSocket(), buildCmdResponse(*client, "MODE " + client->getNickname() + " " + client->getUsermode(), OPT_CLIENT));
}
