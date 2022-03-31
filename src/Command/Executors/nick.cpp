#include "Command.hpp"
#include "CommunicationManager.hpp"

bool Command::commandNick(Client * client, std::vector<std::string> tokens) {
	// Exceptions
	//if (tokens.size() != 2) throw Exception::ERR_NONICKNAMEGIVEN();
	if (!isValidStringData(tokens[1])) throw Exception::ERR_ERRONEOUSNICKNAME(tokens[1]);
	if (_communicationManager->getClientManager()->isNicknameTaken(tokens[1])) throw Exception::ERR_NICKNAMEINUSE(tokens[1]);
	if (!client->isAuthenticated()) throw Exception::ERR_PASSWDMISMATCH();

	client->setNickname(tokens[1]);
	return false;
}