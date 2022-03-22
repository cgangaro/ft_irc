#ifndef TCP_COMMUNICATION_MANAGER_HPP
#define TCP_COMMUNICATION_MANAGER_HPP

#include "TCPCommons.hpp"
#include "TCPClientManager.hpp"
#include "Channel.hpp"

class TCPCommunicationManager {
	private:
		TCPClientManager* _clientManager;
		std::vector<Channel> _channels_server;

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
		std::vector<std::string> split(const char *buffer, std::string space_delimiter);
		void commandUser(std::vector<std::string> buf, std::vector<TCPClient>::iterator it);
		void commandNickname(std::vector<std::string> buf, std::vector<TCPClient>::iterator it);
		void commandPass(std::vector<std::string> buf, std::vector<TCPClient>::iterator it);
		void commandJoin(std::vector<std::string> buf, std::vector<TCPClient>::iterator it);

		void commandJoin_Verif(std::vector<std::string> buf, std::vector<TCPClient>::iterator it);
		bool verifPasswordChannel(std::string channel, std::string password);
		bool verifExistChannel(std::string channel);
};

#endif