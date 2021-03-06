#ifndef _CLIENT_MANAGER_H
#define _CLIENT_MANAGER_H

#include <algorithm>
#include <vector>
#include "Commons.hpp"
#include "Client.hpp"

class ClientManager {
	private:
		std::vector<Client> _clients;
		fd_set	_readfds;
		int	_maxSocket;

	public:
		ClientManager();
		~ClientManager();

		void addSocket(SOCKET sock);
		void addClient(SOCKET sock, SOCKADDR_IN sin);
		std::vector<Client>::iterator removeClient(std::vector<Client>::iterator it);
		//std::vector<Client>::iterator disconnectClient(std::vector<Client>::iterator it);
		static void deleteClient(Client & client);
		SOCKET initReadfdsClient(fd_set *readfds, SOCKET max_socket);
		int readClient();
		void sendToOthersClient(SOCKET sock_sender, std::string sender, std::string received);
		std::vector<Client>* getClients(void);
		int getMaxSocket(void) const;
		int getNbClient(void) const;
		fd_set* getReadfds(void);
		void refreshMaxSocket();
		bool isNicknameTaken(std::string nickname) const;
		bool checkListUsers(std::string user) const;
		SOCKET retSocketClient(std::string client_name) const;
};

#endif
