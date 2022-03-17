#ifndef TCP_COMMUNICATION_MANAGER_HPP
#define TCP_COMMUNICATION_MANAGER_HPP

#include "TCPCommons.hpp"
#include "TCPClientManager.hpp"

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
};

#endif