#ifndef TCP_CLIENT_MANAGER_H
#define TCP_CLIENT_MANAGER_H

#include <algorithm>
#include <vector>
#include "TCPCommons.hpp"
#include "TCPClient.hpp"

class TCPClientManager {
	private:
		std::vector<TCPClient> _clients;
		fd_set	_readfds;
		int	_maxSocket;

	public:
		TCPClientManager();
		~TCPClientManager();

		void addSocket(SOCKET sock);
		void addClient(SOCKET sock, SOCKADDR_IN sin);
		void removeClient(SOCKET client);
		void disconnectClient(SOCKET client);
		static void deleteClient(TCPClient & client);
		SOCKET initReadfdsClient(fd_set *readfds, SOCKET max_socket);
		int readClient();
		void sendToOthersClient(SOCKET sock_sender, std::string sender, std::string received);
		std::vector<TCPClient>* getClients(void);
		int getMaxSocket(void) const;
		int getNbClient(void) const;
		fd_set* getReadfds(void);
		void refreshMaxSocket();
};

#endif