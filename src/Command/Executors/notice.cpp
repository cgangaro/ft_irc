#include "Command.hpp"
#include "CommunicationManager.hpp"

bool Command::commandNotice(Client * client, std::vector<std::string> tokens) {
	std::string msg_to_send;
	std::vector<std::string> cmd_and_msg = split(this->_latestCommand.c_str(), ":"); //marche que si on n'integre pas ':' dans isValidStringData() !
	std::vector<std::string> cmd = split(cmd_and_msg[0].c_str(), " ");

	if (tokens.size() < 3) return false;
	if (cmd_and_msg.size() > 1)
	{
		if (cmd.size() > 2) return false;
		msg_to_send = this->_latestCommand.erase(0, this->_latestCommand.find(':', 0) + 1);
	}
	else
		msg_to_send = tokens[2];
	msg_to_send = "NOTICE " + cmd[1] + " :" + msg_to_send + CRLF;
	if (_communicationManager->getClientManager()->checkListUsers(cmd[1]))
		_communicationManager->sendToOne(client->getUsername(), "", _communicationManager->getClientManager()->retSocketClient(cmd[1]), msg_to_send);
	else if (_communicationManager->verifExistChannel(cmd[1]))
	{
		if (_communicationManager->returnChannel(cmd[1])->verifIfRegisteredUser(client->getNickname()) || !(_communicationManager->returnChannel(cmd[1])->getModeSettings() & F_NOEXTERNMSGS))
			_communicationManager->sendToChannel(*client, *_communicationManager->returnChannel(cmd[1]), msg_to_send, 0);
	}
	return false;
}