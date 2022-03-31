#include "Command.hpp"
#include "CommunicationManager.hpp"

bool Command::commandNick(Client * client, std::vector<std::string> tokens, std::string complete_cmd) {
	(void)complete_cmd;
	// Exceptions
	if (tokens.size() != 2) throw Exception::ERR_NONICKNAMEGIVEN();
	if (!isValidStringData(tokens[1])) throw Exception::ERR_ERRONEOUSNICKNAME(tokens[1]);
	if (_communicationManager->getClientManager()->isNicknameTaken(tokens[1])) throw Exception::ERR_NICKNAMEINUSE(tokens[1]);
	if (!client->isAuthenticated()) throw Exception::ERR_PASSWDMISMATCH();

	client->setNickname(tokens[1]);
	return false;
}

bool Command::commandUser(Client * client, std::vector<std::string> tokens, std::string complete_cmd) {
	(void)complete_cmd;
	// Exceptions
	if (tokens.size() < 5) throw Exception::ERR_NEEDMOREPARAMS(tokens[0]);
	if (client->isRegistered()) throw Exception::ERR_ALREADYREGISTERED();
	if (!client->isAuthenticated()) throw Exception::ERR_PASSWDMISMATCH();

	std::string welcomeMsg = REGISTRATION_SUCCESS(client->getNickname());
	std::vector<std::string> reply = split(welcomeMsg.c_str(), CRLF);
	client->setUsername(tokens[1]);
	client->registerMe();
	_communicationManager->sendMsg(client->getSocket(),
		buildMultipleCmdResponse(*client, reply));
	return false;
}

// TODO: disconnect on error
bool Command::commandPass(Client * client, std::vector<std::string> tokens, std::string complete_cmd) {
	(void)complete_cmd;
	// Exceptions
	if (tokens.size() != 2) throw Exception::ERR_NEEDMOREPARAMS(tokens[0]);
	if (client->isRegistered()) throw Exception::ERR_ALREADYREGISTERED();
	if (tokens[1] != _password) throw Exception::ERR_PASSWDMISMATCH();
	
	client->authenticate();
	return false;
}

bool Command::commandJoin(Client * client, std::vector<std::string> tokens, std::string complete_cmd) {
	(void)complete_cmd;
	if (!(tokens.size() >= 2 && tokens.size() <= 3)) throw Exception::ERR_NEEDMOREPARAMS(tokens[0]);
	try {
		if (tokens.size() == 2)
			joinChannel(client, tokens[1], "");
		else
			joinChannel(client, tokens[1], tokens[2]);
	}
	catch (std::exception & e) {
		this->_communicationManager->sendMsg(client->getSocket(), e.what());
	}
	_communicationManager->test_printChannels();
	client->test_printChannels();
	return false;
}

bool Command::commandPrivmsg(Client * client, std::vector<std::string> tokens, std::string complete_cmd) {
	(void)tokens;
	std::vector<std::string> cmd_and_msg = split(complete_cmd.c_str(), ":"); //marche que si on n'integre pas ':' dans isValidStringData() !
	std::vector<std::string> cmd = split(cmd_and_msg[0].c_str(), " ");
	if (cmd.size() != 2)
	{
		if (cmd.size() > 2)
			throw Exception::ERR_TOOMANYTARGETS(cmd_and_msg[0].erase(0, strlen("PRIVMSG ")));
		else
			throw Exception::ERR_NEEDMOREPARAMS(tokens[0]);
	}
	if (cmd_and_msg.size() < 2)
		throw Exception::ERR_NOTEXTTOSEND();
	if (_communicationManager->getClientManager()->checkListUsers(cmd[1]))
		_communicationManager->sendToOne(client->getUsername(), "", _communicationManager->getClientManager()->retSocketClient(cmd[1]), complete_cmd.erase(0, complete_cmd.find(':', 0) + 1));
	else if (_communicationManager->verifExistChannel(cmd[1]))
		_communicationManager->sendToChannel(*client, *_communicationManager->returnChannel(cmd[1]), complete_cmd.erase(0, complete_cmd.find(':', 0) + 1));
	else
		throw Exception::ERR_NOSUCHNICK(cmd[1]);
	return false;
}

bool Command::commandMsg(Client * client, std::vector<std::string> tokens, std::string complete_cmd) {
	commandPrivmsg(client, tokens, complete_cmd);
	return false;
}

bool Command::commandQuit(Client * client, std::vector<std::string> tokens, std::string complete_cmd) {
	(void)client;
	(void)tokens;
	(void)complete_cmd;
	std::cout << __func__ << std::endl;
	return false;
}
