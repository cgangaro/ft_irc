#ifndef _COMMUNICATION_MANAGER_HPP
#define _COMMUNICATION_MANAGER_HPP

#include "Commons.hpp"
#include "ClientManager.hpp"
#include "Channel.hpp"
#include "Command.hpp"

class CommunicationManager {
	private:
		ClientManager* _clientManager;
		std::vector<Channel> _channels_server;
		Command _interpreter;

	public:
		CommunicationManager();
		CommunicationManager(ClientManager* _clientManager);
		~CommunicationManager();

		CommunicationManager& operator=(const CommunicationManager& cm);
		void setInterpreter(Command interpreter);
		ClientManager* getClientManager(void) const;
		std::string messageBuilder(std::string sender, Channel & channel, const char* msg) const;
		Channel & getDefaultChannel(void);
		void sendMsg(SOCKET sock, std::string msg);
		void sendToOne(std::string sender, std::string channel, SOCKET sock, std::string rawMsg);
		void sendToChannel(Client client, Channel channel, std::string msg);
		void processClientActivity(void);

		bool verifExistChannel(std::string channel);
		bool verifChannelPassword(std::string channel, std::string password);
		void addChannel(std::string channel, std::string password, SOCKET admin);
		//void addUserToChannel(std::string channel, Client * client);
		Channel * returnChannel(std::string channel);

		void test_printChannels(void);

};

#endif
