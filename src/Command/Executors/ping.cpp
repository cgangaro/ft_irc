#include "Command.hpp"
#include "CommunicationManager.hpp"

bool Command::commandPing(Client * client, std::vector<std::string> tokens) {
	(void)client;
	(void)tokens;
	std::cout << __func__ << std::endl;
	return false;
}