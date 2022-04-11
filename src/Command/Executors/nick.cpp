#include "Command.hpp"
#include "CommunicationManager.hpp"

bool Command::commandNick(Client * client, std::vector<std::string> tokens) {
	// Exceptions
	if (tokens.size() != 2) throw Exception::ERR_NONICKNAMEGIVEN();
	if (!isValidStringData(tokens[1])) throw Exception::ERR_ERRONEOUSNICKNAME(tokens[1]);
	if (_communicationManager->getClientManager()->isNicknameTaken(tokens[1])) throw Exception::ERR_NICKNAMEINUSE(tokens[1]);
	if (!client->isAuthenticated()) throw Exception::ERR_PASSWDMISMATCH();

	bool firstConnection = !client->isRegistered();

	client->setNickname(tokens[1]);
	client->registerMe();
	firstConnection = firstConnection && client->isRegistered();
	if (firstConnection) sendWelcomeMessage(client);
	return false;
}