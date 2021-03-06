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
	&Command::commandPing,
	&Command::commandTopic,
	&Command::commandOper,
	&Command::commandMode,
	&Command::commandNotice,
	&Command::commandKick
};

std::string Command::channelPrefix = "&#+!";

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

Command& Command::operator=(const Command& cm) {
	this->_communicationManager = cm._communicationManager;
	this->_password = cm._password;
	this->_commands = cm._commands;
	return *this;
}

std::string Command::recomposeCommand(char* inputBuffer, Client * client) {
	std::string clientBuffer(client->getBuffer());
	std::string outputBuffer;
	size_t pos;

	clientBuffer += inputBuffer;
	if ((pos = clientBuffer.rfind('\n')) == std::string::npos) {
		client->setBuffer(clientBuffer);
		return "";
	}
	outputBuffer = clientBuffer.substr(0, pos);
	clientBuffer.erase(0, pos + 2);
	client->setBuffer(clientBuffer);
	return outputBuffer;
}

/*
** Splitting the received data into maybe multiple commands
*/
bool Command::interpret(char* buffer, Client * client) {
	bool shouldDisconnect = false;
	std::vector<std::string> cmds;
	std::string input;

	input = recomposeCommand(buffer, client);
	cmds = split(input.c_str(), CRLF);
	for (std::vector<std::string>::iterator it = cmds.begin(); it != cmds.end(); ++it) {
		if (!it->empty() && (shouldDisconnect = processCommand(&(*it), client)))
			break;
	}
	return shouldDisconnect;
}

std::vector<std::string> Command::extractArgs(std::string cmd) {
	std::vector<std::string> args;
	std::string lastArg;
	size_t pos;

	pos = cmd.find(':');
	if (pos != std::string::npos) {
		lastArg = cmd.substr(pos + 1);
		cmd.erase(pos);
	}
	args = split(cmd.c_str(), " ");
	args[0] = toUpper(args[0]);
	if (pos != std::string::npos) args.push_back(lastArg);
	return args;
}

/*
** Processing a single command
*/
bool Command::processCommand(std::string *cmd, Client * client) {
	std::vector<std::string> tokens;
	bool shouldDisconnect = false;

	std::cout << "Processing: " << *cmd << std::endl << std::endl;
	try {
		tokens = extractArgs(*cmd);
		this->_latestCommand = *cmd;
		if (!isKnownCommand(tokens[0])) throw Exception::ERR_UNKNOWNCOMMAND(tokens[0]);
        if (tokens.empty() || (tokens.front() != "PASS" && !client->isAuthenticated())) return false;
		if (tokens.front() != "PASS" && tokens.front() != "NICK" && tokens.front() != "USER" && !client->isRegistered()) return false;
		for (std::vector<t_command>::iterator it = _commands.begin(); it != _commands.end(); ++it) {
			if (it->name == tokens[0]) {
				shouldDisconnect = (this->*(it->executor))(client, tokens);
				break;
			}
		}
	} catch (std::exception & e) {
		this->_communicationManager->sendMsg(client->getSocket(), buildCmdResponse(*client, e.what()));
	}
	return shouldDisconnect;
}
