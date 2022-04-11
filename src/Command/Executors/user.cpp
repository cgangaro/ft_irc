#include "Command.hpp"
#include "CommunicationManager.hpp"

bool Command::commandUser(Client * client, std::vector<std::string> tokens) {
	// Exceptions
	if (tokens.size() < 5) throw Exception::ERR_NEEDMOREPARAMS(tokens[0]);
	if (client->isRegistered()) throw Exception::ERR_ALREADYREGISTERED();
	if (!client->isAuthenticated()) throw Exception::ERR_PASSWDMISMATCH();

	bool firstConnection = !client->isRegistered();

	client->setUsername(tokens[1]);
	client->registerMe();
	firstConnection = firstConnection && client->isRegistered();
	if (firstConnection) sendWelcomeMessage(client);
	return false;
}
