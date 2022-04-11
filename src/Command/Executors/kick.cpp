#include "Command.hpp"
#include "CommunicationManager.hpp"

bool Command::commandKick(Client * client, std::vector<std::string> tokens) {
	std::string msg_to_send("KICK ");
	std::vector<std::string> cmd_and_msg = split(this->_latestCommand.c_str(), ":"); //marche que si on n'integre pas ':' dans isValidStringData() !
	std::vector<std::string> cmd = split(cmd_and_msg[0].c_str(), " ");
	if (cmd.size() != 3) throw Exception::ERR_NEEDMOREPARAMS(tokens[0]);
	if (_communicationManager->verifExistChannel(cmd[1])) throw Exception::ERR_NOSUCHCHANNEL(cmd[1]);
	if (_communicationManager->returnChannel(cmd[1])->verifIfRegisteredUser(client->getNickname())) throw Exception::ERR_NOTONCHANNEL(cmd[1]);
	if (_communicationManager->returnChannel(cmd[1])->verifIfRegisteredAdmin(client->getNickname())) throw Exception::ERR_CHANOPRIVSNEEDED(cmd[1]);
	if (_communicationManager->returnChannel(cmd[1])->verifIfRegisteredAdmin(cmd[2])) throw Exception::ERR_USERNOTINCHANNEL(cmd[2], cmd[1]);
	_communicationManager->returnChannel(cmd[1])->removeUser(cmd[2]);
	msg_to_send = msg_to_send + cmd[1] + " " + cmd[2] + ":";
	if (cmd_and_msg.size() > 1)
		msg_to_send = this->_latestCommand.erase(0, this->_latestCommand.find(':', 0) + 1);
	else
		msg_to_send = cmd[2];
	_communicationManager->sendToHisChannels(*client, _communicationManager->RPL_TOPIC_builder(client, msg_to_send));
	return false;
}