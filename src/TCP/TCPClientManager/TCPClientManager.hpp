#ifndef TCP_CLIENT_MANAGER_H
#define TCP_CLIENT_MANAGER_H

#include <algorithm>
#include <vector>
#include "TCPCommons.hpp"

class TCPClientManager {
	private:
		std::vector<t_client> _clients;

		static void deleteClient(t_client & client);

	public:
		TCPClientManager();
		~TCPClientManager();

		void addClient(t_client & client, int nb_client);
		void removeClient(SOCKET client);
		SOCKET initReadfdsClient(fd_set *readfds, SOCKET max_socket);
		int readClient(fd_set *readfds);
		void sendToOthersClient(SOCKET sock_sender, std::string sender, std::string received);
		// void TCPClientManager::user(t_client *client);
		std::vector<t_client> getClients(void) const;

		class SendFailed : public std::exception
		{
			public:
				virtual const char* what() const throw();
		};
};

#endif