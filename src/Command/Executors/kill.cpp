#include "Command.hpp"
#include "CommunicationManager.hpp"

bool Command::commandKill(Client * client, std::vector<std::string> tokens) {
	(void)tokens;
	(void)client;
	std::cout << __func__ << std::endl;
	return false;
}