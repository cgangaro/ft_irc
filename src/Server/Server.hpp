#ifndef _SERVER_H
#define _SERVER_H

#include "Commons.hpp"
#include "ClientManager.hpp"
#include "CommunicationManager.hpp"
#include <signal.h>

//#define MOTD "Welcome to the server\nEnter your username, your nickname and your password with the commands:\n/USER your_username\n/NICK your_nickname\n/PASS your_password\n"
#define MOTD ""

class Server {

	private:
		SOCKET _socket;
		SOCKADDR_IN _sin;
		ClientManager _clientManager;
		CommunicationManager _communicationManager;


		static SOCKET createSocket();
		int bindSocket();
		void createServer(int port);
		void serverListen(void);
		void waitForActivity();
		bool isNewClientWaiting();
		void promptNewClient(int sock);
		void registerNewClient();

	public:
		Server();
		Server(int port);
		~Server();

		void listenning(void);
		char* getAddress(void) const;
		int getPort(void) const;
		void initServer(void);
		static void killServer(int sig);
		void refreshReadfds();
};

#endif