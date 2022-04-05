#include "Command.hpp"
#include "CommunicationManager.hpp"

bool Command::commandQuit(Client * client, std::vector<std::string> tokens) {
	std::string msg_to_send("QUIT :");
	if (tokens.size() == 1)
		msg_to_send = msg_to_send + "Client Quit";
	else
	{
		for (size_t i = 1; i < tokens.size(); i++)
		{
			if (i == 1 && tokens[i][0] == ':')
				tokens[i].erase(0, 1);
			msg_to_send = msg_to_send + tokens[i];
		}
	}
	_communicationManager->sendToHisChannels(*client, _communicationManager->RPL_TOPIC_builder(client, msg_to_send));
	return true;
}