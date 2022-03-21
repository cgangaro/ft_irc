#ifndef TCP_COMMUNICATION_MANAGER_HPP
#define TCP_COMMUNICATION_MANAGER_HPP

#include "TCPCommons.hpp"
#include "TCPClientManager.hpp"

#define WEL_COMMAND "Please, enter your username and your nickname with the commands:\n/user your_username\n/nickname your_nickname\n"
#define SERVER_NAME "IrcServer"

class TCPCommunicationManager {
	private:
		TCPClientManager* _clientManager;

	public:
		TCPCommunicationManager();
		TCPCommunicationManager(TCPClientManager* _clientManager);
		~TCPCommunicationManager();

		TCPClientManager* getClientManager(void) const;
		std::string messageBuilder(std::string sender, const char* msg) const;
		void sendToOne(std::string sender, SOCKET sock, const char* msg);
		void sendToAll(std::string sender, const char* msg);
		void sendToChannel(std::string sender, const char* msg, std::string channel);
		void processClientActivity(void);
		void command(const char *buffer, std::vector<TCPClient>::iterator it);
		std::vector<std::string> split(const char *buffer);
		void commandUser(std::vector<std::string> buf, std::vector<TCPClient>::iterator it);
		void commandNickname(std::vector<std::string> buf, std::vector<TCPClient>::iterator it);

};

#endif