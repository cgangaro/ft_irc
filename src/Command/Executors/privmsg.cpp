#include "Command.hpp"
#include "CommunicationManager.hpp"

bool Command::commandPrivmsg(Client * client, std::vector<std::string> tokens) {
	std::vector<std::string> cmd_and_msg = split(this->_latestCommand.c_str(), ":"); //marche que si on n'integre pas ':' dans isValidStringData() !
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
		_communicationManager->sendToOne(client->getUsername(), "", _communicationManager->getClientManager()->retSocketClient(cmd[1]), this->_latestCommand.erase(0, this->_latestCommand.find(':', 0) + 1));
	else if (_communicationManager->verifExistChannel(cmd[1]))
		_communicationManager->sendToChannel(*client, *_communicationManager->returnChannel(cmd[1]), this->_latestCommand.erase(0, this->_latestCommand.find(':', 0) + 1));
	else
		throw Exception::ERR_NOSUCHNICK(cmd[1]);
	return false;
}