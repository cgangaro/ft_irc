#ifndef TCP_SERVER_H
#define TCP_SERVER_H

#include "TCPCommons.hpp"
#include "TCPClientManager.hpp"

class TCPServer {

	private:
		SOCKET _socket;
		SOCKADDR_IN _sin;
		TCPClientManager _clientManager;
		fd_set	_readfds; //contient une liste de fd à surveiller, pour n'importe qu'elle activité
		SOCKET _max_socket; //pour slect(), premier argument. Correspond à la plus grande socket à surveiller
		int	_nb_client;


		static SOCKET createSocket();
		int bindSocket();
		void createServer(int port);
		void serverListen(void);
		void initReadfds(void);

	public:
		TCPServer();
		TCPServer(int port);
		~TCPServer();

		void listenning(void);
		int getPort(void) const;
		void initServer(void);
};

#endif