#include "Command.hpp"
#include "CommunicationManager.hpp"

bool Command::commandJoin(Client * client, std::vector<std::string> tokens) {
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