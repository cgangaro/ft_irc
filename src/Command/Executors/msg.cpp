#include "Command.hpp"
#include "CommunicationManager.hpp"

bool Command::commandMsg(Client * client, std::vector<std::string> tokens) {
	commandPrivmsg(client, tokens);
	return false;
}