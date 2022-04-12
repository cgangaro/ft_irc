#include "Command.hpp"
#include "CommunicationManager.hpp"

bool Command::commandPass(Client * client, std::vector<std::string> tokens) {
	// Exceptions
	if (tokens.size() != 2) throw Exception::ERR_NEEDMOREPARAMS(tokens[0]);
	if (client->isRegistered()) throw Exception::ERR_ALREADYREGISTERED();
	if (tokens[1] != _password) throw Exception::ERR_PASSWDMISMATCH();
	
	client->authenticate();
	return false;
}
