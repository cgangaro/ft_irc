#include "Command.hpp"
#include "CommunicationManager.hpp"

bool Command::commandUser(Client * client, std::vector<std::string> tokens) {
	// Exceptions
	if (tokens.size() < 5) throw Exception::ERR_NEEDMOREPARAMS(tokens[0]);
	if (client->isRegistered()) throw Exception::ERR_ALREADYREGISTERED();
	if (!client->isAuthenticated()) throw Exception::ERR_PASSWDMISMATCH();

	client->setUsername(tokens[1]);
	client->registerMe();
	if (client->isRegistered()) sendWelcomeMessage(client);
	return false;
}
