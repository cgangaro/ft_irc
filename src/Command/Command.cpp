#include "Command.hpp"
#include "CommunicationManager.hpp"

commandExecutor Command::_executors[NB_COMMANDS] = {
	&Command::commandNick,
	&Command::commandUser,
	&Command::commandPass,
	&Command::commandJoin,
	&Command::commandPrivmsg,
	&Command::commandMsg,
	&Command::commandQuit,
	&Command::commandPing
};

Command::Command() {}

Command::Command(CommunicationManager *_communicationManager, std::string pwd) : _communicationManager(_communicationManager), _password(pwd) {
	t_command command;
	std::vector<std::string> commandNames = split(COMMANDS, " ");

	for (int i = 0; i < NB_COMMANDS; i++) {
		command.name = commandNames[i];
		command.executor = this->_executors[i];
		_commands.push_back(command);
	}
/* 	std::cout << "=== Command constructor ===" << std::endl;
	std::cout << "\tthis: " << this << std::endl;
	std::cout << "\t_communicationManager: " << _communicationManager << std::endl;
	std::cout << "=== Command END ===" << std::endl; */
}

Command::~Command() {
	
}

Command& Command::operator=(const Command& cm) {
	this->_communicationManager = cm._communicationManager;
	this->_password = cm._password;
	this->_commands = cm._commands;
	return *this;
}
/*
** Splitting the received data into maybe multiple commands
*/
bool Command::interpret(char* buffer, Client * client) {
	bool shouldDisconnect = false;
	std::vector<std::string> cmds;

	std::cout << "Received: " << buffer << std::endl;

	cmds = split(buffer, CRLF);
	for (std::vector<std::string>::iterator it = cmds.begin(); it != cmds.end(); ++it) {
		if (!it->empty() && (shouldDisconnect = processCommand(&(*it), client)))
			break;
	}
	return shouldDisconnect;
}

/*
** Processing a single command
*/
bool Command::processCommand(std::string *cmd, Client * client) {
	std::vector<std::string> tokens;
	bool shouldDisconnect = false;

	std::cout << "Processing: " << *cmd << std::endl << std::endl;

	try {
		tokens = split(cmd->c_str(), " ");
        if (tokens[0] != "PASS" && !client->isAuthenticated()) return false;
		std::cout << "test" << std::endl;
		for (std::vector<t_command>::iterator it = _commands.begin(); it != _commands.end(); ++it) {
			if (it->name == tokens[0]) {
				shouldDisconnect = (this->*(it->executor))(client, tokens, *cmd);
				break;
			}
		}
	} catch (std::exception & e) {
		this->_communicationManager->sendMsg(client->getSocket(), buildCmdResponse(*client, e.what()));
	}
	return shouldDisconnect;
}
