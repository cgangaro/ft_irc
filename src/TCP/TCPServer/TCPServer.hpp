#ifndef TCP_SERVER_H
#define TCP_SERVER_H

#include "TCPCommons.hpp"
#include "TCPClientManager.hpp"
#include "TCPCommunicationManager.hpp"
#include <signal.h>

#define MOTD "Welcome to the server\nEnter your username, your nickname and your password with the commands:\n/USER your_username\n/NICK your_nickname\n/PASS your_password\n"

class TCPServer {

	private:
		SOCKET _socket;
		SOCKADDR_IN _sin;
		TCPClientManager _clientManager;
		TCPCommunicationManager _communicationManager;


		static SOCKET createSocket();
		int bindSocket();
		void createServer(int port);
		void serverListen(void);
		void waitForActivity();
		bool isNewClientWaiting();
		void promptNewClient(int sock);
		void registerNewClient();

	public:
		TCPServer();
		TCPServer(int port);
		~TCPServer();

		void listenning(void);
		char* getAddress(void) const;
		int getPort(void) const;
		void initServer(void);
		static void killServer(int sig);
		void refreshReadfds();
};

#endif