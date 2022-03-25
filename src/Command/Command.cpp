#include "Command.hpp"
#include "CommunicationManager.hpp"

commandExecutor Command::_executors[NB_COMMANDS] = {
	&Command::commandNick,
	&Command::commandUser,
	&Command::commandPass,
	&Command::commandJoin,
	&Command::commandMsg,
	&Command::commandQuit
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
}

Command::~Command() {
	
}

void Command::interpret(char* buffer, Client & client) {
	std::vector<std::string> tokens;
	(void)client;

	std::cout << "Received: " << buffer << std::endl;

	try {
		tokens = split(buffer, " ");
		for (std::vector<t_command>::iterator it = _commands.begin(); it != _commands.end(); ++it) {
			if (it->name == tokens[0]) {
				(this->*(it->executor))(client, tokens);
				break;
			}
		}
	} catch (std::exception & e) {
		this->_communicationManager->sendMsg(client.getSocket(), e.what());
	}
}
