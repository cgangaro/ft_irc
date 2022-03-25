#include "Command.hpp"
#include "CommunicationManager.hpp"

bool Command::commandNick(Client * client, std::vector<std::string> tokens) {
	// Exceptions
	if (tokens.size() != 2) throw Exception::ERR_NONICKNAMEGIVEN();
	if (!isValidStringData(tokens[1])) throw Exception::ERR_ERRONEOUSNICKNAME(tokens[1]);
	if (_communicationManager->getClientManager()->isNicknameTaken(tokens[1])) throw Exception::ERR_NICKNAMEINUSE(tokens[1]);

	client->setNickname(tokens[1]);
	return false;
}

bool Command::commandUser(Client * client, std::vector<std::string> tokens) {
	// Exceptions
	if (tokens.size() < 5) throw Exception::ERR_NEEDMOREPARAMS(tokens[0]);
	if (client->isAuthenticated()) throw Exception::ERR_ALREADYREGISTERED();

	client->setUsername(tokens[1]);
	client->authenticate();
	_communicationManager->sendMsg(client->getSocket(),
		RPL_WELCOME(client->getNickname(), client->getUsername(), SERVER_NAME));
	return false;
}

// TODO: disconnect on error
bool Command::commandPass(Client * client, std::vector<std::string> tokens) {
	// Exceptions
	if (tokens.size() != 2) throw Exception::ERR_NEEDMOREPARAMS(tokens[0]);
	if (client->isAuthenticated()) throw Exception::ERR_ALREADYREGISTERED();
	if (tokens[1] != _password) throw Exception::ERR_PASSWDMISMATCH();
	return false;
}

bool Command::commandJoin(Client * client, std::vector<std::string> tokens) {
	(void)client;
	(void)tokens;
	std::cout << __func__ << std::endl;
	return false;
}

bool Command::commandMsg(Client * client, std::vector<std::string> tokens) {
	(void)client;
	(void)tokens;
	std::cout << __func__ << std::endl;
	return false;
}

bool Command::commandQuit(Client * client, std::vector<std::string> tokens) {
	(void)client;
	(void)tokens;
	std::cout << __func__ << std::endl;
	return false;
}
