#include "Command.hpp"
#include "CommunicationManager.hpp"

void Command::commandNick(Client & client, std::vector<std::string> tokens) {
	(void)client;
	(void)tokens;
	std::cout << __func__ << std::endl;
}

void Command::commandUser(Client & client, std::vector<std::string> tokens) {
	(void)client;
	(void)tokens;
	std::cout << __func__ << std::endl;
}

void Command::commandPass(Client & client, std::vector<std::string> tokens) {
	std::cout << __func__ << std::endl;
	if (tokens.size() != 2) {
		_communicationManager->sendMsg(client.getSocket(), "461 * PASS :Not enough parameters");
		return;
	}
	if (client.isAuthenticated()) {
		_communicationManager->sendMsg(client.getSocket(), "");
		return;
	}
	if (tokens[1] != _password)
		throw Exception::ERR_PASSWDMISMATCH();
	client.authenticate();
}

void Command::commandJoin(Client & client, std::vector<std::string> tokens) {
	(void)client;
	(void)tokens;
	std::cout << __func__ << std::endl;
}

void Command::commandMsg(Client & client, std::vector<std::string> tokens) {
	(void)client;
	(void)tokens;
	std::cout << __func__ << std::endl;
}

void Command::commandQuit(Client & client, std::vector<std::string> tokens) {
	(void)client;
	(void)tokens;
	std::cout << __func__ << std::endl;
}
