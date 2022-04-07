#include "Command.hpp"
#include "CommunicationManager.hpp"

bool Command::commandUser(Client * client, std::vector<std::string> tokens) {
	// Exceptions
	if (tokens.size() < 5) throw Exception::ERR_NEEDMOREPARAMS(tokens[0]);
	if (client->isRegistered()) throw Exception::ERR_ALREADYREGISTERED();
	if (!client->isAuthenticated()) throw Exception::ERR_PASSWDMISMATCH();

	std::string welcomeMsg = REGISTRATION_SUCCESS(client->getNickname());
	std::vector<std::string> reply = split(welcomeMsg.c_str(), CRLF);
	client->setUsername(tokens[1]);
	client->registerMe();
	client->addMode(F_INVISIBLE | F_WALLOPS);
	_communicationManager->sendMsg(client->getSocket(),
		buildMultipleCmdResponse(*client, reply));
	_communicationManager->sendMsg(client->getSocket(), buildCmdResponse(*client, "MODE " + client->getNickname() + " " + client->getUsermode(), OPT_CLIENT));
	return false;
}
