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
		void sendToOne(SOCKET sock, const char* msg);
		void sendToAll(const char* msg);
		void sendToChannel(const char* msg, std::string channel);
};

#endif